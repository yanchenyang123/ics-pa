#include <am.h>
#include <nemu.h>
#include<stdio.h>
#include <riscv/riscv.h>
#define SYNC_ADDR (VGACTL_ADDR + 4)
//static int w_=0;
//static int h_=0;
#ifdef SCREEN_W
  w_=SCREEN_W
#endif

#ifdef SCREEN_H
  h_=SCREEN_H
#endif

void __am_gpu_init() {
  int i;
  int w=400;
  int h=300;
  uint32_t *fb=(uint32_t *)(uintptr_t)FB_ADDR;
  for(i=0;i<w*h;i++) fb[i]=i;
  outl(SYNC_ADDR,1);
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  *cfg = (AM_GPU_CONFIG_T) {
    .present = true, .has_accel = false,
    .width =400 , .height =300,
    .vmemsz = 0
  };
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {

  ctl->pixels=(uint32_t *)(uintptr_t)FB_ADDR;

  if (ctl->sync) {
    outl(SYNC_ADDR, 1);
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
