#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  panic("Not implemented");
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  panic("Not implemented");
}

void int_to_str(char *out1,int integer,int num)
  {
    char str[10]={0};
    int i=0;
    if(integer==0)
      {
        *out1++='0';
        num+=1;
        *out1='\0';
        return ;
      }
    while(integer)
      {
        str[i]=(char)(integer%10+'0');
        integer/=10;
        i++;
      }
    for(int j=0;j<i;j++)
      {
        *out1++=str[i-1-j];
        num+=1;
      }
    *out1='\0';
    return ;

  }

int sprintf(char *out, const char *fmt, ...) {
  va_list ap;
  char *out1=out;
  int num=0;
  va_start(ap,fmt);
  int integer;
  char *str;
  while(*fmt!='\0')
    {
      if(*fmt!='%')
        {
          *out1++=*fmt++;
          num+=1;
        }
      else
        {
          if(*++fmt=='d')
            {
              integer=va_arg(ap,int);
              if(integer<0)
                {
                  *out1++='-';
                  num+=1;
                  int_to_str(out1,integer,num);
                }
              else
                {
                  int_to_str(out1,integer,num);
                }
            }
          else if(*++fmt=='s')
            {
              str=va_arg(ap,char *);
              while(*str)
                {
                  *out1++=*str++;
                  num+=1;
                }
              *out1='\0';
            }
        }
      
    }
  va_end(ap);
  return num;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
