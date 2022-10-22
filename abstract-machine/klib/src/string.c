#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  size_t len=0;
  for(size_t i=0;s[i]!='\0';i++)
    {
      len+=1;
    }
  return len;
}

char *strcpy(char *dst, const char *src) {
  size_t len=strlen(src);
  for(size_t i=0;i<len;i++)
    {
      dst[i]=src[i];
    }
  dst[len]='\0';
  return dst;
}

char *strncpy(char *dst, const char *src, size_t n) {
  for(size_t i=0;i<n;i++)
    {
      dst[i]=src[i];
    }
  dst[n]='\0';
  return dst;
}

char *strcat(char *dst, const char *src) {
  size_t len=strlen(dst);
  size_t len1=strlen(src);
  for(size_t i=0;i<len1;i++)
    {
      dst[len+i]=src[i];
    }
  dst[len+len1]='\0';
  return dst;
}

int strcmp(const char *s1, const char *s2) {
  size_t len1=strlen(s1);
  size_t len2=strlen(s2);
  for(size_t i=0;i<len1;i++)
    {
      if(s1[i]>s2[i]||s2[i]=='\0')
        {
          return 1;
        }
      else if(s1[i]<s2[i])
        {
          return -1;
        }
      else
        {
          continue;
        }
    }
  if(len2==len1)
    {
      return 0;
    }
  else
    {
      return -1;
    }
}

int strncmp(const char *s1, const char *s2, size_t n) {
  size_t len1=strlen(s1);
  size_t len2=strlen(s2);
  if(n>=len1||n>=len2)
    {
      return strcmp(s1,s2);
    }
  else
    {
      for(size_t i=0;i<n;i++)
        {
          if(s1[i]>s2[i])
            {
              return 1;
            }
          else if(s1[i]<s2[i])
            {
              return -1;
            }
          else
            {
              continue;
            }
        }
      return 0;
    }

}

void *memset(void *s, int c, size_t n) {
  void *str=s;
  for(size_t i=0;i<n;i++)
    {
      *(char *)str=(char)c;
      str=(char *)str+1;
    }
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  if(dst<src||(char *)src+n<=(char *)dst)
    {
      return memcpy(dst,src,n);
    }
  else
    {
      for(size_t i=1;i<=n;i++)
      {
        *(char *)(dst+n-i)=*(char *)(src+n-i);
      }
    return dst;
    }
  
}

void *memcpy(void *out, const void *in, size_t n) {
  void *str=out;
  for(size_t i=0;i<n;i++)
    {
      *(char *)out=*(char *)in;
      out=(char *)out+1;
      in=(char *)in+1;
    }
  return str;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  for(size_t i=0;i<n;i++)
    {
      if(*(char *)(s1+i)=='\0'&&*(char *)(s2+i)!='\0')
        {
          return -1;
        }
      else if(*(char *)(s1+i)!='\0'&&*(char *)(s2+i)=='\0')
        {
          return 1;
        }
      else if(*(char *)(s1+i)=='\0'&&*(char *)(s2+i)=='\0')
        {
          return 0;
        }
      if(*(char *)(s1+i)<*(char *)(s2+i))
        {
          return -1;
        }
      else if(*(char *)(s1+i)>*(char *)(s2+i))
        {
          return 1;
        }
    }
  return 0;
}

#endif
