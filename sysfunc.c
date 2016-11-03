/* SYSFUNC.C - Includes SysOp type functions for SyncChat
	 Created: 6-19-96 by Prophet
*/

#include "xsdk.h"
#include "portable.h"

struct actions {
 char action_word[12];  /* Action typed */    /* */
 char response[128];    /* What the user that did the action sees */
 char all[128];         /* What everyone sees if no arg to action */
 char others[128];      /* What other users see if arg to action */
 char reciever[128];    /* What the reciever (if any) of the action sees */
};

void a_editor(void);
void a_getdata(void);
void a_putdata(void);
void a_packdata(void);
void a_import(void);
void a_alphabetize(void);
void a_free(void);

char actions_file[256];
int noa = 0, i;

extern struct actions *action[165];

void a_editor(void)
{
	int done = 0, d = 0, j, line_num, match = 0;
	char s[256], line2[256];

	CRLF;
	bprintf("\1h\1cEnter the Action File to edit\r\n");
	bprintf("\1h\1c([\1wENTER\1c]=\1wACTIONS.LST\1c)\r\n");
	bprintf("\1h\1w:\1n");
	if(!getstr(actions_file, 12, K_LOWPRIO|K_UPPER))
		strcpy(actions_file, "ACTIONS.LST");
	do
		{

		#ifdef __BORLANDC__
		clrscr();
		#endif

		bprintf("\1h\1ySyncChat Actions Editor\r\n\r\n");
		a_getdata();
		a_alphabetize();
		
		#ifdef __BORLANDC__
		textcolor(LIGHTCYAN);
		#endif

		for(i = 0; i < noa; i++)
			{
			bputs("\1h\1c");
			bputs(action[i]->action_word);
			space(12 - strlen(action[i]->action_word));
			bputs(" ");
			if((i + 1) % 6 == 0)
				CRLF;
			}
		if(noa == 0)
			bprintf("\1n\1gNo Actions Available");
		CRLF; CRLF;
		bprintf("\1h\1cCommand (\1w?\1c=\1wHelp\1c): \1w");
		switch(getkeys("LAEDIQ?", 0)) {
			case 'L':
				cls();
				/*line_num = 0;*/
				for(j = 0; j < noa; j++)
					{
					#ifdef __BORLANDC__
					textcolor(LIGHTGRAY);
					#endif

					bprintf("%s\r\n", action[j]->action_word); /*line_num++;*/
					/*if(line_num > 23)
						{
						line_num = 0;
						pause();
						}*/
					bprintf("%s\r\n", action[j]->response); /*line_num++;*/
					/*if(line_num > 23)
						{
						line_num = 0;
						pause();
						}*/
					bprintf("%s\r\n", action[j]->others); /*line_num++;*/
					/*if(line_num > 23)
						{
						line_num = 0;
						pause();
						}*/
					bprintf("%s\r\n", action[j]->all); /*line_num++;*/
					/*if(line_num > 23)
						{
						line_num = 0;
						pause();
						}*/
					bprintf("%s\r\n", action[j]->reciever); /*line_num++;*/
					/*if(line_num > 23)
						{
						line_num = 0;
						pause();
						}*/
					}
				pause();
				break;
			case 'E':
				CRLF;
				bprintf("\1h\1cEnter Action To Edit\1h\1w: \1n");
				if(!getstr(s, 12, K_LOWPRIO|K_UPPER))
					break;
				CRLF;
				for(j = 0; j < noa; j++)
					{
					if(strcmpi(s, action[j]->action_word) == 0)
						{
						match = 1;
						break;
						}
					else
						match = 0;
					}
				if(match)
					{
					do {
						bprintf("\1nAction Word:\r\n");
						bprintf("\1h\1w%s", action[j]->action_word); CRLF;
						bprintf("\1nAction Response:\r\n");
						bprintf("%s", action[j]->response); CRLF;
						bprintf("\1nWhat Everyone Sees (if action is directed to another person):\r\n");
						bprintf("%s", action[j]->others); CRLF;
						bprintf("\1nWhat Everyone Sees (if action IS NOT directed to another person):\r\n");
						bprintf("%s", action[j]->all); CRLF;
						bprintf("\1nWhat 'Reciever' Sees (if action is directed to another person):\r\n");
						bprintf("%s", action[j]->reciever); CRLF;
						CRLF;
						bprintf("\1n\1g[\1h\1c1\1n\1g] Action Word\r\n");
						bprintf("\1n\1g[\1h\1c2\1n\1g] Action Response\r\n");
						bprintf("\1n\1g[\1h\1c3\1n\1g] What Everyone Sees (if directed)\r\n");
						bprintf("\1n\1g[\1h\1c4\1n\1g] What Everyone Sees (if NOT directed)\r\n");
						bprintf("\1n\1g[\1h\1c5\1n\1g] What 'Reciever' Sees (if directed)\r\n");
						CRLF;
						bprintf("\1h\1wEdit Which\1c (\1wQ\1c=\1wQuit\1c)? \1w");
						switch(getnum(5)) {
							case -1:
								d = 1;
								break;
							case 0:
								d = 1;
								break;
							case 1:
								CRLF;
								bprintf("\1nEnter New Action Word:\r\n");
								strcpy(s, action[j]->action_word);
								if(!getstr(action[j]->action_word, 12, K_UPPER|K_LOWPRIO))
									{
									strcpy(action[j]->action_word, s);
									break;
									}
								a_putdata();
								break;
							case 2:
								CRLF;
								bprintf("\1nEnter New Action Response (use CTRL-A codes for color):\r\n");
								strcpy(s, action[j]->response);
								if(!getstr(action[j]->response, 79, K_MSG|K_LOWPRIO|K_WRAP))
									{
									strcpy(action[j]->response, s);
									break;
									}
								if(wordwrap[0])
									{
									if(getstr(line2, 48, K_MSG|K_LOWPRIO))
										{
										strcat(action[j]->response, " ");
										strcat(action[j]->response, line2);
										}
									}
								a_putdata();
								break;
							case 3:
								CRLF;
								bprintf("\1nEnter New \"What Everyone Sees (if directed)\" (use CTRL-A codes for color):\r\n");
								strcpy(s, action[j]->others);
								if(!getstr(action[j]->others, 79, K_MSG|K_LOWPRIO|K_WRAP))
									{
									strcpy(action[j]->others, s);
									break;
									}
								if(wordwrap[0])
									{
									if(getstr(line2, 48, K_MSG|K_LOWPRIO))
										{
										strcat(action[j]->others, " ");
										strcat(action[j]->others, line2);
										}
									}
								a_putdata();
								break;
							case 4:
								CRLF;
								bprintf("\1nEnter New \"What Everyone Sees (if NOT directed)\" (use CTRL-A codes for color):\r\n");
								strcpy(s, action[j]->all);
								if(!getstr(action[j]->all, 79, K_MSG|K_LOWPRIO|K_WRAP))
									{
									strcpy(action[j]->all, s);
									break;
									}
								if(wordwrap[0])
									{
									if(getstr(line2, 48, K_MSG|K_LOWPRIO))
										{
										strcat(action[j]->all, " ");
										strcat(action[j]->all, line2);
										}
									}
								a_putdata();
								break;
							case 5:
								CRLF;
								bprintf("\1nEnter New \"What 'Reciever' Sees (if directed)\" (use CTRL-A codes for color):\r\n");
								strcpy(s, action[j]->reciever);
								if(!getstr(action[j]->reciever, 79, K_MSG|K_LOWPRIO|K_WRAP))
									{
									strcpy(action[j]->reciever, s);
									break;
									}
								if(wordwrap[0])
									{
									if(getstr(line2, 48, K_MSG|K_LOWPRIO))
										{
										strcat(action[j]->reciever, " ");
										strcat(action[j]->reciever, line2);
										}
									}
								a_putdata();
								break;
							}
						CRLF;
						} while(!d);
					d = 0;
					}
				else
					{
					bprintf("\1nAction Not Found.\r\n"); CRLF;
					pause();
					}
				break;
			case 'A':
				if(action[noa] == NULL)
					{
					if((action[noa] =
						 (struct actions*) MALLOC(sizeof(struct actions))) == NULL)
						 break;
					}
				CRLF;
				bprintf("\1nEnter The Action Word\r\n");
				bprintf("(Ex: HIGHFIVE):\r\n");
				if(!getstr(action[noa]->action_word, 12, K_UPPER|K_LOWPRIO))
					break;
				CRLF;
				bprintf("\1nEnter New Action Response (use CTRL-A codes for color)\r\n");
				bprintf("(Ex: ...BAM!):\r\n");
				if(!getstr(action[noa]->response, 128, K_MSG|K_LOWPRIO))
					break;
				CRLF;
				bprintf("\1nEnter What Everyone Sees (if directed) (use CTRL-A codes for color)\r\n");
				bprintf("(Ex: %%s gave %%s a high five!):\r\n");
				if(!getstr(action[noa]->others, 128, K_MSG|K_LOWPRIO))
					break;
				CRLF;
				bprintf("\1nEnter What Everyone Sees (if NOT directed) (use CTRL-A codes for color)\r\n");
				bprintf("(Ex: %%s is giving EVERYONE a high five!):\r\n");
				if(!getstr(action[noa]->all, 128, K_MSG|K_LOWPRIO))
					break;
				CRLF;
				bprintf("\1nEnter What 'Reciever' Sees (if directed) (use CTRL-A codes for color)\r\n");
				bprintf("(Ex: %%s gave YOU a high five!):\r\n");
				if(!getstr(action[noa]->reciever, 128, K_MSG|K_LOWPRIO))
					break;
				noa++;
				a_alphabetize();
				a_putdata();
				break;
			case 'D':
				CRLF;
				bprintf("\1h\1cEnter Action To Delete\1w: \1n");
				if(!getstr(s, 12, K_UPPER|K_LOWPRIO))
					break;
				for(i = 0; i < noa; i++)
					{
					if(strcmpi(action[i]->action_word, s) == 0)
						{
						match = 1;
						break;
						}
					else
						match = 0;
					}
				if(match)
					{
					action[i]->action_word[0] = 0;
					action[i]->response[0] = 0;
					action[i]->others[0] = 0;
					action[i]->all[0] = 0;
					action[i]->reciever[0] = 0;
					a_packdata();
					noa--;
					}
				else
					{
					bprintf("\nAction Not Found.\r\n"); CRLF;
					pause();
					}
				break;
			case 'I':
				a_import();
				break;
			case 'Q':
				done = 1;
				a_putdata();
				break;
			/*case '*':
				a_alphabetize();
				break;*/
			case '?':
				CRLF;
				bprintf("\1h\1b(\1cA\1b)dd An Action"); CRLF;
				bprintf("\1h\1b(\1cE\1b)dit An Action"); CRLF;
				bprintf("\1h\1b(\1cD\1b)elete An Action"); CRLF;
				bprintf("\1h\1b(\1cL\1b)Display %s file", actions_file); CRLF;
				bprintf("\1h\1b(\1cI\1b)mport Actions From Another File"); CRLF;
				bprintf("\1h\1b(\1cQ\1b)uit"); CRLF;
				CRLF;
				pause();
				break;
			}
	} while(!done);
}

void a_getdata(void)
{
	int n, handle;
	FILE *stream;

	/* Flush actions to get ready for a new batch */
	/*for(n = 0; n < noa; n++)
		{
		memset(action[n]->action_word, 0, 12);
		memset(action[n]->response, 0, 128);
		memset(action[n]->all, 0, 128);
		memset(action[n]->others, 0, 128);
		memset(action[n]->reciever, 0, 128);
		} Temporarily disabled - may be causing mem bug */

	if(fexist(actions_file))
		handle = nopen(actions_file, O_RDONLY);
	else
		{
		noa = 0;
		return;
		}
	stream = fdopen(handle, "rb");
	if(stream == NULL)
		{
		perror("Error [a_getdata()]");
		cleanup();
		exit(1);
		}
	n = 0;
	do
		{
		noa = n;
		if(action[n] == NULL)
			{
			if((action[n] =
				 (struct actions*) MALLOC(sizeof(struct actions))) == NULL)
				 {
				 perror("Error [a_getdata() - MALLOC]");
				 cleanup();
				 exit(1);
				 }
			}
		/* Flush again just to make sure */
		memset(action[n]->action_word, 0, 12);
		memset(action[n]->response, 0, 128);
		memset(action[n]->all, 0, 128);
		memset(action[n]->others, 0, 128);
		memset(action[n]->reciever, 0, 128);

		if(!feof(stream))
			fgets(action[n]->action_word, 12, stream);
		if(!feof(stream))
			fgets(action[n]->response, 128, stream);
		if(!feof(stream))
			fgets(action[n]->others, 128, stream);
		if(!feof(stream))
			fgets(action[n]->all, 128, stream);
		if(!feof(stream))
			fgets(action[n]->reciever, 128, stream);
		truncsp(action[n]->action_word);
		truncsp(action[n]->response);
		truncsp(action[n]->all);
		truncsp(action[n]->others);
		truncsp(action[n]->reciever);
		n++;
		} while(!feof(stream));
	fclose(stream);
//	noa--; /* For some reason it reads in one extra, so cut dec to
//											 cut down to size */
}

void a_putdata(void)
{
	int handle;
	FILE *stream;

	handle = nopen(actions_file, O_WRONLY|O_TRUNC|O_CREAT);
  stream = fdopen(handle, "wb");
	if(stream == NULL)
		{
		perror("Error [a_putdata()]");
		cleanup();
		exit(1);
		}
	for(i = 0; i < noa; i++)
		{
		if((action[i]->action_word[0] != 0) && (action[i]->reciever[0] != 0))
			{
			fputs(action[i]->action_word, stream); fputs("\n", stream);
			fputs(action[i]->response, stream); fputs("\n", stream);
			fputs(action[i]->others, stream); fputs("\n", stream);
			fputs(action[i]->all, stream); fputs("\n", stream);
			fputs(action[i]->reciever, stream); fputs("\n", stream);
			}
		}
	fclose(stream);
}

void a_packdata(void)
{
	int i;
	FILE *f;

	f = fopen(actions_file, "w+");
	if(f == NULL)
		{
		perror("Error [a_packdata()]");
		cleanup();
		exit(1);
		}
	for(i = 0; i < noa; i++)
		{
		if((action[i]->action_word[0] != 0) && (action[i]->response[0] != 0))
			{
			fputs(action[i]->action_word, f); fputs("\n", f);
			fputs(action[i]->response, f); fputs("\n", f);
			fputs(action[i]->others, f); fputs("\n", f);
			fputs(action[i]->all, f); fputs("\n", f);
			fputs(action[i]->reciever, f); fputs("\n", f);
			}
		}
	fclose(f);
}

void a_import(void)
{
	int handle;
	char s[13];
	FILE *stream;

	CRLF;
	bprintf("\1h\1cEnter the Action File to import from\r\n");
	bprintf("\1h\1c(Ex: ACTIONS.LST)\r\n");
	bprintf("\1h\1w:\1n");
	if(!getstr(s, 12, K_LOWPRIO|K_UPPER))
		return;
	if(!fexist(s))
		{
		bprintf("\r\n\1nFile not found.\r\n\r\n");
		pause();
		return;
		}
	handle = nopen(s, O_RDONLY);
  stream = fdopen(handle, "rb");
	if(stream == NULL)
		{
		perror("Error [a_import()]");
		cleanup();
		exit(1);
		}
	while(!feof(stream))
		{
		if(action[noa] == NULL)
			{
			if((action[noa] =
				 (struct actions*) MALLOC(sizeof(struct actions))) == NULL)
				 {
				 perror("Error [a_import() - MALLOC]");
				 cleanup();
				 exit(1);
				 }
			}
		fgets(action[noa]->action_word, 12, stream);
		fgets(action[noa]->response, 128, stream);
		fgets(action[noa]->others, 128, stream);
		fgets(action[noa]->all, 128, stream);
		fgets(action[noa]->reciever, 128, stream);
		truncsp(action[noa]->action_word);
		truncsp(action[noa]->response);
		truncsp(action[noa]->others);
		truncsp(action[noa]->all);
		truncsp(action[noa]->reciever);
		noa++;
		}
	fclose(stream);
	noa--;
	a_putdata();
}

void a_alphabetize(void)
{
	int x, y;
	struct actions a_tmp;

	for(y = 0; y <= noa; y++)
		{
		for(x = 0; x < noa - 1; x++)
			{
			if(strcmp(action[x + 1]->action_word, action[x]->action_word) < 0)
				{
				strcpy(a_tmp.action_word, action[x + 1]->action_word);
				strcpy(a_tmp.response, action[x + 1]->response);
				strcpy(a_tmp.all, action[x + 1]->all);
				strcpy(a_tmp.others, action[x + 1]->others);
				strcpy(a_tmp.reciever, action[x + 1]->reciever);
				strcpy(action[x + 1]->action_word, action[x]->action_word);
				strcpy(action[x + 1]->response, action[x]->response);
				strcpy(action[x + 1]->all, action[x]->all);
				strcpy(action[x + 1]->others, action[x]->others);
				strcpy(action[x + 1]->reciever, action[x]->reciever);
				strcpy(action[x]->action_word, a_tmp.action_word);
				strcpy(action[x]->response, a_tmp.response);
				strcpy(action[x]->all, a_tmp.all);
				strcpy(action[x]->others, a_tmp.others);
				strcpy(action[x]->reciever, a_tmp.reciever);
				}
			}
		}
}

void a_free(void)
{
	if(noa > 0)
	{
		for(i = 0; i <= noa - 1; i++)
			FREE(action[i]);
	}
}
