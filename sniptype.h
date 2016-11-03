/*
**  SNIPTYPE.H - Include file for SNIPPETS data types and commonly used macros
*/

#ifndef SNIPTYPE__H
#define SNIPTYPE__H

typedef enum {Error_ = -1, Success_, False_ = 0, True_} Boolean_T;

#if !defined(WIN32) && !defined(_WIN32) && !defined(__NT__) \
      && !defined(_WINDOWS)
 #if !defined(OS2)
  typedef unsigned char  BYTE;
  typedef unsigned long  DWORD;
 #endif
 typedef unsigned short WORD;
#else
 #include <windows.h>
 #define HUGE
#endif

#define NUL '\0'
#define LAST_CHAR(s) (((char *)s)[strlen(s) - 1])
#define TOBOOL(x) (!(!(x)))
#define FREE(p) (free(p),(p)=NULL)

#endif /* SNIPTYPE__H */
