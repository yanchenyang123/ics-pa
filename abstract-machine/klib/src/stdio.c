#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>
#include <string.h>
#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  panic("Not implemented");
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  panic("Not implemented");
}

char *itos(int integer)
  {
    char *str=NULL;
    int index=0;
    if(integer==0)
      {
        *str++='0';
        *str='\0';
        return str;
      }
    for(int i=0;i<10;i++)
      {
        if(integer!=0)
          {
            str[i]=(char)((integer%10)+'0');
            integer/=10;
            index+=1;
          }
        else
          {
            str[i]='\0';
            break;
          }
      }
    for(int i=0;i<index/2;i++)
      {
        str[i]=str[i]+str[index-1-i];
        str[index-1-i]=str[i]-str[index-1-i];
        str[i]=str[i]-str[index-1-i];
      }
    return str;
  }

int sprintf(char *out, const char *fmt, ...) {
  va_list ap;
  char *out1=out;
  int ret_num=0;
  va_start(ap,fmt);
  int integer;
  char *str;
  int fmt_len=strlen(fmt);
  for(int i=0;i<fmt_len;i++)
    {
      if(fmt[i]!='%')
        {
          out1[ret_num]=fmt[i];
          ret_num+=1;
        }
      else
        {
          i++;
          if(fmt[i]=='d')
            {
              integer=va_arg(ap,int);
              str=itos(integer);
              strcat(out1,str);
              ret_num+=strlen(str);
            }
          else if(fmt[i]=='s')
            {
              str=va_arg(ap,char *);
              strcat(out1,str);
              ret_num+=strlen(str);
            }
        }
    }
  va_end(ap);
  return ret_num;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
