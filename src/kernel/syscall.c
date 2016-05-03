#include "kernel/task.h"
#include "kernel/syscall.h"

#include "stdlib/assert.h"
#include "stdlib/syscall.h"

#include "kernel/lib/console/terminal.h"

void syscall(struct task *task)
{
	enum syscall syscall = task->context.gprs.rax;
	int64_t ret = 0;

	switch (syscall) {
	case SYSCALL_PUTS:
		terminal_printf("%s", (char *)task->context.gprs.rbx);
		break;
	case SYSCALL_EXIT:
		terminal_printf("task [%d] exited with value `%d'\n",
				task->id, task->context.gprs.rbx);
		task_destroy(task);

		return schedule();
	default:
		panic("unknown syscall `%u'\n", syscall);
	}

	task->context.gprs.rax = ret;
	task_run(task);
}
