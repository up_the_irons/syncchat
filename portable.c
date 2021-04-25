#include "portable.h"
#include "xsdk.h"

#define DEBUG

#ifdef __unix__

/* A very weak version of Turbo C++/MSDOS findfirst, findnext functions.
 * Only supports '*' (wildcard) at the end of a filename. 
 * attrib is not used at all, included just for portability. */
int findfirst(const char* pathname, struct ffblk *ffblk, int attrib) {
  char *filename, *where;
	char pattern[13];
	int i;
	
	/* Wildcard restriction check */
  if((where = (char*) strchr(pathname, '*')) != NULL) {
	  if(strlen(where) > 1) {
      #ifdef __DEBUG__
		  fprintf(stderr, "findfirst: wildcards only supported at the end of filenames: %s\n", where);
			#endif

			return -1;
	  } else {
	    if((filename = (char*) strrchr(pathname, BACKSLASH)) != NULL) {
	      strncpy(pattern, filename, sizeof(pattern));
	      pattern[12] = '\0'; // For safety

        // shift one character to the left
				for(i = 0; i < strlen(pattern); i++)
				  pattern[i] = pattern[i+1];
				pattern[i] = '\0';

        #ifdef __DEBUG__
				fprintf(stderr, "pattern: %s\n", pattern);
				#endif

	      filename[0] = '\0'; // Chop it off
		  }
	  }
	}

	if((ffblk->dp = (DIR *)(opendir(pathname))) == NULL) {
    #ifdef __DEBUG__
		fprintf(stderr, "Error opening directory, %s, in findfirst\n", pathname);
		#endif

		return -1;
	}

  memset(ffblk->pattern, 0, sizeof(ffblk->pattern));
  strcpy(ffblk->pattern, pattern);

  #ifdef __DEBUG__
	fprintf(stderr, "ffblk->pattern: %s\n", ffblk->pattern);
	#endif

	return findnext(ffblk);
}

int findnext(struct ffblk *ffblk) {
	struct dirent* de;

	while((de = readdir(ffblk->dp)) != NULL) {
    if(ffblk->pattern[0] != 0) {
		  if(strncmp(ffblk->pattern, de->d_name, strlen(ffblk->pattern) - 1) == 0) {
			  strncpy(ffblk->ff_name, de->d_name, sizeof(ffblk->ff_name));
				return 0;
			}
		} else {
		  strncpy(ffblk->ff_name, de->d_name, sizeof(ffblk->ff_name));
			return 0;
	  }
	} 

	return -1;
}

#endif

/* The itoa function was copied from Synchronet source code: src/sbbs3/node.c */
#if !defined _MSC_VER && !defined __BORLANDC__
char* itoa(int val, char* str, int radix)
{
    switch(radix) {
        case 8:
            sprintf(str,"%o",val);
            break;      
        case 10:
            sprintf(str,"%u",val);
            break;      
        case 16:
            sprintf(str,"%x",val);
            break;      
        default:
            sprintf(str,"bad radix: %d",radix);
            break;      
    }   
    return(str);
}

char* ltoa(long val, char* str, int radix)
{
    switch(radix) {
        case 8:
            sprintf(str,"%o",val);
            break;      
        case 10:
            sprintf(str,"%u",val);
            break;      
        case 16:
            sprintf(str,"%x",val);
            break;      
        default:
            sprintf(str,"bad radix: %d",radix);
            break;      
    }   
    return(str);
}
#endif
