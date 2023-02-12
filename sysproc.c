#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include <stdio.h>
#include "usr_trace_state.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int sys_add(void){
  int a, b;
  // cprintf("SYSTEM CALL FOR ADDING 2 numbers %d " , 3);
  argint(0, &a);
  argint(1, &b);
  return a + b;
}

int sys_ps(void){
   return call_ps();
  // return 1;
}


int
sys_print_count(void)
{
  for(uint i = 0; i < syscall_count_arr_size; i++){
    if(syscall_count_arr[i] > 0)
      cprintf("%s %d\n", syscall_name_arr[i], syscall_count_arr[i]);
  }
  return 0;
}

// MOD-1 : Toggle the tracer on or off
int
sys_toggle(void)
{

    if(trace_state == TRACE_OFF){
    for(uint i = 0; i < syscall_count_arr_size; i++){
      syscall_count_arr[i] = 0; 
    }
  }

  if(trace_state == TRACE_ON)
    trace_state = TRACE_OFF;
  else
    trace_state = TRACE_ON;

  return 0;
}