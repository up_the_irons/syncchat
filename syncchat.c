#include <stdio.h>
#include <assert.h>
#ifdef __BORLANDC__
#include <process.h>
#endif
#ifdef __WATCOMC__
#include <direct.h>
#endif

#include "syncchat.h"
#include "xsdk.h"
#include "rg.h"
#include "portable.h"

#define DELETE_TOPIC 0
#define CLEAR_PROMPT 1
#define LOGGING_ON   2

#define SYNC_SPECIFIC 1

#ifdef __BORLANDC__
extern unsigned _stklen = 20000U; /* Increase the stack  - for Turbo C++ */
#endif

/* I don't remember what SP was...  something in TC++
 * I'm going to assume it was a space, for now... */
#define SP ' '

#include "globals.h"

struct actions *action[500];
struct games_s *games[25];
struct channel_s *channel[99];

char done;
char snc_dir[256];
char old_dir[256];
char snc_root[256];
char bbs_soft_dir[128];
char toggles[10];
char bbs_software[64];
char onfile[81];
char entry_msg[128];
char exit_msg[128];
int num_of_actions;
int actions_on;
int dots_again;
int num_of_rooms;
int cur_room_num;
int reged;
int num_of_games;
int x_pos, y_pos;
int act_level;
char* generic_buf;

char *l1, *l2, *l3, *l4, *l5, *l6,  *l7, *l8, *l9,
     *l10, *l11, *l12, *l13, *l14, *l15, *l16, *l17, *l18, *l19,
		 *l20, *l21, *l22, *l23, *l24, *l25, *l26, *l27, *l28, *l29,
     *l30, *l31, *l32, *l33, *l34, *l35, *l36, *l37, *l38, *l39,
     *l40, *l41, *l42, *l43, *l44, *l45, *l46, *l47, *l48, *l49,
     *l50, *l51, *l52, *l53, *l54, *l55, *l56, *l57, *l58, *l59,
     *l60, *l61, *l62, *l63, *l64, *l65, *l66, *l67, *l68, *l69,
     *l70, *l71, *l72, *l73, *l74, *l75, *l76, *l77, *l78, *l79,
     *l80, *l81, *l82, *l83, *l84, *l85, *l86, *l87, *l88, *l89,
     *l90, *l91, *l92, *l93, *l94, *l95, *l96, *l97, *l98, *l99,
     *l100, *l101, *l102, *l103, *l104, *l105, *l106, *l107,
     *l108, *l109, *l110;

int main(int argc, char* argv[])
{
  int f, i, j, handle, numofactions, d, z = 0, t, warned = 0;
	char *s, buff[256], buf2[256], uls[9], ch, tempkey;
	struct stat statbuf;
  struct noderec nr;
	FILE *stream;

	#ifdef __WATCOMC__
	struct find_t fileinfo;
	#else
	struct ffblk ffblk;
	#endif

	// Allocate new globals
	generic_buf = (char*) malloc(512);

	init_globals();

	/* Read in SYNCCHAT.CFG */
	if(load_config() == -1)
    return -1;
	/* PENDING DELETE (08-29-2004)
	handle = nopen("SYNCCHAT.CFG", O_RDONLY);
	if(handle != -1)
		{
		stream = fdopen(handle, "rb");
		if(stream == NULL) {
			perror("Error [SYNCCHAT.CFG]");
			exit(1); }
		for(j = 0; j < 6; j++) /* Get BBS Software Info /
			{
			fgets(bbs_software, 64, stream);
			truncsp(bbs_software);
			}
		rewind(stream);
    if(strcmpi(bbs_software, SYNCHRONET) != 0)
			{
			fgets(buf2, 81, stream);
			sprintf(sys_op,"%.40s",buf2);
			truncsp(sys_op);
			fgets(buf2, 81, stream);
			sprintf(sys_name,"%.40s",buf2);
			truncsp(sys_name);
			fgets(snc_dir, 256, stream); /* Seeking... /
			}
		else
			{
			for(j = 0; j < 3; j++)
				fgets(snc_dir, 256, stream);
			}
		fgets(snc_dir, 256, stream);
		truncsp(snc_dir);
		if(snc_dir[strlen(snc_dir)-1]!=BACKSLASH)
			snc_dir[strlen(snc_dir)-1] = BACKSLASH;
			//strcat(snc_dir,"\\");
		fgets(toggles, 10, stream); truncsp(toggles);
		fgets(bbs_software, 64, stream); truncsp(bbs_software);
		fgets(buff, 7, stream); truncsp(buff);
		sys_nodes = atoi(buff); /* If Sync, this will be overwritten /
		fgets(buff, 7, stream); truncsp(buff);
		sysop_level = atoi(buff);
		fgets(buff, 7, stream); truncsp(buff);

		#ifdef __BORLANDC__
		mswtyp = atoi(buff); /* If Sync, this will be overwritten /
		#endif

		fgets(bbs_soft_dir, 128, stream); truncsp(bbs_soft_dir);
		backslash(bbs_soft_dir);
		fgets(buff, 8, stream); truncsp(buff);
		act_level = atoi(buff);
		fclose(stream);
		strcpy(snc_root, snc_dir);
		}
	else
		{
		bprintf("SYNCCHAT.CFG not found, use SCONFIG to create...\r\n");
		exit(1);
		}
	*/

  /* Make temp dir*/
  snc_dir[strlen(snc_dir) - 1] = 0;
  _mkdir(snc_dir);
  backslash(snc_dir);
  /* End */

	if(strcmpi(bbs_software, SYNCHRONET) == 0)
		{
		s=getenv("SBBSNODE");
			if(s)
				strcpy(node_dir,s);
			else {
				printf("\nSBBSNODE environment variable must be set\n");
				exit(0); }

		if(node_dir[strlen(node_dir)-1]!=BACKSLASH)
			snc_dir[strlen(snc_dir)-1] = BACKSLASH;
			//strcat(node_dir,"\\");
		}
	else
		{
		if(argc < 2)
			{
			printf("usage: SYNCCHAT [node_dir]\r\n\r\n");
			printf("Ex: SYNCCHAT C:\\BBS\\NODE1\r\n\r\n");
			printf("node_dir must be the directory where DOOR.SYS is located!\r\n");
			exit(1);
			}
		strcpy(node_dir, argv[1]);
		backslash(node_dir);
		}

	initdata();
	#ifndef SYNC_SPECIFIC
	x00_init(com_port);
	#endif

  /* Check for gender (cause fuckin' door.sys doesn't have it) */
	if(strcmpi(bbs_software, "0") != 0)
	{
	_mkdir("SEX"); /* Doesn't hurt if directory is already there */
	sprintf(buff, "SEX%c%i.*", BACKSLASH, user_number);
	i = findfirst(buff,&ffblk,0);
	if(!i)
		{
		truncsp(ffblk.ff_name);
		s = strstr(ffblk.ff_name, ".");
		s++;
		user_sex = s[0];
		}
	else
		{
		bprintf("\1h\1wNew User Questions\r\n");
		bprintf("\1h\1cYour Sex (Don't Lie, It Won't Be Asked Again)? [\1wM\1c/\1wF\1c]: \1w");
		user_sex = getkeys("MF",0);
		sprintf(buff, "SEX%c%i.%c", BACKSLASH, user_number, user_sex);
		handle = nopen(buff, O_CREAT|O_WRONLY);
		close(handle); /* Just create file */
		}
	}

	/* Make TMP dir*/
	_mkdir("TMP");
	/* End */

	/* Make new LOG */
	if(!fexist("SYNCCHAT.LOG"))
		{
		add_to_log("SyncChat Log (Delete periodically to avoid a BIG log file :)\r\n");
		add_to_log("------------\r\n\r\n");
		}
	/* End */

	cls();
  bprintf("0lnhy[rÄnrÄhkÄÄ›bScyncbCchat m3nm.h0r2 ALPHA                             kÄÄnrÄhÄy]\r\n");
  bprintf("n(C) Copyright 1995, 2004 Garry Dolleyn\r\n");
	if(registered2()==0) {
		sprintf(buff, "\1wRegistered to \1h\1w%s\1n.\r\n", sys_name);
		center(buff);
		}
	else
		bprintf("0‰nhUnregistered. Please help your SysOp register this product.n\r\n");

	/* Create users private chat room (directory) */
	strcpy(buff, snc_dir);
	itoa(user_number, uls, 10);
	strcat(buff, uls);

	 #ifdef __WATCOMC__
	 if(_mkdir(buff) != 0)
		 {
		 strcat(buff, "\\*.*");
		 d = _dos_findfirst(buff, _A_NORMAL, &fileinfo);
		 while(!d) {
				if((fileinfo.name[0] != 'O') && (fileinfo.name[1] != 'N') &&
					 (fileinfo.name[2] != '.'))
					{
					unlink(fileinfo.name);
					d = _dos_findnext(&fileinfo);
					}
				}
		 #ifdef __OS2__
		 _dos_findclose(&fileinfo);
		 #endif
		 }

		#else 
  	if(_mkdir(buff) != 0)
	  	{

			#ifdef __unix__
  		strcat(buff, "/ON.*");
			#else
  		strcat(buff, "\\ON.*");
			#endif
			
	  	d = findfirst(buff,&ffblk,0); i = 0;
		  while((!d) && (i <= 256)) {
			  	 i++;
				   strcpy(buf2, snc_dir);
  				 strcat(buf2, uls);

					 #ifdef __unix__
	  			 strcat(buf2, "/");
					 #else
	  			 strcat(buf2, "\\");
					 #endif

		  		 strcat(buf2, ffblk.ff_name);
			  	 if(fexist(buf2)) /* Make sure onfile is 'deletable' before deleting it */
	  					{
		  				do {
			  				stat(buf2, &statbuf);
				  		} while(!(statbuf.st_mode & S_IWRITE));
  						unlink(buf2);
	  				}
		  		 d = findnext(&ffblk);
			   }
	  	}

	   #endif

	/* Add to ROOMS.LST */
	handle = nopen("ROOMS.LST", O_WRONLY|O_CREAT|O_APPEND);
	if(handle == -1)
		{
		perror("Error [ROOMS.LST]");
		cleanup();
		exit(1);
		}
	write(handle, &user_name, sizeof(user_name));
	memset(buff, 0, 256);
	itoa(user_number, buff, 10);
	truncsp(buff);
	write(handle, &buff, 10);
	close(handle);

	/* Read GAMES.DAT into structures */
	if(fexist("GAMES.DAT")) {
		d = 0;
		handle = nopen("GAMES.DAT", O_RDONLY);
    stream = fdopen(handle, "rb");
		while(!feof(stream))
			{
			if((games[d] = (struct games_s*)
					MALLOC(sizeof(struct games_s))) == NULL)
				break;
			memset(games[d]->exec, 0, 256);
			memset(games[d]->display, 0, 256);

			fgets(games[d]->exec, 256, stream);
			fgets(games[d]->display, 256, stream);
			truncsp(games[d]->exec);
			truncsp(games[d]->display);
			if((s = strstr(games[d]->exec, "*")) != NULL)
				s[0] = '0' + node_num;
			d++;
			if(registered3())
				{
				if(d >= 2)
					break;
				}
			}
		fclose(stream);
		num_of_games = d;
		}

	if(fexist("CHANNELS.DAT"))
		{
		handle = nopen("CHANNELS.DAT", O_RDONLY);
		stream = fdopen(handle, "rb");
		d = 0;
		do {
			if((channel[d] = (struct channel_s*)
					MALLOC(sizeof(struct channel_s))) == NULL)
				{
				perror("Error [Loading Channels]"); CRLF;
				pause();
				num_of_rooms = d;
				cleanup();
				exit(1);
				}
			memset(channel[d]->name, 0, 256);
      memset(channel[d]->sl, 0, 10);
			memset(channel[d]->actions_file, 0, 256);
			memset(channel[d]->dir, 0, 256);
			/* To lazy to read in whole structure... ;) */
			fgets(channel[d]->name, 256, stream);
      fgets(channel[d]->sl, 10, stream);
			fgets(channel[d]->actions_file, 256, stream);
			fgets(channel[d]->dir, 256, stream); /* Advance file pointer */
			if(d == 0) /* If first channel ("Main") set root directory */
				strcpy(channel[d]->dir, snc_dir);
			else /* If any other channel, branch off root in CHAN directories */
				{
				sprintf(buff, snc_dir);
				sprintf(buf2, "%i", d);
				strcat(buff, buf2);
				strcpy(channel[d]->dir, buff);
				strcat(channel[d]->dir, "CHAN");
				/* Make all the dirs for different sysop defined public */
				_mkdir(channel[d]->dir);
				}
			truncsp(channel[d]->name);
			truncsp(channel[d]->sl);
			truncsp(channel[d]->actions_file);
			truncsp(channel[d]->dir);
			d++;         /* channels */
			} while((!feof(stream)) && (d < 99));
		fclose(stream);
		num_of_rooms = d;
		}
	else
		{
		if((channel[0] = (struct channel_s*)
				MALLOC(sizeof(struct channel_s))) == NULL)
			{
			fprintf(stderr, "Error: Out Of Memory"); CRLF;
			pause();
			cleanup();
			exit(2);
			}
		handle = nopen("CHANNELS.DAT", O_WRONLY|O_CREAT);
		stream = fdopen(handle, "wb");
		fprintf(stream, "Main\n");
		fprintf(stream, "0\n");
		fprintf(stream, "ACTIONS.LST\n");
		fprintf(stream, " \n");
		fclose(stream);
		strcpy(channel[0]->dir, snc_root);
		strcpy(channel[0]->name, "Main");
		strcpy(channel[0]->sl, "0");
		strcpy(channel[0]->actions_file, "ACTIONS.LST");
		truncsp(channel[0]->dir);
		truncsp(channel[0]->name);
		truncsp(channel[0]->sl);
		truncsp(channel[0]->actions_file);
		num_of_rooms = 1;
		}

		get_actions();
		create_onfile();
		get_strings();

		sprintf(buff, "%s entered SyncChat.\r\n", user_name);
		add_to_log(buff);

    if(strcmpi(bbs_software, RENEGADE) == 0)
      {
      sprintf(buff, "%sMULTNODE.DAT", bbs_soft_dir);
      f = nopen(buff, O_RDWR);
      if(f == -1)
        {
        bprintf("\r\nError opening %s\r\n", buff);
        return;
        }
      read(f, &nr, sizeof(struct noderec));

      /* Make sure they are still 'available' */
      if(nr.status.NActive)
        {
        lseek(f, tell(f) - (long)(sizeof(struct noderec)), SEEK_SET);
        nr.status.NAvail = 1;
        write(f, &nr, sizeof(struct noderec));
        }
      close(f);
      }


/**************************************************************************/
/* Main Program                                                           */
/**************************************************************************/

	CRLF;
	bprintf(l1);
	bprintf(l2);
	bprintf(l11, channel[cur_room_num]->name);
	print_topic(l15);

	/* Handles Entry Messages =] */
	get_e_msgs();
	if(entry_msg[0])
		{
		strcat(entry_msg, "\r\n");
		printall(entry_msg);
		}
	else
		{
		sprintf(buff, l25, user_name);
		printall(buff);
		}

	whosin_cur_room();
	bprintf(l4);
	registered6();
	do {
		#ifndef SYNC_SPECIFIC
		while(x00_peek_ahead_input(com_port) == 0)
		#else
		while((tempkey=inkey(0))==0)
		#endif
			{
			checkline();
			if(z > 10)
				{
				registered6();
				z = 0;
				}
			if(dots_again)
				bputs(l44);
			dots_again = 0;
			mswait(50);  /* Bit o' a delay ;).. Gives up timeslices - good for */
			get_me();    /* Multitasking :) */
			if(strcmpi(bbs_software, SYNCHRONET) == 0)
				{
				getnmsg();
				getsmsg(user_number);
				}
			if(strcmpi(bbs_software, TELEGARD) == 0)
				tggetnmsg();
      if(strcmpi(bbs_software, RENEGADE) == 0)
        rggetnmsg();
			if(!reged)
				{
				if(time(NULL)-starttime > 10) /* Unreg'd users get only 10 mins! */
					{
          bprintf("\r\n\1h\1wSorry, because this is an UNREGISTERED copy of SyncChat, you only get 10 minutes\r\n");
					bprintf("to chat.\r\n\r\n");
					bprintf("\1n\1wThis copy of SyncChat is \1h\1i\1rUNREGISTERED\1n.  \1n\1wIf you've enjoyed using this\r\n");
					bprintf("\1n\1wteleconference and would like to be able to play more than just TWO games while\r\n");
					bprintf("\1n\1wchatting and get more than 10 minutes of chat time, please consider \1hadopting \r\n");
					bprintf("me\1n!  \1n\1wI am fairly inexpensive \1h\1g($25.00)\1n and \1n\1w\1n\1wwith your help, you and your\r\n");
					bprintf("Sysop (%s) can enjoy FREE upgrades!\r\n\r\nPausing\1..\1..\1..\1..\1..\r\n\r\n", sys_op);
					pause();
					cleanup();
					exit(0);
					}
				}
			if(!SYSOP && !strchr(user_exempt,'T')) /* Warns user of time */
				{
				if((t=(timeleft-(time(NULL)-starttime))) < 360)
					{
					switch(t) {
						case 300:
							if(warned) break;
							CRLF; bprintf(l58, "5");
							bputs(l44);
							warned = 1;
							break;
						case 240:
							if(warned) break;
							CRLF; bprintf(l58, "4");
							bputs(l44);
							warned = 1;
							break;
						case 180:
							if(warned) break;
							CRLF; bprintf(l58, "3");
							bputs(l44);
							warned = 1;
							break;
						case 120:
							if(warned) break;
							CRLF; bprintf(l58, "2");
							bputs(l44);
							warned = 1;
							break;
						case 60:
							if(warned) break;
							CRLF; bprintf(l59, "1");
							bputs(l44);
							warned = 1;
							break;
						case -1:
							checktimeleft();
							break;
						default:
							warned = 0;
						}
					}
				}
			}
		#ifdef SYNC_SPECIFIC
		ungetkey(tempkey);
		#endif
		send_me();
		dots_again = 1;
		z++;
	} while (done == 0);
	
	cleanup();

	free(generic_buf);

	return 0;
}

/****************************************************************************/
/* GET_ME is for SyncChat... revised getnmsg */
/****************************************************************************/

void get_me(void)
{
	char str[256], *buf;
	int file;
	long length;
	node_t thisnode;

//if(strcmpi(bbs_software, SYNCHRONET) == 0)
//	{
//	getnodedat(node_num,&thisnode,1);
//	thisnode.misc&=~NODE_NMSG;                      /* clear the NMSG flag */
//	putnodedat(node_num,thisnode);
//	}
// Is this needed anymore? (08-30-04)
	
sprintf(str,"%sN%3.3u.SNC",snc_dir,node_num);
if(flength(str)<1L) {
/*  unlink(str); Possible bug */
	return; }
if((file=nopen(str,O_RDWR))==-1) {
	printf("Couldn't open %s for read/write\r\n",str);
	return; }
length=filelength(file);
if((buf=MALLOC(length+1))==NULL) {
	close(file);
	printf("Couldn't allocate %lu bytes for %s\r\n",length+1,str);
	return; }
if(read(file,buf,length)!=length) {
	close(file);
	FREE(buf);
	printf("Couldn't read %lu bytes from %s\r\n",length,str);
	return; }
chsize(file,0L);
close(file);
buf[length]=0;

if(strstr(buf, "Ÿ›‘¬‡") != NULL) /* Here's where the 'secret' comes in. */
	{
	CRLF;
  unlink(str);

	goto_main(1,1,1);
	FREE(buf);
	dots_again = 1;
	return;
	}
if(toggles[CLEAR_PROMPT] == '1')
	del_prompt();
else
	CRLF;
/* printf("\r\nEntering bputs(buf)...\r\n"); */
bputs(buf);
/* printf("\r\nLeaving bputs(buf)...\r\n"); */
FREE(buf);
dots_again = 1;
}

/****************************************************************************/
/* SCPUTNMSG is also for SyncChat... revised putnmsg
/****************************************************************************/

void scputnmsg(int num, char *strin)
{
	char str[256], s[256], tmpstr[256], *pstr;
	int file,i;
	node_t node;

if(!ok_to_send(num))
	return;
sprintf(s, "%sON.%i", snc_dir, num);
if(!fexist(s))
	return;
sprintf(str,"%sN%3.3u.SNC",snc_dir,num);
if((file=nopen(str,O_WRONLY|O_CREAT|O_APPEND))==-1) {
	printf("Couldn't open %s for append\r\n",str);
	return; }
i=strlen(strin);
if(write(file,strin,i)!=i) {
	close(file);
	printf("Error writing %u bytes to %s\r\n",i,str);
	return; }
close(file);
//getnodedat(num,&node,0);
//if((1/*node.status==NODE_INUSE || node.status==NODE_QUIET*/)
//*&& !(node.misc&NODE_NMSG)*/) {
//  getnodedat(num,&node,1);
//    node.misc|=NODE_NMSG;
//  putnodedat(num,node); }

}

/****************************************************************************/
/* SEND_ME is for SyncChat... revised nodemsg() that sends stuff in telecon.
/* format.
/***************************************************************************/

void send_me(void)
{
	char    str[256],s[256],line[256],second_l[256], third_l[256],buf[512],
					to_user[30],
					fn[100], line2[256], buf2[512], *sarg, *s2, *a_only, tmp, *s3;
	int     i,j,k,l,m,n,o,arg,is_number = 0,match = 0, old_room_num, handle;
	node_t  thisnode;
	node_t  node;
	FILE *stream;

	memset(str, 0, 256);
	memset(s, 0, 256);
	memset(line, 0, 256);
	memset(second_l, 0, 256);
	memset(third_l, 0, 256);
	memset(buf, 0, 512);
  memset(to_user, 0, 30);
  memset(fn, 0, 100);
	memset(line2, 0, 256);
	memset(buf2, 0, 512);
	memset(old_dir, 0, 256);

	sarg = line;

/*	bprintf("\r\nIn send_me..."); */
/*if(strchr(user_rest,'C')) {
	bputs("You cannot send messages.\r\n");
	return; }
getnodedat(node_num,&thisnode,0);
wordwrap[0]=0;
if(lastnodemsg) {
	getnodedat(lastnodemsg,&node,0);
	if(node.status!=NODE_INUSE)
		lastnodemsg=0; }*/
/*if(!whos_online(0))
	return;*/
/*bprintf("\r\nngNumber of node to send message to, whAngll, "
	"or whQnguit [%u]: wh",lastnodemsg);
i=getkeys("QA",sys_nodes);
if(i==-1)
	return;
if(i&0x8000 || !i) {
	if(!i)
		i=lastnodemsg;
	else {
		i^=0x8000;
		lastnodemsg=i; }
	if(!i || i>sys_nodes)
		return;
	getnodedat(i,&node,0);
	if(node.status!=NODE_INUSE && !SYSOP)
		bprintf("\r\n_whNode %d is not in use.\r\n",i);
	else if(i==node_num)
		bputs("\r\nThere's no need to send a message to yourself.\r\n");
	else if(node.misc&NODE_POFF && !SYSOP)
		bprintf("\r\nrhiDon't bug %s.n\r\n"
			,node.misc&NODE_ANON ? "UNKNOWN USER"
			: username(node.useron));
	else {
		bputs("_yhMessage: ");
		if(!getstr(line,70,K_LINE))
			return;
		sprintf(buf
			,"\7_whNode %2d: g%sng sent you a message:\r\nwh4%sn\r\n"
			,node_num
			,thisnode.misc&NODE_ANON ? "UNKNOWN USER" : user_name,line);
		putnmsg(i,buf); } }
else if(i=='A') {       */
	if(!getstr(line,78,K_MSG|K_LOWPRIO|K_WRAP))
		{
		if(isdigit(snc_dir[strlen(snc_dir) - 2]))
			{
			strcpy(s, snc_dir);
			s[strlen(s) - 1] = 0;
			strcpy(str, strrchr(s, BACKSLASH));
			for(j = 0; j <= strlen(str); j++)
				str[j] = str[j + 1];
			i = atoi(str);
			if(user_number != i) /* Do the CHAN.NAM shit here, or reverse of */
				bprintf(l20, scusername(i)/*username(i)*/); /* scusername, only works online */
      if(user_number == i)  
				bprintf(l12);
			}
		else {
			bprintf(l11, channel[cur_room_num]->name);
			}
		print_topic(l15);
		whosin_cur_room();
		return;
		}
		if(wordwrap[0]) {
		if(getstr(second_l,78,K_MSG|K_LOWPRIO|K_WRAP)) {
			strcat(line, " ");
			strcat(line, second_l); }
		}
		if(wordwrap[0]) {
		if(getstr(third_l, 79,K_MSG|K_LOWPRIO)) {
			strcat(line, " ");
			strcat(line, third_l); }
		}

/*************************************************************************/
/* The following code interprets actions                                 */
/*************************************************************************/
	if(actions_on) {
	for(k = 0; k < num_of_actions; k++)
		{
		if(line[0] < 33)
			{
			match = 0;
			break;
			}
		a_only = strchr(line, ' ');
		if(a_only != NULL) {
			tmp = a_only[0];
			a_only[0] = 0; } /* Cuts off 'line' at space after action */
		if(strcmpi(action[k]->action_word, line) == 0)
			match = 1;
		else
			match = 0;
		l = strlen(action[k]->action_word);
		if(a_only != NULL)
			a_only[0] = tmp;
		if(match)
			{
			if(line[l] > 33) /* If no space after action */
				match = 0;
			break;
			}
		}
	if(match)
		{
		/*** Init some strings ***/
		s2 = strstr(action[k]->all, "~s~");
		if(s2 != NULL)
			{
			if(tolower(user_sex) == 'm')
				{ s2[0] = 'h'; s2[1] = 'i'; s2[2] = 'm'; }
			if(tolower(user_sex) == 'f')
				{ s2[0] = 'h'; s2[1] = 'e'; s2[2] = 'r'; }
			}
		s2 = strstr(action[k]->all, "~r~");
		if(s2 != NULL)
			{
			if(tolower(user_sex) == 'm')
				{ s2[0] = 'h'; s2[1] = 'i'; s2[2] = 's'; }
			if(tolower(user_sex) == 'f')
				{ s2[0] = 'h'; s2[1] = 'e'; s2[2] = 'r'; }
			}
		s2 = strstr(action[k]->others, "~s~");
		if(s2 != NULL)
			{
			if(tolower(user_sex) == 'm')
				{ s2[0] = 'h'; s2[1] = 'i'; s2[2] = 'm'; }
			if(tolower(user_sex) == 'f')
				{ s2[0] = 'h'; s2[1] = 'e'; s2[2] = 'r'; }
			}
		s2 = strstr(action[k]->others, "~r~");
		if(s2 != NULL)
			{
			if(tolower(user_sex) == 'm')
				{ s2[0] = 'h'; s2[1] = 'i'; s2[2] = 's'; }
			if(tolower(user_sex) == 'f')
				{ s2[0] = 'h'; s2[1] = 'e'; s2[2] = 'r'; }
			}
		s2 = strstr(action[k]->reciever, "~s~");
		if(s2 != NULL)
			{
			if(tolower(user_sex) == 'm')
				{ s2[0] = 'h'; s2[1] = 'i'; s2[2] = 'm'; }
			if(tolower(user_sex) == 'f')
				{ s2[0] = 'h'; s2[1] = 'e'; s2[2] = 'r'; }
			}
		s2 = strstr(action[k]->reciever, "~r~");
		if(s2 != NULL)
			{
			if(tolower(user_sex) == 'm')
				{ s2[0] = 'h'; s2[1] = 'i'; s2[2] = 's'; }
			if(tolower(user_sex) == 'f')
				{ s2[0] = 'h'; s2[1] = 'e'; s2[2] = 'r'; }
			}

		/*************************/

		/* Print action to everyone else (if arg) (ie "WAVE 3") */
		if(line[l++] == ' ') /* Make sure there is a space after the action. */
			{
			if(line[l] > 33) /* Make sure there is an arg after the space! */
				{
				/* The next 3 lines put the arg in 'sarg'. */
				for(m = 0; m <= strlen(action[k]->action_word); m++)
					 sarg++;
				/* This loops finds out if the arg is a node number or user name. */
				for(m = 0; m <= (strlen(sarg) - 1); m++)
					{
					if(isdigit(sarg[m]) > 0)
						is_number = 1;
					else
						{
						is_number = 0;
						break;
						}
					}
				/* Process action if a node number arg was specified. */
				if(is_number)
					{
					arg = atoi(sarg); /* Put 'sarg' into the integer 'arg'. */
					if(arg > sys_nodes)
						{
						bprintf(l29, arg);
						return;
						}
					if(who_is_on_node(arg) == 0)
						{
						bprintf(l30, arg);
						return;
						}
					strcpy(sarg, who_is_on_node(arg));
					sprintf(s, action[k]->others, user_name, sarg);
					print_to_all_nodes_except(s, arg);
					print_to_all_nodes_except("\r\n", arg);
					sprintf(s, action[k]->reciever, user_name);
					if(arg == node_num)
						{
						bprintf("%s\r\n", action[k]->response);
						bprintf("%s\r\n", s);
						return;
						}
					scputnmsg(arg, s);
					scputnmsg(arg, "\r\n");
					}
				/* Process action if a user name arg was specified. */
				else
					{
					if(stricmp(sarg, "HELP") == 0)
						{
						bprintf(l26, action[k]->action_word);
						bprintf("\1h\1w");
						bprintf(action[k]->all, user_name);
						CRLF;
						if ((s2 = strstr(action[k]->others, "~*~")) != 0)
							{
							tmp = s2[0];
							s2[0] = 0;
							bprintf(l77, action[k]->action_word);
							sprintf(s, action[k]->others, user_name);
							strcat(s, "<User Input Here>");
							bputs("\1h\1w");
							bputs(s); CRLF;
							s2[0] = tmp;
							}
						else
							{
							bprintf(l27, action[k]->action_word);
							bprintf("\1h\1w");
							bprintf(action[k]->others, user_name, "SysOp");
							bprintf("\r\n");
							}
						return;
						}

					/* Generate action text if user specified is in SyncChat. */
					if(full_name(sarg)) // For protection (08-29)
				    strncpy(fn, full_name(sarg), 100);
					n = user_in_telecon(fn, 1);
					o = user_in_telecon(fn, 2);
					/* bprintf("\r\nn = %i\r\n", n);
					bprintf("\r\nfull_name(sarg) = %s\r\n", full_name(sarg));
					bprintf("\r\nline = %s\r\n", line); */

					if(n == 0)
						{
						/* Do Generic Actions */
						s2 = strstr(action[k]->others, "~*~");
						if(s2 != 0)
							{
							s3 = s2; s3 = s3 + 3;
							strcpy(second_l, s3);
							tmp = s2[0];
							s2[0] = 0; /* Chop */
							bprintf("%s\r\n", action[k]->response);
							sprintf(s, action[k]->others, user_name);
							strcat(s, sarg);
							strcat(s, second_l);
							/*bprintf("%s\r\n", s);*/
							printall(s); printall("\r\n");
              /*bprintf(s);*/
              /** Add to SYNCCHAT.LOG **/
              strcpy(buf2, s); strip_ctrla(buf2);
              add_to_log(buf2); 
              /** End **/
							/*bprintf(s); bprintf("\r\n");*/
							s2[0] = tmp;
							}
						else
							{
              sprintf(s, l55, sarg); /* l55 = Sorry, User-ID is not ... */
							rollover(s);
							bprintf(s);
							}
						return;
						}
					if(strlen(sarg) < 3)
						return;
					if(n)
						{ /* Username called */ /* use 'fn' instead of username(n)! */
						sprintf(s, action[k]->others, user_name, fn/*username(n)*/);
						print_to_all_nodes_except(s, o); /* Print action to others */
						print_to_all_nodes_except("\r\n", o);
            /** Add To SYNCCHAT.LOG **/
            strcpy(buf2,s); strip_ctrla(buf2);
            add_to_log(buf2); 
            /** End **/
						sprintf(s, action[k]->reciever, user_name);
						/* bprintf("\r\no = %i, node_num = %i\r\n", o, node_num); */
						if(o == node_num) /* If directing action to yourself */
							{               /* bypass the file stuff and just print to */
							bprintf("%s\r\n", action[k]->response); /* the action to you. */
							bprintf("%s\r\n", s);
							return;
							}
						scputnmsg(o, s); /* Print action to 'reciever' */
						scputnmsg(o, "\r\n");
						}
					/*else
						{
						match = 0;
						bprintf(l28, sarg);
						}*/
					}
				}
			else
				{
				return;
				}
			}
		else
			{
			/* Print action to everyone else (if no arg) (ie "WAVE") */
			sprintf(s, action[k]->all, user_name);
			printall(s);
			printall("\r\n");
      /** Add To SYNCCHAT.LOG **/
      strcpy(buf2, s); strip_ctrla(buf2);
      add_to_log(buf2); 
      /** End **/
			}
			/* Print response to user */
		if(match)
			{
			bprintf("%s\r\n", action[k]->response);
			return;
			}
		return;
		}
	}

/**************************************************************************/
/* This part of code interprets stuff like ">Pro Hey.." or for whispers,  */
/* "/Pro whispers...".                                                    */
/**************************************************************************/
	if( (line[0] == '>') || (line[0] == '/') ) {
		if( !isalpha(line[1]) )
			return;
		for(k = 1; (line[k] != ' ') && (k < 26); k++)
			to_user[k - 1] = line[k];
		if(line[k] < SP)
			return;
		if(k < 4)
			return;
		to_user[k - 1] = 0;
		if(full_name(to_user) == NULL)
			{
			sprintf(s, l55, to_user);
			rollover(s);
			bprintf(s);
			return;
			}
		strcpy(fn, full_name(to_user));
		strcpy(line2, strchr(line, ' '));
		o = user_in_telecon(fn, 2);
		if(line[0] == '>') {
			sprintf(buf, l6, user_name,
							fn, line2);
			print_to_all_nodes_except(rollover(buf), o);
      /** Add To SYNCCHAT.LOG **/
      strcpy(buf2, buf); strip_ctrla(buf2);
      add_to_log(buf2); 
      /** End **/
			sprintf(buf, l7,/*thisnode.misc&NODE_ANON
							? "UNKNOWN USER" :*/ user_name, line2);
			if(o == node_num) /* If 'talking' to yourself (I don't know why you  */
				{               /* would want to...), bypass the file shit and just*/
				bprintf(l40, fn);
				bputs(rollover(buf)); /* print it to the screen.                 */
				return;
				}
			bprintf(l40, fn);
			scputnmsg(o, rollover(buf)); }
		else {
			sprintf(buf2, l9/*"_hc®%s¯ Whispered To %sb:wh%sn\r\n"*/,
							/*thisnode.misc&NODE_ANON	? "UNKNOWN USER" :*/ user_name, fn, line2);
			sprintf(buf, l8/*"_hc®%s¯ Whispered To You\1b:wh%sn\r\n"*/,
							/*thisnode.misc&NODE_ANON	? "UNKNOWN USER" :*/ user_name, line2);
			if(o == node_num) /* If whispering to yourself (I don't know why you */
				{								/* would want to...), bypass the file shit and just*/
				bprintf(l41, fn);
				bprintf(rollover(buf)); /* print it to the screen.                 */
				print_to_ops(rollover(buf2), fn);
        /** Add To SYNCCHAT.LOG **/
        strip_ctrla(buf2); add_to_log(buf2); 
        /** End **/
				return;
				}
			print_to_ops(rollover(buf2), fn);
      /** Add To SYNCCHAT.LOG **/
      strip_ctrla(buf2); add_to_log(buf2); 
      /** End **/
			bprintf(l41, fn);
			scputnmsg(o, rollover(buf)); }
		return;
	}
	else {
		sprintf(buf,l5,/*thisnode.misc&NODE_ANON ? "UNKNOWN USER"
			:*/user_name, line);
		}
	if (strcmp(strlwr(line), "x")==0)
	{
		if (registered()==1 && (reged==0))
		{
			bprintf("\1n\1wThis copy of SyncChat is \1h\1i\1rUNREGISTERED\1n.  \1n\1wIf you've enjoyed using this\r\n");
			bprintf("\1n\1wteleconference and would like to be able to play more than just TWO games while\r\n");
			bprintf("\1n\1wchatting and get more than 10 minutes of chat time, please consider \1hadopting\r\n");
			bprintf("me\1n!  \1n\1wI am fairly inexpensive \1h\1g($25.00)\1n and \1n\1w\1n\1wwith your help, you and your\r\n");
			bprintf("Sysop (%s) can enjoy FREE upgrades!\r\n\r\nPausing\1..\1..\1..\1..\1..\r\n\r\n", sys_op);
			pause();
		}
	done = 1;
	return;
	}
	if (strcmp(strlwr(line), "w")==0)
	{
		if(strcmpi(bbs_software, SYNCHRONET) == 0)
      scwhos_online(1);
    if(strcmpi(bbs_software, IMPULSE) == 0)
			impwhos_online();
		if(strcmpi(bbs_software, TELEGARD) == 0)
			tgwhos_online(1);
		if(strcmpi(bbs_software, RENEGADE) == 0)
			rgwhos_online(1);
		return;
	}
	if (strcmp(strlwr(line), "p")==0)
	{
		if(strcmpi(bbs_software, SYNCHRONET) == 0)
			nodemsg();
		if(strcmpi(bbs_software, TELEGARD) == 0)
			tg_page();
    if(strcmpi(bbs_software, RENEGADE) == 0)
      rg_page();
		return;
	}
	if (strcmp(line, "?")==0)
	{
		if(fexist("HELP.ASC"))
			{
			if(fexist("HELP.ANS") && (user_misc&ANSI))
				printfile("HELP.ANS");
			else
				printfile("HELP.ASC");
			}
		else if(fexist("HELP.ANS") && (user_misc&ANSI))
			printfile("HELP.ANS");
		else {
			bprintf("\1h\1cSyncChat Commands\r\n");
			bprintf("\1bÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\r\n");
			CRLF;
      if( (strcmpi(bbs_software, SYNCHRONET) == 0) ||
					(strcmpi(bbs_software, IMPULSE) == 0)    ||
					(strcmpi(bbs_software, TELEGARD) == 0) )
				bprintf("\1h\1w[\1yW\1w]\1w Who's Online\r\n");
			if( (strcmpi(bbs_software, SYNCHRONET) == 0) ||
					(strcmpi(bbs_software, TELEGARD) == 0) )
				bprintf("\1h\1w[\1yP\1w]\1w Page Someone\r\n");
			bprintf("\1h\1w[\1yA\1w]\1w Actions - List And Help\r\n");
			bprintf("\1h\1w[\1yG\1w]\1w Games!\r\n");
			bprintf("\1h\1w[\1yR\1w] Enter SyncRegistry! (Registry Of Users - VERY FUN)\r\n");
			bprintf("\1h\1w[\1yJ\1w]\1w Join A Public Channel.\r\n");
			bprintf("\1w\1h    Type 'J <username>' to join someone's PRIVATE channel.\r\n");
			bprintf("\1w\1h    Note: The user must be in SyncChat to join their channel!\r\n");
			bprintf("\1h\1w[\1yT\1w]\1w Topic - Change Channel Topic.\r\n");
			bprintf("\1h\1w[\1yS\1w]\1w Scan - See who is in SyncChat and which channel they are in.\r\n");
			bprintf("\1h\1w[\1yF\1w]\1w Forget (Ignore) a user.\r\n");
			bprintf("\1h\1w[\1yE\1w]\1w Edit Your Entry/Exit Messages.\r\n");
			if(user_level >= act_level)
				{
				bprintf("\1h\1w[\1yD\1w]\1w Actions Editor (Ops Only)\r\n");
				}
			bprintf("\1h\1w[\1yX\1w]\1w Exit\r\n");
			CRLF;
			pause();
			bprintf("\1h\1cOther cool things you can do with SyncChat\r\n");
			bprintf("\1bÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\r\n");
			CRLF;
			bprintf("\1nTo direct a message to someone use the \"\1h\1c>\1n\" character.\r\n");
			bprintf("For example, to direct a message to Etherius, type:\r\n");
			bprintf("\1h\1m>eth What's Up?\r\n");
			bprintf("\1nTo whisper (send private message) to someone use the \"\1h\1c/\1n\" character.\r\n");
			bprintf("For example, to whisper to Etherius, type:\r\n");
			bprintf("\1h\1m/eth What's Up?\r\n");
			CRLF;
			bprintf("\1n\1rREMEMBER!\1n You ONLY need to use the\1h\1w FIRST THREE\1n letters of someone's handle\r\n");
			bprintf("when used with commands like \"J\", \">\", etc...  This makes things a lot easier!\r\n");
			bprintf("Try it!\r\n");
			}
		return;
	}
	if(strcmpi(line, "a") == 0)
	{
		if(num_of_actions == 0)
			{
			bprintf(l10); /* l10 = No actions available */
			return;
			}
		if(fexist("ACTHELP.ASC"))
			{
			if(fexist("ACTHELP.ANS") && (user_misc&ANSI))
				printfile("ACTHELP.ANS");
			else
				printfile("ACTHELP.ASC");
			}
		else if(fexist("ACTHELP.ANS") && (user_misc&ANSI))
			printfile("ACTHELP.ANS");
		else {
			bprintf("\1h\1c");
			center("List Of Actions");
			bprintf("\r\n\1h\1b");
			center("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ");
			bprintf("\r\n\r\n\1h\1w");
			for(i = 0; i < num_of_actions; i++) {
				bprintf(action[i]->action_word);
				space(12 - strlen(action[i]->action_word));
				bputs(" ");
				if((i + 1) % 6 == 0)
				bprintf("\r\n"); }
			bprintf("\r\n\r\n\1h\1c");
			center("Help On Actions");
			bprintf("\r\n\1h\1b");
			center("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ");
			bprintf("\r\n\r\n");
			bprintf("\1nTo do an action, just type it's name.  To direct an action to someone, type\r\n");
			bprintf("the action's name, then the user's name.  For example, to give a high five to\r\n");
			bprintf("your friend Prophet, type \"HF PROPHET\" or \"HF PRO\".  Instead of the user name,\r\n");
			bprintf("you can also type the node number the user is on.  To see what an action looks\r\n");
			bprintf("like to other users, type the action's name, then \"HELP\" (Ex: \"HF HELP\")\r\n");
				}
		return;
	}
/*	if(strcmpi(line, "dir") == 0)
		{
		strcpy(s, snc_dir);
		if(s[strlen(s) - 1] == '\\')
			s[strlen(s) - 1] = 0;
		sprintf(buf2, "dir %s", s);
		system(buf2);
		return;
		}*/
  if(strcmpi(line, "r") == 0)
		{
		if(!fexist("SYNCREG.EXE"))
			{
			bprintf("\1nError: Tell the SysOp that SYNCREG.EXE is missing.\r\n");
			bprintf("Cannot enter registry...\r\n");
			return;
			}
    sprintf(s, "SYNCREG.EXE %s", node_dir);
		system(s);
		#ifndef SYNC_SPECIFIC
		x00_init(com_port); /* SyncRegistry deinits the com port
													 so get have to init it again */
		#endif
		/* registry(); */
    cls();
		return;
		}
	if(strcmpi(line, "g") == 0)
		{
		if(!fexist("GAMES.DAT"))
			{
			bputs(l54);
			return;
			}
		play_games();
		return;
		}
	if(line[0] == 'j' && (line[1] <= SP))
	{
/* Note on free_actions().  DESQview seems to hate it.  I took 'em out.
	 That means if someone goes from a channel with 400 actions to one with
	 2 actions, there will still be 400 actions allocated in memory yet the
	 user will only be able to use those 2 actions.. just a reminder.. */

		if(!(line[2] <= SP)) /* If arg... */
			{
      memset(to_user, 0, 30);
			memset(fn, 0, 100);
			for(k = 2; (!(line[k] < 32)) && (k < 27); k++)
				to_user[k - 2] = line[k];
			if(line[k - 2] <= SP)
				return;
			to_user[k - 2] = 0; k = 0;
			if(strlen(to_user) < 3) /* Less than three character argument. */
				return;               /* Abort. */
			if(full_name2(to_user) == NULL) {
				bprintf(l19); /* No such channel. */
				return; }     /* Abort. */
/*			bprintf(".. = %s\r\n", full_name2(to_user));*/
			strcpy(s, full_name2(to_user));
			i = scusernumber(s);
/*      bprintf("s = '%s'\r\n", full_name2(to_user));
			bprintf("i = %i\r\n", i);*/
			if(!ok_to_join(i) && (i != user_number))
				{
				bprintf(l91,
								full_name2(to_user));
				return;
				}
			sprintf(s, l37, user_name);
			printall(s);
			goto_main(0,0,0); /* Makes dead code below... */
			strcpy(fn, full_name2(to_user)); /* fn = Prophet */
			strcpy(old_dir, snc_dir); /* snc_dir = E:\ or E:\1\ */
			sprintf(str, "ON.%i", node_num); /* str = ON.3 */
			strcat(old_dir, str); /* old_dir = E:\ON.3 or E:\1\ON.3 */
			strcpy(str, snc_dir); /* str = E:\ or E:\1\ */
			k = 0;
			if(isdigit(str[strlen(str) - 2])) { /* <---- here, dead code */
				do {
					buf2[k] = str[strlen(str) - 1];
					str[strlen(str) - 1] = 0;
					k++;
				} while(str[strlen(str) - 1] != BACKSLASH); }
			buf2[k] = 0;
			for(k = 0; k <= strlen(buf2); k++)
				buf2[k] = buf2[k + 1];
//			if(atoi(buf2) == user_number) {
//				bprintf(l42); /* Already in private channel. */
//				return; }     /* Abort. */
      itoa(scusernumber(fn), s, 10); /* Usernumber called - scusernumber */
			/* bprintf("\r\ns = %s, buf2 = %s\r\n", s, buf2); */
      if(strcmpi(s, buf2) == 0) { /* If already in channel wanting to join, */
        if(scusernumber(fn) == user_number) /* Usernumber called - see above */
					{
					bprintf(l42);
					return;
          }             /* scusername would be good here */
        sprintf(s, l43, scusername(atoi(s))/*username(atoi(s))*/); /* Username called */
				bprintf(s);              /* inform user of stupidity, */
				return; }                /* and return. */
      strcat(str, s); /* s = user_number, str = E:\ then E:\1 */
      sprintf(s, "ON.%i", node_num); /* s = ON.3 */
			#ifdef __unix__
      strcat(str, "/"); /* str = E:\1\ */
			#else
      strcat(str, "\\"); /* str = E:\1\ */
			#endif
      strcpy(snc_dir, str); /* snc_dir = E:\1\ */
			strcat(str, s); /* str = E:\1\ON.3 */
			if(rename(old_dir, str) != 0) {
				perror("Error");
				cleanup();
				exit(1); }
      strcpy(onfile, str); /* onfile = E:\1\ON.3 */
			if(strcmpi(fn, user_name) == 0)
				bprintf(l12);
			else
				bprintf(l20, fn);
			print_topic(l15);
			whosin_cur_room();
			sprintf(s, l38, user_name);
			printall(s);
			cur_room_num = -1;
//      bputs("Crashed before free_actions, get_actions\r\n");
			/*free_actions();*/ get_actions();
//      bputs("Crashed after free_actions, get_actions\r\n");
			return;
			}
		/*bprintf("\1h\1wJoin a (\1h\1cP\1w)ublic or Pr(\1h\1ci\1w)vate channel? : \1h\1y");
		switch(getkeys("PI\r", 0)) {
			case 'P': */
				bputs(l60);
				CRLF;
					for(j = 0; (j < num_of_rooms) &&
										 (channel[j]->name[0] != 0) &&
										 (channel[j]->dir[0]  != 0); j++)
					{
					bprintf(l61, j + 1, channel[j]->name);
					}
				CRLF;
				bputs(l62);
				i = getnum(j);
				if(i < 1)
					return;
				if(i - 1 == cur_room_num)
					{
					bprintf(l11, channel[cur_room_num]->name);
					print_topic(l15);
					whosin_cur_room();
					return;
					}
				l = atoi(channel[i - 1]->sl);
				if(user_level < l)
					{
					bprintf(l63);
					return;
					}
				sprintf(s, l37, user_name);
				printall(s);
				goto_main(0,0,0);
				/*bprintf("Crashed after goto_main\r\n"); Test code */
				if(i - 1 == 0)
					{
					cur_room_num = 0;
					bprintf(l11, channel[cur_room_num]->name);
					print_topic(l15);
					/*bputs("Crashed before whosin_cur_room()\r\n"); Test Code */
					whosin_cur_room();
					/*bputs("Crashed after whosin_cur_room()\r\n"); Test Code */
					sprintf(s, l38, user_name);
					printall(s);
//					bputs("Before free_actions(), get_actions();\r\n"); /*Test Code */
					/*free_actions();*/ get_actions();
//					bputs("After free_actions(), get_actions();\r\n"); /*Test Code */
					return;
					}
				/*bprintf("\r\nonfile = %s", onfile);
				bprintf("\r\nsnc_dir = %s\r\n", snc_dir);*/
				strcpy(old_dir, snc_dir);
				strcpy(s, channel[i - 1]->dir);
				sprintf(str, "ON.%i", node_num);
				if(s[strlen(s) - 1] != BACKSLASH)
					s[strlen(s) - 1] = BACKSLASH;
					//strcat(s, "\\");
				strcat(s, str);
				/*bprintf("\r\n%s\r\n", s); Test Code
				bprintf("\r\n%s\r\n", onfile);*/
				if(rename(onfile, s) != 0) {
					perror("Error");
					cleanup();
					exit(1); }
				strcpy(snc_dir, channel[i - 1]->dir);
				if(snc_dir[strlen(snc_dir) - 1] != BACKSLASH)
					snc_dir[strlen(snc_dir) - 1] = BACKSLASH;
					//strcat(snc_dir, "\\");
				/*bprintf("\r\nsnc_dir = %s\r\n", snc_dir);*/
				strcpy(onfile, s);
				cur_room_num = i - 1;
				bprintf(l11, channel[cur_room_num]->name);
				print_topic(l15);
				whosin_cur_room();
				sprintf(s, l38, user_name);
				printall(s);
				/*free_actions();*/ get_actions();
				return;
	}
  if(strcmpi(line, "e") == 0)
    {
    edit_e_msgs();
    return;
		}
	if(strcmpi(line, "d") == 0)
		{
		if(user_level >= act_level) {
      /*free_actions();*/
			a_editor();
      get_actions();
    }
		return;
		}
	if(strcmpi(line, "s") == 0)
		{
		scan();
		return;
		}
/*  if(strcmpi(line, "f") == 0)
		{
		bputs("\1h\1cYou can use this command to ignore any user.  After you forget a user, you\r\n");
		bputs("\1h\1cwill not recieve ANY messages (actions, messages, whispers, etc...) from that\r\n");
		bputs("\1h\1cuser.\r\n");
		bputs("\1h\1cSyntax: 'F <User-ID>'\r\n");
		bputs("\1h\1cRepeat this command to 'unforget' a user.\r\n");
		return;
    }*/
	if((line[0] == 'f') && (line[1] <= SP))
		{
		if(!(line[2] <= SP)) /* If arg... */
			{
			memset(to_user, 0, 30);
			memset(fn, 0, 100);
			for(k = 2; (!(line[k] < 32)) && (k < 27); k++)
				to_user[k - 2] = line[k];
			if(line[k - 2] <= SP)
				return;
			to_user[k - 2] = 0; k = 0;
			if(strlen(to_user) < 3) /* Less than three character argument. */
				return;               /* Abort. */
			if(full_name2(to_user) == NULL) {
				bprintf(l55, to_user); /* No such User-ID. */
				return; }     /* Abort. */
			if(has_been_forgotten(full_name2(to_user)))
				{
				unforget(full_name2(to_user));
        bprintf(l81, full_name2(to_user));
				}
			else
				{
				forget(full_name2(to_user));
				bprintf(l79, full_name2(to_user));
				bputs(l80);
				}
			}
		return;
		}
	if((line[0] == 'n') && (line[1] <= SP))
		{
		if(!(line[2] <= SP)) /* If arg... */
			{
			memset(to_user, 0, 30);
			memset(fn, 0, 100);
			for(k = 2; (!(line[k] < 32)) && (k < 27); k++)
				to_user[k - 2] = line[k];
			if(line[k - 2] <= SP)
				return;
			to_user[k - 2] = 0; k = 0;
			if(strlen(to_user) < 3) /* Less than three character argument. */
				return;               /* Abort. */
			if(full_name2(to_user) == NULL) {
				bprintf(l55, to_user); /* No such User-ID. */
				return; }     /* Abort. */
			invite(full_name2(to_user));
			}
		return;
		}
	if(strcmpi(line, "t") == 0) {
		print_topic(l13); CRLF;
		if(isdigit(snc_dir[strlen(snc_dir) - 2])) {
			strcpy(s, snc_dir);
			s[strlen(s) - 1] = 0;
			strcpy(str, strrchr(s, BACKSLASH));
			for(j = 0; j <= strlen(str); j++)
				str[j] = str[j + 1];
			i = atoi(str);
			if(user_number != i) {
				bprintf(l35);
				bprintf(l36);
			} else {
				if(!noyes(l33))
					change_topic(); }
			CRLF; return; }
		if(!noyes(l33))
			change_topic();
		return; }
/** Add line to SYNCCHAT.LOG */
	strcpy(buf2, buf);
  strip_ctrla(buf2);
	add_to_log(rollover(buf2));
/** END **/
	if(alone())
		{
		/* bprintf("\r\nRight before bputs(l3) (alone), 'bout to leave send_me...");*/
		bputs(l3);
		/* bprintf("\r\nafter bputs(l3) (alone), leaving send_me..."); */
		return;
		}
	bputs(l39);
	/* bprintf("\r\nRight before printall, 'bout to leave send_me..."); */
	printall(rollover(buf));
	/* bprintf("\r\nafter printall, leaving send_me..."); */
}

/****************************************************************************/
/* for SyncChat: Displays the information for node number 'number' contained in 'node'    */
/****************************************************************************/
void scprintnodedat(uchar number, node_t node)
{
	char hour,mer[3],tmp[256],s[256],node_num[10];
	char node_status[64], node_action[64], connection_rate[15];
	int i;

memset(s, 0, 256);
memset(node_status, 0, 64);
memset(node_action, 0, 64);
memset(connection_rate, 0, 15);

itoa(number, node_num, 10);

switch(node.status) {
		case NODE_WFC:
  strcpy(node_status,"\1nWaiting for call");
	break;
		case NODE_OFFLINE:
  strcpy(node_status,"\1h\1kOffline");
	break;
		case NODE_NETTING:
  strcpy(node_status,"\1h\1kNetworking");
	break;
	case NODE_LOGON:
	strcpy(node_status,"At logon prompt");
	break;
	case NODE_EVENT_WAITING:
	strcpy(node_status,"Waiting for all nodes to become inactive");
	break;
		case NODE_EVENT_LIMBO:
	sprintf(node_status,"Waiting for node %d to finish external event",node.aux);
	break;
		case NODE_EVENT_RUNNING:
	strcpy(node_status,"Running external event");
	break;
	case NODE_NEWUSER:
	attr(GREEN|HIGH);
	strcpy(node_status,"New user");
		attr(GREEN);
	strcat(node_status," applying for access ");
	if(!node.connection)
			strcpy(connection_rate,"Local");
	else
			sprintf(connection_rate,"%u",node.connection);
	break;
	case NODE_QUIET:
	if(!SYSOP) {
      strcpy(node_status,"\1nWaiting for call");
		break; }
		case NODE_INUSE:
		attr(WHITE|HIGH);
	if(node.misc&NODE_ANON && !SYSOP)
			strcpy(node_status,"UNKNOWN USER");
	else
			strcpy(node_status,username(node.useron));
		attr(HIGH|YELLOW);
/*	bputs(" "); */
	switch(node.action) {
			case NODE_MAIN:
    strcpy(node_action,"At main menu");
		break;
			case NODE_RMSG:
    strcpy(node_action,"Reading messages");
		break;
			case NODE_RMAL:
    strcpy(node_action,"Reading mail");
		break;
		case NODE_RSML:
    strcpy(node_action,"Reading sent mail");
		break;
			case NODE_RTXT:
    strcpy(node_action,"Reading text files");
		break;
			case NODE_PMSG:
    strcpy(node_action,"Posting message");
		break;
			case NODE_SMAL:
    strcpy(node_action,"Sending mail");
		break;
			case NODE_AMSG:
    strcpy(node_action,"Posting auto-message");
		break;
			case NODE_XTRN:
		if(!node.aux)
        strcpy(node_action,"At external program menu");
		else {
          strcpy(node_action,"Running ");
					i=node.aux-1;
					if(i>=total_xtrns || !xtrn[i][0])
            strcat(node_action,"external program");
					else
						strcat(node_action,xtrn[i]); }
		break;
			case NODE_DFLT:
    strcpy(node_action,"Changing defaults");
		break;
			case NODE_XFER:
    strcpy(node_action,"At transfer menu");
		break;
			case NODE_RFSD:
        sprintf(node_action,"Retrieving from device #%d",node.aux);
		break;
			case NODE_DLNG:
    strcpy(node_action,"Downloading");
		break;
			case NODE_ULNG:
    strcpy(node_action,"Uploading");
		break;
			case NODE_BXFR:
        strcpy(node_action,"Transferring bidirectional");
		break;
			case NODE_LFIL:
    strcpy(node_action,"Listing files");
		break;
			case NODE_LOGN:
    strcpy(node_action,"Logging on");
		break;
			case NODE_LCHT:
    sprintf(node_action,"In local chat with %s",sys_op);
		break;
			case NODE_MCHT:
		if(node.aux) {
      sprintf(node_action,"In multinode chat channel %d",node.aux&0xff);
					if(node.aux&0x1f00)  /* password */
						outchar('*'); }
		else
        strcpy(node_action,"In multinode global chat channel");
		break;
			case NODE_PAGE:
        sprintf(node_action,"Paging node %u for private chat",node.aux);
				break;
			case NODE_PCHT:
        sprintf(node_action,"In private chat with node %u",node.aux);
				break;
			case NODE_GCHT:
    sprintf(node_action,"Chatting with %s",sys_guru);
		break;
			case NODE_CHAT:
    strcpy(node_action,"In chat section");
		break;
			case NODE_TQWK:
    strcpy(node_action,"Transferring QWK packet");
		break;
			case NODE_SYSP:
    strcpy(node_action,"Performing sysop activities");
		break;
			default:
		bputs(itoa(node.action,tmp,10));
		break;  }
	if(!node.connection)
			strcpy(connection_rate,"Local");
	else
			sprintf(connection_rate,"%u",node.connection);
	if(node.action==NODE_DLNG) {
			if((node.aux/60)>12) {
		hour=(node.aux/60)-12;
		strcpy(mer,"pm"); }
			else {
		if((node.aux/60)==0)    /* 12 midnite */
				hour=12;
		else hour=node.aux/60;
		strcpy(mer,"am"); }
			sprintf(tmp," ETA %02d:%02d %s"
				,hour,node.aux%60,mer);
			strcat(node_action,tmp); }
	break; }
i=NODE_LOCK;
if(node.status==NODE_INUSE || SYSOP)
	i|=NODE_POFF|NODE_AOFF|NODE_MSGW|NODE_NMSG;
/*if(node.misc&i) {
		bputs(" (");
	if(node.misc&(i&NODE_AOFF))
		outchar('A');
		if(node.misc&NODE_LOCK)
		outchar('L');
	if(node.misc&(i&(NODE_MSGW|NODE_NMSG)))
		outchar('M');
	if(node.misc&(i&NODE_POFF))
		outchar('P');
	outchar(')'); }
if(SYSOP && ((node.misc
		&(NODE_ANON|NODE_UDAT|NODE_INTR|NODE_RRUN|NODE_EVENT|NODE_DOWN))
		|| node.status==NODE_QUIET)) {
		bputs(" [");
		if(node.misc&NODE_ANON)
		outchar('A');
		if(node.misc&NODE_INTR)
		outchar('I');
		if(node.misc&NODE_RRUN)
		outchar('R');
		if(node.misc&NODE_UDAT)
		outchar('U');
		if(node.status==NODE_QUIET)
		outchar('Q');
		if(node.misc&NODE_EVENT)
		outchar('E');
		if(node.misc&NODE_DOWN)
		outchar('D');
	outchar(']'); }
if(node.errors && SYSOP) {
	attr(RED|HIGH|BLINK);
		bprintf(" %d error%c",node.errors, node.errors>1 ? 's' : '\0' ); } */
	sprintf(s, l66, node_num, node_status, node_action, connection_rate);
	bputs(s);
}

/****************************************************************************/
/* for SYNCCHAT!!! :This function lists users that are online.                                                           */
/* If listself is true, it will list the current node.                                          */
/* Returns number of active nodes (not including current node).                         */
/****************************************************************************/
int scwhos_online(char listself)
{
	int i,j;
	node_t node;

if( (!ctrl_dir[0]) || (strcmpi(bbs_software, SYNCHRONET) != 0) )
	return(0);
bputs(l64);
bputs(l65);
for(j=0,i=1;i<=sys_nodes;i++) {
	getnodedat(i,&node,0);
	if(i==node_num) {
		if(listself)
			scprintnodedat(i,node);
		continue; }
  if(node.status==NODE_INUSE || (SYSOP && node.status==NODE_QUIET)) {
		scprintnodedat(i,node);
		if(!lastnodemsg)
			lastnodemsg=i;
		j++; } }
/* if(!j)
	bputs("\1nNo other active nodes.\r\n"); */
return(j);
}

/*************************************************************************/
/* This function prints 'buf' to every node EXCEPT the node it is called */
/* from.																																 */
/*************************************************************************/

void printall(char *buf)
	{
	int i;
	node_t node;

	for(i=1;i<=sys_nodes;i++)
	{
		if(!in_telecon(i))
			continue;
		if(i==node_num)
			continue;
//    getnodedat(i,&node,0);
		/*if(node.status==NODE_INUSE || (SYSOP && node.status==NODE_QUIET))*/
			scputnmsg(i,buf);
		}
	}

/*************************************************************************/
/* This function prints 'buf' to every node EXCEPT node 'i' if 'i' is    */
/* non-zero.  Does not print to current current node.         					 */
/*************************************************************************/

void print_to_all_nodes_except(char *buf, int i)
{
	int j;
	node_t node;

	for(j=1;j<=sys_nodes;j++)
	{
		if(!in_telecon(j))
			continue;
		if(j==node_num)
			continue;
		if(j==i) continue; /* Do not print to node 'i' */
		/*getnodedat(j,&node,0);*/
		/*if(node.status==NODE_INUSE || (SYSOP && node.status==NODE_QUIET))*/
			scputnmsg(j,buf);
		}
}

int in_telecon(int node)
{
	char s[81];

	sprintf(s, "%sON.%i", snc_dir, node);
	if(!fexist(s))
			return(0);
	else
		return(1);
}

/*************************************************************************/
/* Returns the name of the user who is on node 'node'.  If the node is   */
/* not valid, or no one is on that node, a null pointer is returned.     */
/* Scans only current channel																						 */
/*************************************************************************/
char *who_is_on_node(int node)
{
	int handle;
	char s[81];
	FILE *f;

	memset(s, 0, 81);

	sprintf(s, "%sON.%i", snc_dir, node);
	handle = nopen(s, O_RDONLY);
  f = fdopen(handle, "rb");
	if(f == NULL)
		{
		sprintf(s, "%sGONE.%i", snc_dir, node);
		handle = nopen(s, O_RDONLY);
    f = fdopen(handle, "rb");
		if(f == NULL)
			return(NULL);
		}
	memset(generic_buf, 0, 512);
	fgets(generic_buf, 50, f);
	fclose(f);
	truncsp(generic_buf);
	return(generic_buf);
}

/*************************************************************************/
/* This function returns a non-zero value if the user name 'name' is     */
/* present in SyncChat.  That value depends on 'mode':                   */
/* Mode 1 - returns user number of user 'name'        									 */
/* Mode 2 - returns node number 'user' is on.											       */
/* Only scans current channel																						 */
/*************************************************************************/
int user_in_telecon(char *name, int mode)
{
	int i, handle, user_number;
	char s[81], buf[50];
	FILE *f;

	memset(buf, 0, 50);
	memset(s, 0, 81);

	for(i = 1; i <= sys_nodes; i++)
		{
		if(in_telecon(i))
			{
			sprintf(s, "%sON.%i", snc_dir, i);
			handle = nopen(s, O_RDONLY);
      f = fdopen(handle, "rb");
			if(f == NULL)
				{
				/* bprintf("Error: fopen(s, \"r\"); in user_in_telecon - Inform the SysOp about this!\r\n"); */

				//return(NULL); chaned 08-24-2004
				return(0);
				}
			fgets(buf, 50, f);
			fgets(s, 81, f); /* dummy seek */
			truncsp(s);
			fgets(s, 81, f);
			truncsp(s);
			user_number = atoi(s);
			fclose(f);
			truncsp(buf);
			if(strcmpi(buf, name) == 0)
				{
				if(mode == 1)
					return(user_number/*usernumber(name)*/);
				if(mode == 2) return(i);
				}
			}
		}
	return(0);
}

/*************************************************************************/
/* Here it is!!  The function that will determine the tightwads from the
/* Donald Trumps! (LAME JOKE)!! ;) This will return a 0 if SyncChat is
/* registered, else 1.
/*************************************************************************/

int registered(void)
{

	long  namecode = 0, bbscode = 0, x, index, len, len1, len2;
	char t[256], temp;
	char name[256], bbsname[256], regcode[256];
	FILE *regfile;
	int handle;

	handle = nopen("SYNCCHAT.CFG", O_RDONLY);
  regfile = fdopen(handle, "rb");
	if(regfile == NULL)
		return(0);
	fgets(name, 256, regfile);
	fgets(bbsname, 256, regfile);
	fgets(regcode, 256, regfile);
	truncsp(name); truncsp(bbsname); truncsp(regcode);
	strcat(name, "\n"); strcat(bbsname, "\n"); strcat(regcode, "\n");

	fclose(regfile);
	len = strlen(name)-1;
	len1 = strlen(bbsname)-1;
	len2 = len+len1;
	len2 = len2+( (atol(name) + 9) * (atol(bbsname) + 3) );
	len2 = len2*105;
	len2 = len2*34;

	for(index = 0 ; index <= len ; index++)
	{
		temp = name[index];
		namecode = namecode + temp;
	}
	temp = 0;
	for(index = 0 ; index <= len1 ; index++)
	{
		temp = bbsname[index];
		bbscode = bbscode + temp;
	}
	namecode = namecode -  10;
	bbscode =  bbscode - 10;
	x = ((namecode*len)+(bbscode));
	x = x*len2;
	ltoa(x, t, 10);
	regcode[strlen(regcode)-1]=0;
	truncsp(regcode);
	if (strcmp(regcode, t)==0)
		return(0);
	else
		return(1);

}

int registered2(void)
{

	long  namecode = 0, bbscode = 0, x, index, len, len1, len2;
	char t[256], temp;
	char name[256], bbsname[256], regcode[256];
	FILE *regfile;
	int handle;

	handle = nopen("SYNCCHAT.CFG", O_RDONLY);
  regfile = fdopen(handle, "rb");
	if(regfile == NULL)
		return(0);
	fgets(name, 256, regfile);
	fgets(bbsname, 256, regfile);
	fgets(regcode, 256, regfile);
	truncsp(name); truncsp(bbsname); truncsp(regcode);
	strcat(name, "\n"); strcat(bbsname, "\n"); strcat(regcode, "\n");
	fclose(regfile);
	len = strlen(name)-1;
	len1 = strlen(bbsname)-1;
	len2 = len+len1;
	len2 = len2+( (atol(name) + 9) * (atol(bbsname) + 3) );
	len2 = len2*105;
	len2 = len2*34;

	for(index = 0 ; index <= len ; index++)
	{
		temp = name[index];
		namecode = namecode + temp;
	}
	temp = 0;
	for(index = 0 ; index <= len1 ; index++)
	{
		temp = bbsname[index];
		bbscode = bbscode + temp;
	}
	namecode = namecode -  10;
	bbscode =  bbscode - 10;
	x = ((namecode*len)+(bbscode));
	x = x*len2;
	ltoa(x, t, 10);
	regcode[strlen(regcode)-1]=0;
	truncsp(regcode);
	if (strcmp(regcode, t)==0)
		return(0);
	else
		return(1);

}

int registered3(void)
{

	long  namecode = 0, bbscode = 0, x, index, len, len1, len2;
	char t[256], temp;
	char name[256], bbsname[256], regcode[256];
	FILE *regfile;
	int handle;

	handle = nopen("SYNCCHAT.CFG", O_RDONLY);
  regfile = fdopen(handle, "rb");
	if(regfile == NULL)
		return(0);

	fgets(name, 256, regfile);
	fgets(bbsname, 256, regfile);
	fgets(regcode, 256, regfile);
	truncsp(name); truncsp(bbsname); truncsp(regcode);
	strcat(name, "\n"); strcat(bbsname, "\n"); strcat(regcode, "\n");

	fclose(regfile);
	len = strlen(name)-1;
	len1 = strlen(bbsname)-1;
	len2 = len+len1;
	len2 = len2+( (atol(name) + 9) * (atol(bbsname) + 3) );
	len2 = len2*105;
	len2 = len2*34;

	for(index = 0 ; index <= len ; index++)
	{
		temp = name[index];
		namecode = namecode + temp;
	}
	temp = 0;
	for(index = 0 ; index <= len1 ; index++)
	{
		temp = bbsname[index];
		bbscode = bbscode + temp;
	}
	namecode = namecode -  10;
	bbscode =  bbscode - 10;
	x = ((namecode*len)+(bbscode));
	x = x*len2;
	ltoa(x, t, 10);
	regcode[strlen(regcode)-1]=0;
	truncsp(regcode);
	if (strcmp(regcode, t)==0)
		return(0);
	else
		return(1);

}

int registered4(void)
{

	long  namecode = 0, bbscode = 0, x, index, len, len1, len2;
	char t[256], temp;
	char name[256], bbsname[256], regcode[256];
	FILE *regfile;
	int handle;

	handle = nopen("SYNCCHAT.CFG", O_RDONLY);
  regfile = fdopen(handle, "rb");
	if(regfile == NULL)
		return(0);

	fgets(name, 256, regfile);
	fgets(bbsname, 256, regfile);
	fgets(regcode, 256, regfile);
	truncsp(name); truncsp(bbsname); truncsp(regcode);
	strcat(name, "\n"); strcat(bbsname, "\n"); strcat(regcode, "\n");

	fclose(regfile);
	len = strlen(name)-1;
	len1 = strlen(bbsname)-1;
	len2 = len+len1;
	len2 = len2+( (atol(name) + 9) * (atol(bbsname) + 3) );
	len2 = len2*105;
	len2 = len2*34;

	for(index = 0 ; index <= len ; index++)
	{
		temp = name[index];
		namecode = namecode + temp;
	}
	temp = 0;
	for(index = 0 ; index <= len1 ; index++)
	{
		temp = bbsname[index];
		bbscode = bbscode + temp;
	}
	namecode = namecode -  10;
	bbscode =  bbscode - 10;
	x = ((namecode*len)+(bbscode));
	x = x*len2;
	ltoa(x, t, 10);
	regcode[strlen(regcode)-1]=0;
	truncsp(regcode);
	if (strcmp(regcode, t)==0)
		return(0);
	else
		return(1);

}

int registered5(void)
{

	long  namecode = 0, bbscode = 0, x, index, len, len1, len2;
	char t[256], temp;
	char name[256], bbsname[256], regcode[256];
	FILE *regfile;
	int handle;

	handle = nopen("SYNCCHAT.CFG", O_RDONLY);
  regfile = fdopen(handle, "rb");
	if(regfile == NULL)
		return(0);

	fgets(name, 256, regfile);
	fgets(bbsname, 256, regfile);
	fgets(regcode, 256, regfile);
	truncsp(name); truncsp(bbsname); truncsp(regcode);
	strcat(name, "\n"); strcat(bbsname, "\n"); strcat(regcode, "\n");

	fclose(regfile);
	len = strlen(name)-1;
	len1 = strlen(bbsname)-1;
	len2 = len+len1;
	len2 = len2+( (atol(name) + 9) * (atol(bbsname) + 3) );
	len2 = len2*105;
	len2 = len2*34;

	for(index = 0 ; index <= len ; index++)
	{
		temp = name[index];
		namecode = namecode + temp;
	}
	temp = 0;
	for(index = 0 ; index <= len1 ; index++)
	{
		temp = bbsname[index];
		bbscode = bbscode + temp;
	}
	namecode = namecode -  10;
	bbscode =  bbscode - 10;
	x = ((namecode*len)+(bbscode));
	x = x*len2;
	ltoa(x, t, 10);
	regcode[strlen(regcode)-1]=0;
	truncsp(regcode);
	if (strcmp(regcode, t)==0)
		return(0);
	else
		return(1);

}

void registered6(void)
{

	long  namecode = 0, bbscode = 0, x, index, len, len1, len2;
	char t[256], temp;
	char name[256], bbsname[256], regcode[256];
	FILE *regfile;
	int handle;

	handle = nopen("SYNCCHAT.CFG", O_RDONLY);
  regfile = fdopen(handle, "rb");
	if(regfile == NULL)
		{
		reged = 0;
		return;
		}
	fgets(name, 256, regfile);
	fgets(bbsname, 256, regfile);
	fgets(regcode, 256, regfile);
	truncsp(name); truncsp(bbsname); truncsp(regcode);
	strcat(name, "\n"); strcat(bbsname, "\n"); strcat(regcode, "\n");

	fclose(regfile);
	len = strlen(name)-1;
	len1 = strlen(bbsname)-1;
	len2 = len+len1;
	len2 = len2+( (atol(name) + 9) * (atol(bbsname) + 3) );
	len2 = len2*105;
	len2 = len2*34;

	for(index = 0 ; index <= len ; index++)
	{
		temp = name[index];
		namecode = namecode + temp;
	}
	temp = 0;
	for(index = 0 ; index <= len1 ; index++)
	{
		temp = bbsname[index];
		bbscode = bbscode + temp;
	}
	namecode = namecode -  10;
	bbscode =  bbscode - 10;
	x = ((namecode*len)+(bbscode));
	x = x*len2;
	ltoa(x, t, 10);
	regcode[strlen(regcode)-1]=0;
	truncsp(regcode);
	if (strcmp(regcode, t)==0)
		reged = 1;
	else
		reged = 0;
}

void space(int n)
/* Prints 'n' spaces */
{
	int i;

	if(n < 1) return;
	for(i = 0; i < n; i++)
		bputs(" ");
}

char *full_name(char *s)
/* Given a string such as "Pro", if "Prophet" is online and in cur channel*/
/* this function'll return "Prophet".  If not, it returns NULL.           */
{
	int i;
	char strl[256], save[256];

	memset(strl, 0, 256);
	strcpy(save, s);

	for(i=1;i<=sys_nodes;i++) {
		if(in_telecon(i)) {
			memset(generic_buf, 0, 512);
			strcpy(generic_buf, who_is_on_node(i));
			strcpy(strl, generic_buf);
			if(strstr(strlwr(strl), strlwr(s)) != NULL)
				return(generic_buf); }
		}
	strcpy(s, save);
	return(NULL);
}

char *full_name2(char *s)
/* Given a string such as "Pro", if "Prophet" is online, it'll return     */
/* "Prophet".	 Works across ALL channels.                                 */
{
	int handle;
	char strl[50], user_number[10];
	FILE *stream;

	handle = nopen("ROOMS.LST", O_RDONLY);
	if(handle == -1)
		{
		bputs("Error opening ROOMS.LST in full_name2().\r\n");
		return(NULL);
		}
	lseek(handle, 0L, SEEK_SET);
	while(!eof(handle)) {
		memset(generic_buf, 0, 512);
    read(handle, generic_buf, sizeof(user_name));
		//read(handle, &user_number, 10); /* Read in just for simplicity */
		truncsp(generic_buf);
		strcpy(strl, generic_buf);
		if(strstr(strlwr(strl), s) != NULL) {
			close(handle);
			return(generic_buf); }
		}
	close(handle);
	return(NULL);
}


char* rollover(char *s)
/* This function will modify the string passed, and then return it.
	 What it basicly does is insert a '\r\n' into a string that is about to
	 run off the screen (screen wrap basically).  When the '\r\n' is insterted,
	 the string will no longer run off the screen, but appear on the next line
	 when printed.  Works up to 3 lines.
*/
{
	int i, n = 0, j = 0; /* i for a counter, n for counting CTRL-A's */
	char *s_alias, tmparray[256], tmp[1];

	while(j < 237) {
	j += 79;
	if(bstrlen(s) < j) return(s);
	if(s[strlen(s)] == ' ') return(s);
	s_alias = s;
	for(i = (j - 79); s_alias[i] != '\0'; i++) {
		if(s_alias[i] == 1)
			{ n++; n++; i++; } }
	s_alias = s; /* Refresh s_alias */
	tmp[0] = s[j + n]; s[j + n] = 0; /* Start chopping string */
	if( (s_alias = strrchr(s, ' ')) == NULL) {
		s[j + n] = tmp[0]; /* Repair string :) */
		return(s); /* No spaces in string, so just return string untouched. */
	} else {
		s[j + n] = tmp[0];
		strcpy(tmparray, (s_alias + 1)); /* tmparray contains chopped string */
		s_alias[0] = '\r'; s_alias[1] = '\n'; /* Insert CR/LF into orig string */
		for(i = 2; i <= (strlen(tmparray) + 2); i++)
			s_alias[i] = tmparray[i - 2];
		s_alias[i + 1] = 0;
	 /*	return(s);*/ }
	}
	return(s);
/* Whatta function!! ;) */
/* Just look at how little space it took up, but does so much! ;) */
/* Yes, I compressed it on purpose to make it complicated... =] */
}

/* Prints 'buf' to all ops (users with 90 or higher user level) */
/* Usefull for SysOps to see whispers. */
void print_to_ops(char *buf, char *fname)
	{
	int i, k, handle;
	char name[30], j[3], tmp[512];
	node_t node;
	FILE *stream;

	for(i=1;i<=sys_nodes;i++)
	{
    if(i==node_num)
      continue;
		if(!in_telecon(i))
			continue;
		sprintf(tmp, "%sON.%i", snc_dir, i);
		handle = nopen(tmp, O_RDONLY);
    stream = fdopen(handle, "rb");
		fgets(name, 30, stream);
		truncsp(name);
		fgets(j, 7, stream);
		truncsp(j);
		fclose(stream);
		if(strcmpi(name, fname) == 0)
			continue;
		/* bprintf("\r\nj = %s\r\n", j); */
		k = atoi(j);
		/* bprintf("\r\nk = %i\r\n", k); */
    if(k < sysop_level)
			continue;
		/* bprintf("\r\npast continue onto getnodedat!!\r\n"); */
    /* getnodedat(i,&node,0); */
/*		if(node.status==NODE_INUSE || (SYSOP && node.status==NODE_QUIET))*/
			scputnmsg(i,buf);
		}
	}

void removefrom_rooms_lst(void)
{
	int i, handle, match = 0;
	long offset;
//	char **names;
//	FILE *stream;
	char name[45], user_number[10];

	memset(user_number, 0, 10);
	memset(name, 0, 45);
	handle = nopen("ROOMS.LST", O_RDWR);
	if(handle == -1)
		{
		bprintf("Error removing name from ROOMS.LST\r\n");
		pause();
		return;
		}
	do { /* Search for where name is */
		//read(handle, &name, sizeof(user_name)); 08-28
		read(handle, name, sizeof(user_name));
		//read(handle, &user_number, 10); 08-28
		read(handle, user_number, 10);
		truncsp(name);
		/* bprintf("\r\nname = %s", name);
		bprintf("\r\nuser_name = %s", user_name);
		pause(); */
		if(strcmpi(user_name, name) == 0) /* We found it */
			{
			match = 1;
			offset = tell(handle);
			break;
			}
		} while(!eof(handle));
	if(match == 0)	/* Name was not found in ROOMS.LST! */
		{
		/* bprintf("\r\nno match!\r\n"); pause(); */
		return;
		}
	memset(name, 0, 45); memset(user_number, 0, 10); /* Blank vars */
	lseek(handle, offset - 55, SEEK_SET); /* Go back to beginning of name */
	write(handle, &name, sizeof(user_name)); /* Write blank (empty) data
																					 /* (hence, "erase") */
	write(handle, &user_number, 10);
	/* Packing... */
	while(!eof(handle)) {
		offset = tell(handle);
		read(handle, name, sizeof(user_name));
		//read(handle, &name, sizeof(user_name)); 08-28
		//read(handle, &user_number, 10); 08-28
		read(handle, user_number, 10);
		lseek(handle, offset - (sizeof(user_name) + 10), SEEK_SET);
		write(handle, &name, sizeof(user_name));
		write(handle, &user_number, 10);
		read(handle, name, sizeof(user_name));
		//read(handle, &name, sizeof(user_name)); 08-28
		read(handle, user_number, 10); 
		//read(handle, &user_number, 10); 08-28
		}
	/* Clip end of file */
	if(chsize(handle, filelength(handle) - 55) != 0)
		{
		bprintf("Erroring resizing ROOMS.LST\r\n");
		pause();
		}
	close(handle);
}

void cleanup(void)
{
	int k, attrib;
	char buff[256], uls[9], dir[256], s[256];
	struct stat statbuf;

	fprintf(stderr, "%s|%i|%c\n", BACKSLASH, snc_dir,user_number);

	if((alone()) && (toggles[DELETE_TOPIC] == '1')
		) /* These 2 little lines take care of what Dink and Etherius */
		delete_topic(); /* keep bitching about!! ;) I think it's pretty */
										/* self-explanatory!! ;) */

//  get_me(); /* Get all waiting messages so they are deleted. */
//  get_me();
  delete_snc_file();
  del_invite_file();

	/* Handles Exit Messages =] */
	get_e_msgs();
	if(exit_msg[0])
		{
		strcat(exit_msg, "\r\n");
		printall(exit_msg);
		}
	else
		{
		sprintf(buff, l31, user_name);
		printall(buff);
		}

	goto_main(0,0,0);
	if(fexist(onfile)) /* Make sure onfile is 'deletable' before deleting it */
		{
    do { 
			stat(onfile, &statbuf);
		} while(!(statbuf.st_mode & S_IWRITE));
    unlink(onfile); /* Change this */
		}
	itoa(user_number, uls, 10);
	if(isdigit(snc_dir[strlen(snc_dir) - 2]))
		{
		snc_dir[strlen(snc_dir) - 1] = 0;
		strcpy(dir, strrchr(snc_dir, BACKSLASH));
		for(k = 0; k <= strlen(dir); k++)
			dir[k] = dir[k + 1];
		#ifdef __unix__
		strcat(snc_dir, "/");
		#else
		strcat(snc_dir, "\\");
		#endif
		if(strcmpi(uls, dir) == 0)
			{
			sprintf(buff, "%sTOPIC.TXT", snc_dir, node_num);
			if(fexist(buff)) /* Make sure onfile is 'deletable' before deleting it */
				{
				do {
					stat(buff, &statbuf);
				} while(!(statbuf.st_mode & S_IWRITE));
				unlink(buff);
				}
			/* printall("\r\n"); */
			printall("Ÿ›‘¬‡"); /* Secret!! ;) */
			}
		do {
			snc_dir[strlen(snc_dir) - 1] = 0;
		} while(snc_dir[strlen(snc_dir) - 1] != BACKSLASH);
		sprintf(buff, "%s%i%cTOPIC.TXT", BACKSLASH, snc_dir, user_number);
		if(fexist(buff)) /* Make sure onfile is 'deletable' before deleting it */
			{
			do {
				stat(buff, &statbuf);
			} while(!(statbuf.st_mode & S_IWRITE));
			unlink(buff);
			}
		strcpy(buff, snc_dir);
		strcat(buff, uls);
		#ifdef __unix__
		strcat(buff, "/"); /* !!! */
		#else
		strcat(buff, "\\"); /* !!! */
		#endif
		strcpy(snc_dir, buff);
		printall("Ÿ›‘¬‡"); /* Secret!! ;) */
		buff[strlen(buff) - 1] = 0;
		k = rmdir(buff);
		if(k == -1) {}
			/* perror("Error"); Remember we don't echo this anymore because someone
													may still be in the channel in which case the dir
													would NOT have been removed correctly.  If all goes
													well, the dir should be removed by THAT PERSON. */
		}
	else
		{
						
		sprintf(buff, "%s%i%cTOPIC.TXT", BACKSLASH, snc_dir, user_number);
		if(fexist(buff)) /* Make sure onfile is 'deletable' before deleting it */
			{
			do {
				stat(buff, &statbuf);
			} while(!(statbuf.st_mode & S_IWRITE));
			unlink(buff);
			}
		strcpy(buff, snc_dir);
		strcat(buff, uls);
		if(buff[strlen(buff) - 1] != BACKSLASH)
			buff[strlen(buff) - 1] = BACKSLASH;
			//strcat(buff, "\\"); /* !!! */
		strcpy(snc_dir, buff);
		printall("Ÿ›‘¬‡"); /* Secret!! ;) */
		buff[strlen(buff) - 1] = 0;
		k = rmdir(buff);
		/*bprintf(buff); Test code */
		if(k == -1) {}
			/* perror("Error"); See above */
		}
	/* kill_room(cur_room_num, snc_dir); */
	free_actions();
	for(k = 0; k < num_of_rooms; k++)
		FREE(channel[k]);
	for(k = 0; k < num_of_games; k++)
		FREE(games[k]);
	free_strings();
	removefrom_rooms_lst();
	delete_forget_file();

/** Add to log **/
	sprintf(s, "%s left SyncChat.\r\n", user_name);
	add_to_log(s);
/****************/

	#ifndef SYNC_SPECIFIC
	x00_deinit(com_port);
	#endif
}

void whosin_cur_room(void)
{
	int k = 0, i;
	char *buf1, *buf2, *buf3, *buf4, *s, str[256];

	if((buf1 = (char*) MALLOC(1024)) == NULL)
		{
		bputs("Error: Out Of Memory [buf1 = whosin_cur_room]");
		exit(2);
		}
	if((buf2 = (char*) MALLOC(1024)) == NULL)
		{
		bputs("Error: Out Of Memory [buf2 = whosin_cur_room]");
		exit(2);
		}
	if((buf4 = (char*) MALLOC(100)) == NULL)
		{
		bputs("Error: Out Of Memory [buf4 = whosin_cur_room]");
		exit(2);
		}
	if((s = (char *) MALLOC(256)) == NULL)
		{
		bputs("Error: Out Of Memory [s = whosin_cur_room]");
		exit(2);
		}

	memset(buf1, 0, 1024);
	memset(buf2, 0, 1024);
	memset(buf4, 0, 100);
	memset(s, 0, 256);

	for(i=1;i<=sys_nodes;i++) {
		if(i==node_num)
			continue;
		if(in_telecon(i)) {
			k++;
			if (k==1) {
				sprintf(buf1, "%s%s", l21, who_is_on_node(i)); }
			if (k > 1) {
				if(k > 2) {
					sprintf(s, " %sand", l22);
					buf3 = strstr(buf1, s);
					sprintf(buf3, "%s, %s%s", l22, l21, buf4); }
				strcpy(buf4, who_is_on_node(i));
				sprintf(buf2, " %sand %s%s", l22, l21, who_is_on_node(i));
				strcat(buf1, buf2); }
		}
	}
	if (k==0)
		bputs(l3);
	if (k==1) {
		strcat(buf1, l24);
		bputs(buf1); CRLF;
	}
	if (k>1) {
		strcat(buf1, l23);
		bputs(buf1); CRLF;
	}
	buf1[0] = 0; buf2[0] = 0; buf4[0] = 0; s[0] = 0;
	k = 0;
	for(i=1;i<=sys_nodes;i++) {
		if(i==node_num)
			continue;
		sprintf(str, "%sGONE.%i", snc_dir, i);
		if(fexist(str)) {
			k++;
			if (k==1) {
				sprintf(buf1, "%s%s", l48, who_is_on_node(i)); }
			if (k > 1) {
				if(k > 2) {
					sprintf(s, " %sand", l49);
					buf3 = strstr(buf1, s);
					sprintf(buf3, "%s, %s%s", l49, l48, buf4); }
				strcpy(buf4, who_is_on_node(i));
				sprintf(buf2, " %sand %s%s", l49, l48, who_is_on_node(i));
				strcat(buf1, buf2); }
		}
	}
	if (k==1) {
		strcat(buf1, l51);
		bputs(buf1);
		CRLF;
	}
	if (k>1) {
		strcat(buf1, l50);
		bputs(buf1);
	CRLF;
	}
	FREE(buf1); FREE(buf2); FREE(buf4); FREE(s);
}

void print_topic(char* str)
{
	char s[81], topic[80];
	int handle;
	FILE *stream;

	sprintf(s, "%sTOPIC.TXT", snc_dir);
	if(fexist(s)) {
		handle = nopen(s, O_RDONLY);
    stream = fdopen(handle, "rb");
		if(stream == NULL) {
			perror("Error [TOPIC.TXT]");
			cleanup();
			exit(1); }
		fgets(topic, 80, stream);
		fclose(stream);
		truncsp(topic);
		bputs(str);
		bputs(" ");
		bputs(topic); }
	else
		bputs(l14);
	CRLF;
}

void change_topic(void)
{
	char s[256], topic[79];
	int handle;
	FILE *stream;

	CRLF;
	bprintf(l17);
	bprintf(l18);
	if(getstr(topic, 79, K_MSG|K_LOWPRIO))
		{
		sprintf(s, "%sTOPIC.TXT", snc_dir);
		if(fexist(s))
			handle = nopen(s, O_WRONLY|O_TRUNC);
		else
			handle = nopen(s, O_WRONLY|O_CREAT);
    stream = fdopen(handle, "wb");
		fputs(topic, stream);
		fclose(stream);
		CRLF;
		bprintf(l16);
		bprintf(topic);
		CRLF;
		sprintf(s, l34, user_name);
		printall(s);
		printall(topic);
		printall("\r\n");
		}
}

void goto_main(int print_boot_msg, int print_header, int del_priv_dir)
{
	int j;
	char old_dir[256], str[256], s[256], s2[256], s3[256];

	if(cur_room_num != -1)
		{
		if((alone()) && (toggles[DELETE_TOPIC] == '1')) /* These 2 little lines take care of what Dink and Etherius */
			delete_topic(); /* keep bitching about!!! ;) */
		if(cur_room_num == 0) /* Already in Main :) */
			return;
		strcpy(s, channel[cur_room_num]->dir);
		if(s[strlen(s) - 1] != BACKSLASH)
			s[strlen(s) - 1] = BACKSLASH;
			//strcat(s, "\\");
		sprintf(s2, "ON.%i", node_num); /* s2 = ON.3 */
		strcat(s, s2); /* s = E:\CHAN1\ON.3 */
		strcpy(s3, snc_root); /* s3 = E:\ */
		strcpy(snc_dir, s3);
		strcat(s3, s2); /* s3 = E:\ON.3 */
		if(rename(s, s3) != 0)
			{
			perror("Error");
			cleanup();
			exit(1);
			}
		strcpy(onfile, s3);
		/*bprintf("\r\nonfile = %s", onfile); Test code
		bprintf("\r\nsnc_dir = %s\r\n", snc_dir); */
		if(print_header)
			{
			bprintf(l11, channel[cur_room_num]->name);
			print_topic(l15);
			whosin_cur_room();
			}
		cur_room_num = 0;
		return;
		}
	else
		{
		if((alone()) && (toggles[DELETE_TOPIC] == '1')) /* These 2 little lines take care of what Dink and Etherius */
			delete_topic(); /* keep bitching about!!! ;) */
		strcpy(s, snc_dir);
		strcpy(s3, snc_dir);
		s[strlen(s) - 1] = 0;
		strcpy(s2, strrchr(s, BACKSLASH));
		for(j = 0; j <= strlen(s2); j++)
			s2[j] = s2[j + 1];
		strcpy(old_dir, snc_dir);
		sprintf(str, "ON.%i", node_num);
		strcat(old_dir, str);
		if(isdigit(snc_dir[strlen(snc_dir) - 2]))
			{
			snc_dir[strlen(snc_dir) - (strlen(s2) + 1)] = 0;
			sprintf(str, "%sON.%i", snc_dir, node_num);
			strcpy(onfile, str);
			if(rename(old_dir, str) != 0)
				{
				perror("Error");
				cleanup();
				exit(1);
				}
			cur_room_num = 0;
			s3[strlen(s3) - 1] = 0;
			/* sprintf(str, "dir %s", s3);
			system(str); */
			if(del_priv_dir)
				rmdir(s3); /* Attempts to remove the private channel (directory)!! */
			if(print_boot_msg)
				bprintf(l32);
			if(print_header)
				{
				bprintf(l11, channel[cur_room_num]->name);
				print_topic(l15);
				whosin_cur_room();
				}
			}
		/* cur_room_num = -1; bug ??? */
		}
}

void play_games(void)
{
  #ifdef __WATCOMC__
  unsigned drive, total;
  #endif

	int k, i = 0, result;
	char *path, *dir, *s, *str;

	path = (char *) MALLOC(256);
	dir = (char *) MALLOC(256);
	s = (char *) MALLOC(256);
	str = (char *) MALLOC(3);

	strcpy(path, "X:\\");      /* fill string with form of response: X:\ */
  #ifdef __TURBOC__
	path[0] = 'A' + getdisk();    /* replace X with current drive letter */
  #endif
  #ifdef __WATCOMC__
  _dos_getdrive(&drive);
  path[0] = 'A' + (drive - 1);
  #endif

  #ifdef __TURBOC__
	getcurdir(0, path+3);  /* fill rest of string with current directory */
	#endif

  #ifdef __WATCOMC__
  if(getcwd(path,256) == NULL)
    {
		perror("Error");
		cleanup();
    exit(1);
		}
  #endif

	/* bprintf("\r\npath==%s", path); // !!! test code !!! */
	/* path[strlen(path) - 1] = 0;
	if(path[strlen(path) - 1] == ':')
		strcat(path, "\\"); */
	bputs(l45);
	CRLF;
	for(k = 0; ((games[k]->exec[0] != 0) && (k < num_of_games)); k++)
		{
		if(registered4() && (k >= 2) && (reged))
			break;
		sprintf(s, l46, k + 1, games[k]->display);
		bputs(s);
		}
	CRLF;
	bputs(l47);
	if(!getstr(str,3,K_NUMBER))
		return;
	i = atoi(str);
	/* bprintf("\r\n i == %i\r\n", i); !!! test code !!! */
	if((i <= 0) || (i > k))
		return;
	strcpy(s, games[i - 1]->exec);
	while(s[strlen(s) - 1] != BACKSLASH)
		s[strlen(s) - 1] = 0;
	s[strlen(s) - 1] = 0;
	/* return; test code */
	/* bprintf("\r\ns == %s", s); !!! test code !!! */

  #ifdef __TURBOC__
	setdisk(toupper(s[0]) - 'A');
  #endif

  #ifdef __WATCOMC__
  _dos_setdrive(toupper(s[0]) - 'A', &total);
	#endif

	/* bprintf("\r\ntoupper(s[0]) == %c", toupper(s[0])); !!! test code !!! */
	if(s[strlen(s) - 1] == ':')
    s[strlen(s) - 1] = BACKSLASH;
		//strcat(s, "\\");
	if(chdir(s) == -1)
		{
		bprintf("Error: No Such File or Directory"); CRLF;
		bprintf("Please tell the SysOp!"); CRLF;

    #ifdef __TURBOC__
		setdisk(toupper(path[0]) - 'A');
		#endif

    #ifdef __WATCOMC__
		_dos_setdrive(toupper(path[0]) - 'A', &total);
		#endif

		return;
		}
	/* bprintf("\r\ngames[i - 1].exec == %s", games[i - 1].exec);
	bprintf("\r\ncurrent drive == %c", getdisk() + 'A'); !!! test code !!!
	pause(); */
	delete_onfile();
	create_gonefile();
	sprintf(s, l52, user_name, games[i - 1]->display);
	printall(s);
//	free_actions(); free_strings(); /* Free up some memory */
	system(games[i-1]->exec);
/*	result = spawnle(P_WAIT, games[i-1].exec, NULL, environ);
	if (result == -1)
	{
		perror("Error from spawnle"); CRLF;
		pause();
		FREE(path); FREE(dir); FREE(s); FREE(str);
		cleanup();
		exit(1);
	}*/
//	get_strings(); get_actions(); /* Read back in free'd data :) */
	delete_gonefile();
	create_onfile();
	/* bprintf("\r\nYou would be running game: %s", games[i - 1].exec);
	!!! test code !!! */

	#ifdef __TURBOC__
	setdisk(toupper(path[0]) - 'A');
	#endif

  #ifdef __WATCOMC__
	_dos_setdrive(toupper(path[0]) - 'A', &total);
  #endif

	chdir(path);
	sprintf(s, l53, user_name, games[i - 1]->display);
	printall(s);
	FREE(path); FREE(dir); FREE(s); FREE(str);
	cls();
}

void create_onfile(void)
{
	char uls[9];
  int handle, tmp;
	FILE *stream;

	/* Create ON.? file */
	sprintf(onfile, "%sON.%i", snc_dir, node_num);
	handle = nopen(onfile, O_WRONLY|O_CREAT);
  stream = fdopen(handle, "wb");
	if(stream == NULL) {
		perror("Error [ON. (create_onfile())]");
		cleanup();
		exit(1); }
	fputs(user_name, stream);
	fputs("\r\n", stream);
  itoa(user_level, uls, 10);
  fputs(uls, stream);
	fputs("\r\n", stream);
	itoa(user_number, uls, 10);
	fputs(uls, stream);
	fclose(stream);
}

void create_gonefile(void)
{
	char uls[9], s[256];
	int handle;
	FILE *stream;

	/* Create GONE.? file */
	sprintf(s, "%sGONE.%i", snc_dir, node_num);
	handle = nopen(s, O_WRONLY|O_CREAT);
  stream = fdopen(handle, "wb");
	if(stream == NULL) {
		perror("Error");
		cleanup();
		exit(1); }
	fputs(user_name, stream);
	fputs("\r\n", stream);
	itoa(user_level, uls, 10);
	fputs(uls, stream);
	fputs("\r\n", stream);
	itoa(user_number, uls, 10);
	fputs(uls, stream);
	fclose(stream);
}

void delete_gonefile(void)
{
	char s[256];
	struct stat statbuf;

	sprintf(s, "%sGONE.%i", snc_dir, node_num);
	if(fexist(s)) /* Make sure onfile is 'deletable' before deleting it */
		{
		do {
			stat(s, &statbuf);
		} while(!(statbuf.st_mode & S_IWRITE));
		unlink(s);
		}
}

void delete_onfile(void)
{
	char s[256];
	struct stat statbuf;

	sprintf(s, "%sON.%i", snc_dir, node_num);
	if(fexist(s)) /* Make sure onfile is 'deletable' before deleting it */
		{
		do {
			stat(s, &statbuf);
		} while(!(statbuf.st_mode & S_IWRITE));
		unlink(s);
		}
}

#ifdef __WATCOMC__

int alone(void)
{
	char str[256], of[256];
  struct find_t fileinfo;
  unsigned short done;

	strcpy(str, snc_dir);
	strcat(str, "ON.*");
	sprintf(of, "ON.%i", node_num);
	done = _dos_findfirst(str, _A_NORMAL, &fileinfo);
  if(strcmpi(fileinfo.name, of) == 0)
		{
    done = _dos_findnext(&fileinfo);
    if(errno == ENOENT)
      {
      #ifdef __OS2__
      _dos_findclose(&fileinfo);
      #endif
			return(1);
      }
		}
  #ifdef __OS2__
	_dos_findclose(&fileinfo);
  #endif
  return(0);
}

#else

int alone(void)
{
	char str[256], of[256];
	struct ffblk ffblk;
	int done;

	strcpy(str, snc_dir);
	strcat(str, "ON.*");
	sprintf(of, "ON.%i", node_num);
	done = findfirst(str,&ffblk,0);
	if(strcmpi(ffblk.ff_name, of) == 0)
		{
		done = findnext(&ffblk);
		if(done == -1)
			return(1);
		}
	return(0);
}

#endif

void free_actions(void)
{
	int k;

	if(num_of_actions > 0) {
		for(k = 0; k <= num_of_actions - 1; k++)
			FREE(action[k]); }
/*		bprintf("Freed %i (%i) actions", k+1, k); Test Code */
}

void free_strings(void)
{
	FREE(l1); FREE(l2); FREE(l3); FREE(l4); FREE(l5); FREE(l6); FREE(l7);
	FREE(l8); FREE(l9); FREE(l10); FREE(l11); FREE(l12); FREE(l13); FREE(l14);
	FREE(l15); FREE(l16); FREE(l17); FREE(l18); FREE(l19); FREE(l20); FREE(l21);
	FREE(l22); FREE(l23); FREE(l24); FREE(l25); FREE(l26); FREE(l27); FREE(l28);
	FREE(l29); FREE(l30); FREE(l31); FREE(l32); FREE(l33); FREE(l34); FREE(l35);
	FREE(l36); FREE(l37); FREE(l38); FREE(l39); FREE(l40); FREE(l41); FREE(l42);
	FREE(l43); FREE(l44); FREE(l45); FREE(l46); FREE(l47); FREE(l48); FREE(l49);
	FREE(l50); FREE(l51); FREE(l52); FREE(l53); FREE(l54); FREE(l55); FREE(l56);
	FREE(l57); FREE(l58); FREE(l59); FREE(l60);
	FREE(l61); FREE(l62); FREE(l63); FREE(l64); FREE(l65); FREE(l66);
	FREE(l67); FREE(l68); FREE(l69); FREE(l70);
	FREE(l71); FREE(l72); FREE(l73); FREE(l74); FREE(l75); FREE(l76);
	FREE(l77); FREE(l78); FREE(l79); FREE(l80);
	FREE(l81); FREE(l82); FREE(l83); FREE(l84); FREE(l85); FREE(l86);
	FREE(l87); FREE(l88); FREE(l89); FREE(l90);
	FREE(l91); FREE(l92); FREE(l93); FREE(l94); FREE(l95); FREE(l96);
	FREE(l97); FREE(l98); FREE(l99); FREE(l100);
  FREE(l101); FREE(l102); FREE(l103); FREE(l104); FREE(l105); FREE(l106);
  FREE(l107); FREE(l108); FREE(l109); FREE(l110);

}

void get_actions(void)
{
	int handle, j;
	FILE *stream;

	if(cur_room_num > -1)
		handle = nopen(channel[cur_room_num]->actions_file, O_RDONLY);
	else
		handle = nopen("ACTIONS.LST", O_RDONLY);

  stream = fdopen(handle, "rb");
	if(stream == NULL)
		{
		num_of_actions = 0;
		actions_on = 0;
		return;
		}

	if(stream != NULL) {
		j = 0;
		do
			{
			num_of_actions = j;
			assert(j < 500);
			if(action[j] == NULL) {
				if((action[j] =
					 (struct actions*) MALLOC(sizeof(struct actions))) == NULL)
					 {
					 bputs("Error: Out Of Memory");
					 exit(2);
					 }
				}
			if(!feof(stream))
				fgets(action[j]->action_word, 12, stream);
			if(!feof(stream))
				fgets(action[j]->response, 128, stream);
			if(!feof(stream))
				fgets(action[j]->others, 128, stream);
			if(!feof(stream))
				fgets(action[j]->all, 128, stream);
			if(!feof(stream))
				fgets(action[j]->reciever, 128, stream);
			truncsp(action[j]->action_word);
			truncsp(action[j]->response);
			truncsp(action[j]->others);
			truncsp(action[j]->all);
			truncsp(action[j]->reciever);
			j++;
			} while(!feof(stream));
		actions_on = 1;
		fclose(stream);
		}
}

void get_strings(void)
{
	int handle;
	FILE *stream;

	/* Allocate mem for strings */
	l1 = (char *) MALLOC(256);
	l2 = (char *) MALLOC(256);
	l3 = (char *) MALLOC(256);
	l4 = (char *) MALLOC(256);
	l5 = (char *) MALLOC(256);
	l6 = (char *) MALLOC(256);
	l7 = (char *) MALLOC(256);
	l8 = (char *) MALLOC(256);
	l9 = (char *) MALLOC(256);
	l10 = (char *) MALLOC(256);
	l11 = (char *) MALLOC(256);
	l12 = (char *) MALLOC(256);
	l13 = (char *) MALLOC(256);
	l14 = (char *) MALLOC(256);
	l15 = (char *) MALLOC(256);
	l16 = (char *) MALLOC(256);
	l17 = (char *) MALLOC(256);
	l18 = (char *) MALLOC(256);
	l19 = (char *) MALLOC(256);
	l20 = (char *) MALLOC(256);
	l21 = (char *) MALLOC(256);
	l22 = (char *) MALLOC(256);
	l23 = (char *) MALLOC(256);
	l24 = (char *) MALLOC(256);
	l25 = (char *) MALLOC(256);
	l26 = (char *) MALLOC(256);
	l27 = (char *) MALLOC(256);
	l28 = (char *) MALLOC(256);
	l29 = (char *) MALLOC(256);
	l30 = (char *) MALLOC(256);
	l31 = (char *) MALLOC(256);
	l32 = (char *) MALLOC(256);
	l33 = (char *) MALLOC(256);
	l34 = (char *) MALLOC(256);
	l35 = (char *) MALLOC(256);
	l36 = (char *) MALLOC(256);
	l37 = (char *) MALLOC(256);
	l38 = (char *) MALLOC(256);
	l39 = (char *) MALLOC(256);
	l40 = (char *) MALLOC(256);
	l41 = (char *) MALLOC(256);
	l42 = (char *) MALLOC(256);
	l43 = (char *) MALLOC(256);
	l44 = (char *) MALLOC(256);
	l45 = (char *) MALLOC(256);
	l46 = (char *) MALLOC(256);
	l47 = (char *) MALLOC(256);
	l48 = (char *) MALLOC(256);
	l49 = (char *) MALLOC(256);
	l50 = (char *) MALLOC(256);
	l51 = (char *) MALLOC(256);
	l52 = (char *) MALLOC(256);
	l53 = (char *) MALLOC(256);
	l54 = (char *) MALLOC(256);
	l55 = (char *) MALLOC(256);
	l56 = (char *) MALLOC(256);
	l57 = (char *) MALLOC(256);
	l58 = (char *) MALLOC(256);
	l59 = (char *) MALLOC(256);
	l60 = (char *) MALLOC(256);
	l61 = (char *) MALLOC(256);
	l62 = (char *) MALLOC(256);
	l63 = (char *) MALLOC(256);
	l64 = (char *) MALLOC(256);
	l65 = (char *) MALLOC(256);
	l66 = (char *) MALLOC(256);
	l67 = (char *) MALLOC(256);
	l68 = (char *) MALLOC(256);
	l69 = (char *) MALLOC(256);
	l70 = (char *) MALLOC(256);
	l71 = (char *) MALLOC(256);
	l72 = (char *) MALLOC(256);
	l73 = (char *) MALLOC(256);
	l74 = (char *) MALLOC(256);
	l75 = (char *) MALLOC(256);
	l76 = (char *) MALLOC(256);
	l77 = (char *) MALLOC(256);
	l78 = (char *) MALLOC(256);
	l79 = (char *) MALLOC(256);
	l80 = (char *) MALLOC(256);
	l81 = (char *) MALLOC(256);
	l82 = (char *) MALLOC(256);
	l83 = (char *) MALLOC(256);
	l84 = (char *) MALLOC(256);
	l85 = (char *) MALLOC(256);
	l86 = (char *) MALLOC(256);
	l87 = (char *) MALLOC(256);
	l88 = (char *) MALLOC(256);
	l89 = (char *) MALLOC(256);
	l90 = (char *) MALLOC(256);
	l91 = (char *) MALLOC(256);
	l92 = (char *) MALLOC(256);
	l93 = (char *) MALLOC(256);
	l94 = (char *) MALLOC(256);
	l95 = (char *) MALLOC(256);
	l96 = (char *) MALLOC(256);
	l97 = (char *) MALLOC(256);
	l98 = (char *) MALLOC(256);
	l99 = (char *) MALLOC(256);
  l100 = (char *) MALLOC(256);
  l101 = (char *) MALLOC(256);
  l102 = (char *) MALLOC(256);
  l103 = (char *) MALLOC(256);
  l104 = (char *) MALLOC(256);
  l105 = (char *) MALLOC(256);
  l106 = (char *) MALLOC(256);
  l107 = (char *) MALLOC(256);
  l108 = (char *) MALLOC(256);
	l109 = (char *) MALLOC(256);
  l110 = (char *) MALLOC(256);

/*************************************************************************/
/* Read in the STRINGS.DAT file                                          */
/*************************************************************************/
	if(fexist("STRINGS.DAT")) {
		handle = nopen("STRINGS.DAT", O_RDONLY);
		stream = fdopen(handle, "rb");
		if(stream == NULL) {
			perror("Error [STRINGS.DAT]"); CRLF;
			printf("Run SCONFIG->String Editor to automatically create a new STRINGS.DAT\r\n");
			cleanup();
			exit(1); }
		fgets(l1, 256, stream);
		fgets(l2, 256, stream);
		fgets(l3, 256, stream);
		fgets(l4, 256, stream);
		fgets(l5, 256, stream);
		fgets(l6, 256, stream);
		fgets(l7, 256, stream);
		fgets(l8, 256, stream);
		fgets(l9, 256, stream);
		fgets(l10, 256, stream);
		fgets(l11, 256, stream);
		fgets(l12, 256, stream);
		fgets(l13, 256, stream);
		fgets(l14, 256, stream);
		fgets(l15, 256, stream);
		fgets(l16, 256, stream);
		fgets(l17, 256, stream);
		fgets(l18, 256, stream);
		fgets(l19, 256, stream);
		fgets(l20, 256, stream);
		fgets(l21, 256, stream);
		fgets(l22, 256, stream);
		fgets(l23, 256, stream);
		fgets(l24, 256, stream);
		fgets(l25, 256, stream);
		fgets(l26, 256, stream);
		fgets(l27, 256, stream);
		fgets(l28, 256, stream);
		fgets(l29, 256, stream);
		fgets(l30, 256, stream);
		fgets(l31, 256, stream);
		fgets(l32, 256, stream);
		fgets(l33, 256, stream);
		fgets(l34, 256, stream);
		fgets(l35, 256, stream);
		fgets(l36, 256, stream);
		fgets(l37, 256, stream);
		fgets(l38, 256, stream);
		fgets(l39, 256, stream);
		fgets(l40, 256, stream);
		fgets(l41, 256, stream);
		fgets(l42, 256, stream);
		fgets(l43, 256, stream);
		fgets(l44, 256, stream);
		fgets(l45, 256, stream);
		fgets(l46, 256, stream);
		fgets(l47, 256, stream);
		fgets(l48, 256, stream);
		fgets(l49, 256, stream);
		fgets(l50, 256, stream);
		fgets(l51, 256, stream);
		fgets(l52, 256, stream);
		fgets(l53, 256, stream);
		fgets(l54, 256, stream);
		fgets(l55, 256, stream);
		fgets(l56, 256, stream);
		fgets(l57, 256, stream);
		fgets(l58, 256, stream);
		fgets(l59, 256, stream);
		fgets(l60, 256, stream);
		fgets(l61, 256, stream);
		fgets(l62, 256, stream);
		fgets(l63, 256, stream);
		fgets(l64, 256, stream);
		fgets(l65, 256, stream);
		fgets(l66, 256, stream);
		fgets(l67, 256, stream);
		fgets(l68, 256, stream);
		fgets(l69, 256, stream);
		fgets(l70, 256, stream);
		fgets(l71, 256, stream);
		fgets(l72, 256, stream);
		fgets(l73, 256, stream);
		fgets(l74, 256, stream);
		fgets(l75, 256, stream);
		fgets(l76, 256, stream);
		fgets(l77, 256, stream);
		fgets(l78, 256, stream);
		fgets(l79, 256, stream);
		fgets(l80, 256, stream);
		fgets(l81, 256, stream);
		fgets(l82, 256, stream);
		fgets(l83, 256, stream);
		fgets(l84, 256, stream);
		fgets(l85, 256, stream);
		fgets(l86, 256, stream);
		fgets(l87, 256, stream);
		fgets(l88, 256, stream);
		fgets(l89, 256, stream);
		fgets(l90, 256, stream);
		fgets(l91, 256, stream);
		fgets(l92, 256, stream);
		fgets(l93, 256, stream);
		fgets(l94, 256, stream);
		fgets(l95, 256, stream);
		fgets(l96, 256, stream);
		fgets(l97, 256, stream);
		fgets(l98, 256, stream);
		fgets(l99, 256, stream);
		fgets(l100, 256, stream);
    fgets(l101, 256, stream);
    fgets(l102, 256, stream);
    fgets(l103, 256, stream);
    fgets(l104, 256, stream);
    fgets(l105, 256, stream);
    fgets(l106, 256, stream);
		fgets(l107, 256, stream);
		fgets(l108, 256, stream);
    fgets(l109, 256, stream);
    fgets(l110, 256, stream);
		fclose(stream);
		truncsp(l1); truncsp(l2); truncsp(l3); truncsp(l4); truncsp(l5);
		truncsp(l6); truncsp(l7); truncsp(l8); truncsp(l9); truncsp(l10);
		truncsp(l11); truncsp(l12); truncsp(l13); truncsp(l14); truncsp(l15);
		truncsp(l16); truncsp(l17); truncsp(l18); truncsp(l19); truncsp(l20);
		truncsp(l21); truncsp(l22); truncsp(l23); truncsp(l24); truncsp(l25);
		truncsp(l26); truncsp(l27); truncsp(l28); truncsp(l29); truncsp(l30);
		truncsp(l31); truncsp(l32); truncsp(l33); truncsp(l34); truncsp(l35);
		truncsp(l36); truncsp(l37); truncsp(l38); truncsp(l39); truncsp(l40);
		truncsp(l41); truncsp(l42); truncsp(l43); truncsp(l44); truncsp(l45);
		truncsp(l46); truncsp(l47); truncsp(l48); truncsp(l49); truncsp(l50);
		truncsp(l51); truncsp(l52); truncsp(l53); truncsp(l54); truncsp(l55);
		truncsp(l56); truncsp(l57); truncsp(l58); truncsp(l59); truncsp(l60);
		truncsp(l61); truncsp(l62); truncsp(l63); truncsp(l64); truncsp(l65);
		truncsp(l66); truncsp(l67); truncsp(l68); truncsp(l69); truncsp(l70);
		truncsp(l71); truncsp(l72); truncsp(l73); truncsp(l74); truncsp(l75);
		truncsp(l76); truncsp(l77); truncsp(l78); truncsp(l79); truncsp(l80);
		truncsp(l81); truncsp(l82); truncsp(l83); truncsp(l84); truncsp(l85);
		truncsp(l86); truncsp(l87); truncsp(l88); truncsp(l89); truncsp(l90);
		truncsp(l91); truncsp(l92); truncsp(l93); truncsp(l94); truncsp(l95);
		truncsp(l96); truncsp(l97); truncsp(l98); truncsp(l99); truncsp(l100);
		truncsp(l101); truncsp(l102); truncsp(l103); truncsp(l104); truncsp(l105);
		truncsp(l106); truncsp(l107); truncsp(l108); truncsp(l109); truncsp(l110);
		if(l1 != NULL)
			strcat(l1, "\r\n");
		if(l2 != NULL)
			strcat(l2, "\r\n");
		if(l3 != NULL)
			strcat(l3, "\r\n");
		if(l4 != NULL)
			strcat(l4, "\r\n");
		if(l5 != NULL)
			strcat(l5, "\r\n");
		if(l6 != NULL)
			strcat(l6, "\r\n");
		if(l7 != NULL)
			strcat(l7, "\r\n");
		if(l8 != NULL)
			strcat(l8, "\r\n");
		if(l9 != NULL)
			strcat(l9, "\r\n");
		if(l10 != NULL)
			strcat(l10, "\r\n");
		if(l11 != NULL)
			strcat(l11, "\r\n");
		if(l12 != NULL)
			strcat(l12, "\r\n");
	//		strcat(l13, "\r\n");
	//		strcat(l14, "\r\n");
	//		strcat(l15, "\r\n");
	//    strcat(l16, "\r\n");
		if(l17 != NULL)
			strcat(l17, "\r\n");
	//    strcat(l18, "\r\n");
		if(l19 != NULL)
			strcat(l19, "\r\n");
		if(l20 != NULL)
			strcat(l20, "\r\n");
	//		strcat(l21, "\r\n");
	//		strcat(l22, "\r\n");
		if(l25 != NULL)
			strcat(l25, "\r\n");
		if(l26 != NULL)
			strcat(l26, "\r\n");
		if(l27 != NULL)
			strcat(l27, "\r\n");
		if(l28 != NULL)
			strcat(l28, "\r\n");
		if(l29 != NULL)
			strcat(l29, "\r\n");
		if(l30 != NULL)
			strcat(l30, "\r\n");
		if(l31 != NULL)
			strcat(l31, "\r\n");
		if(l32 != NULL)
			strcat(l32, "\r\n");
		if(l34 != NULL)
			strcat(l34, "\r\n");
		if(l35 != NULL)
			strcat(l35, "\r\n");
		if(l36 != NULL)
			strcat(l36, "\r\n");
		if(l37 != NULL)
			strcat(l37, "\r\n");
		if(l38 != NULL)
			strcat(l38, "\r\n");
		if(l39 != NULL)
			strcat(l39, "\r\n");
		if(l40 != NULL)
			strcat(l40, "\r\n");
		if(l41 != NULL)			strcat(l41, "\r\n");
		if(l42 != NULL)			strcat(l42, "\r\n");
		if(l43 != NULL)			strcat(l43, "\r\n");
		if(l45 != NULL)			strcat(l45, "\r\n");
		if(l46 != NULL)			strcat(l46, "\r\n");
		if(l52 != NULL)			strcat(l52, "\r\n");
		if(l53 != NULL)			strcat(l53, "\r\n");
		if(l54 != NULL)			strcat(l54, "\r\n");
		if(l55 != NULL)			strcat(l55, "\r\n");
		if(l58 != NULL)			strcat(l58, "\r\n");
		if(l59 != NULL)			strcat(l59, "\r\n");
		if(l60 != NULL)			strcat(l60, "\r\n");
		if(l61 != NULL)			strcat(l61, "\r\n");
		if(l63 != NULL)			strcat(l63, "\r\n");
		if(l64 != NULL)			strcat(l64, "\r\n");
		if(l65 != NULL)			strcat(l65, "\r\n");
		if(l66 != NULL)			strcat(l66, "\r\n");
		if(l71 != NULL)      strcat(l71, "\r\n");
		if(l72 != NULL)			strcat(l72, "\r\n");
		if(l76 != NULL)			strcat(l76, "\r\n");
		if(l77 != NULL)			strcat(l77, "\r\n");
		if(l79 != NULL)      strcat(l79, "\r\n");
		if(l80 != NULL)			strcat(l80, "\r\n");
		if(l81 != NULL)			strcat(l81, "\r\n");
		if(l82 != NULL)			strcat(l82, "\r\n");
		if(l83 != NULL)			strcat(l83, "\r\n");
		if(l84 != NULL)			strcat(l84, "\r\n");
		if(l85 != NULL)			strcat(l85, "\r\n");
		if(l86 != NULL)			strcat(l86, "\r\n");
		if(l87 != NULL)			strcat(l87, "\r\n");
		if(l88 != NULL)			strcat(l88, "\r\n");
		if(l89 != NULL)			strcat(l89, "\r\n");
		if(l90 != NULL)			strcat(l90, "\r\n");
		if(l91 != NULL)			strcat(l91, "\r\n");
		if(l92 != NULL)			strcat(l92, "\r\n");
		if(l93 != NULL)			strcat(l93, "\r\n");
		if(l94 != NULL)			strcat(l94, "\r\n");
		if(l95 != NULL)			strcat(l95, "\r\n");
		if(l96 != NULL)			strcat(l96, "\r\n");
		if(l97 != NULL)			strcat(l97, "\r\n");
		if(l98 != NULL)			strcat(l98, "\r\n");
		if(l99 != NULL)			strcat(l99, "\r\n");
		if(l100 != NULL)			strcat(l100, "\r\n");
		if(l101 != NULL)			strcat(l101, "\r\n");
		if(l102 != NULL)			strcat(l102, "\r\n");
		if(l103 != NULL)			strcat(l103, "\r\n");
		if(l104 != NULL)			strcat(l104, "\r\n");
		if(l105 != NULL)			strcat(l105, "\r\n");
		if(l106 != NULL)			strcat(l106, "\r\n");
		}
	else {
		strcpy(l1, "\1h\1wWelcome to SyncChat!\r\n");
		strcpy(l2, "\1h\1yÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\r\n\1w");
		strcpy(l3, "\1n\1gYou are currently alone.\r\n");
		strcpy(l4, "\1h\1cType \"?\" if you need help.\r\n");
		strcpy(l5, "\1_\1n\1gFrom %s\1h\1c: \1w%s\r\n");
		strcpy(l6, "\1_\1n\1gFrom %s (to %s)\1h\1c:\1w%s\r\n");
		strcpy(l7, "\1_\1n\1gFrom %s (to you)\1h\1c:\1w%s\r\n");
		strcpy(l8, "\1_\1n\1gFrom %s (whispered to you)\1h\1c:\1w%s\r\n");
		strcpy(l9, "\1_\1n\1gFrom %s (whispered to %s)\1h\1c:\1w%s\r\n");
		strcpy(l10, "\1nThere are no actions available.\r\n");
		strcpy(l11, "\1nYou are in the \1h\1c%s \1npublic channel.\r\n");
		strcpy(l12, "\1nYou are in your private channel.\r\n");
		strcpy(l13, "\1h\1mCurrent Topic\1w:\1c");
		strcpy(l14, "\1nThere is no topic for this room yet.");
		strcpy(l15, "\1h\1mTopic\1w:\1b");
		strcpy(l16, "\1n\1gTopic changed to\1h\1w: \1c");
		strcpy(l17, "\1h\1mEnter new topic\r\n");
		strcpy(l18, "\1h\1w:\1c");
		strcpy(l19, "\1nNo such channel.\r\n");
		strcpy(l20, "\1nYou are in \1h\1c%s\1n's private channel.\r\n");
		strcpy(l21, "\1h\1g");
		strcpy(l22, "\1n\1g");
		strcpy(l23, "\1n\1g are here with you.");
		strcpy(l24, "\1n\1g is here with you.");
		strcpy(l25, "\1h\1g%s \1n\1ghas entered.\r\n");
		strcpy(l26, "\1nIf you just type \1h\1b\"\1c%s\1b\"\1n, others will see this:\r\n");
		strcpy(l27, "\1nIf you type something like \1h\1b\"\1c%s SYSOP\1b\"\1n, others will see this:\r\n");
		strcpy(l28, "\1n%s is not in SyncChat.\r\n");
		strcpy(l29, "\1nNode %i doesn't exist!\r\n");
		strcpy(l30, "\1nNode %i is not in SyncChat.\r\n");
		strcpy(l31, "\1h\1g%s \1n\1ghas left.\r\n");
		strcpy(l32, "\1h\1ySwitching channels...\r\n");
		strcpy(l33, "\1h\1bChange Topic");
		strcpy(l34, "\1h\1b%s changed the topic of this channel to: \1c\r\n");
		strcpy(l35, "\1nYou are not in your private channel.\r\n");
		strcpy(l36, "You can't change the topic of this channel.");
		strcpy(l37, "\1h\1g%s \1n\1gleft the channel.\r\n");
		strcpy(l38, "\1h\1g%s \1n\1gentered the channel.\r\n");
		strcpy(l39, "\1n-- Message Sent --\r\n");
		strcpy(l40, "\1n-- Message Sent To %s --\r\n");
		strcpy(l41, "\1n-- Message Sent Only To %s --\r\n");
		strcpy(l42, "\1nYou are already in your private channel!\r\n");
		strcpy(l43, "\1nYou are already in \1h\1c%s\1n's private channel!\r\n");
		strcpy(l44, "\1h\1w:\1c");
		strcpy(l45, "\1h\1cGames:\1w\r\n");
		strcpy(l46, "\1n\1g[\1h\1c%i\1n\1g] \1h\1w%s\r\n");
		strcpy(l47, "\1h\1mSelection: \1h\1w");
		strcpy(l48, "\1n");
		strcpy(l49, "\1h\1k");
		strcpy(l50, "\1h\1k are off playing games.");
		strcpy(l51, "\1h\1k is off playing a game.");
		strcpy(l52, "\1h\1g%s \1n\1gwent off to play \1h\1w%s\1n\1g...\r\n");
		strcpy(l53, "\1h\1g%s \1n\1gis back from playing \1h\1w%s\1n\1g...\r\n");
		strcpy(l54, "\1nNo games available - Tell your SysOp to set a few up!\r\n");
		strcpy(l55, "\1nSorry, \"%s\" is not the User-ID of anyone present in SyncChat.\r\n");
		strcpy(l56, "\1_\1b\1h%s (Y/n) ? \1w");
		strcpy(l57, "\1_\1b\1h%s (y/N) ? \1w");
		strcpy(l58, "\1h\1wYou only have \1i\1h\1r%s\1n\1h\1w minutes left.\r\n");
		strcpy(l59, "\1h\1wYou only have \1i\1h\1r%s\1n\1h\1w minute left.\r\n");
		strcpy(l60, "\1h\1cPublic Channels:\r\n");
		strcpy(l61, "\1n\1g(\1h\1c%i\1n\1g) %s\r\n");
		strcpy(l62, "\1h\1wSelection: \1h\1y");
		strcpy(l63, "\1nYou cannot access that channel.\r\n");
		strcpy(l64, "\1h\1cNode   Username                    Location                           BPS\r\n");
		strcpy(l65, "\1h\1gÄÄ\1n\1gÄ\1h\1gÄ\1n\1gÄÄÄÄ\1h\1gÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\r\n");
		strcpy(l66, " \1h\1b%-5.5s\1h\1w%-27.27s\1y%-36.36s\1m%i\r\n");
    strcpy(l67, "\1h\1gCurrent Entry Message:\1n");
    strcpy(l68, "\1h\1gCurrent Exit Message:\1n");
    strcpy(l69, "\1nNone");
		strcpy(l70, "Would you like to edit your current Entry/Exit messages");
    strcpy(l71, "\1h\1cEnter New Entry Message\1n");
    strcpy(l72, "\1h\1cEnter New Exit Message\1n");
    strcpy(l73, "Save Changes");
		strcpy(l74, "ngNumber of node to send message to, whAngll, or whQnguit [%u]: wh");
		strcpy(l75, "_yhMessage: ");
		strcpy(l76, "\1h\1bTime Left (in minutes)\1c: \1w%i");
		strcpy(l77, "\1nIf you type \1h\1b\"\1c%s <your input here>\1b\"\1n, others will see this:\r\n");
		strcpy(l78, "\1n\1gNumber of node to send message to, or \1h\1wQ\1n\1guit : \1h\1w");
		strcpy(l79, "\1h\1c%s is now being ignored.\r\n");
		strcpy(l80, "\1h\1cYou will no longer recieve messages from this user.\r\n");
		strcpy(l81, "\1h\1cYou are no longer ignoring %s.\r\n");
		strcpy(l82, "\1h\1cUsername                            \1n... \1h\1wF I \1n... \1n\1gChannel (Topic)\r\n");
		strcpy(l83, "\1h\1bÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\r\n");
		strcpy(l84, "\1h\1y%-35s     %s       %s\r\n");
		strcpy(l85, "\1h\1y%-35s     %s       %s's Private Channel\r\n");
		strcpy(l86, "\1h\1y%-45s   (%s)");
		strcpy(l87, "\1h\1gF = User has been forgotten with the [F]orget command.\r\n");
		strcpy(l88, "\1h\1gI = User has been invited into your private channel.\r\n");
		strcpy(l89, "%s is now banned from your Private Channel.\r\n");
		strcpy(l90, "You have been invited to %s's Private Channel.\r\n");
		strcpy(l91, "You have not been invited into %s's Private Channel.\r\n");
		strcpy(l92, "You have been banned from %s's Private Channel.\r\n");
		strcpy(l93, "%s has been notified of your invitation.\r\n");
		}
}

char* scusername(int number)
/*
Returns the user name to 'number'.  Only works with users online.
Returns NULL if no name match found.
*/
{
	int handle;
	char unumber[10];

	handle = nopen("ROOMS.LST", O_RDONLY);
	if(handle == -1)
		{
		bprintf("Error opening ROOMS.LST in scusername()\r\n");
		pause();
		}
	do {
		memset(generic_buf, 0, 512);
		read(handle, generic_buf, sizeof(user_name));
		read(handle, unumber, 10);
		//read(handle, &unumber, 10); 08-28
		if(atoi(unumber) == number)
			{
			close(handle);
			return(generic_buf);
			}
	} while(!eof(handle));
	close(handle);
	return(0);
}

void del_prompt(void)
{
	int i;

	/* bprintf("\r\nIn del_prompt\r\n"); */
	if(toggles[CLEAR_PROMPT] == '1')
	{
	for(i = 0; i < bstrlen(l44); i++)
		bprintf("\b \b");
	}
}

void edit_e_msgs(void)
{
	char e_file[128];
	int fp;

	memset(entry_msg, 0, 128);
	memset(exit_msg, 0, 128);

	get_e_msgs();

  bputs(l67); bputs("\r\n");
  if(entry_msg[0] != 0)
    bputs(entry_msg);
  else
    bputs(l69);
  CRLF; CRLF;
  bputs(l68); bputs("\r\n");
  if(exit_msg[0] != 0)
    bputs(exit_msg);
  else
    bputs(l69);
  CRLF; CRLF;
  if(!noyes(l70))
    {
    CRLF;
    bputs(l71); bputs(l18);
		getstr(entry_msg, 120, K_EDIT|K_AUTODEL|K_LOWPRIO|K_MSG);
		CRLF;
    bputs(l72); bputs(l18);
    getstr(exit_msg, 120, K_EDIT|K_AUTODEL|K_LOWPRIO|K_MSG);
    if(yesno(l73))
			 write_e_msgs();
		}
}

void get_e_msgs(void)
{
  char e_file[128];
  int fp;

	memset(entry_msg, 0, 128);
	memset(exit_msg, 0, 128);

  _mkdir("EMSGS"); /* If dir already exists, nothing bad happens... */
  sprintf(e_file, "EMSGS%c%i.EM", BACKSLASH, user_number);
  if(fexist(e_file))
    {
    fp = nopen(e_file, O_RDONLY);
    if(fp == -1)
      bprintf("Error opening %s...\r\n", e_file);
    else
      {
      //read(fp, &entry_msg, 128); 08-28
      read(fp, entry_msg, 128);
      //read(fp, &exit_msg, 128); 08-28
      read(fp, exit_msg, 128);
      truncsp(entry_msg);
			truncsp(exit_msg);
			close(fp);
      }
    }
}

void write_e_msgs(void)
{
  char e_file[128];
  int fp;

  _mkdir("EMSGS"); /* If dir already exists, nothing bad happens... */
  sprintf(e_file, "EMSGS%c%i.EM", BACKSLASH, user_number);
  fp = nopen(e_file, O_WRONLY|O_CREAT);
  if(fp == -1)
    bprintf("Error opening %s...\r\n", e_file);
  else
    {
    write(fp, &entry_msg, 128);
    write(fp, &exit_msg, 128);
    truncsp(entry_msg);
    truncsp(exit_msg);
    close(fp);
    }
}

void delete_snc_file(void)
{
  char str[256];

  sprintf(str,"%sN%3.3u.SNC",snc_dir,node_num);
  if(fexist(str))
    unlink(str);
}
