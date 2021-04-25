/* TG.C - Includes functions for native SyncChat<->Telegard 3.0+ Interface
	 Created 6-4-96 by Prophet
*/

#include "xsdk.h"
#include "portable.h"
#include "telegard.h"

#define TELEGARD "3"
#define CLEAR_PROMPT 1

extern char  bbs_soft_dir[128], bbs_software[64], toggles[10];
extern char  *l64, *l65, *l66, *l75, *l78;
extern int   dots_again;

extern void pascaltoc_string(char *s);

void ctopascal_string(char *s)
{
	int len, i, j;

	len = strlen(s);
	i = 0; j = len;
	while(i <= len) {
		i++;
		s[j+1]= s[j];
		j--; }
	s[0] = len;
}

void tgwhos_online(int display_all)
{
	int f, node = 0;
	char s[256], node_s[32], bps[32];
	nodesrec nr;

	if(strcmpi(bbs_software, TELEGARD) != 0)
		return;
  sprintf(s, "%sNODES.DAT", bbs_soft_dir);
	f = nopen(s, O_RDONLY);
	if(f == -1)
		{
		bprintf("\r\nError opening %s\r\n", s);
		return;
		}
	bputs(l64);
	bputs(l65);
	do {
		node++;
		read(f, &nr, sizeof(nodesrec));
		itoa(node, node_s, 10);
		ltoa(nr.bpsrate, bps, 10);
		pascaltoc_string(nr.handle);
		pascaltoc_string(nr.status);
		if(strcmpi(bps, "0") == 0)
			strcpy(bps, "Local");
		switch (nr.statusid) {
			case 0: strcpy(nr.handle, "\1nWaiting for call");
							strcpy(nr.status, " "); strcpy(bps, " "); break;
			case 1: strcpy(nr.handle, "\1h\1kOffline");
							strcpy(nr.status, " "); strcpy(bps, " "); break;
			case 2: strcpy(nr.handle, "\1nRunning event...");
							strcpy(nr.status, " "); strcpy(bps, " "); break;
			case 4: strcpy(nr.handle, "\1h\1kWaiting for reset...");
							strcpy(nr.status, " "); strcpy(bps, " "); break;
			}
		if((nr.flags.ishidden == 1) && (!SYSOP)) {
			strcpy(nr.handle, "\1nWaiting for call");
			strcpy(nr.status, " "); strcpy(bps, " "); }
		sprintf(s, l66, node_s, nr.handle, nr.status, bps);
		bputs(s);
		} while( (!eof(f)) && (!(node >= sys_nodes)) );
  close(f);
}

long tg_whos_on_node(int nodenum)
/* Returns the user-ID of user on node 'nodenum' */
{
	char s[256];
	int f, node = 0;
	nodesrec nr;
	useridxrec uidxr;
	IDidxrec iidxr;

	if(strcmpi(bbs_software, TELEGARD) != 0)
		return -1;
  sprintf(s, "%sNODES.DAT", bbs_soft_dir);
	f = nopen(s, O_RDONLY);
	if(f == -1)
		{
		bprintf("\r\nError opening %s\r\n", s);
		return -1;
		}
	while((node < nodenum) && (!eof(f))) {
		node++;
		read(f, &nr, sizeof(nodesrec)); }
	close(f);
	pascaltoc_string(nr.handle);
	pascaltoc_string(nr.realname);
  sprintf(s, "%sUSERS.IDX", bbs_soft_dir);
	f = nopen(s, O_RDONLY);
	if(f == -1) {
		bprintf("\r\nError opening %s\r\n", s);
		return -1; }
	do {
		read(f, &uidxr, sizeof(useridxrec));
		pascaltoc_string(uidxr.name);
	} while( (strcmpi(nr.handle, uidxr.name) != 0) && (!eof(f)));
	close(f);
	if(strcmpi(nr.handle, uidxr.name) == 0) {
    sprintf(s, "%sUSERID.IDX", bbs_soft_dir);
		f = nopen(s, O_RDONLY);
		if(f == -1) {
			bprintf("\r\nError opening %s\r\n", s);
			return -1; }
		do {
			read(f, &iidxr, sizeof(IDidxrec));
			if(iidxr.number == uidxr.number)
				return(iidxr.userID);
		} while(!eof(f));
	}
	return -1;
}

void tgputnmsg(int node, char* message)
{
	char s[256];
	int f;
	long userIDX;
	shortmsgrec ssmr;

  sprintf(s, "%sINODE%d.DAT", bbs_soft_dir, node);
	f = nopen(s, O_WRONLY|O_APPEND|O_CREAT);
	if(f == -1) {
		bprintf("\r\nError opening %s\r\n", s);
		return; }
	userIDX = tg_whos_on_node(node);
	if(userIDX != -1) {
		ssmr.userid = userIDX;
		ctopascal_string(message);
		strcpy(ssmr.msg, message);
		ssmr.msgid = 0;
		write(f, &ssmr, sizeof(shortmsgrec));
	}
	close(f);
}

void tggetnmsg(void)
{
	char s[256];
	int f;
	long length;
	shortmsgrec ssmr;

  sprintf(s, "%sINODE%d.DAT", bbs_soft_dir, node_num);
	if(flength(s)<1L) {
		return; }
	if((f=nopen(s,O_RDWR))==-1) {
		printf("Couldn't open %s for read/write\r\n",s);
		return; }
	read(f, &ssmr, sizeof(shortmsgrec));
	chsize(f,0L);
	close(f);
	if(toggles[CLEAR_PROMPT] == '1') /* New Addition */
		del_prompt();
	else
		CRLF;
	pascaltoc_string(ssmr.msg);
	bputs(ssmr.msg);
	dots_again = 1;
}

void tg_page(void)
{
	char s[256], buf[256], line[80];
	int f, i, c;
	nodesrec nr;

	tgwhos_online(1);
	CRLF;

	bprintf(l78);
	i=getkeys("Q\r",sys_nodes);

	if(i==-1)
		return;
	if(i == '\r')
		return;
	i^=0x8000;
	if(!i || i>sys_nodes)
		return;
	if(toupper(i) == 'Q')
		return;

  sprintf(s, "%sNODES.DAT", bbs_soft_dir);
	f = nopen(s, O_RDONLY);
	if(f == -1) {
		bprintf("\r\nError opening %s\r\n", s);
		return; }
	c = 0;
	while((c < i) && (!eof(f))) {
		c++;
		read(f, &nr, sizeof(nodesrec));
		}
	close(f);
	if(nr.statusid != 3) {
		bprintf("\r\n_whNode %d is not in use.\r\n",i);
		return;
		}
	else if(i == node_num) {
		bputs("\r\n\1nThere's no need to send a message to yourself.\r\n");
		return;
		}
	else if((nr.flags.isquiet == 1) && (!SYSOP)) {
		bprintf("\r\n\1nDon't bug %s", nr.handle);
		return;
		}
	else {
		bputs(l75);
		if(!getstr(line,70,K_LINE))
			return;
		sprintf(buf
			,"`04<`0C(`8E*`0C)`04> `0FFrom %s (Node %d):`09\r\n%s\r\n"
			,user_name,node_num,line);
		tgputnmsg(i,buf);
		}
}
