/* IMP.C - Includes functions for native SyncChat<->Impulse interface
   Created: 5-27-96 by Prophet
*/

#include "xsdk.h"
#include "portable.h"

extern char  bbs_soft_dir[128], bbs_software[64];
extern char  *l64, *l65, *l66;
extern uchar sys_nodes;
typedef unsigned char byte;
typedef char acstring[ 21 ];

#define IMPULSE "2"

/* Pascal Version

  noderec=
  record
    desc    :string[40];            { Short node description (Subscriber line, 2400 line, HST line, etc) }
    acs     :acstring;              { ACS required to log in to that node }
    status  :byte;                  { What the node is doing at the moment }
    username:string[40];            { User that is on right now }
    usernum :integer;               { User # that is on right now }
  end;

*/

struct noderec {
	char       desc[41];
	acstring   acs;
	byte       status;
  char       username[41];
	int        usernum;
} node;

/* Pascal Version

		case node.status of
			0:s:='Waiting for Caller';
			1:s:='Offline';
			2:s:='Logging in';
			3:s:='Menuing';
			4:s:='Uploading';
			5:s:='Downloading';
			6:s:='Entering a message';
			7:s:='Reading a message';
		 11..20:s:='Chat forum #'+cstr(node.status-10);
		end;

*/

void pascaltoc_string(char *s)
/* Converts a Pascal string to a C string */
{
  int i = 0, j, len;

  /* Punch in NULL */
	s[ (s[0] - 0) + 1 ] = 0;
	/* Shift string to the left */
  len = (int)s[0];
  while(s[i++] != 0) 
/*  while(i++ < len) */
    s[i - 1] = s[i];
}

void impwhos_online(void)
{
  char s[256], status[81], node_s[32];
  int f, node = 0;
  struct noderec nr;

	if(strcmpi(bbs_software, IMPULSE) != 0)
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
		read(f, &nr.desc, 41); pascaltoc_string(nr.desc);
		read(f, &nr.acs, 21); pascaltoc_string(nr.acs);
		read(f, &nr.status, sizeof(byte));
		read(f, &nr.username, 41); pascaltoc_string(nr.username);
		read(f, &nr.usernum, sizeof(int));
		switch(nr.status) {
			case 0:
				strcpy(nr.username, "\1nWaiting for call");
				strcpy(status, " "); break;
			case 1:
				strcpy(nr.username, "\1h\1kOffline");
				strcpy(status, " "); break;
			case 2:
				strcpy(nr.username, "\1nLogging on...");
				strcpy(status, " "); break;
			case 3:
				strcpy(status, "\1h\1wMenuing"); break;
			case 4:
				strcpy(status, "\1h\1wUploading"); break;
			case 5:
				strcpy(status, "\1h\1wDownloading"); break;
			case 6:
				strcpy(status, "\1h\1wEntering a message"); break;
			case 7:
				strcpy(status, "\1h\1wReading a message"); break;
			default:
				strcpy(status, "\1n\1rL\1h\1ri\1n\1rmbo!"); break;
			}
		itoa(node, node_s, 10);
		sprintf(s, l66, node_s, nr.username, status, " ");
    bputs(s);
    } while( (!eof(f)) && !(node >= sys_nodes) );  
  close(f);
}
