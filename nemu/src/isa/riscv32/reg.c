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

#include <isa.h>
#include "local-include/reg.h"

 
/*
x0 	zero 	hardwired to 0, ignores writes 	n/a
x1 	ra 	return address for jumps 	no
x2 	sp 	stack pointer 	yes
x3 	gp 	global pointer 	n/a
x4 	tp 	thread pointer 	n/a
x5 	t0 	temporary register 0 	no
x6 	t1 	temporary register 1 	no
x7 	t2 	temporary register 2 	no
x8 	s0 or fp 	saved register 0 or frame pointer 	yes
x9 	s1 	saved register 1 	yes
x10 	a0 	return value or function argument 0 	no
x11 	a1 	return value or function argument 1 	no
x12 	a2 	function argument 2 	no
x13 	a3 	function argument 3 	no
x14 	a4 	function argument 4 	no
x15 	a5 	function argument 5 	no
x16 	a6 	function argument 6 	no
x17 	a7 	function argument 7 	no
x18 	s2 	saved register 2 	yes
x19 	s3 	saved register 3 	yes
x20 	s4 	saved register 4 	yes
x21 	s5 	saved register 5 	yes
x22 	s6 	saved register 6 	yes
x23 	s7 	saved register 7 	yes
x24 	s8 	saved register 8 	yes
x25 	s9 	saved register 9 	yes
x26 	s10 	saved register 10 	yes
x27 	s11 	saved register 11 	yes
x28 	t3 	temporary register 3 	no
x29 	t4 	temporary register 4 	no
x30 	t5 	temporary register 5 	no
x31 	t6 	temporary register 6 	no
pc 	(none) 	program counter 	n/a
*/
const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

void isa_reg_display() {
   for(int i=0;i<32;i+=1)
    { 
      printf("%s      0x%x       %d\n",regs[i],gpr(i),gpr(i));
    }
}

word_t isa_reg_str2val(const char *s, bool *success) {
      for(int i=0;i<32;i+=1)
    {     
      if(strncmp(s,regs[i],3)==0)
        {
          success=(_Bool *)true;
          return gpr(i);

        }
    }
    success=(_Bool *)false;
    assert(0);
      }
