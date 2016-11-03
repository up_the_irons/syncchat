#include <stdio.h>

#include "xsdk.h"

#include "globals.h"
#include "portable.h"

/* Read in SYNCCHAT.CFG */
int load_config(void) {
  char s[256];

  int handle;
	int i;

	FILE *stream;

	memset(s, 0, 256);

	handle = nopen("SYNCCHAT.CFG", O_RDONLY);
	if(handle != -1)
	{
		stream = fdopen(handle, "rb");
		if(stream == NULL) {
			perror("Error [SYNCCHAT.CFG]");
			exit(1); }
		for(i = 0; i < 6; i++) /* Get BBS Software Info */
		{
			fgets(bbs_software, 64, stream);
			truncsp(bbs_software);
		}
		rewind(stream);
    if(strcmpi(bbs_software, SYNCHRONET) != 0)
		{
			fgets(s, 81, stream);
			sprintf(sys_op,"%.40s",s);
			truncsp(sys_op);
			fgets(s, 81, stream);
			sprintf(sys_name,"%.40s",s);
			truncsp(sys_name);
			fgets(snc_dir, 256, stream); /* Seeking... */
		} else {
			for(i = 0; i < 3; i++)
				fgets(snc_dir, 256, stream);
		}
		fgets(snc_dir, 256, stream);
		truncsp(snc_dir);
		if(snc_dir[strlen(snc_dir)-1]!=BACKSLASH)
			snc_dir[strlen(snc_dir)-1] = BACKSLASH;
			//strcat(snc_dir,"\\");
		fgets(toggles, 10, stream); truncsp(toggles);
		fgets(bbs_software, 64, stream); truncsp(bbs_software);

		/* 08-29: 'buff' changed to 's'*/

		memset(s, 0, sizeof(s));
		fgets(s, 7, stream); truncsp(s);
		sys_nodes = atoi(s); /* If Sync, this will be overwritten */
		
		memset(s, 0, sizeof(s));
		fgets(s, 7, stream); truncsp(s);
		sysop_level = atoi(s);

		memset(s, 0, sizeof(s));
		fgets(s, 7, stream); truncsp(s);
		#ifdef __BORLANDC__
		mswtyp = atoi(s); /* If Sync, this will be overwritten */
		#endif

		fgets(bbs_soft_dir, 128, stream); truncsp(bbs_soft_dir);
		backslash(bbs_soft_dir);

		memset(s, 0, sizeof(s));
		fgets(s, 8, stream); truncsp(s);
		act_level = atoi(s);

		fclose(stream);
		strcpy(snc_root, snc_dir);
	}
	else
	{
		fprintf(stderr, "SYNCCHAT.CFG not found, use SCONFIG to create...\r\n");
		return -1;
	}

	return 0;
}
