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


void int_to_str(char *str,int integer,int index)
  {
    int num1=0;
    int a=0;
    char *str1=NULL;
    while(true)
      {
        if(integer>=10)
          {
            a=integer%10;
            integer/=10;
            str1[num1]=a+'0';
            num1+=1; 
          }
        else
          {
            str1[num1]=integer+'0';
            num1+=1;
            break;
          }
      }
    for(int i=0;i<num1;i++)
      {
        str[index+i]=str1[num1-i-1];
        index+=1;
      }
  }
int sprintf(char *out, const char *fmt, ...) {
  va_list ap;
  int num=0;
  va_start(ap,fmt);
  int integer;
  char *str=NULL;
  for(size_t i=0;fmt[i]!='\0';i++)
    {
      if(fmt[i]!='%')
        {
          out[num]=fmt[i];
          num+=1;
        }
      else
        {
          if(fmt[i+1]=='d')
            {
              integer=va_arg(ap,int);
              if(integer<0)
                {
                  out[num]='-';
                  num+=1;
                  int_to_str(out,-integer,num);
                }
              else
                {
                  int_to_str(out,integer,num);
                }

            }
          else if(fmt[i+1]=='s')
            {
              str=va_arg(ap,char*);
              for(size_t i=0;i<strlen(str);i++)
                {
                  out[num]=str[i];
                  num+=1;
                }

            }
          i=i+1;
        }
    }
  return num;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
