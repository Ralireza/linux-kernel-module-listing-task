#include <linux/init.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h> 


void dfs(struct task_struct *task)
{
	struct task_struct *next_task; //kernel struct for task
	struct list_head *list;
	list_for_each(list, &task->children) {
		next_task = list_entry(list, struct task_struct, sibling);
		printk(KERN_INFO "[pid: %d] pname: %s [state: %ld]\n",next_task->pid, next_task->comm, next_task->state); // printk()  for print log in kernel mode
		dfs(next_task); //recursive calling dfs function
	}	
}
int dfs_tree_tasks_init(void)
{
	printk(KERN_INFO "Loading module\n");
	dfs(&init_task);
	return 0;
}	

void dfs_tree_tasks_exit(void)
{
	printk(KERN_INFO "Removing module\n");
}

module_init(dfs_tree_tasks_init); // start module and call dfs function from here
module_exit(dfs_tree_tasks_exit); // exit module


