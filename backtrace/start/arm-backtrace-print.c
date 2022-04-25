#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <inttypes.h>

#include <rtems/score/cpu.h>
#include <rtems/bspIo.h>
#include <rtems/score/thread.h>
#include <rtems/score/stack.h>
#include <rtems/fatal.h>
#include <rtems/score/isr.h>
#include <rtems/score/percpu.h>
#include <bsp/my_fatal.h>

static void _CPU_backtrace_dump(void);
static void _CPU_backtrace_print_in_exception(const rtems_exception_frame *eframe);
/**
 *  * @brief Prints the backtrace of myself via printk().
 *   */
void rtems_backtrace_dump()
{
  _CPU_backtrace_dump();
}

void rtems_backtrace_print_in_exception(
  const rtems_exception_frame *eframe
)
{
  _CPU_backtrace_print_in_exception(eframe);
}




static bool in_task_stack(uint32_t *p)
{
    Thread_Control *executing = _Thread_Get_executing();
    Stack_Control *task_stack_ctl = &(executing->Start.Initial_stack);

    return (uint32_t) p > (uint32_t) task_stack_ctl->area
        && (uint32_t) p < (uint32_t) task_stack_ctl->area + (uint32_t) task_stack_ctl->size;
}

static bool in_isr_stack(uint32_t *p)
{
    return (uint32_t) p > (uint32_t) _ISR_Stack_area_begin
        && (uint32_t) p < (uint32_t) _ISR_Stack_area_begin + (uint32_t) _ISR_Stack_size;
}

static char *pc2str(uint32_t *pc)
{
    uint32_t *pos = pc;
    char *str;
    uint32_t offset;

    while ((*pos & 0xff000000) != 0xff000000) {
        pos -= 1;
    }

    offset = *pos & 0x00ffffff;
    str = (char *) ((uint32_t)pos - (uint32_t)offset);

    return str;
}

static void stack_frame_print(CPU_stack_frame *frame, int level)
{
    printk("#%d %p %s\n", level, frame->register_pc, pc2str(frame->register_pc));
}

void backtrace_print(CPU_stack_frame *frame)
{
    uint32_t *fp = frame->register_fp;
    CPU_stack_frame cur_frame = *frame;
    bool is_task_stack = in_task_stack((uint32_t *) frame->register_sp);
    bool is_isr_stack = in_isr_stack((uint32_t *) frame->register_sp);

    printk("*** Beginning of backtrace: ***\n");
    for (int i = 0; i < 20; i += 1) {
        stack_frame_print(&cur_frame, i);

        if ((is_task_stack && !in_task_stack(fp))
            || (is_isr_stack && !in_isr_stack(fp))) {
            break;
        }

        cur_frame.register_pc = (uint32_t *) *fp;
        cur_frame.register_sp = (uint32_t *) *(fp - 2);
        cur_frame.register_fp = (uint32_t *) *(fp - 3);
        fp = cur_frame.register_fp;
    }
    printk("*** End of backtrace. ***\n");
}

void _CPU_backtrace_print_in_exception(const CPU_Exception_frame *eframe)
{
    CPU_stack_frame sframe;

    sframe.register_sp = eframe->register_sp;
    if (!in_task_stack(sframe.register_sp)) {
        return;
    }

    sframe.register_fp = eframe->register_r11;
    sframe.register_pc = eframe->register_pc;

    backtrace_print(&sframe);
}

void _CPU_backtrace_dump()
{
    CPU_stack_frame sframe;

    __asm__ volatile (
        "mov %0, pc\n"
        "mov %1, sp\n"
        "mov %2, fp\n"
        :"=r" (sframe.register_pc), "=r" (sframe.register_sp), "=r" (sframe.register_fp)
        :
        :"memory"
    );

    backtrace_print(&sframe);
}
