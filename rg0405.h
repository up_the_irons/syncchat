#ifndef RENEGADE_H
#define RENEGADE_H

/********************************************************************
 **                                                                **
 **         Renegade 04-05 Exp structures; C header file           **
 **         Translated from Pascal                                 **
 **                                                                **
 **         USE AT YOUR OWN RISK!                                  **
 **                                                                **
 **         Converted to 04-05 by Dave Sawford                     **
 **                               (dws@mrao.cam.ac.uk)             **
 ********************************************************************/



#define VER             "04-05 Exp"
#define MAXPROTOCOLS    120
#define MAXEVENTS       10
#define MAXARCS         8
#define MAXBATCHFILES   50
#define MAXMENUCMDS     100
#define MAXRESULTCODES  13
#define MAXEXTDESC      9


typedef unsigned char boolean;
#ifndef bit_o
typedef unsigned int  bit;
#endif
typedef unsigned char byte;
typedef unsigned int  word;


typedef char astr [160];
typedef char str8 [8];
typedef char acstring [21];     /*  Access Condition String              */
typedef byte acrq [27];         /*  Access Restriction flags ('@'..'Z')  */



struct uflags {
        
        bit rlogon      : 1;            /* L - Limited to one call a day  */
        bit rchat       : 1;            /* C - No SysOp paging            */
        bit rvalidate   : 1;            /* V - Posts are unvalidated      */
        bit ruserlist   : 1;            /* U - Can't list users           */
        bit ramsg       : 1;            /* A - Can't post an auto message */
        bit rpostan     : 1;            /* * - Can't post anonymously     */
        bit rpost       : 1;            /* P - Can't post                 */
        bit remail      : 1;            /* E - Can't send email           */
        bit rvoting     : 1;            /* K - Can't use voting booth     */
        bit rmsg        : 1;            /* M - Force email deletion       */
        bit vt100       : 1;            /* Supports VT100                 */
        bit hotkey      : 1;            /* hotkey input mode              */    
        bit avatar      : 1;            /* Supports Avatar                */
        bit pause       : 1;            /* screen pausing                 */
        bit novice      : 1;            /* user requires novice help      */
        bit ansi        : 1;            /* Supports ANSI                  */
        bit color       : 1;            /* Supports color                 */
        bit alert       : 1;            /* Alert SysOp upon login         */
        bit smw         : 1;            /* Short message(s) waiting       */
        bit nomail      : 1;            /* Mailbox is closed              */
        bit fnodlratio  : 1;            /* 1 - No UL/DL ratio             */
        bit fnopostratio: 1;            /* 2 - No post/call ratio         */
        bit fnocredits  : 1;            /* 3 - No credits checking        */
        bit fnodeletion : 1;            /* 4 - Protected from deletion    */

        };



struct suflags {

        bit lockedout   : 1;            /* if locked out                    */
        bit deleted     : 1;            /* if deleted                       */
        bit trapactivity: 1;            /* if trapping users activity       */
        bit trapseparate: 1;            /* if trap to seperate TRAP file    */
        bit chatauto    : 1;            /* if auto chat trapping            */
        bit chatseparate: 1;            /* if separate chat file to trap to */
        bit slogseparate: 1;            /* if separate SysOp log            */
        bit clsmsg      : 1;            /* if clear-screens                 */
				bit rip         : 1;            /* if RIP graphics can be used      */
        bit fseditor    : 1;            /* if Full Screen Editor            */
        bit AutoDetect  : 1;            /* Use auto-detected emulation      */
  
        };



struct anontyp {

        bit atno        : 1;            /* Anonymous posts not allowed */
        bit atyes       : 1;            /* Anonymous posts are allowed */
        bit atforced    : 1;            /* Force anonymous             */
        bit atdearabby  : 1;            /* "Dear Abby" base            */
        bit atanyname   : 1;            /* Post under any name         */

        };



struct netattr {

        bit Private             : 1;
        bit Crash               : 1;
        bit Recd                : 1;
        bit NSent               : 1;
        bit FileAttach          : 1;
        bit Intransit           : 1;
        bit Orphan              : 1;
        bit KillSent            : 1;
        bit Local               : 1;
        bit Hold                : 1;
        bit Unused              : 1;
        bit FileRequest         : 1;
        bit ReturnReceiptRequest: 1;
        bit IsReturnReceipt     : 1;
        bit AuditRequest        : 1;
        bit FileUpdateRequest   : 1;

        };



typedef netattr netattribs;

typedef byte colors [2] [10];          /*  Color tables  */
typedef int secrange [256];            /*  Access tables */

typedef byte mzscanr [32];             /*  Which message bases to scan  */
typedef byte fzscanr [32];             /*  Which file bases to scan     */
typedef long mhireadr [250];           /*  Lastread pointers            */



struct useridxrec {                    /* USERS.IDX : Sorted names listing */
  
        char Name [37];                /* CRC-32 of the user's name        */
        int Number;                    /* user number                      */
        int Left;
        int Right;
        boolean RealName;              /* User's real name?                */
        boolean Deleted;               /* deleted or not                   */

        };



struct userrec {                       /* USERS.DAT : User records */

	char name [37];                /* system name              */
	char realname [37];            /* real name                */
	char street [31];              /* street address           */
	char citystate [31];           /* city, state              */ 
	char callerid [21];            /* Caller id (?)            */
	char zipcode [11];             /* zipcode                  */
	char ph [13];                  /* phone #                  */
	long pw;                       /* Password in long int form*/
	char usrdefstr [3] [36];       /* type of computer         */
                                       /* occupation               */
                                       /* BBS reference            */
	long bday;                     /* birthdate                */
	long firston;                  /* first on date            */ 
	long laston;                   /* last on date             */
	char note [36];                /* SysOp note               */
	char userstartmenu [9];        /* menu to start at         */
	char lockedfile [9];           /* print lockout msg        */
        uflags flags;                  /* flags                    */
        suflags sflags;                /* status flags             */
        acrq ar;                       /* AR flags                 */
	unsigned char vote [25];       /* voting data              */

	char sex;                       /* gender                   */
	long ttimeon;                   /* total time on            */
	long uk;                        /* UL k                     */ 
	long dk;                        /* DL k                     */
	long lastqwk;                   /* date/time of last qwk packet     */
	long credit;                    /* Amount of credit a user has      */
	long debit;                     /* Amount of debit a user has       */ 
	long expiration;                /* Expiration date of this user     */
	long passwordchanged;           /* date password changed            */ 

	int tltoday;                    /* # min left today         */
	int forusr;                     /* forward mail to          */

	word uploads;
	word downloads;                 /* # of ULs/# of DLs        */
	word loggedon;                  /* # times on               */
	word msgpost;                   /* # message posts          */
	word emailsent;                 /* # email sent             */
	word feedback;                  /* # feedback sent          */
	word timebank;                  /* # mins in bank           */
	word timebankadd;               /* # added today            */
	word dlktoday;                  /* # kbytes dl today        */
	word dltoday;                   /* # files dl today         */
	word timebankwith;              /* amount of time withdrawn today   */
	word lastmbase;                 /* # last msg base          */
	word lastfbase;                 /* # last file base         */

	byte waiting;                   /* mail waiting             */
	byte linelen;                   /* line length              */
	byte pagelen;                   /* page length              */
	byte char ontoday;              /* # times on today         */
	byte char illegal;              /* # illegal logons         */
	byte char defarctype;           /* default QWK archive type         */
	byte char ColorScheme;          /* User's color scheme #            */
	byte char sl, dsl;              /* SL / DSL                 */

	char Subscription;              /* Subscription (?) */
	char expireto;                  /* Subscription level to expire to  */
	char lastconf;                  /* last conference they were in     */

	boolean TeleConfEcho;           /* echo Teleconf lines?             */
	boolean TeleConfInt;            /* interrupt during typing?         */
	boolean getownqwk;              /* add own messages to qwk packet?  */
	boolean scanfilesqwk;           /* scan file bases for qwk packets? */

	unsigned char privateqwk;       /* get private mail in qwk packets? */

	char reserved [39];

	};
    


struct msgstatusr {
    
        bit mdeleted    : 1;
        bit sent        : 1;
        bit unvalidated : 1;
        bit permanent   : 1;
        bit allowmci    : 1;
        bit netmail     : 1;
        bit prvt        : 1;
        bit forwarded   : 1;

        };



struct mhireadrec {
  
        boolean NewScan;                /* New scan this base?    */
        long LastRead;                  /* Last message date read */

        };



struct fromtoinfo {                    /* from/to information for mheaderrec */
    
        byte anon;
        word usernum;                  /* user number */
        char as [37];                  /* posted as   */
        char real [37];                /* real name   */
        char name [37];                /* system name */
        word zone;
        word net;
        word node;
        word point;

        };



struct mheaderrec {
     
        fromtoinfo from, mto;           /* message from/to info         */
        long pointer;                   /* starting record of text      */
        word textsize;                  /* size of text                 */
        word replyto;                   /* ORIGINAL + REPLYTO = CURRENT */
        long date;                      /* date/time packed string      */
        byte dayofweek;                 /* message day of week          */
        msgstatusr status;              /* message status flags         */
        word replies;                   /* times replied to             */
        char subject [41];              /* subject of message           */
        char origindate [20];           /* date of echo/group msgs      */
        byte fileattached;              /* 0=No, 1=Yes&Del, 2=Yes&Save  */
        NetAttribs netattribute;        /* Netmail attributes           */
        byte res [2];                   /* reserved                     */

        };



struct historyrec {                     /* HISTORY.DAT : Summary logs */
    
        char date [9];
        word userbaud [5];
        word active, callers, newusers, posts, email, feedback;
        word errors, uploads, downloads;
        long uk, dk;
  
        };



struct filearcinforec {                /* Archive configuration records */
    
        boolean active;                /* active or not                     */
        char ext [4];                  /* file extension                    */
        char listline [26];            /* /x for internal                   */
                                       /* x: 1=ZIP, 2=ARC/PAK, 3=ZOO, 4=LZH */
        char arcline [26];             /* compression cmdline               */
        char unarcline [26];           /* de-compression cmdline            */
        char testline [26];            /* integrity test cmdline            */
        char cmtline [26];             /* comment cmdline                   */
        int succlevel;                 /* success ERRORLEVEL,               */
                                       /* -1=ignore results                 */
        };



struct fstringrec {                    /* STRING.DAT */
    
        char anonymous [81];           /* "[Anonymous]" string               */
        char note [2] [81];            /* Logon notes (L #1-2)               */
        char lprompt [81];             /* Logon prompt (L #3)                */ 
        char echoc;                    /* Echo char for PWs                  */
        char yourpassword [81];        /* "Your password:"                   */
        char yourphonenumber [81];     /* "Your phone number:"               */
        char engage [81];              /* "Engage Chat"                      */
        char endchat [81];             /* "End Chat"                         */
        char wait [81];                /* "SysOp Working"                    */
        char pause [81];               /* "Pause"                            */
        char entermsg1 [81];           /* "Enter Message" line #1            */
        char entermsg2 [81];           /* "Enter Message" line #2            */
        char newscan1 [81];            /* "NewScan begin"                    */
        char newscan2 [81];            /* "NewScan done"                     */
        char newuserpassword [81];     /* "Newuser password:"                */
        char automsgt [81];            /* Auto-Message title                 */
        char autom;                    /* Auto-Message border characters     */

        char shelldos1 [81];           /* " >> SysOp shelling to DOS ..."    */
        char readingemail [81];        /* "Read mail (?=Help) :"             */
        char chatcall1 [81];           /* "Paging SysOp, please wait..."     */
        char chatcall2 [81];           /* ">>><*><<<"                        */ 
        char shuttleprompt [81];       /* "Enter your user name or number :" */
        char namenotfound [81];        /* "Name NOT found in user list."     */ 
        char bulletinline [81];        /* Bulletin line                      */
        char protocolp [81];           /* "Protocol (?=List) :"              */

        char listline [81];            /* "List files - P to pause"          */ 
        char newline [81];             /* "Search for new files -"           */
        char searchline [81];          /* "Search all dirs for file mask"    */
        char findline1 [81];           /* "Search for descriptions... "      */
        char findline2 [81];           /* "Enter the string to search for.." */
        char downloadline [81];        /* "Download - "                      */
        char uploadline [81];          /* "Upload - "                        */ 
        char viewline [81];            /* "View interior files - "           */
        char nofilecredits [81];       /* "Insufficient file credits."        */
        char unbalance [81];           /* "Your UL/DL ratio is unbalanced"   */

        char ilogon [81];              /* "Logon incorrect"                 */
        char gfnline1 [81];            /* "[Enter]=All files"               */
        char gfnline2 [81];            /* "File mask: "                     */
        char batchadd [81];            /* "File added to batch queue."      */
        char addbatch [81];            /* "Batch download flagging - "      */
        char readq [81];               /* "Begin reading at [1-54](Q=Quit):"*/
        char scanq [81];               /* "Begin scanning at [1-54](Q=Quit):"*/
        char default [81];             /* "Press [Enter]to use defaults"   */
        char newscanall [81];          /* ") [Newscan All]("               */ 
        char newscandone [81];         /* ") [Newscan Done]("              */
        char chatreason [81];          /* 'Give me a good reason to chat'   */
        char quote_line [2] [81];      /* Quoting so and so to so and so    */
        char userdefques [3] [81];     /* user defined question 1...3       */
        char userdefed [3] [11];       /* user def'd q, user editor strings */
        char continue [81];            /* Continue?                         */
        
        };



struct modemflags {                     /* MODEM.DAT status flags */

        bit lockedport  : 1;            /* COM port locked at constant rate */
        bit xonxoff     : 1;            /* XON/XOFF (software) flow control */
        bit ctsrts      : 1;            /* CTS/RTS (hardware) flow control  */
        bit DigiBoard   : 1;            /* This line uses a Digiboard       */

        };



struct linerec {
    
        word InitBaud;                  /* initialization baud                     */
        byte comport;                   /* COM port number                         */
        modemflags mflags;              /* status flags                            */
        char init [31];                 /* init string                             */ 
        char answer [31];               /* answer string                           */
        char hangup [31];               /* hangup string                           */
        char offhook [31];              /* phone off-hook string                   */
        char doorpath [41];             /* path to write door info files to */
        char TeleConfNormal [41];
        char TeleConfAnon [41];         /* You figure it out!               */
        char TeleConfGlobal [41];
        char TeleConfPrivate [41];

        char OK [21];
        char RING [21];
        char RELIABLE [21];
        char CALLERID [21];
        char NOCARRIER [21];
        char CONNECT [22] [20];         /* 300, 600, 1200, 2400, 4800, 7200, */
                                        /* 9600, 12000, 14400, 16800, 19200, */
                                        /* 21600, 24000, 26400, 28800, 31200,*/
                                        /* 33600, 38400, 57600, 115200 + 2   */

        boolean usecallerid;            /* Insert caller ID into Sysop note? */
        acstring logonacs;              /* acs string to logon this node     */
              
        char IRQ [11];
        char Address [11];              /* used only for functional MCI codes */
                                        /* %C = Comport address              */
                                        /* %E = IRQ                          */
                                        
        byte AnswerOnRing;              /* Answer after how many rings?      */
        boolean MultiRing;              /* Answer Ringmaster or some other   */
                                        /* type of multi-ring system ONLY    */
        };



struct validationrec {

        char description [26];          /* description                   */
        byte newsl;                     /* new SL                        */
        byte newdsl;                    /* new DSL                       */
        acrq newar;                     /* new AR                        */
        uflags newac;                   /* new AC                        */
        int newfp;                      /* file points to add            */
        long newcredit;                 /* new credit (added)            */
        word expiration;                /* days until expiration         */
        char expireto;                  /* validation level to expire to */
        boolean softar;                 /* TRUE=AR added to current, else replaces*/
        boolean softac;                 /* TRUE=AC    "   "   "       "      "    */ 
        char newmenu [9];               /* User start out menu */
  
        };



struct generalrec {
    
        char datapath [41];            /* DATA path                          */
        char miscpath [41];            /* MISC path                          */
        char menupath [41];            /* MENU path                          */
        char logspath [41];            /* LOGS path                          */
        char msgpath [41];             /* MSGS path                          */
        char nodepath [41];            /* NODE list path                     */
        char temppath [41];            /* TEMP path                          */
        char protpath [41];            /* PROT path                          */
        char arcspath [41];            /* ARCS path                          */

        char bbsname [41];             /* BBS name                           */
        char bbsphone [13];            /* BBS phone number                   */
        char sysopname [31];           /* SysOp's name                       */

        int lowtime;                 /* SysOp begin minute (in minutes)    */
        int hitime;                  /* SysOp end time                     */
        int dllowtime;               /* normal downloading hours begin..   */
        int dlhitime;                /* ..and end                          */
        int minbaudlowtime;          /* minimum baud calling hours begin.. */
        int minbaudhitime;           /* ..and end                          */
        int minbauddllowtime;        /* minimum baud downloading hours begin..*/
        int minbauddlhitime;         /* ..and end                          */

        long minimumbaud;            /* minimum baud rate to logon         */
        long minimumdlbaud;          /* minimum baud rate to download      */

        boolean shuttlelog;          /* Use Shuttle Logon?                 */
        boolean closedsystem;        /* Allow new users?                   */
        boolean swapshell;           /* Swap on shell?                     */

        acstring sysoppw;            /* SysOp password                     */
        acstring newuserpw;          /* newuser password                   */
        acstring minbaudoverride;    /* override minimum baud rate         */
        acstring qwknetworkacs;      /* QWK network REP acs                */

        char crapola2 [9];           /*                                    */

        acstring sop;                /* SysOp                              */
        acstring csop;               /* Co-SysOp                           */
        acstring msop;               /* Message SysOp                      */
        acstring fsop;               /* File SysOp                         */
        acstring spw;                /* SysOp PW at logon                  */
        acstring seepw;              /* see SysOp PWs remotely             */
        acstring normpubpost;        /* make normal public posts           */
        acstring normprivpost;       /* send normal e-mail                 */
        acstring anonpubread;        /* see who posted public anon         */
        acstring anonprivread;       /* see who sent anon e-mail           */
        acstring anonpubpost;        /* make anon posts                    */
        acstring anonprivpost;       /* send anon e-mail                   */
        acstring seeunval;           /* see unvalidated files              */
        acstring dlunval;            /* DL unvalidated files               */
        acstring nodlratio;          /* no UL/DL ratio                     */
        acstring nopostratio;        /* no post/call ratio                 */
        acstring nofilecredits;      /* no file credits checking           */
        acstring ulvalreq;           /* uploads require validation         */
        acstring TeleConfMCI;        /* ACS access for MCI codes while teleconfin'*/
        acstring overridechat;       /* override chat hours                */

        byte maxprivpost;            /* max email can send per call        */
        byte maxfback;               /* max feedback per call              */
        byte maxpubpost;             /* max posts per call                 */
        byte maxchat;                /* max sysop pages per call           */
        byte maxwaiting;             /* max mail waiting                   */
        byte csmaxwaiting;           /* max mail waiting for Co-SysOp +    */
        byte junk1;                  /* -------------------------------    */
        byte junk2;                  /* -------------------------------    */
        byte maxlogontries;          /* tries allowed for PW's at logon    */
        byte sysopcolor;             /* SysOp color in chat mode           */
        byte usercolor;              /* user color in chat mode            */
        int minspaceforpost;         /* minimum drive space left to post   */
        int minspaceforupload;       /* minimum drive space left to upload */

        byte backsysoplogs;          /* days to keep SYSOP##.LOG           */
        byte eventwarningtime;       /* minutes before event to warn user  */
        byte wfcblanktime;           /* minutes before blanking WFC menu   */

        boolean allowalias;          /* allow handles?                     */
        boolean phonepw;             /* phone number password in logon?    */
        boolean localsec;            /* use local security?                */
        boolean globaltrap;          /* trap everyone's activity?          */
        boolean autochatopen;        /* automatically open chat buffer?    */
        boolean autominlogon;        /* Auto-Message at logon?             */
        boolean bullinlogon;         /* bulletins at logon?                */
        boolean lcallinlogon;        /* "Last Few Callers" list at logon?  */
        boolean yourinfoinlogon;     /* "Your Info" at logon?              */
        boolean offhooklocallogon;   /* phone off-hook for local logons?   */
        boolean forcevoting;         /* manditory voting?                  */ 
        boolean compressbases;       /* "compress" file/msg base numbers?  */
        boolean searchdup;           /* search for dupes files when UL?    */
        byte slogtype;               /* log type: File/Printer/Both        */
        boolean stripclog;           /* strip colors from SysOp log?       */ 
        int newapp;                  /* send new user application to #     */
        int timeoutbell;             /* minutes before timeout beep        */    
        int timeout;                 /* minutes before timeout             */
        boolean useems;              /* use EMS for overlay                */
        boolean usebios;             /* use BIOS for video output          */
        boolean iemsi;               /* use iemsi                          */
        int alertbeep;               /* time between alert beeps           */

        filearcinforec filearcinfo [MAXARCS];  /* archive specs           */
        char filearccomment [3] [41];   /* BBS comment files for archives  */
        boolean uldlratio;              /* use UL/DL ratios?               */
        boolean filecreditratio;        /* use auto file-credit compensation?  */
        byte filecreditcomp;            /* file credit compensation ratio   */
        byte filecreditcompbasesize;    /* file credit base compensation size*/
        byte ulrefund;                  /* percent of time to refund on ULs */
        byte tosysopdir;                /* SysOp file base                 */
        boolean validateallfiles;       /* validate files automatically?   */
        int maxintemp;                  /* max K allowed in TEMP           */
        int minresume;                  /* min K to allow resume-later     */

        boolean filediz;                /* Search/Import file_id.diz       */

        word maxqwktotal;               /* max msgs in a packet, period    */
        word maxqwkbase;                /* max msgs in a base              */

        int CreditMinute;               /* Credits per minute              */
        int CreditPost;                 /* Credits per post                */
        int CreditEmail;                /* Credits per Email sent          */

        boolean sysoppword;             /* check for sysop password?       */

        int CreditFreeTime;             /* Amount of "Free" time given to user at logon*/
        boolean TrapTeleConf;           /* Trap teleconferencing to ROOMx.TRP? */

        byte RES98 [6];

        char allstartmenu [9];          /* logon menu to start users on    */
        char bulletprefix [9];          /* default bulletins filename      */

        secrange timeallow;             /* time allowance                  */
        secrange callallow;             /* call allowance                  */
        secrange dlratio;               /* # ULs/# DLs ratios              */
        secrange dlkratio;              /* DLk/ULk ratios                  */
        secrange postratio;             /* posts per call ratio            */
        secrange dloneday;              /* Max number of dload files in one day*/
        secrange dlkoneday;             /* Max k downloaded in one day     */

        char lastdate [9];              /* last system date                */
        byte curwindow;                 /* type of SysOp window in use     */
        boolean istopwindow;            /* is window at top of screen?     */
        long callernum;                 /* system caller number            */
        int numusers;                   /* number of users                 */

        char multpath [41];             /* MULT path                       */

        byte junkola [3];               /* -= NOT USED =-                  */

        boolean recompress;             /* recompress like archives?       */

        boolean rewardsystem;           /* use file rewarding system?      */

        word passwordchange;            /* change password at least every x days */

        char netmailpath [41];          /* path to netmail                 */
        acstring netmailacs;            /* do they have access to netmail? */

        int rewardratio;                /* % of file points to reward back */

        byte birthdatecheck;            /* check user's birthdate every xx logons*/ 

        acstring Invisible;             /* Invisible mode?                 */

        char fileattachpath [41];       /* directory for file attaches     */

        acstring fileattachacs;         /* acs to attach files to messages */
        acstring changevote;            /* acs to change their vote        */

        boolean trapgroup;              /* record group chats?             */ 

        boolean qwktimeignore;          /* ignore time remaining for qwk download?*/

        boolean networkmode;            /* Network mode ?                  */

        byte SwapTo;                    /* Swap where?                     */

        byte res [23];                  /* bleah                           */

        boolean windowon;               /* is the sysop window on?         */
        long regnumber;                 /* registration number             */

        boolean chatcall;               /* Whether system keeps beeping after chat*/

        char packetname [9];            /* QWK packet name                 */
        char qwkwelcome [51];           /* QWK welcome file name           */
        char qwknews [51];              /* QWK news file name              */
        char qwkgoodbye [51];           /* QWK goodbye file name           */
        char qwklocalpath [41];         /* QWK path for local usage        */

        boolean dailylimits;            /* Daily file limits on/off        */
        boolean multinode;              /* enable multinode support        */
        word daysonline;                /* days online                     */
        long totalcalls;                /* incase different from callernum */ 
        long totalusage;                /* total usage in minutes          */
        long totalposts;                /* total number of posts           */
        long totaldloads;               /* total number of dloads          */
        long totaluloads;               /* total number of uloads          */

        boolean percall;                /* time limits are per call or per day?*/
        boolean testuploads;            /* perform integrity tests on uploads?*/ 

        char Origin [51];               /* Default Origin line             */
        byte Text_Color;                /* Colour of standard text         */
        byte Quote_Color;               /* Colour of quoted text           */
        byte Tear_Color;                /* Colour of tear line             */
        byte Origin_Color;              /* Colour of origin line           */
        boolean SKludge;                /* Show kludge lines?              */
        boolean SSeenby;                /* Show SEEN-BY lines?             */
        boolean SOrigin;                /* Show origin lines?              */
        boolean AddTear;                /* Show tear line?                 */

        NetAttribs netattribute;        /* Default netmail attributes      */
        
        struct {                        /* 20 Addresses                    */
                word zone;              /* 21st is for UUCP address        */
                word net;
                word node;
                word point;

                } aka [21];
                                                                                                
        char DefEchoPath [41];          /* Default echomail path           */
        int CreditInternetMail;         /* Cost for Internet mail          */
        
        char crap5 [372];               /* Shite                           */

        validationrec validation [26];  /* Validation records A - Z        */

        char macro [10] [101];          /* sysop macros                    */
  
        };



struct smr {                            /* SHORTMSG.DAT : One-line messages */
    
        astr msg;
        int destin;

        };



struct votingr {                        /* VOTING.DAT : Voting records     */
    
        char description [66];          /* voting question                 */
        acstring acs;                   /* acs required to vote on this    */
        word choicenumber;              /* number of choices               */
        word numvoted;                  /* number of votes on it           */
        char madeby [36];               /* who created it                  */
        acstring addchoicesacs;         /* acs required to add choices     */
    
        struct {

                char description [66];  /* answer description              */
                char description2 [66]; /* answer description #2           */
                int numvoted;           /* # user's who picked this answer */
    
                } choices [25];

        };



struct mbflags {

        bit mbunhidden  : 1;    /* whether *VISIBLE* to users w/o access */
        bit mbrealname  : 1;    /* whether real names are forced         */
        bit mbcrap      : 1;    /*                                       */
        bit mbinternet  : 1;    /* if internet message base              */
        bit mbfilter    : 1;    /* whether to filter ANSI/8-bit ASCII    */
        bit mbskludge   : 1;    /* strip IFNA kludge lines               */
        bit mbsseenby   : 1;    /* strip SEEN-BY lines                   */
        bit mbsorigin   : 1;    /* strip origin lines                    */
        bit mbprivate   : 1;    /* allow private messages                */
        bit mbforceread : 1;    /* force the reading of this base        */
        bit mbScanOut   : 1;    /* Needs to be scanned out by renemail   */
        bit mbaddtear   : 1;    /* add tear/origin lines                 */
        bit mbtopstar   : 1;    /* whether Top Star for GroupMail base   */

        };


                                                                      
struct boardrec {               /* MBASES.DAT : Message base records  */

        char name [41];         /* message base description           */
        char filename [9];      /* HDR/DAT data filename              */
        char msgpath [41];      /* messages pathname                  */
        acstring acs;           /* access requirement                 */
        acstring postacs;       /* post access requirement            */
        acstring mciacs;        /* MCI usage requirement              */
        acstring sysopacs;      /* Message base sysop requirement     */
        word maxmsgs;           /* max message count                  */
        anontyp anonymous;      /* anonymous type                     */
        char password [21];     /* base password                      */
        mbflags mbstat;         /* message base status vars           */
        int mbtype;             /* base type (0=Local,1=Echo,2=Group) */
        char origin [51];       /* origin line                        */
        byte text_color;        /* color of standard text             */
        byte quote_color;       /* color of quoted text               */
        byte tear_color;        /* color of tear line                 */
        byte origin_color;      /* color of origin line               */
        byte aka;               /* alternate address                  */
        word QWKIndex;          /* QWK indexing number                */
        byte res [11];          /* RESERVED                           */
  
        };



struct fbflags {

	bit fbnoratio     : 1;   /* if <No Ratio> active                  */
	bit fbunhidden    : 1;   /* whether *VISIBLE* to users w/o access */
	bit fbdirdlpath   : 1;   /* if *.DIR file stored in DLPATH        */
	bit fbshowname    : 1;   /* show uploaders in listings            */
	bit fbusegifspecs : 1;   /* whether to use GifSpecs               */
	bit fbcdrom       : 1;   /* base is read only, no sorting or ul scanning*/
	bit fbshowdate    : 1;   /* show date uploaded in listings        */
	bit fbnodupecheck : 1;   /* No dupe check in this area            */

        };
     

struct ulrec {                 /* FBASES.DAT  : File base records         */

        char name [41];        /* area description                        */
        char filename [13];    /* filename + ".DIR"                       */
        char dlpath [41];      /* download path                           */
        char ulpath [41];      /* upload path                             */
        word maxfiles;         /* max files allowed                       */
        char password [21];    /* password required                       */
        byte arctype;          /* wanted archive type (1..max,0=inactive) */
        byte cmttype;          /* wanted comment type (1..3,0=inactive)   */
        int res1;              /* not used                                */
        fbflags fbstat;        /* file base status vars                   */ 
        acstring acs;          /* access requirements                     */
        acstring ulacs;        /* upload requirements                     */
        acstring dlacs;        /* download requirements                   */
        byte res [10];         /* RESERVED                                */

        };



struct filstat {

        bit notval      : 1;    /* if file is NOT validated */
        bit isrequest   : 1;    /* if file is REQUEST       */
        bit resumelater : 1;    /* if file is RESUME-LATER  */
        bit hatched     : 1;    /* has file been hatched?   */
        bit pad         : 4;
                        : 0;

        };



struct ulfrec {                        /* *.DIR : File records             */

        char filename [13];            /* Filename                         */
        char description [61];         /* File description                 */
        int credits;                   /* File points                      */
        word downloaded;               /* Number DLs                       */
        byte sizemod;                  /* # chars over last 128 byte block */
        word blocks;                   /* # 128 byte blks                  */
        word owner;                    /* ULer of file                     */
        char stowner [37];             /* ULer's name                      */
        char date [9];                 /* Date ULed                        */
        word daten;                    /* Numeric date ULed                */
        long vpointer;                 /* Pointer to verbose descr, -1 if none*/
        filstat filestat;              /* File status                      */
        byte res [10];                 /* RESERVED                         */
  
        };



struct verbrec {                /* EXTENDED.DAT: Extended descriptions */
  
        char descr [9] [51];
  
        };



struct lcallers {               /* LASTON.DAT : Last few callers records */

        long callernum;         /* system caller number                  */
        char name [37];         /* user name of caller                   */
        word number;            /* user number of caller                 */
        char citystate [31];    /* city/state of caller                  */
        char baud [6];          /* baud of caller                        */
        char timeon [9];        /* time logged on                        */
        word daynum;            /* day num logged on                     */
        boolean wasnew;         /* was it a new user?                    */
  
        };



struct eventrec {               /* EVENTS.DAT : Event records            */

        boolean active;         /* whether active                        */
        char description [31];  /* event description                     */
        char etype;             /* ACS,Chat,Dos,External,Pack Msgs,Sort Files */
        char execdata [21];     /* errorlevel if "E", commandline if "D" */
        boolean softevent;      /* event runs whenever "convenient"      */
        boolean missed;         /* run even even if missed               */
        boolean monthly;        /* monthly event?                        */
        boolean busyduring;     /* busy phone DURING event?              */
        int exectime;           /* time of execution                     */
        int durationorlastday;  /* length of time event takes            */
        byte offhooktime;       /* off-hook time before; 0 if none       */
        byte Enode;             /* node number to execute on (0 = all)   */
        byte execdays;          /* bitwise execution days or day of month if monthly*/
  
        };

  
  
struct mnuflags {

        bit clrscrbefore     : 1; /* C: clear screen before menu display    */
        bit dontcenter       : 1; /* D: don't center the menu titles!       */
        bit nomenuprompt     : 1; /* N: no menu prompt whatsoever?          */
        bit forcepause       : 1; /* P: force a pause before menu display?  */
        bit autotime         : 1; /* T: is time displayed automatically?    */
        bit forceline        : 1; /* F: Force full line input               */
        bit NoGenericAnsi    : 1; /* 1: DO NOT generate generic prompt if ANSI*/
        bit NoGenericAvatar  : 1; /* 2: DO NOT generate generic prompt if AVT*/
        bit NoGenericRIP     : 1; /* 3: DO NOT generate generic prompt if RIP*/
        bit NoGlobalDisplayed: 1; /* 4: DO NOT display the global commands! */
        bit NoGlobalUsed     : 1; /* 5: DO NOT use global commands          */

        };



struct menurec {                       /* *.MNU : Menu records            */
  
        char menuname [3] [101];       /* menu name                       */
        char directive [13];           /* help file displayed             */
        char longmenu [13];            /* displayed in place of long menu */
        char menuprompt [121];         /* menu prompt                     */
        acstring acs;                  /* access requirements             */
        char password [16];            /* password required               */
        char fallback [9];             /* fallback menu                   */
        byte forcehelplevel;           /* forced help level for menu      */
        byte gencols;                  /* generic menus: # of columns     */
        byte gcol [3];                 /* generic menus: colors           */
        mnuflags menuflags;            /* menu status variables           */
  
        };

  
  
struct cmdflags {
   
        bit hidden      : 1;            /* H: is command ALWAYS hidden?  */
        bit unhidden    : 1;            /* U: is command ALWAYS visible? */

        };



struct commandrec {                    /* *.MNU : Command records       */
 
        char ldesc [71];               /* long command description      */
        char sdesc [36];               /* short command description     */
        char ckeys [15];               /* command-execution keys        */
        acstring acs;                  /* access requirements           */
        char cmdkeys [3];              /* command keys: type of command */
        char options [51];             /* MString: command data         */
        cmdflags commandflags;         /* command status variables      */
  
        };

  
  
struct xbflags {
   
        bit xbactive        : 1;
        bit xbisbatch       : 1;
        bit xbisresume      : 1;
        bit xbxferokcode    : 1;
        bit xbbidirectional : 1;
        bit xbreliable      : 1;

        };



struct protrec {                       /* PROTOCOL.DAT records     */

        xbflags xbstat;                /* protocol flags           */
        char ckeys [15];               /* command keys             */
        char descr [41];               /* description              */
        acstring acs;                  /* access string            */
        char templog [26];             /* temp. log file           */
        char uloadlog [26];            
        char dloadlog [26];            /* permanent log files      */
        char ulcmd [79];
        char dlcmd [79];               /* UL/DL commandlines       */
        char ulcode [6] [7];
        char dlcode [6] [7];           /* UL/DL codes              */
        char envcmd [61];              /* environment setup cmd    */
        char dlflist [26];             /* DL file lists            */
        int maxchrs;                   /* max chrs in cmdline      */
        int logpf, logps;              /* pos in log file for data */
        byte res [15];                 /* RESERVED                 */
  
        };



struct confrec {                       /* CONFRENC.DAT : Conference data */

        struct {
      
                acstring acs;          /* access requirement             */
                char name [41];        /* name of conference             */
    
                } conference [27];
  
        };



struct nodeflags {
    
        bit NActive   : 1;      /* Is this node active?               */
        bit NAvail    : 1;      /* Is this node's user available?     */
        bit NUpdate   : 1;      /* This node should re-read it's user */
        bit NHangup   : 1;      /* Hangup on this node                */
        bit NRecycle  : 1;      /* Recycle this node to the OS        */
        bit NInvisible: 1;      /* This node is Invisible             */

        };



struct noderec {                       /* MULTNODE.DAT               */

        word User;                     /* What user number           */
        char UserName[37];            /* User's name                */
        char CityState[31];           /* User's location            */
        char Sex;                      /* User's sex                 */
        byte Age;                      /* User's age                 */
        long LogonTime;                /* What time they logged on   */
        byte Activity;                 /* What are they doing?       */
        char Description[21];         /* Optional string            */
        nodeflags Status;       
        byte Room;                     /* What room are they in?     */
        word Channel;                  /* What channel are they in?  */
        char Invited [32];             /* Have they been invited ?   */
        char Booted [32];              /* Have they been kicked off? */
        char Forget [32];              /* Who are they forgetting?   */
    
        };



struct RoomRec {                       /* ROOM.DAT                 */

        char Topic [41];               /* Set by a /T or something */
        boolean Anonymous;             /* Is Room anonymous?       */
        boolean Private;               /* Is Room private?         */
        boolean Occupied;              /* Is anyone in here?       */
        word Moderator;                /* Who's the moderator?     */
    
        };



struct scanrec {                        /* *.SCN files     */
        
        boolean NewScan;                /* Scan this base? */
        long LastRead;                  /* Last date read  */

        };



struct SchemeRec {                     /* Scheme.dat                      */
    
        char Description [31];         /* Description of the color scheme */
        byte Color [200];              /* Colors in scheme                */
    
        };

        /*  1  -   10 system colors       */
        /*  11 -   file list colors       */
        /*  28 -   msg list colors        */
        /*  45 -   file area list colors  */
        /*  55 -   msg area list colors   */
        /*  65 -   user list colors       */
        /*  80 -   who's online colors    */
        /*  100-   last on colors         */
        /*  115-   qwk colors             */
        /*  135-   email colors           */



#endif
