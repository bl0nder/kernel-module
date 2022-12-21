#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/pid.h>
#include <linux/pid_namespace.h>
#include <linux/moduleparam.h>
#include <linux/sched.h>
#include <linux/cred.h>

MODULE_AUTHOR("Palaash Goel");
MODULE_LICENSE("GPL");

static int pNum;
static struct task_struct* pTask;
static struct pid* pidStruct;

module_param(pNum, int, 666);

int init_module(void) {
    if ((pidStruct = find_get_pid(pNum)) == NULL) {
        pr_info("NULL PID found. Terminating.\n");
        return -1;
    }
    

    if ((pTask = pid_task(pidStruct, PIDTYPE_PID)) == NULL) {
        pr_info("NULL task struct found. Terminating.\n");
        return -1;
    }

    pr_info("Process Name: %s\n", pTask -> comm);
    pr_info("PID: %d\n", pTask -> pid);
    pr_info("UID: %d\n", pTask -> cred -> uid);
    pr_info("PGID: %d\n", pTask -> cred -> gid);
    pr_info("Process Name: %s\n", pTask -> comm);
    //Getting executable path
    // char* path = malloc(1000);

    // struct mm_struct* mm = pTask -> mm;

    // if (mm != NULL) {
    //     down_read(&mm->mmap_base);
    //     if (mm->exe_file != NULL) 
    //     {
    //         strcpy(path, mm -> exe_file -> f_path -> d_name, 1000);           
    //     }
    //     up_read(&mm->mmap_base);
    // } 

    // printk(KERN_INFO "Command path: %s\n", path);
    return 0;
}

void cleanup_module() {
    printk(KERN_INFO "Cleaning module has run.\n");
}



