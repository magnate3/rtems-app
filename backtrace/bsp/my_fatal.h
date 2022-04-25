#include "my_cpu.h"
/**
 *  * @brief Stack frame.
 *   * 
 *    */
typedef CPU_stack_frame rtems_stack_frame;
//void _CPU_backtrace_dump();
//void _CPU_backtrace_print_in_exception(const rtems_exception_frame *eframe);

//static void _CPU_backtrace_dump();
/**
 *  * @brief Prints the backtrace of myself via printk().
 *   */
void rtems_backtrace_dump(void);
//static inline void rtems_backtrace_dump()
//{
//  _CPU_backtrace_dump();
//}
//
///**
// *  * @brief Prints the backtrace who cause the exception via printk().
// *   */
void rtems_backtrace_print_in_exception(
  const rtems_exception_frame *eframe);
//static inline void rtems_backtrace_print_in_exception(
//  const rtems_exception_frame *eframe
//)
//{
//  _CPU_backtrace_print_in_exception(eframe);
//}
