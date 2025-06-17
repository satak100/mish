#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// new global variable to hold target character
static char target_char = '\0';

// system call: setTargetChar
uint64
sys_setTargetChar(void)
{
  int c;
  // fetch argument as int; treat lower byte as character
  if(argint(0, &c) < 0)
    return -1;
  target_char = (char)c;
  return 0;
}

// system call: countTargetFreq
uint64
sys_countTargetFreq(void)
{
  uint64 ustr; // user space address
  if(argaddr(0, &ustr) < 0)
    return -1;

  // copy user string into kernel buffer while counting
  char buf[256];
  int len = fetchstr(ustr, buf, sizeof(buf));
  if(len < 0)
    return -1;
  int count = 0;
  for(int i = 0; buf[i]; i++)
    if(buf[i] == target_char)
      count++;
  return count;
}
