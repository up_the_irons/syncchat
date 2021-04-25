#include "xsdk.h"
#include "portable.h"

struct channel_s {
	char name[256];					/* Name of channel */
	char sl[4];							/* Min SL to enter channel */
	char actions_file[13];	/* ACTIONS.LST used for this channel */
	char dir[256];					/* The directory of the channel */
	};

extern char snc_dir[256], snc_root[256], toggles[10];
extern struct channel_s *channel[99];
extern int num_of_rooms;
extern char *l82, *l83, *l84, *l85, *l86, *l87, *l88, *l89, *l90, *l92, *l93;

#define LOGGING_ON 2

// Prototypes
char* print_raw_topic(int channel, int priv_channel);
void uninvite(char *who);

void delete_topic(void)
{
	char buff[256];
	struct stat statbuf;

	sprintf(buff, "%sTOPIC.TXT", snc_dir);
	if(fexist(buff)) /* Make sure onfile is 'deletable' before deleting it */
		{
		do {
			stat(buff, &statbuf);
		} while(!(statbuf.st_mode & S_IWRITE));
		unlink(buff);
		}
}

void scan(void)
/* MBBS SCAN command */
{
  int handle, total_online, i, to, node_count, cur_room_scanned, done,
      at_end = 0;
	long offset;
	char tmp[55], file[81], name[50], priv_chan_name[50], orig_snc_dir[256];
	FILE *stream;
	struct ffblk ffblk;

	handle = nopen("ROOMS.LST", O_RDONLY);
	if(handle == -1)
		{
		bputs("Error [ROOMS.LST]: Cannot open ROOMS.LST in scan(void)\r\n");
		pause();
		cleanup();
		exit(1);
		}
	total_online = 0;
	while(!eof(handle))
		{
		if( (i = read(handle, &tmp, 55)) != -1) {
			if(i == 55)
				total_online++;
			}
		}
	close(handle);
	to = total_online; node_count = 0; cur_room_scanned = 2;
	strcpy(orig_snc_dir, snc_dir);
	bputs(l82);
	bputs(l83);
	while(to)
		{
		node_count++;
		if(node_count > sys_nodes)
			break;
		sprintf(file, "%sON.%i", snc_root, node_count);
		if(fexist(file))
			{
			handle = nopen(file, O_RDONLY);
			if(handle == -1)
				{
				bprintf("Error [%s]: Cannot open %s in scan(void)\r\n", file);
				continue;
				}
			stream = fdopen(handle, "rb");
			fgets(name, 50, stream);
			truncsp(name);
			fclose(stream);
			bprintf(l84, name,
						 (has_been_forgotten(name) ? "*" : " "),
						 (has_been_invited(name) ? "*" : " "),
						 "Main");
			bprintf(l86, "", print_raw_topic(1,0));
			to--;
			}
		}
  if(to != 0)
		/* Search other public channels */
    {
    if(num_of_rooms >= 2) /* Scan channels only if present */
      {
			/* Scan until all rooms scanned */
      while(cur_room_scanned <= num_of_rooms)
        {
        sprintf(file, "%s%iCHAN\\ON.*", snc_root, cur_room_scanned-1);
        done = findfirst(file, &ffblk, 0); /* Find first ON.* */
        while(!done)
          {
          sprintf(file, "%s%iCHAN\\%s", snc_root, cur_room_scanned-1,
                  ffblk.ff_name);
					/* Process.. */
          handle = nopen(file, O_RDONLY);
          if(handle == -1)
            {
            bprintf("Error [%s]: Cannot open %s in scan(void)\r\n",
                    file, ffblk.ff_name);
            done = findnext(&ffblk);
            continue;
            }
          stream = fdopen(handle, "rb");
          fgets(name, 50, stream);
          truncsp(name);
          fclose(stream);
          bprintf(l84, name,
                 (has_been_forgotten(name) ? "*" : " "),
                 (has_been_invited(name) ? "*" : " "),
                 channel[cur_room_scanned-1]->name);
          bprintf(l86, "",
                  print_raw_topic(cur_room_scanned,0));
          to--; /* One less user to scan... */
          if(to > 0) /* Find next ON.* unless all users scanned */
            done = findnext(&ffblk);
          else /* If all users scanned, let's exit loop */
            done = 1;
          }
        if(to > 0) /* Still have users to scan */
          cur_room_scanned++; /* Scan next public channel */
        else
          break; /* No more users to scan, exit loop */
        }
      }
    }
  if(to != 0)
		/* Search private channels */
    {
    offset = 0;
    while(to)
      {
      handle = nopen("ROOMS.LST", O_RDONLY);
      lseek(handle, offset, SEEK_SET);
      read(handle, &priv_chan_name, sizeof(user_name));
      truncsp(priv_chan_name);
      read(handle, &tmp, 10); truncsp(tmp);
      offset = tell(handle);
      if(eof(handle))
        at_end = 1;
      close(handle);
      i = atoi(tmp);
      sprintf(file, "%s%i\\ON.*", snc_root, i);
      done = findfirst(file, &ffblk, 0); /* Find first ON.* */
      while(!done)
        {
        sprintf(file, "%s%i\\%s", snc_root, i, ffblk.ff_name);
				/* Process.. */
        handle = nopen(file, O_RDONLY);
        if(handle == -1)
          {
          bprintf("Error [%s]: Cannot open %s in scan(void)\r\n",
                  file, ffblk.ff_name);
          done = findnext(&ffblk);
          continue;
          }
        stream = fdopen(handle, "rb");
        fgets(name, 50, stream);
        truncsp(name);
        fclose(stream);
        bprintf(l85, name,
               (has_been_forgotten(name) ? "*" : " "),
               (has_been_invited(name) ? "*" : " "),
               priv_chan_name);
        bprintf(l86, "", print_raw_topic(0, i));
        to--; /* One less user to scan... */
        if(to > 0) /* Find next ON.* unless all users scanned */
          done = findnext(&ffblk);
        else /* If all users scanned, let's exit loop */
          done = 1;
        }
      if(at_end)
        to = 0;
      }
    }
	CRLF;
	bprintf(l87);
	bprintf(l88);
	/*bprintf("\1h\1gTotal Online: %i\r\n", total_online);*/
}

char* print_raw_topic(int channel, int priv_channel)
/* Like print_topic, but doesn't display the "str <topic>", just
	 "<topic>".  Also takes 'channel' parameter.  '1' means topic of Main
	 channel, '2' means topic of channel #2, etc.. If channel is '0' then
	 priv_channel will correspond to the private channel's topic. */
{
	char s[81], *topic;
	int handle;
	FILE *stream;

	topic = (char*) malloc(80);

	if(channel == 0)
		sprintf(s, "%s%i\\TOPIC.TXT", snc_root, priv_channel);
	else if(channel == 1)
		sprintf(s, "%sTOPIC.TXT", snc_root);
	else if(channel > 1)
		sprintf(s, "%s%iCHAN\\TOPIC.TXT", snc_root, channel-1);
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
	return(topic); }
	else
		return("No Topic");
}

int in_telecon_allchan(int node)
/* Returns 1 if a user one 'node' is present in SyncChat.  Works across all
	 channels.
*/
{
	char s[81], file[81], tmp[55], priv_chan_name[50];
	int to, handle, cur_room_scanned, done, i;
	long offset;

	sprintf(s, "%sON.%i", snc_root, node);
	if(fexist(s))
			return(1);
	else
		{
		if(num_of_rooms >= 2) /* Scan channels only if present */
			{
			/* Scan until all rooms scanned */
			cur_room_scanned = 2;
			while(cur_room_scanned <= num_of_rooms)
				{
				sprintf(file, "%s%iCHAN\\ON.%i", snc_root, cur_room_scanned-1,
								node);
				if(fexist(file))
					return(1);
				cur_room_scanned++;
				}
			}
		offset = 0;
		handle = nopen("ROOMS.LST", O_RDONLY);
		if(handle == -1)
			{
			bputs("Error [ROOMS.LST]: Cannot open ROOMS.LST in in_telecon_allchan()\r\n");
			return(0);
			}
		to = 0;
		while(!eof(handle))
			{
			if( (i = read(handle, &tmp, 55)) != -1) {
				if(i == 55)
					to++;
				}
			}
		close(handle);
		while(to)
			{
			handle = nopen("ROOMS.LST", O_RDONLY);
			lseek(handle, offset, SEEK_SET);
			read(handle, &priv_chan_name, sizeof(user_name));
			truncsp(priv_chan_name);
			read(handle, &tmp, 10); truncsp(tmp);
			offset = tell(handle);
			close(handle);
			i = atoi(tmp);
			sprintf(file, "%s%i\\ON.%i", snc_root, i, node);
			if(fexist(file))
				return(1);
			to--;
			}
		}
	return(0);
}

void forget(char* who)
/* [F]orget command */
{
	int n, f;
	char s[81], str[15];

	n = scusernumber(who);
	if(n != 0)
		{
		sprintf(s, "%s%i.FOR", snc_root, n);
		f = nopen(s, O_WRONLY|O_CREAT|O_APPEND);
		sprintf(str, "%10.10u", node_num);
		write(f, str, 10);
		close(f);
		}
}

void unforget(char* who)
{
/* Unforget command */
	int i, n, f;
	char s[81], str[15];

	n = scusernumber(who);
	if(n != 0)
		{
		sprintf(s, "%s%i.FOR", snc_root, n);
		f = nopen(s, O_RDWR);
		while(!eof(f))
			{
			read(f, &str, 10);
			str[10] = 0;
			/*bprintf("unforget - %s - str\r\n", str); Test code */
			i = atoi(str);
			/*bprintf("unforget - %i\r\n", i); Test code
			bprintf("unforget - %i - node_num\r\n", node_num); */
			if(i == node_num)
				{
				/* bputs("tah\r\n"); Test code
				bprintf("tell(f) = %il", tell(f)); */
				lseek(f, (tell(f) - 10L), SEEK_SET);
				write(f, "0000000000", 10);
				close(f);
				return;
				}
			}
		close(f);
		}
}

int has_been_forgotten(char* who)
/* Returns a '1' if 'who' has been 'forgotten' with the [F]orget command. */
{
	int n, i, f;
	char s[81], str[15];

	n = scusernumber(who);
	if(n != 0)
		{
		sprintf(s, "%s%i.FOR", snc_root, n);
		f = nopen(s, O_RDONLY);
		while(!eof(f))
			{
			read(f, &str, 10);
			str[10] = 0;
			i = atoi(str);
			/* bprintf("has_been_forgotten - %i\r\n", i); Test code */
			if(i == node_num)
				{
				close(f);
				return(1);
				}
			}
		close(f);
		}
	return(0);
}


void delete_forget_file(void)
{
	char s[256];

	sprintf(s, "%s%i.FOR", snc_root, user_number);
	unlink(s);
}

int ok_to_send(int node)
{
/* Returns '1' if it is ok to send a message to 'node'.  Returns '0' if not.
	 Would return '0' if 'node' has forgotten the current node.
*/
	int n, i, f;
	char s[81], str[15];


	sprintf(s, "%s%i.FOR", snc_root, user_number);
	f = nopen(s, O_RDONLY);
	while(!eof(f))
		{
		read(f, &str, 10);
		str[10] = 0;
		i = atoi(str);
		if(i == node)
			{
			close(f);
			return(0);
			}
		}
	close(f);
	return(1);
}

void invite(char *who)
/* [I]nvite command */
{
	char buff[256], s[256];
	int f;
	long i;

	sprintf(buff, "%s%i\\INVITE.DAT", snc_root, user_number);
	if(has_been_invited(who))
		{
		bprintf(l89, who);
		uninvite(who);
		return;
		}
	if((i = (long)scusernumber(who)) != 0)
		{
		f = nopen(buff, O_WRONLY|O_CREAT|O_APPEND);
		write(f, &i, sizeof(long));
		close(f);
		sprintf(s, l90, user_name);
		scputnmsg(user_on_node(who), s);
		bprintf(l93, who);
		}
}

void uninvite(char *who)
{
	int i, f;
	long n, j, z = 0, offset;
	char s[81], str[15], s2[256];

	n = (long)scusernumber(who);
	if(n != 0)
		{
		sprintf(s, "%s%i\\INVITE.DAT", snc_root, user_number);
		f = nopen(s, O_RDWR);
		while(!eof(f))
			{
			offset = tell(f);
			read(f, &j, sizeof(long));
			if(j == (long)scusernumber(who))
				{
				lseek(f, offset, SEEK_SET);
				write(f, &z, sizeof(long));
				close(f);
				sprintf(s2, l92, user_name);
				scputnmsg(user_on_node(who), s2);
				return;
				}
			}
		close(f);
		}
}

int has_been_invited(char *who)
/* Returns '1' if 'who' has been invited to current users private channel. */
{
	char buff[256];
	int f;
	long i;

	sprintf(buff, "%s%i\\INVITE.DAT", snc_root, user_number);
	f = nopen(buff, O_RDONLY);
	while(!eof(f))
		{
		read(f, &i, sizeof(long));
		if(((long)scusernumber(who)) == i)
			{
			close(f);
			return(1);
			}
		}
	close(f);
	return(0);
}


void del_invite_file(void)
/* Deletes INVITE.DAT of current user */
{
	char s[256];

	sprintf(s, "%s%i\\INVITE.DAT", snc_root, user_number);
	unlink(s);

}

int user_on_node(char *who)
/* Returns the node number of who 'who' is on.  Works across all channels */
{
	char s[81], file[81], tmp[55], priv_chan_name[50], buf[50];
	int to, handle, cur_room_scanned, done, i, j, user_num;
	long offset;
	FILE *f;

	for(j = 1; j <= sys_nodes; j++) /* Loop through all nodes */
		{
		if(in_telecon_allchan(j)) /* If current node is SyncChat... */
			{												 /* Find out if it is 'who' and return node */
			sprintf(s, "%sON.%i", snc_root, j);
			if(fexist(s))
				{
				handle = nopen(s, O_RDONLY);
				f = fdopen(handle, "rb");
				if(f == NULL)
					//return(NULL);
					return(0); // Modified 08-28-2004
				fgets(buf, 50, f);
				fgets(s, 81, f); /* dummy seek */
				truncsp(s);
				fgets(s, 81, f);
				truncsp(s);
//				user_num = atoi(s);
				fclose(f);
				truncsp(buf);
				if(strcmpi(buf, who) == 0)
					return(j);
				}
			else
				{
				if(num_of_rooms >= 2) /* Scan channels only if present */
					{
					/* Scan until all rooms scanned */
					cur_room_scanned = 2;
					while(cur_room_scanned <= num_of_rooms)
						{
						sprintf(file, "%s%iCHAN\\ON.%i", snc_root, cur_room_scanned-1,
										j);
						if(fexist(file))
							{
							handle = nopen(file, O_RDONLY);
							f = fdopen(handle, "rb");
							if(f == NULL)
					      //return(NULL);
					      return(0); // Modified 08-28-2004
							fgets(buf, 50, f);
							fgets(s, 81, f); /* dummy seek */
							truncsp(s);
							fgets(s, 81, f);
							truncsp(s);
//							user_num = atoi(s);
							fclose(f);
							truncsp(buf);
							if(strcmpi(buf, who) == 0)
								return(j);
							}
						cur_room_scanned++;
						}
					}
				offset = 0;
				handle = nopen("ROOMS.LST", O_RDONLY);
				if(handle == -1)
					{
					bputs("Error [ROOMS.LST]: Cannot open ROOMS.LST in in_telecon_allchan()\r\n");
					return(0);
					}
				to = 0;
				while(!eof(handle))
					{
					if( (i = read(handle, &tmp, 55)) != -1) {
						if(i == 55)
							to++;
						}
					}
				close(handle);
				while(to)
					{
					handle = nopen("ROOMS.LST", O_RDONLY);
					lseek(handle, offset, SEEK_SET);
					read(handle, &priv_chan_name, sizeof(user_name));
					truncsp(priv_chan_name);
					read(handle, &tmp, 10); truncsp(tmp);
					offset = tell(handle);
					close(handle);
					i = atoi(tmp);
					sprintf(file, "%s%i\\ON.%i", snc_root, i, j);
					if(fexist(file))
						{
						handle = nopen(file, O_RDONLY);
						f = fdopen(handle, "rb");
						if(f == NULL)
					    //return(NULL);
					    return(0); // Modified 08-28-2004
						fgets(buf, 50, f);
						fgets(s, 81, f); /* dummy seek */
						truncsp(s);
						fgets(s, 81, f);
						truncsp(s);
//						user_num = atoi(s);
						fclose(f);
						truncsp(buf);
						if(strcmpi(buf, who) == 0)
							return(j);
						}
					to--;
					}
				}
			}
		}
	return(0);
}


int ok_to_join(int chan_num)
/* Returns '1' if current user has been invited into 'chan_num' */
{
	int f;
	char s[256];
	long i;

	sprintf(s, "%s%i\\INVITE.DAT", snc_root, chan_num);
	f = nopen(s, O_RDONLY);
	while(!eof(f))
		{
		read(f, &i, sizeof(long));
		if(i == (long)user_number)
			{
			close(f);
			return(1);
			}
		}
	close(f);
	return(0);
}

int scusernumber(char *name)
/*
Returns the user number to user 'name'.  Obviously, 'name' must be online.
If not, 0 is returned */
{
  int handle;
  char uname[45], number[10];

	handle = nopen("ROOMS.LST", O_RDONLY);
	if(handle == -1)
		{
		bprintf("Error opening ROOMS.LST in scusernumber()\r\n");
		pause();
		}
	do {
		read(handle, &uname, sizeof(user_name));
		read(handle, &number, 10);
		truncsp(uname);
		if(strcmpi(uname, name) == 0)
			{
			close(handle);
			return(atoi(number));
			}
	} while(!eof(handle));
	close(handle);
	return(0);
}

void add_to_log(char *s)
/* Add 's' to SYNCCHAT.LOG */
{
	int f;

  if(!logging())
    return;
	f = nopen("SYNCCHAT.LOG", O_WRONLY|O_CREAT|O_APPEND);
	if(f == -1)
		{
		bprintf("Error opening SYNCCHAT.LOG in add_to_log()\r\n");
		return;
		}
	write(f, s, strlen(s));
	if(s[strlen(s) - 1] != '\n')
		write(f, "\n", strlen("\n"));
	close(f);
}

void strip_ctrla(char *strin)
{
	uchar str[512];
	uchar a,c,d,e;

e=strlen(strin);
c=d=0;
while(c<e) {
	while(strin[d]==1) {
		d++; d++; }
	str[c]=strin[d];
	c++; d++;
	}
strcpy(strin,str);
}

int logging(void)
/* Returns 1 if the "Log Activities In SYNCCHAT.LOG" is toggled to YES in
   SCONFIG, 0 if not */
{
  if(toggles[LOGGING_ON] == '1') 
    return(1);
  else
    return(0);
}

