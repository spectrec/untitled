#ifndef __USER_SYSCALL_H__
#define __USER_SYSCALL_H__

#include <stdint.h>

void sys_puts(const char *string);
void sys_exit(int ret);

#endif
