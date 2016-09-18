/* Public Domain [mini] c runtime library replacements for Win32 */

/* include this file before or instead of <windows.h>
   as its string functions conflict with string.h
 */

#ifndef _MINI_CRT_LIB_
#define _MINI_CRT_LIB_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif

/* you must call this before using any other function!!! */
void mCRTinit(void);

typedef unsigned long time_t;
typedef unsigned size_t;

extern int errno;

#ifndef NULL
#ifdef  __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#ifdef UNICODE
#ifndef _T
#define __T(x)   L ## x
#define _T(x)    __T(x)
#define _TEXT(x) __T(x)
#endif
char * _T2A(unsigned short *str);
#define _A2T(x) _A2U(x)
#define _tcscat wcscat
#define _tcscpy wcscpy
#define _tcscpyn wcsncpy
#define _tcscmp wcscmp
#define _tcslen wcslen
#else
#ifndef _T
#define _T(x) x
#define _TEXT(x) x
#endif
#define _T2A(x) (x)
#define _A2T(x) (x)
#define _tcscat strcat
#define _tcscpy strcpy
#define _tcscpyn strncpy
#define _tcscmp strcmp
#define _tcslen strlen
#endif
unsigned short * _A2U(char *str);

void * malloc(size_t size);
void * calloc(size_t num, size_t size);
void free(void *ptr);
void * realloc(void *ptr, size_t size);
#ifdef UNICODE
wchar_t * strdup(const wchar_t *str);
wchar_t * tstrrchr(const wchar_t *str, int c);
#else
char * strdup(const char *str);
char * tstrrchr(const char *str, int c);
#endif
char * strrchr(const char *str, int c);

#ifdef UNICODE
#define strlen lstrlenW
#define strcpy lstrcpyW
#define strncpy lstrcpynW
#define strcat lstrcatW
#define strcmp lstrcmpW
#define strcmpi lstrcmpiW
#else
#define strlen lstrlenA
#define strcpy lstrcpyA
#define strncpy lstrcpynA
#define strcat lstrcatA
#define strcmp lstrcmpA
#define strcmpi lstrcmpiA
#endif

#define wcslen lstrlenW
#define wcscpy lstrcpyW
#define wcsncpy lstrcpynW
#define wcscat lstrcatW
#define wcscmp lstrcmpW
#define wcscmpi lstrcmpiW



// MSVC [6&7] Professional+ these are intrinsic
// and this causes a duplicate function error,
// but on Standard they are not intrinsic or if
// forced as functions then these are needed.
#define NO_INTRINSIC_MEMFUNCS 1
#if defined(_MSC_VER) && defined(NO_INTRINSIC_MEMFUNCS)
/* Ensure these are treated as functions and not inlined as intrinsics, or disable /Oi */
#pragma warning(disable:4164)  // intrinsic function not declared
#pragma function(memcpy, memset, memcmp)
#endif
void * memmove(void *s1, const void *s2, size_t n);
void *memcpy(void *s1, const void *s2, size_t n);
void *memset(void *s, int c, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);

#define ESUCCESS 0
#define ENOMEM 12
#define EACCES 13
#define EEXIST 17
#define EINVAL 22

#define EOF -1

typedef struct FILE
{ 
  /*HANDLE*/void * handle;
  int eof;        /* used by feof macro to determine if read ended with error or end of file */
  int err;        /* used by ferror macro to indicate error condition encountered */
} FILE;

extern FILE *stdin, *stdout, *stderr;

#define feof(f) f->eof
#define ferror(f) f->err

/* fopen, only r[b],w[b],r[b]+,w[b]+ supported, that is a (append is not) */
#ifdef UNICODE
FILE * fopen(const wchar_t *filename, const char *mode);
#else
FILE * fopen(const char *filename, const char *mode);
#endif
size_t fwrite(const void *buffer, long size, long count, FILE *f);
long fread(const void *buffer, long size, long count, FILE *f);
int fclose(FILE *f);

int fprintf(FILE *f, const char *format, ...);
int sprintf(char *buf, const char *format, ...);
#define vsprintf wvsprintf
int fputc(int c, FILE *f);

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

int fseek(FILE *f, long offset, int origin);
long ftell(FILE *f);
void rewind(FILE *f);

/* just stubs */
int fflush(FILE *f);
FILE *_fdopen(int handle, const char *mode);

#ifdef __cplusplus
}
#endif

#ifndef WINVER  /* default to NT4/W9x compatibility */
#define WINVER 0x0400
#endif
#define WIN32_LEAN_AND_MEAN
#define _INC_STRING		/* don't allow windows.h to include MS clib's string.h */
#define _INC_MEMORY
#define _INC_EXCPT      /* don't allow VC8+SDK2003R2 to include MS clib */
#define _INC_CTYPE
#define __STRALIGN_H_
#include <windows.h>

#endif /* _MINI_CRT_LIB_ */
