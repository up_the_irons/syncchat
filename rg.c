/* RG.C - Includes functions for native SyncChat<->Renegade 5-11+ Interface
	 Created 12-4-96 by Prophet (Garry Dolley)
*/

#include "xsdk.h"
#include "portable.h"
#include "rg.h"

#define RENEGADE "4"
#define CLEAR_PROMPT 1

extern char  bbs_soft_dir[128], bbs_software[64], toggles[10];
extern char  *l64, *l65, *l66, *l75, *l78;
extern int   dots_again;

extern void pascaltoc_string(char *s);

void dump_structs(struct noderec nrec)
{
  bprintf("NActive = %d\r\n", nrec.status.NActive);
  bprintf("NAvail = %d\r\n", nrec.status.NAvail);
  bprintf("NUpdate = %d\r\n", nrec.status.NUpdate);
  bprintf("NHangup = %d\r\n", nrec.status.NHangup);
  bprintf("NRecycle = %d\r\n", nrec.status.NRecycle);
  bprintf("NInvisible = %d\r\n", nrec.status.NInvisible);
  bprintf("User = %d\r\n", nrec.User);
  bprintf("UserName = %s\r\n", nrec.UserName);
  bprintf("CityState = %s\r\n", nrec.CityState);
  bprintf("Sex = %c\r\n", nrec.Sex);
  bprintf("Age = %d\r\n", nrec.Age);
  bprintf("LogonTime = %il\r\n", nrec.LogonTime);
  bprintf("Activity = %d\r\n", nrec.Activity);
}

void rgwhos_online(int display_all)
{
	int f, node = 0;
	char s[256], node_s[32], bps[32], status[256];
	struct noderec nr;

	if(strcmpi(bbs_software, RENEGADE) != 0)
		return;
  sprintf(s, "%sMULTNODE.DAT", bbs_soft_dir);
	f = nopen(s, O_RDWR);
	if(f == -1)
		{
		bprintf("\r\nError opening %s\r\n", s);
		return;
		}
	bputs(l64);
	bputs(l65);
	do {
		node++;
		read(f, &nr, sizeof(struct noderec));

    /* Make sure they are still 'available' 
		if(nr.status.NActive)
			{
			lseek(f, tell(f) - (long)(sizeof(struct noderec)), SEEK_SET);
			nr.status.NAvail = 1;
			write(f, &nr, sizeof(struct noderec));
      } */

		itoa(node, node_s, 10);
/*		ltoa(nr.bpsrate, bps, 10); MULTNODE.DAT doesn't seem to have this
																 field! */
		pascaltoc_string(nr.UserName);
		/* Make status */
/*
					 1:Description := 'Transferring files';
					 2:Description := 'Out in a door';
					 3:Description := 'Reading messages';
					 4:Description := 'Writing a message';
					 5:Description := 'Reading Email';
					 6:Description := 'Using offline mail';
					 7:Description := 'Teleconferencing';
				 255:Description := Noder.Description;
				 else Description := 'Miscellaneous';
*/
		switch (nr.Activity) {
			case 1: strcpy(status, "Transfering files"); break;
			case 2: strcpy(status, "Out in a door"); break;
			case 3: strcpy(status, "Reading messages"); break;
			case 4: strcpy(status, "Writing a message"); break;
			case 5: strcpy(status, "Reading Email"); break;
			case 6: strcpy(status, "Using offline mail"); break;
			case 7: strcpy(status, "Teleconferencing"); break;
      case 255:
        pascaltoc_string(nr.Description);
        strcpy(status, nr.Description);
        break;
      default: strcpy(status, "Miscellaneous"); break;
/*        strcpy(nr.UserName, "\1nWaiting for call"); strcpy(status, " ");
				break; */
		}

/*		pascaltoc_string(nr.status);
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
			} */
		if(nr.status.NActive == 0) {
			strcpy(nr.UserName, "\1nWaiting for call");
			strcpy(status, " "); }
		if((nr.status.NInvisible) && (!SYSOP)) {
			strcpy(nr.UserName, "\1nWaiting for call");
			strcpy(status, " "); }
		if(nr.User == 0) {
			strcpy(nr.UserName, "\1nWaiting for call");
			strcpy(status, " "); }

/*		if((nr.flags.ishidden == 1) && (!SYSOP)) {
			strcpy(nr.handle, "\1nWaiting for call");
			strcpy(nr.status, " "); strcpy(bps, " "); } */
		sprintf(s, l66, node_s, nr.UserName, status, "");
		bputs(s);
/*    dump_structs(nr);*/
		} while( (!eof(f)) && (!(node >= sys_nodes)) );
	close(f);
}

void rgputnmsg(int node, char* message)
{
	char s[256];
  int f, len;

	sprintf(s, "%sMESSAGE.%d", bbs_soft_dir, node);
	f = nopen(s, O_WRONLY|O_APPEND|O_CREAT);
	if(f == -1) {
		bprintf("\r\nError opening %s\r\n", s);
		return; }
  len = strlen(message);
	ctopascal_string(message);
  write(f, message, len);
	close(f);
}

void rggetnmsg(void)
{
	char s[256];
	char message[256];
	int f;

	sprintf(s, "%sMESSAGE.%d", bbs_soft_dir, node_num);
	if(flength(s)<1L) {
		return; }
	if((f=nopen(s,O_RDWR))==-1) {
		printf("Couldn't open %s for read/write\r\n",s);
		return; }
	read(f, message, 256);
	chsize(f,0L);
	close(f);
	if(toggles[CLEAR_PROMPT] == '1') /* New Addition */
		del_prompt();
	else
		CRLF;
	pascaltoc_string(message);
	bputs(message);
	dots_again = 1;
}

void rg_page(void)
{
	char s[256], buf[256], line[80];
	int f, i, c;
  struct noderec nr;

	rgwhos_online(1);
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

	sprintf(s, "%sMULTNODE.DAT", bbs_soft_dir);
	f = nopen(s, O_RDONLY);
	if(f == -1) {
		bprintf("\r\nError opening %s\r\n", s);
		return; }
	c = 0;
	while((c < i) && (!eof(f))) {
		c++;
    read(f, &nr, sizeof(struct noderec));
		}
	close(f);
  if(nr.status.NActive == 0) {
		bprintf("\r\n_whNode %d is not in use.\r\n",i);
		return;
		}
	else if(i == node_num) {
		bputs("\r\n\1nThere's no need to send a message to yourself.\r\n");
		return;
		}
  else if((nr.status.NAvail == 0) && (!SYSOP)) {
    bprintf("\r\n\1nDon't bug %s", nr.UserName);
		return;
		}
	else {
		bputs(l75);
		if(!getstr(line,70,K_LINE))
			return;
		sprintf(buf
      ,"|11<|14(|12*|14)|11> |15From %s (Node %d):|09\r\n%s\r\n"
			,user_name,node_num,line);
		rgputnmsg(i,buf);
		}
}
