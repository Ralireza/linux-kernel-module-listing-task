#define _POSIX_SOURCE

#include <linux/init.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h> 





int listing_tasks_init(void)
{
	struct task_struct *task;//kernel struct for proccess

	for_each_process(task) {
		printk(KERN_INFO "[pid: %d] pname: %s [state: %ld]\n", task->pid, task->comm, task->state);// printk()  for print log in kernel mode
	}
	return 0;
}

void listing_tasks_exit(void)
{
	printk(KERN_INFO "Removing module\n");
}

module_init(listing_tasks_init);// start module 
module_exit(listing_tasks_exit);// exit module

