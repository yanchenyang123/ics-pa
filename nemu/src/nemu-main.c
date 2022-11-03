/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include<common.h>
#include "isa.h"
void init_monitor(int, char *[]);
void am_init_monitor();
void engine_start();
int is_exit_status_bad();
void iringbuf_init_();
int main(int argc, char *argv[]) {
  /* Initialize the monitor. */
#ifdef CONFIG_TARGET_AM
  am_init_monitor();
#else
  init_monitor(argc, argv);
#endif
#ifdef CONFIG_IRINGBUF
  iringbuf_init_();
#endif

  /* Start engine. */
  engine_start();
  /*char *A[10000];
  FILE *fa=fopen("NEMU/tools/input","r");
  assert(fa!=NULL);
  while(!feof(fa))
    {
      fscanf(fa,"%[^\n]",&A);
    }
  int index=0;
  for(int i=0;i<10000;i++)
    {
      int b;
      char c[100000];
      int n=sscanf(A[i],"%d' '%s",&b,c);
      if(index==expr(c,true))
        {
          index+=1;
        }
    }
  printf("%d",index);*/
  return 0;
}
