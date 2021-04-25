#ifndef __GLOBALS_H
#define __GLOBALS_H

#define SYNCHRONET         "0"
#define OTHER_BBS_SOFTWARE "1"
#define IMPULSE            "2" 
#define TELEGARD           "3"
#define RENEGADE           "4"

/* Global structure definitions */
struct games_s {
	char exec[256];        /* Executable line */
	char display[256];     /* What user sees in selection */
};

struct channel_s {
	char name[256];					/* Name of channel */
  char sl[10];             /* Min SL to enter channel */
	char actions_file[13];	/* ACTIONS.LST used for this channel */
	char dir[256];					/* The directory of the channel */
	};

struct actions {
  char action_word[12];  /* Action typed */    /* */
  char response[128];    /* What the user that did the action sees */
  char all[128];         /* What everyone sees if no arg to action */
  char others[128];      /* What other users see if arg to action */
  char reciever[128];    /* What the reciever (if any) of the action sees */
};

/* Global vars */
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
int	cur_room_num; 
int reged;
int num_of_games;

int x_pos, y_pos;
int	act_level;

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

#endif
