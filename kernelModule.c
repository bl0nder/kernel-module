#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/pid.h>
#include <linux/moduleparam.h>
#include <linux/sched.h>
#include <linux/cred.h>

MODULE_AUTHOR("Palaash Goel");

static int pNum;
static task_struct* pTask;
static pid* pidStruct;

module_param(pNum, int, 666);

int init_module(void) {
    if ((pidStruct = find_get_pid(pNum)) == NULL) {
        printk(KERN_ALERT "NULL PID found. Terminating.\n");
        return -1;
    }
    

    if ((pTask = pid_task(pidStruct, PIDTYPE_PID)) == NULL) {
        printk(KERN_ALERT "NULL task struct found. Terminating.\n");
        return -1;
    }

    printk(KERN_INFO "Process Name: %s\n", pTask -> comm);
    printk(KERN_INFO "PID: %d\n", pTask -> pid);
    printk(KERN_INFO "UID: %d\n", pTask -> cred -> uid);
    printk(KERN_INFO "PGID: %d\n", pTask -> cred -> gid);
    printk(KERN_INFO "Process Name: %s\n", pTask -> comm);
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



