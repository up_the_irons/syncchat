#ifndef __PORTABLE_H
#define __PORTABLE_H

#ifdef __TURBOC__
#define __BORLANDC__
#endif

#ifndef __BORLANDC__

#include <sys/types.h>
#include <dirent.h>

struct ffblk {
	char ff_reserved[21];
	char ff_attrib;
	int  ff_ftime;
	int  ff_fdate;
	long ff_fsize;
	char ff_name[13];
	DIR  *dp;
	char pattern[13];
};

#endif

#ifdef __unix__

#define mkdir(dir)      mkdir(dir,0777)
#define strcmpi(s1,s2)  strcasecmp(s1,s2)

#include <stdio.h>
#include <unistd.h>

int eof(int handle);
int findfirst(const char* pathname, struct ffblk *ffblk, int attrib);
int findnext(struct ffblk *ffblk);

#endif

#if !defined _MSC_VER && !defined __BORLANDC__
char* itoa(int val, char* str, int radix);
char* ltoa(long val, char* str, int radix);
#endif

#endif
