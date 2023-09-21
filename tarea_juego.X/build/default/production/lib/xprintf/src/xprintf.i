# 1 "lib/xprintf/src/xprintf.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/opt/microchip/mplabx/v6.05/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8/pic/include/language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "lib/xprintf/src/xprintf.c" 2
# 21 "lib/xprintf/src/xprintf.c"
# 1 "lib/xprintf/src/xprintf.h" 1






# 1 "/opt/microchip/xc8/v2.41/pic/include/c99/string.h" 1 3



# 1 "/opt/microchip/xc8/v2.41/pic/include/c99/musl_xc8.h" 1 3
# 5 "/opt/microchip/xc8/v2.41/pic/include/c99/string.h" 2 3





# 1 "/opt/microchip/xc8/v2.41/pic/include/c99/features.h" 1 3
# 11 "/opt/microchip/xc8/v2.41/pic/include/c99/string.h" 2 3
# 25 "/opt/microchip/xc8/v2.41/pic/include/c99/string.h" 3
# 1 "/opt/microchip/xc8/v2.41/pic/include/c99/bits/alltypes.h" 1 3
# 122 "/opt/microchip/xc8/v2.41/pic/include/c99/bits/alltypes.h" 3
typedef unsigned size_t;
# 168 "/opt/microchip/xc8/v2.41/pic/include/c99/bits/alltypes.h" 3
typedef __int24 int24_t;
# 204 "/opt/microchip/xc8/v2.41/pic/include/c99/bits/alltypes.h" 3
typedef __uint24 uint24_t;
# 411 "/opt/microchip/xc8/v2.41/pic/include/c99/bits/alltypes.h" 3
typedef struct __locale_struct * locale_t;
# 26 "/opt/microchip/xc8/v2.41/pic/include/c99/string.h" 2 3

void *memcpy (void *restrict, const void *restrict, size_t);
void *memmove (void *, const void *, size_t);
void *memset (void *, int, size_t);
int memcmp (const void *, const void *, size_t);
void *memchr (const void *, int, size_t);

char *strcpy (char *restrict, const char *restrict);
char *strncpy (char *restrict, const char *restrict, size_t);

char *strcat (char *restrict, const char *restrict);
char *strncat (char *restrict, const char *restrict, size_t);

int strcmp (const char *, const char *);
int strncmp (const char *, const char *, size_t);

int strcoll (const char *, const char *);
size_t strxfrm (char *restrict, const char *restrict, size_t);

char *strchr (const char *, int);
char *strrchr (const char *, int);

size_t strcspn (const char *, const char *);
size_t strspn (const char *, const char *);
char *strpbrk (const char *, const char *);
char *strstr (const char *, const char *);
char *strtok (char *restrict, const char *restrict);

size_t strlen (const char *);

char *strerror (int);




char *strtok_r (char *restrict, const char *restrict, char **restrict);
int strerror_r (int, char *, size_t);
char *stpcpy(char *restrict, const char *restrict);
char *stpncpy(char *restrict, const char *restrict, size_t);
size_t strnlen (const char *, size_t);
char *strdup (const char *);
char *strndup (const char *, size_t);
char *strsignal(int);
char *strerror_l (int, locale_t);
int strcoll_l (const char *, const char *, locale_t);
size_t strxfrm_l (char *restrict, const char *restrict, size_t, locale_t);




void *memccpy (void *restrict, const void *restrict, int, size_t);
# 7 "lib/xprintf/src/xprintf.h" 2
# 28 "lib/xprintf/src/xprintf.h"
extern void (*xfunc_output)(int);
void xputc (int chr);
void xfputc (void (*func)(int), int chr);
void xputs (const char* str);
void xfputs (void (*func)(int), const char* str);
void xprintf (const char* fmt, ...);
void xsprintf (char* buff, const char* fmt, ...);
void xfprintf (void (*func)(int), const char* fmt, ...);
void put_dump (const void* buff, unsigned long addr, int len, size_t width);




extern int (*xfunc_input)(void);
int xgets (char* buff, int len);
int xatoi (char** str, long* res);
int xatof (char** str, double* res);
# 21 "lib/xprintf/src/xprintf.c" 2






# 1 "/opt/microchip/xc8/v2.41/pic/include/c99/stdarg.h" 1 3







# 1 "/opt/microchip/xc8/v2.41/pic/include/c99/bits/alltypes.h" 1 3





typedef void * va_list[1];
# 9 "/opt/microchip/xc8/v2.41/pic/include/c99/stdarg.h" 2 3

#pragma intrinsic(__va_start)
#pragma intrinsic(__va_arg)

extern void * __va_start(void);
extern void * __va_arg(void *, ...);
# 27 "lib/xprintf/src/xprintf.c" 2

void (*xfunc_output)(int);
static char *strptr;
# 160 "lib/xprintf/src/xprintf.c"
void xputc (
 int chr
)
{
 xfputc(xfunc_output, chr);
}


void xfputc (
 void(*func)(int),
 int chr
)
{


 if (func) {
  func(chr);
 } else if (strptr) {
   *strptr++ = chr;
 }
}







void xputs (
 const char* str
)
{
 xfputs(xfunc_output, str);
}


void xfputs (
 void(*func)(int),
 const char* str
)
{
 while (*str) {
  xfputc(func, *str++);
 }
}
# 233 "lib/xprintf/src/xprintf.c"
static void xvfprintf (
 void(*func)(int),
 const char* fmt,
 va_list arp
)
{
 unsigned int r, i, j, w, f;
 int n, prec;
 char str[32], c, d, *p, pad;




 long v;
 unsigned long uv;


 for (;;) {
  c = *fmt++;
  if (!c) break;
  if (c != '%') {
   xfputc(func, c); continue;
  }
  f = w = 0;
  pad = ' '; prec = -1;
  c = *fmt++;
  if (c == '0') {
   pad = '0'; c = *fmt++;
  } else {
   if (c == '-') {
    f = 2; c = *fmt++;
   }
  }
  if (c == '*') {
   n = (*(int *)__va_arg(*(int **)arp, (int)0));
   if (n < 0) {
    n = 0 - n; f = 2;
   }
   w = n; c = *fmt++;
  } else {
   while (c >= '0' && c <= '9') {
    w = w * 10 + c - '0';
    c = *fmt++;
   }
  }
  if (c == '.') {
   c = *fmt++;
   if (c == '*') {
    prec = (*(int *)__va_arg(*(int **)arp, (int)0));
    c = *fmt++;
   } else {
    prec = 0;
    while (c >= '0' && c <= '9') {
     prec = prec * 10 + c - '0';
     c = *fmt++;
    }
   }
  }
  if (c == 'l') {
   f |= 4; c = *fmt++;





  }
  if (!c) break;
  switch (c) {
  case 'b':
   r = 2; break;
  case 'o':
   r = 8; break;
  case 'd':
  case 'u':
   r = 10; break;
  case 'x':
  case 'X':
   r = 16; break;
  case 'c':
   xfputc(func, (char)(*(int *)__va_arg(*(int **)arp, (int)0))); continue;
  case 's':
   p = (*(char* *)__va_arg(*(char* **)arp, (char*)0));
   if (!p) p = "";
   j = strlen(p);
   if (prec >= 0 && j > (unsigned int)prec) j = prec;
   for ( ; !(f & 2) && j < w; j++) xfputc(func, pad);
   while (*p && prec--) xfputc(func, *p++);
   while (j++ < w) xfputc(func, ' ');
   continue;
# 332 "lib/xprintf/src/xprintf.c"
  default:
   xfputc(func, c); continue;
  }
# 348 "lib/xprintf/src/xprintf.c"
  if (f & 4) {
   v = (long)(*(long *)__va_arg(*(long **)arp, (long)0));
  } else {
   v = (c == 'd') ? (long)(*(int *)__va_arg(*(int **)arp, (int)0)) : (long)(*(unsigned int *)__va_arg(*(unsigned int **)arp, (unsigned int)0));
  }

  if (c == 'd' && v < 0) {
   v = 0 - v; f |= 1;
  }
  i = 0; uv = v;
  do {
   d = (char)(uv % r); uv /= r;
   if (d > 9) d += (c == 'x') ? 0x27 : 0x07;
   str[i++] = d + '0';
  } while (uv != 0 && i < sizeof str);
  if (f & 1) str[i++] = '-';
  for (j = i; !(f & 2) && j < w; j++) xfputc(func, pad);
  do xfputc(func, str[--i]); while (i != 0);
  while (j++ < w) xfputc(func, ' ');
 }
}


void xprintf (
 const char* fmt,
 ...
)
{
 va_list arp;


 *arp = __va_start();
 xvfprintf(xfunc_output, fmt, arp);
 ((void)0);
}


void xfprintf (
 void(*func)(int),
 const char* fmt,
 ...
)
{
 va_list arp;


 *arp = __va_start();
 xvfprintf(func, fmt, arp);
 ((void)0);
}


void xsprintf (
 char* buff,
 const char* fmt,
 ...
)
{
 va_list arp;


 strptr = buff;
 *arp = __va_start();
 xvfprintf(0, fmt, arp);
 ((void)0);
 *strptr = 0;
 strptr = 0;
}
# 424 "lib/xprintf/src/xprintf.c"
void put_dump (
 const void* buff,
 unsigned long addr,
 int len,
 size_t width
)
{
 int i;
 const unsigned char *bp;
 const unsigned short *sp;
 const unsigned long *lp;


 xprintf("%08lX ", addr);

 switch (width) {
 case sizeof (char):
  bp = buff;
  for (i = 0; i < len; i++) {
   xprintf(" %02X", bp[i]);
  }
  xputs("  ");
  for (i = 0; i < len; i++) {
   xputc((unsigned char)((bp[i] >= ' ' && bp[i] <= '~') ? bp[i] : '.'));
  }
  break;
 case sizeof (short):
  sp = buff;
  do {
   xprintf(" %04X", *sp++);
  } while (--len);
  break;
 case sizeof (long):
  lp = buff;
  do {
   xprintf(" %08lX", *lp++);
  } while (--len);
  break;
 }

 xputc('\n');
}







int (*xfunc_input)(void);






int xgets (
 char* buff,
 int len
)
{
 int c, i;


 if (!xfunc_input) return 0;

 i = 0;
 for (;;) {
  c = xfunc_input();
  if (c < 0 || c == '\r') break;
  if (c == '\b' && i) {
   i--;
   if (1) xputc(c);
   continue;
  }
  if (c >= ' ' && i < len - 1) {
   buff[i++] = c;
   if (1) xputc(c);
  }
 }
 if (1) {
  xputc('\r');
  xputc('\n');
 }
 buff[i] = 0;
 return (int)(c == '\r');
}
# 525 "lib/xprintf/src/xprintf.c"
int xatoi (
 char **str,
 long *res
)
{
 unsigned long val;
 unsigned char c, r, s = 0;


 *res = 0;

 while ((c = **str) == ' ') (*str)++;

 if (c == '-') {
  s = 1;
  c = *(++(*str));
 }

 if (c == '0') {
  c = *(++(*str));
  switch (c) {
  case 'x':
   r = 16; c = *(++(*str));
   break;
  case 'b':
   r = 2; c = *(++(*str));
   break;
  default:
   if (c <= ' ') return 1;
   if (c < '0' || c > '9') return 0;
   r = 8;
  }
 } else {
  if (c < '0' || c > '9') return 0;
  r = 10;
 }

 val = 0;
 while (c > ' ') {
  if (c >= 'a') c -= 0x20;
  c -= '0';
  if (c >= 17) {
   c -= 7;
   if (c <= 9) return 0;
  }
  if (c >= r) return 0;
  val = val * r + c;
  c = *(++(*str));
 }
 if (s) val = 0 - val;

 *res = val;
 return 1;
}
