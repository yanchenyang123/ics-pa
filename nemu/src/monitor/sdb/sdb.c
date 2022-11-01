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
#include <cpu/cpu.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "sdb.h"
#include <memory/paddr.h>
#include <stdbool.h>
typedef struct watchpoint {
  int NO;
  struct watchpoint *next;
  char *e;


  /* TODO: Add more members if necessary */

} WP;
static int is_batch_mode = false;
extern WP *head;
extern WP *free_;
extern WP wp_pool[32];
void init_regex();
void init_wp_pool();
void p_all_points();
WP* new_wp(char *e);
WP* free_wp(int i);
/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}


static int cmd_si(char *args);
static int cmd_q(char *args) {
  return -1;
}

static int cmd_help(char *args);
static int cmd_info(char *args);
static int cmd_x(char *args);
static int cmd_p(char *args);
static int cmd_w(char *args);
static int cmd_d(char *args);
static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display information about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },
  { "si","Let the program execute N instructions in a single step and then suspend execution,When N is not given, it defaults to 1",cmd_si },
  { "info","Print Program States",cmd_info},
  { "x","Scan memory",cmd_x},
  { "p","Solve the EXPR",cmd_p},
  { "w","Set a Viewpoint,When EXPR is changed,stop the program",cmd_w},
  { "d","Remove a Viewpoint",cmd_d}
  /* TODO: Add more commands */

};

#define NR_CMD ARRLEN(cmd_table)

static int cmd_si(char *args) {    //zhi xing zhiling
	char *token,*tokens[10];
  int i=0;
  int n=0;
	token=strtok(args," ");
  while(token!=NULL)
  {
    tokens[i]=token;
    token=strtok(NULL," ");
    i+=1;
  }
  i-=1;

  if(i==-1)
    {
      cpu_exec(1);
      return 0;
    }
  else if(i>=1)
    {
      printf("Unknown command si %s\n",args);
      return 0;
    }
  else 
    {
      for(int j=0;tokens[0][j]!='\0';j+=1)
        {
          if(tokens[0][j]<'0'||tokens[0][j]>'9')
            {
              printf("Unknown command si %s\n",args);
              return 0;
            }
          else{
            n=n*10+(tokens[0][j]-'0');
            
            
          }
        }
      cpu_exec(n);
      return 0;
    }        
          
}

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

static int cmd_info(char *args)
  { 
    char *token=strtok(args," ");
    if(strcmp(token,"r")==0)
     {
      isa_reg_display();
      
     }
    else if(strcmp(token,"w")==0)
      {
        p_all_points();
      }
    else
      {
        printf("Unknown command info %s\n",token);
      }
     return 0;
  }

static int cmd_x(char *args)
  {
    char *token,*tokens[10];
    token=strtok(args," ");
    int i=0;
    while(token!=NULL){
      tokens[i]=token;
      token=strtok(NULL," ");
      i+=1;
    }
    i-=1;
    if(i==1)
        {
          paddr_t index;
          sscanf(tokens[1],"%x",&index);
          int N;
          sscanf(tokens[0],"%d",&N);
          for(int i=0;i<N;i++)
              {
                printf("0x%x:     %x\n",index,paddr_read(index,4));
                index+=4;

              }


        }
    return 0;
  }

static int cmd_p(char *args)
  {
    _Bool *succese;
    succese=(_Bool *)true;
    expr(args,succese);
    return 0;
  }

static int cmd_w(char *args)
   {
    new_wp(args);
    return 0;
   }
static int cmd_d(char *args)
  {
    int wp_index;
    sscanf(args,"%d",&wp_index);
    free_wp(wp_index);
    return 0;
  }

void sdb_set_batch_mode() {
  is_batch_mode = true;
}


void sdb_mainloop() {
  sdb_set_batch_mode();
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}

void init_sdb() {
  /* Compile the regular expressions. */
  init_regex();

  /* Initialize the watchpoint pool. */
  init_wp_pool();
}
