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

int number_of_int(int integer)
  {
    int num=0;
    int a=10;
    while(true)
      {
        if(integer<a)
          {
            return num;
          }
        else
          {
            a*=10;
            num+=1;
          }
      }
  }

int pow(int n)
  {
    int a=10;
    for(int j=0;j<n;j++)
      {
        a*=10;
      }
    return a;
  }


int sprintf(char *out, const char *fmt, ...) {
  va_list ap;
  char *out1=out;
  va_start(ap,fmt);
  int integer;
  char *str;
  while(*fmt!='\0')
    {
      if(*fmt!='%')
        {
          *out1++=*fmt++;
        }
      else
        {
          ++fmt;
          if(*fmt=='d')
            {
              integer=va_arg(ap,int);
              if(integer<0)
                {
                  *out1++='-';
                  integer=-integer;
                }
              int index=number_of_int(integer);
              for(int i=index;i>=0;i--)
                {
                  *out1++=(char)((integer/pow(i))+'0');
                  integer=integer%pow(i);
                }
            }
          else if(*fmt=='s')
            {
              str=va_arg(ap,char *);
              while(*str!='\0')
                {
                  *out1++=*str++;
                }
            }
        }
    }
  
  va_end(ap);
  return 0;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
