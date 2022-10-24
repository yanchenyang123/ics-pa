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
    size_t n=0;
    while(integer)
      {
        str[index+n]=integer%10+48;
        integer/=10;
        n+=1;
      }
    for(size_t i=0;i<n/2;i++)
      {
        str[index+i]=str[index+i]+str[index+n-1-i];
        str[index+n-1-i]=str[index+i]-str[index+n-1-i];
        str[index+i]=str[index+i]-str[index+n-1-i];
      }
    index+=n;  
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
              while(*str!='\0')
                {
                  *out++=*str++;
                }
              *out='\0';
            }
          i=i+1;
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
