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

module_param(pNum, int,  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

int init_module(void) {
    if (!(pidStruct = find_get_pid(pNum))) {
        printk(KERN_INFO "NULL PID found. Terminating.\n");
        return 0;
    }
    

    if (!(pTask = pid_task(pidStruct, PIDTYPE_PID))) {
        printk(KERN_INFO "NULL task struct found. Terminating.\n");
        return 0;
    }

    printk(KERN_INFO "Process Name: %s\n", pTask -> comm);
    printk(KERN_INFO "PID: %d\n", pTask -> pid);
    printk(KERN_INFO "UID: %d\n", pTask -> cred -> uid);
    printk(KERN_INFO "PGID: %d\n", pTask -> cred -> gid);
    printk(KERN_INFO "Command Path: %s\n", pTask -> comm);
    
    
    //Getting executable path - This was not working for some reason which is why I resorted to simply using pTask -> comm as the command path
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

void cleanup_module(void) {
    printk(KERN_INFO "Module has finished. Cleanup module has run.\n");
}
