/*****************************************************************************/
/*>                                                                         <*/
/*>                     Telegard Bulletin Board System                      <*/
/*>         Copyright 1995,1996 by Tim Strike.    All rights reserved.      <*/
/*>                                                                         <*/
/*>                      Data types and structures                          <*/
/*>                                                                         <*/
/*****************************************************************************/
/*****************************************************************************/
/* --------------- IMPORTANT NOTICE -- PLEASE READ CAREFULLY --------------- */
/*****************************************************************************/

/*                                                           June 9th, 1996

  Note to all Telegard 3.0 developers;

  These structures are the final release structures for Telegard 3.0.

  These structures may be used to modify and create new programs which
  will be compatible with Telegard 3.0.  Enclosed with this structure kit
  are several documents which outline the various date file formats that
  Telegard 3.0 uses.  The development documentation, DEVEL300.DOC, has
  many helpful hints and information regarding most of the data files which
  Telegard uses -- please read it before attempting to use the data
  structures.

  The structures have been commented as best as possible.  If you need
  more information on how to use/access data within these structures,
  please see the accompanying documentation for contact methods.

  Several portions of these structures outline multinode capabilities.  As
  of Telegard 3.0, the BBS is not fully multinode compatible.  A release
  will be made as soon as possible which will accomodate full multinode
  features.  Until then, presume that the features that have been outlined
  in this document are up-to-date and working in Telegard 3.0.

  Thanks for your interest in Telegard 3.0.  Utility developers who wish
  more information regarding distribution should look at the accompanying
  documentation -- there are several helpful areas which should be read.

  We can use all the questions, comments and ideas that you can think of.

  Thanks,
  Telegard 3.0 Development Team

*/

#ifndef __TELEGARD_H
#define __TELEGARD_H

/*****************************************************************************/
/* ----------------------- CONSTANT DEFINITIONS ---------------------------- */
/*****************************************************************************/

#define TG_VER              "3.0"      /* TG's version this header is for */

#define MAXARCS             10         /* archive commands (1..max) */
#define MAXPROTOCOL         26         /* protocol records (A..Z)   */
#define MAXLEVEL            26         /* level records (A..Z)      */
#define MAXEVENTS           16         /* scheduled events (0..max) */
                                       /* 0 = -X[n] cmd (RESERVED)  */
#define MAXMENUCMDS         75         /* menu commands (1..max) */
#define MAXQUEUE            20         /* queue storage (1..max) */
#define NUMVOTEAS           16         /* voting answers (0..max) */
#define NUMVOTEQS           20         /* voting questions (1..max) */

#define MJAM                1          /* JAM format */
#define MSQUISH             2          /* Squish format */

#define MLOCAL              1          /* Local */
#define MNETMAIL            2          /* Netmail */
#define MECHOMAIL           3          /* Echomail */

#define MPUBLIC             1          /* Public Messages */
#define MPRIVATE            2          /* Private Messages */

#define ATNO                1          /* No anonymous allowed */
#define ATYES               2          /* Anonymus allowed */
#define ATFORCED            3          /* Forced anonymous */
#define ATDEARABBY          4          /* "Dear Abby" message base */
#define ATANYNAME           5          /* Anyname posting */

/*---------------------------------------------------------------------------*/

typedef unsigned char boolean;         /* Turbo Pascal "boolean" */
typedef unsigned char byte;            /* Turbo Pascal "byte" */
typedef signed short int integer;      /* Turbo Pascal "integer" */
typedef signed long int longint;       /* Turbo Pascal "longint" */
typedef unsigned char string;          /* Turbo Pascal "string" */
typedef unsigned short int word;       /* Turbo Pascal "word" */
typedef unsigned int bit;              /* shorthand for C bit fields */

/*****************************************************************************/
/* ------------------------ TYPE DEFINITIONS ------------------------------- */
/*****************************************************************************/

typedef string acstring[41];           /* Access Control system string */
typedef integer intrange[256];         /* security tables - integers */
typedef byte byterange[256];           /* security tables - bytes */

typedef longint unixtime;              /* unix time stamp - seconds */
                                       /* since 01/01/70 */

typedef byte acrq[4];                  /* AR Flags */
typedef acrq acrqs;                    /* AR Flags set */

typedef struct          /* user AC flags */
{
    bit rlogon : 1;                    /* L - One call per day */
    bit rchat : 1;                     /* C - Can't page the SysOp */
    bit rnetmaildel : 1;               /* F - Force Netmail deletion */
    bit ramsg : 1;                     /* A - Can't post AutoMessage */
    bit rpostan : 1;                   /* * - Can't post anonymously */
    bit rpostpvt : 1;                  /* E - Can't post private */
    bit rpostnet : 1;                  /* N - Can't post NetMail */
    bit rpost : 1;                     /* P - Can't post at all */
    bit rvoting : 1;                   /* K - Can't vote */
    bit rmsg : 1;                      /* M - Forced email deletion */
    bit rpostecho : 1;                 /* G - Can't post EchoMail */
    bit fnodlratio : 1;                /* 1 - No UL/DL ratio */
    bit fnopostratio : 1;              /* 2 - No post/call ratio */
    bit fnofilepts : 1;                /* 3 - No file points checking */
    bit fnodeletion : 1;               /* 4 - Protection from deletion */
    bit fnodailyratio : 1;             /* 5 - No daily DL ratio */
    bit fnodltime : 1;                 /* 6 - No DL time check */
    bit fnopwchange : 1;               /* 7 - No forced pw change */
    bit ftimepercall : 1;              /* 8 - Time on per call basis */
}
uflags;

typedef struct          /* Bitmapped date format */
{
    word date;                         /* date  5432109876543210 */
                                       /*       Y------M---D---- */
    word time;                         /* time  5432109876543210 */
                                       /*       H----M-----S---- */
}
bitmapdate;


/*****************************************************************************/
/* ------------------- CONFIGURATION DATA STRUCTURES ----------------------- */
/*****************************************************************************/

typedef struct          /* CONFIG.TG - System configuration */
{
    word versionid;                    /* version (eg $3000 = V3.0) */
    string datapath[80];               /* DATA path */
    string textpath[80];               /* TEXT path */
    string langpath[80];               /* LANGUAGES path */
    string menupath[80];               /* MENUS path */
    string logspath[80];               /* LOG path */
    string msgpath[80];                /* MSGS path */
    string semaphore[80];              /* SEMAPHORE path */
    string attchpath[80];              /* FILE ATTACH path */
    string swappath[80];               /* SWAP path */
    string arcpath[41];                /* ARCHIVE path */
    string protpath[41];               /* PROTOCOL path */
    string filepath[80];               /* FILE path */
    byte reserved1[120];               /* RESERVED */

    string bbsname[81];                /* BBS name */
    string bbsphone[21];               /* BBS phone number */
    string bbslocation[51];            /* BBS location */
    string sysopname[31];              /* SysOp's full name or alias */
    boolean multinode;                 /* System is Multinode? */
    string bulletprefix[9];            /* default bulletin prefix */
    boolean highbitinfo;               /* High-bit in user info? */
    byte nodecheck;                    /* NodeCheck threshold (s) */
    boolean nodetask;                  /* Node from TASK environment */
                                       /*   if -Nnn not specified */
    boolean hiddenpw;                  /* Passwords are hidden?
					    1. Always verify passwords
					       against user.pwcrc
					    2. TRUE  user.pwtext=''
					    3. FALSE check user.pwcrc
					       if crc(input)=user.pwcrc
					       then set user.pwtext=pw
					    4. If changing pw, always
					       update CRC field -- VERY
					       important! */
    byte reserved2[4];                 /* RESERVED  */
    boolean localtimeout;              /* local timeout logoff? */
    string sysoppw[21];                /* SysOp PW */
    byte timeoutbell;                  /* minutes before timeout bell */
    byte timeout;                      /* minutes before timeout logoff */
    byte backsysoplogs;                /* days to keep SYSOP##.LOG */
    byte slogtype;                     /* SysOp log type
                                                0 - File
                                                1 - Printer
                                                2 - Both */
    boolean stripclog;                 /* strip colors from SysOp log? */
    boolean compressbases;             /* "compress" base numbers? */
    byte reserved3[100];               /* RESERVED */

    word audiolowtime;                 /* Allow audio hours */
    word audiohitime;
    boolean monoscreen;                /* Monochrome screen */
    boolean useems;                    /* use EMS for overlay */
    boolean usebios;                   /* use BIOS for local video output */
    boolean cgasnow;                   /* Suppres snow on CGA systems */
    byte screensize;                   /* Screen size
                                                0 - Default/Auto
                                                1 - 25
                                                2 - 28  (VGA)
                                                3 - 43/50 (EGA/VGA) lines*/
    byte wfcblanktime;                 /* minutes to blank WFC screen */
    byte printerport;                  /* printer port (1-3) */
    byte openfiledelay;                /* OpenFile delay b/w attempts */
    byte openfileatt;                  /* OpenFile attempts */
    byte openfiletimeout;              /* OpenFile timeout message */
    byte openfileabort;                /* OpenFile timed abort */
    byte reserved4[20];                /* RESERVED */

    byte chatpagelen;                  /* Page length in seconds */
    byte chatattempts;                 /* # of chat attempts */
    byte sysopcolor;                   /* SysOp chat color */
    byte usercolor;                    /* User chat color */
    boolean chatreason;                /* ask for a chat reason? */
    boolean chattime;                  /* refund chat time? */
    string externalchat[80];           /* External chat command */
    byte chatdoortype;                 /* Chat door file type: */
                                       /*   0: none        3: WWIV */
                                       /*   1: GAP         4: PCBoard  */
                                       /*   2: RBBS-PC                */
    byte reserved5[74];                /* RESERVED */
                                                                               /* External Utilities */
    string fsecmd[41];                 /* Full screen editor command */
    byte fsedoortype;                  /* FSE door file type: */
                                       /*   0: none        3: WWIV     */
                                       /*   1: GAP         4: PCBoard  */
                                       /*   2: RBBS-PC             */
    byte swapshelltype;                /* swap shell type: */
                                       /*   0: disk        2: XMS */
                                       /*   1: EMS                 */
    boolean swaponarchive;             /* swap on archive command */
    boolean swapondoor;                /* swap on door command */
    boolean swapondosshell;            /* swap on DOS shell */
    boolean swaponevent;               /* swap on DOS Shell event */
    boolean swaponfse;                 /* swap on full-screen editor */
    boolean swaponsysbat;              /* swap on system batch files */
    boolean swaponxfer;                /* swap on file transfer */
    boolean swapshell;                 /* swap shell function enabled? */
    word envspace;                     /* DOS Environment space */
    byte reserved6[48];                /* RESERVED */

    intrange timeallow;                /* daily time */
    byterange callallow;               /* daily calls */
    byterange dlratio;                 /* # ULs/# DLs ratios */
    intrange dlkratio;                 /* DLK/ULK ratios */
    byterange postratio;               /* post/call ratios */
    byterange dailyratio;              /* daily DL #files ratios */
    intrange dailykratio;              /* daily DL KB ratios */
    intrange timebankmax;              /* timebank max limit */
    byterange timedeposit;             /* timebank daily deposit */
    byterange timewithdraw;            /* timebank daily withdraw */

    byte ansitype;                     /* ANSI Logon -
                                              0  Ask
                                              1  Detect
                                              2  Force NO
                                              3  Force YES */
    byte lastcallers;                  /* days of last callers */
    byte maxlogontries;                /* tries for PW's at logon */
    byte maxlogonmins;                 /* minutes allowed for logon */
    boolean allowalias;                /* allow aliases? (handles) */
    boolean datapw;                    /* data phone # password */
    boolean voicepw;                   /* voice phone # password */
    boolean localsec;                  /* is local security ON? */
    boolean displaysec;                /* is local screen-security ON? */
    boolean globaltrap;                /* trap ALL USER'S activity? */
    boolean autochatopen;              /* does chat buffer auto-open? */
    boolean languagefirst;             /* language section first? */
    byte reserved6a;                   /* bulletins in logon? */
    byte lcallinlogon;                 /* "Last Calls" list in logon? */
    byte reserved7;                    /* RESERVED */
    boolean offhooklocallogon;         /* phone off-hook for local? */
    boolean forcevoting;               /* logon voting mandatory? */
    boolean iemsi;                     /* allow IEMSI logons */
    boolean checkmulti;                /* check for multiple logons */
    byte reserved8[41];                /* RESERVED */
    string logonmenu[9];               /* logon menu to start users on */
    string watcharea[9];               /* area for pw attempt warnings */
    string inquiryarea[9];             /* area for forgotten PW inquiry */
    word passdays;                     /* # of days to change password */
    boolean updatelocal;               /* local calls in statistics */
    boolean timeleftbank;              /* timebank prompt w/no time? */
    longint minbaud;                   /* minimum logon baudrate */
    longint graphicsbaud;              /* minimum graphics baudrate */
    byte reserved9[63];                /* RESERVED */

    string newapp[37];                 /* new user letter to user */
    boolean opensystem;                /* allow new users? */
    boolean newiemsi;                  /* allow IEMSI new user logons */
    byte linelen;                      /* default video line length */
    byte pagelen;                      /* default video page length */
    byte datefmt;                      /* date format - 0 ASK */
    boolean scanphone;                 /* scan for duplicate phone #'s? */
    boolean autopassword;              /* allow auto-created PW's? */
    string language[9];                /* default language, ''  ASK */
    byte ansi;                         /* ANSI               0  ASK */
    byte avatar;                       /* Avatar             1  YES */
    byte clrscr;                       /* Clear Screen       2  NO */
    byte pause;                        /* screen pause */
    byte hotkeys;                      /* Hotkeys */
    byte fse;                          /* Full Screen Editor */
    boolean mailaddress;               /* Ask for  Mail Address? */
    boolean gender;                    /*          Gender? */
    boolean dataph;                    /*          Data Phone? */
    boolean voiceph;                   /*          Voice Phone? */
    boolean dob;                       /*          Date of Birth? */
    char newuserlevel;                 /* New User Level */
    byte flinput;                      /* Full-line input   0 Ask
                                                            1 Yes
                                                            2 No */
    byte countryinput;                 /* Country input   0 Ask 
                                                          1 U.S.
                                                          2 Canada
                                                          3 Int'l */
    boolean killcolor;                 /* Strip colour from entry fields */
    byte reserved10[30];               /* RESERVED */

    acstring crosspost;                /* Cross-post message ACS */

    string batchfileext[4];            /* batch filename extension */
    byte reserved11[32];               /* RESERVED */

    word minspaceforpost;              /* minimum drive space to post */
    boolean emaillist;                 /* allow email user listing? */
    boolean smartquote;                /* use smartquote features? */
    boolean quickquote;                /* use quickquote features? */
    acstring ccmail;                   /* ACS to carbon copy messages */
    acstring creq;                     /* ACS for request confirm receipt */
    acstring fileattach;               /* ACS to attach file */
    acstring normpubpost;              /* ACS to post public messages */
    acstring normprivpost;             /* ACS to post private messages */
    acstring normnetpost;              /* ACS to post netmail messages */
    acstring nopostratio;              /* ACS for no post/call ratio */
    acstring anonpubread;              /* ACS see who posted public anon */
    acstring anonprivread;             /* ACS see who posted private anon */
    acstring anonpubpost;              /* ACS to post anon public messages */
    acstring anonprivpost;             /* ACS to post anon private message */
    boolean netconfirm;                /* honor confirmation request */
    boolean msguploads;                /* allow upload of messages? */
    boolean nodelookup;                /* allow nodelist lookup */
    acstring fileattachnet;            /* ACS attach file - netmail */
    boolean antiqueUUCP;               /* antique UUCP; UUCP in header,
                                             TO: in message text */   
    string writescanlog[41];           /* path to ECHOMAIL.JAM/NETMAIL.JAM */
    boolean checkfsesave;              /* confirm FSE save? */
    byte reserved13[15];               /* RESERVED */

    acstring sop;                      /* SysOp ACS */
    acstring csop;                     /* C-SysOp ACS */
    acstring spw;                      /* SysOp PW at logon ACS */

    byte wfc[15];                      /* WFC Menu Colours */
    boolean heartbeat;                 /* WFC "Heartbeat" */
    byte reserved14[25];               /* RESERVED */

    string qwkpktname[9];              /* packet name */
    string qwkwelcomefile[9];          /* BBS welcome file */
    string qwknewsfile[9];             /* BBS news file */
    string qwkgoodbyefile[9];          /* BBS goodbye file */
    string qwklocaldlpath[41];         /* local QWK download path */
    string qwklocalulpath[41];         /* local REP upload path */
    byte reserved15[41];               /* RESERVED */
    word qwkmaxmsgs;                   /* max messages to DL (0=unlim) */
    string qwkarc[4];                  /* default archive */
    boolean qwkextctrl;                /* extended CONTROL.DAT info ? */
    string qwknewsgen[61];             /* news program */
    string qwkfilesgen[61];            /* new files program */
    byte qwknews;                      /* include news        0 Ask */
    byte qwkwelcome;                   /* include welcome     1 Yes */
    byte qwkgoodbye;                   /* include goodbye     2 No */
    byte qwknewfiles;                  /* include new files list */
    byte qwksession;                   /* include session texts */

    byte reserved16[95];               /* RESERVED */

    string ulbase[9];                  /* default UL base */
    boolean showulname;                /* show upload name */
    acstring blindulacs;               /* blind upload ACS */
    byte filetest;                     /* file upload test type
                                             0 : none
                                             1 : archive integrity
                                             2 : upload processor */
    acstring filepwacs;                /* ACS for users to add pw */
    boolean truncdesc;                 /* truncate file_id/testinfo
					     imported descriptions */
    byte drive_tblupd;                 /* CD-ROM drive table update
					     0 : every call
                                             1-254 : once every n hours
                                             255 : never */
    boolean searchdup;                 /* search for dupe filenames? */
    boolean globaldl;                  /* global downloads allowed? */
    boolean allowdldesc;               /* allow description download? */
    boolean importfileid;              /* import file descriptions? */
    boolean nodupeext;                 /* no check of extension on dupe files? */
    boolean valallfiles;               /* validate files automatically? */
    byte unlistfp;                     /* file points for unlisted DLs */
    byte ulrefund;                     /* percent time refund for ULs */
    byte dlchecktype;                  /* DL checking (0=off,1=UL/DL,2=points) */
    word maxintemp;                    /* max KB allowed in TEMP\ARC\ */
    word minspaceul;                   /* minimum KB drive space left to upload */
    word ulfpkbyte;                    /* UL K-bytes per file point */
    word ulfpforfile;                  /* UL # points assigned to file */
    word ulfpforuser;                  /* UL # points assigned to user */
    string sysopulbase[9];             /* file base for SysOp uploads */
    acstring seeunval;                 /* ACS to see unvalidated files */
    acstring dlunval;                  /* ACS to DL unvalidated files */
    acstring ulvalreq;                 /* UL validation not-required */
    string virusscanner[81];           /* Virus Scanner Command */
    byte passederrlvl;                 /* Passed Scanner Errorlevel */
    byte gifspectype;                  /* Gifspec type     0 Last line */
                                       /*                  1 Before*  */
                                       /*  *-old method, desc is      */
                                       /*    truncated if necessary   */
    boolean useTESTINFO;               /* import TESTINFO.DAT -- if */
                                       /* virus scanner creates it.  */
    string testpath[41];               /* path to TESTINFO.DAT */
    boolean textview;                  /* allow text w/archive view */
    boolean pausebefore;               /* pause list before next dir */
    acstring dlunavail;                /* dl unavailable (failed) files */
}
configrec;

typedef struct          /* SYSTEM.DAT - System operational variables */
{
    byte usereditlvl;                  /* type of user editor */
                                       /*   0 - 2,  Short - Long */
    byte curwindow;                    /* type of SysOp window */
    boolean istopwindow;               /* SysOp window on top? */
    longint callernum;                 /* total number of callers */
    boolean windowon;                  /* is SysOp window on? */
    byte reserved[400];                /* RESERVED */
}
systemrec;

/*****************************************************************************/
/* ----------------------- USER DATA STRUCTURES ---------------------------- */
/*****************************************************************************/

typedef struct          /* USERS.DAT status flags */
{
    bit lockedout : 1;                 /* if locked out */
    bit udeleted : 1;                  /* if deleted */
    bit trapactivity : 1;              /* if trapping users activity */
    bit trapseparate : 1;              /* if trap to separate TRAP file */
    bit chatauto : 1;                  /* if autochat trapping */
    bit chatseparate : 1;              /* if separate chat file to trap to */
    bit slogseparate : 1;              /* if separate SysOp log kept */
    bit alert : 1;                     /* alert SysOp when use logs on */
}
userstatus;

typedef struct          /* USERS.DAT - User flags */
{
    bit newusermsg : 1;                /* sent newuse message? */
    bit clsmsg : 1;                    /* clear screen before messages? */
    bit flinput : 1;                   /* full line input? */
    bit hotkey : 1;                    /* menu hotkeys active */
    bit pause : 1;                     /* pause? */
    bit novice : 1;                    /* user is at novice help level */
    bit hiddenlog : 1;                 /* not displayed in call/online listing */
    bit hiddenlist : 1;                /* not displayed in user listings */
}
userflags;

typedef struct          /* USERS.DAT - User account records */
{
    string name[37];                   /* user name */
    string realname[37];               /* real name */
    string street[31];                 /* mail address */
    string location[31];               /* city, province */
    string postalcode[11];             /* postal code */
    string voiceph[21];                /* voice phone # */
    string dataph[21];                 /* data phone # */

    string pwtext[21];                 /* user password */

    /* DEVELOPERS NOTE:  The pwtext field *may* be empty.  Please observe
     the following when updating passwords:

        1. All password input is UPPERCASE
        2. If ConfigRec.HiddenPW = TRUE, then only the CRC32 of the password
           is stored in the user record (userrec.crcpw). 
        3. If ConfigRec.HiddenPW = FALSE, both the CRC32 and the actual
           password are stored in the user record.
       *4. When checking input passwords against the file, only the CRC32
           value should be tested (the pwtext may or may not be correct).  
           If ConfigRec.HiddenPW = FALSE, and the pwtext field is EMPTY, 
           then after a correct password the field will be automatically
           updated.  If ConfigRec.HiddenPW = TRUE, the pwtext will *not* be 
           updated (this is obvious).
       *5. Passwords should *only* be displayed (pwtext) if the CRC32 of
           the pwtext field *matches* the pwcrc field.  Otherwise, the 
           pwtext field is likely incorrect.  When changing passwords, the
           user should be prompted only, not shown their previous password.
    */    

    unixtime lastdate;                 /* laston date/time */
    string firstdate[9];               /* firston date */
    string pwdate[9];                  /* last date of PW change */
    string birthdate[9];               /* Birth date */
    char gender;                       /* gender - M/F */
    string subdate[9];                 /* subscription started */
    string expiredate[9];              /* subscription expires */
    char expireto;                     /* expire to level A - Z, !=Delete */

    string comment[41];                /* SysOp comment on user */
    string notes[3][41];               /* SysOp definable variables (notes files) */
    string lockfile[9];                /* lockout msg to print */

    longint pwcrc;                     /* CRC-32 of users password */

    byte reserved1[14];                /* RESERVED */
    byte ugraphics;                    /* user graphics protocol
                                             0 : TTY - no fallback
                                             1 : ANSI
                                             2 : Avatar
                                             3 : RIP    */
    byte fallback;                     /* 2nd fallback protocol
                                             1 : ANSI
                                             2 : Avatar
                                             3 : RIP
                                             3rd TTY */
    byte linelen;                      /* line length (# cols) */
    byte pagelen;                      /* page length (# rows) */
    userflags flags;                   /* flags (see above) */
    userstatus status;                 /* status (see above) */
    byte reserved2;                    /* RESERVED */

    byte sl;                           /* SL */
    uflags ac;                         /* user flags */
    acrqs aflags1;                     /* Access flags - Set 1 */
    acrqs aflags2;                     /* Access flags - Set 2 */
    longint userID;                    /* unique User-ID - THIS VALUE
                                          SHOULD NOT BE CHANGED BY ANY
                                          PROGRAM!! */
    char level;                        /* current validation level */
    byte datefmt;                      /* Date Format
                                          0 - MM/DD/YY
                                          1 - DD/MM/YY
                                          2 - YY/MM/DD */
    byte reserved7;                    /* RESERVED */
    longint macroptr;                  /* pointer for MACROS.DAT (-1 = none) */
    longint votedate;                  /* last vote */
    byte reserved3[17];                /* RESERVED */

    char lastgroup;                    /* last group */
    word lastmsg;                      /* last message base # */
    word pubpost;                      /* # public posts */
    word privpost;                     /* # private posts */
    word netpost;                      /* # netmail posts */
    string mailbox[37];                /* mailbox status
                                          ''        Open/Normal
                                          'CLOSED'  Closed
                                          Username  Forwarded to... */
    longint credit;                    /* NetMail points (credit) */
    longint debit;                     /* NetMail points (debit) */
    byte fsetype;                      /* FSE usage (0=never,1=always,2=ask) */
    byte reserved4[32];                /* RESERVED */

    string qwkarc[4];                  /* QWK default archiver */
    boolean qwkfromyou;                /* bundle from user */
    boolean qwkbwctrl;                 /* create BW control file? */
    boolean qwknews;                   /* include news? */
    boolean qwkwelcome;                /* include welcome? */
    boolean qwkgoodbye;                /* include goodbye? */
    boolean qwknewfiles;               /* include new files list? */
    boolean qwkpointer;                /* include pointer file? */
    boolean qwksession;                /* include session listing? */
    byte reserved5[23];                /* RESERVED */

    char defprotocol;                  /* default protocol (A-Z)
                                          ! = Select at download time */
    word lastfile;                     /* last file base # */
    word uploads;                      /* amount ULed (files) */
    word downloads;                    /* amount DLed (file) */
    word todaydl;                      /* amount DLed today (files) */
    longint uk;                        /* amount ULed (kbytes) */
    longint dk;                        /* amount DLed (kbytes) */
    longint todaydk;                   /* amount DLed today (kbytes) */
    longint filepoints;                /* file points remaining */

    longint totaltime;                 /* total time on system */
    word timebank;                     /* # mins in Time Bank */
    word totalcalls;                   /* total calls to system */
    integer tltoday;                   /* time left today */
    integer tbtoday;                   /* bank activit +/- time */
    byte todaycalls;                   /* calls to system today */
    byte illegal;                      /* illegal logons */
    byte vote[NUMVOTEQS];              /* voting data */
    string language[9];                /* langauge */
    byte reserved6;                    /* RESERVED */
}
userrec;

typedef struct          /* USERS.IDX - Sorted names listing */
{
    string name[37];                   /* user name */
    integer number;                    /* user record # */
                                       /*     -1 = Deleted */
}
useridxrec;

typedef struct          /* USERID.IDX - Sorted ID listing */
{
    longint userID;                    /* User-ID from user record */
    integer number;                    /* user record # */
                                       /*     -1 = Deleted */
}
IDidxrec;

/*****************************************************************************/
/* ----------------------- AREA DATA STRUCTURES ---------------------------- */
/*****************************************************************************/

typedef struct          /* FAREAS.IDX/MAREAS.IDX - Area index records */
{
    string name[9];                    /* base filename */
    integer number;                    /* base record # */
                                       /*     -1 = Deleted */
}
areaidxrec;

/*****************************************************************************/
/* ---------------------- FILE AREA DATA STRUCTURES ------------------------ */
/*****************************************************************************/

typedef struct          /* FAREAS.DAT status flags */
{
    bit fbnoratio : 1;                 /* <No Ratio> active */
    bit fbvisible : 1;                 /* Visible to users w/o access? */
    bit fbRESERVED1 :1;                /* RESERVED */
    bit fbcdrom : 1;                   /* CD-ROM/read-only media */
    bit fbusegifspecs : 1;             /* whether to use GifSpecs */
}
fareaflags;

typedef struct          /* FAREAS.DAT - File base records */
{
    string desc[41];                   /* area description */
    string filename[9];                /* filename */
    string infofile[9];                /* info filename */
    string path[41];                   /* path */
    string arctype[4];                 /* archive (''=inactive) */
    byte reserved1;                    /* RESERVED */
    fareaflags fstatus;                /* file area status */
    acstring sysopacs;                 /* SysOp access */
    acstring listacs;                  /* list/view access */
    acstring nameacs;                  /* see uploader name access */
    acstring ulacs;                    /* upload access */
    acstring dlacs;                    /* download access */
    byte scantype;                     /* scan type    0=Default ON
                                                       1=Default OFF
                                                       2=Always */
    string cdlabel[12];                /* CD-ROM label */
    unixtime createdate;               /* base creation date */
    string filepath[41];               /* *.FB? storage path */
    byte reserved2[42];                /* RESERVED */
}
farearec;

typedef struct          /* FILES.IDX - File index record */
{
    string filename[13];               /* filename [key] */
    integer filebase;                  /* filebase */
                                       /*    -1 = Deleted */
    integer filerecord;                /* file offset */
    byte reserved[4];                  /* RESERVED */
}
fileidxrec;

typedef struct          /* *.FB status flags */
{
    bit freedl : 1;                    /* if file is free */
    bit notime : 1;                    /* if file is time check free */
    bit validated : 1;                 /* if file is validated */
    bit available : 1;                 /* if file is available - will */
                                       /*    be toggled FALSE only */
                                       /*    if failed by filescan */
    bit offline : 1;                   /* if file is offline */
    bit hatch : 1;                     /* if file hatched via SDS */
}
fbstat;

typedef struct          /* *.FB File records */
{
    string filename[13];               /* filename */
    string description[46];            /* description */
    longint extended;                  /* pointer to extended desc */
                                       /*    -1 = no extended desc */
    longint size;                      /* length of file (bytes) */
    unixtime uldate;                   /* date uploaded */
    unixtime filedate;                 /* date on file */
    unixtime dldate;                   /* date last downloaded */
    fbstat filestatus;                 /* file status */
    word filepoints;                   /* points */
    word downloads;                    /* number of downloads */
    string uploader[37];               /* uploader's name */
    longint passwordCRC;               /* CRC of password to dl */
    byte reserved[20];                 /* RESERVED */
}
fbrec;

typedef struct          /* *.FBE Extended descriptions */
{
    string filename[13];               /* filename (for reference) */
    string desc[5][46];                /* description */
    longint nextlink;                  /* offset to next record */
                                       /*      -1 = last record */
    byte reserved[10];                 /* RESERVED */
}
fbextrec;

/*
   The record offset into the *.FSI file is userrec.userid-1 (ie, if userid
   field = 2 then the record offset into file scan tables file is 1). */

typedef struct          /* *.FSI File scan records */
{
    boolean filescan;                  /* base in file scan */
}
fbscanrec;

typedef struct          /* DRIVES.DAT : CDROM/Network label storage */
{
    unixtime update;                   /* last update */
    byte disktype[26];                 /* drive type
                                            0-2: None, Floopy, HD
                                            3 : CDROM
                                            4 : Network */
    string disklabel[26][12];          /* drive labels */
}
driverec;

typedef struct          /* *.QQQ transfer queue record */
{
    string filename[13];               /* filename */
    longint filearea;                  /* filebase # */
                                       /* UL -1   SysOp Area */
    string desc[46];                   /* description */
    longint extended;                  /* extended descriptions in *.QQD */
    string path[56];                   /* DL: path of file */
    longint filepw;                    /* UL: File password */
    byte reserved;                     /* RESERVED */
    integer points;                    /* DL: # file points */
    longint filesize;                  /* DL: filesize (bytes) */
    boolean freeratio;                 /* DL: file is FREE ratio */
    boolean freetime;                  /* DL: file is FREE time */
    boolean readonly;                  /* DL: file is on read-only media */
}
queuerec;

/*****************************************************************************/
/* -------------------- MESSAGE AREA DATA STRUCTURES ----------------------- */
/*****************************************************************************/

typedef struct          /* MAREAS.DAT status flags */
{
    bit mbrealname : 1;                /* real names are forced */
    bit mbvisible : 1;                 /* visible to users w/o access */
    bit mbansi : 1;                    /* filter ANSI */
    bit mb8bit : 1;                    /* filter 8-bit */
    bit mbstrip : 1;                   /* strip center/title codes */
    bit mbaddtear : 1;                 /* add tear/origin lines */
    bit mbnopubstat : 1;               /* messages not added to user */
                                       /*   public post total - i.e. */
                                       /*   will not calculate in PCR */
    bit mbnocredit : 1;                /* Netmail credit not used */
    bit mbinternet : 1;                /* Internet (UUCP) handling */
    bit mbfileattach : 1;              /* allow file attaches */
    bit mbstripcolour : 1;             /* strip TG color codes */
}
mareaflags;

typedef struct          /* MAREAS.DAT - Message base records */
{
    string name[41];                   /* message base description */
    string msgpath[41];                /* messages pathname */
    string filename[9];                /* data filenames */
    string infofile[9];                /* base info filename */
    acstring readacs;                  /* read access */
    acstring postacs;                  /* post access */
    acstring sysopacs;                 /* SysOp access */
    acstring netacs;                   /* network access */
    word maxmsgs;                      /* max message count */
    word maxdays;                      /* max days to kee messages */
    mareaflags mstatus;                /* status */
    byte mbformat;                     /* message base format */
    byte mbtype;                       /* message base type */
    byte anonymous;                    /* anonymous type */
    byte mbpost;                       /* message base posting type */
    string origin[51];                 /* origin line */
    byte kludge_color;                 /* color of kludge line */
    byte quote_color;                  /* color of quoted line */
    byte tear_color;                   /* color of tear line */
    byte origin_color;                 /* color of origin line */
    byte addr;                         /* network address # */
    byte scantype;                     /* scan type    0 = Default ON
                                                       1 = Default OFF
                                                       2 = Mandatory */
    unixtime createdate;               /* base creation date */
    longint qwkindex;                  /* QWK-permanent index */
    byte text_color;                   /* color of text line */
    byte reserved[40];                 /* RESERVED */
}
marearec;

/*
   The record offset into the *.MSI file is userrec.userid-1 (ie, if userid
   field = 2 then the record offset into message scan tables file is 1).
   This is the same offset that is used for the Squish (*.SQL) last read
   files.  The JAM (*.JLR) records can be searched for the matching userID
   to load lastread record. */

typedef struct          /* *.MSI : Message scan/lastread pointers */
{
    boolean mailscan;                  /* base in mail scan */
    boolean qwkscan;                   /* base in qwk scan */
}
mbscanrec;

typedef struct          /* QWK.IDX - QWK message base index */
{
    integer areanum;                   /* QWK area number */
    string areatag[9];                 /* message base filename */
}
qwkidxrec;

typedef struct          /* packetid.QPT - QWK lastread pointer record */
{
    integer areanum;                   /* QWK area number */
    longint lastread;                  /* last read pointer */
}
qptrrec;

/*****************************************************************************/
/* ----------------------- OTHER DATA STRUCTURES --------------------------- */
/*****************************************************************************/

typedef struct          /* Menu header status flags */
{
    bit clrscrbefore : 1;              /* C - clrscr before menu? */
    bit dontcenter : 1;                /* D - don't center titles! */
    bit forcefullline : 1;             /* F - force full line input */
    bit nomenuprompt : 1;              /* N - no menu prompt */
    bit forcepause : 1;                /* P - force pause before menu? */
    bit autotime : 1;                  /* T - auto time display? */
    bit dontcentersub : 1;             /* S: don't center subtitles! */
    bit forcekey : 1;                  /* K: force key input */
}
menuflags;

typedef struct          /* *.MNU Menu header */
{
    string menutitle[3][101];          /* menu titles */
    string dispfile[13];               /* help file displayed */
                                       /*  ''        Generic */
    string helpfile[13];               /* tutorial help file */
                                       /*     ''      Generic */
                                       /*   '*OFF*'   Disabled */
    string prompt[121];                /* menu prompt */
    acstring menuacs;                  /* access requirements */
    string password[16];               /* password required */
    string fallback[9];                /* fallback menu */
    byte helplevel;                    /* forced help level for menu */
    byte columns;                      /* generic menu: # of columns */
    byte colours[6];                   /* generic menu: colors */
    menuflags menuflags;               /* menu status variables */
    boolean global;                    /* load global menu */
    word reserved1;                    /* RESERVED */
    string nodestat[37];               /* Who's Online Status */
    byte reserved2[10];                /* RESERVED */
}
menurec;

typedef struct          /* *.MNU  Command records */
{
    string ldesc[71];                  /* long description */
    string sdesc[36];                  /* short description */
    byte reserved[16];                 /* RESERVED */
    string keys[15];                   /* execute keys */
                                       /*   'FIRSTCMD' = Exec. Menu Loaded */
                                       /*   'TITLE' = Sub-title */
                                       /*   'ENTER' = <ENTER> */
                                       /*   'SPACE' = <SPACEBAR> */
    acstring acs;                      /* access requirements */
    string cmdtype[3];                 /* command type */
    string options[51];                /* command options */
    byte viewtype;                     /* display of command */
                                       /*    0   ACS dependent */
                                       /*    1   Always visible */
                                       /*    2   Always hidden */
}
commandrec;

/*---------------------------------------------------------------------------*/

typedef struct          /* *.BBS - BBS Listings */
{
    string phone[21];                  /* BBS phone number */
    string name[31];                   /* BBS name */
    string sysop[31];                  /* BBS SysOp name */
    string description[31];            /* Other Description */
    string speed[5];                   /* Speed */
    string software[9];                /* Software */
    unixtime firstdate;                /* First date added */
    unixtime lastedit;                 /* Last date edited */
    string editor[37];                 /* entry editor */
}
bbslistrec;

/*---------------------------------------------------------------------------*/

typedef struct          /* ARCHIVE.DAT - Archiver Setup */
{
    boolean active;                    /* is this format active? */
    string extension[4];               /* archive extension */
    string description[51];            /* archiver description */
    string compress[51];               /* pack archive command */
    string decompress[51];             /* unpack archive command */
    string test[51];                   /* test archive command */
    string view[51];                   /* view archive command */
                                       /*  '' = internal (if avail)  */
    string comment[51];                /* comment archive command */
    byte success;                      /* sucess errorlevel */
    boolean viewcapture;               /* redirect external viewer */
    byte reserved[34];                 /* RESERVED */
}
archiverec;

/*---------------------------------------------------------------------------*/

typedef struct           /* GROUPS.DAT - Groups data */
{
   acstring acs;                       /* ACS requirement */
   string name[41];                    /* name of group */
   boolean visible;                    /* visible w/o ACS */
   byte reserved[20];
}
groupsrec[27];                         /* groups @, A-Z */

/*---------------------------------------------------------------------------*/

typedef struct          /* EVENTS.DAT status flags */
{
    bit active : 1;                    /* event is active */
    bit busyduring : 1;                /* phone off-hook during event */
    bit monthly : 1;                   /* event is executed monthly */
    bit forced : 1;                    /* event is forced */
}
eventflags;

typedef struct          /* EVENTS.DAT - Scheduled event records */
{
    eventflags flags;                  /* status flags */
    string desc[31];                   /* description */
    char etype;                        /* Event type:
                                                A:ACS,
                                                C:Chat,
                                                E:External,
                                                O:OS */
    string execdata[41];               /* Event data:
                                                ACS:  ACS command
                                                OS:   OS command
                                                Exit: ERRORLEVEL for exit */
    word exectime;                     /* execution time (minutes) */
    word duration;                     /* event duration (minutes) */
    byte execdays;                     /* monthly: day (1-28) */
                                       /* daily: days (bitwise) */
    unixtime lastexec;                 /* date event last executed */
    word node;                         /* affected nodes (0=all) */
}
eventrec[MAXEVENTS];

/*---------------------------------------------------------------------------*/

typedef struct          /* HISTORY.DAT - History logs */
{
    string date[9];                    /* history date */
    word userbaud[26];                 /* logon BPS rates */
                                       /*      0 - Local   10 - 16800 */
                                       /*      1 - 300     11 - 19200 */
                                       /*      2 - 1200    12 - 21600 */
                                       /*      3 - 1275    13 - 24000 */
                                       /*      4 - 2400    14 - 26400 */
                                       /*      5 - 4800    15 - 28800 */
                                       /*      6 - 7200    16 - 38400 */
                                       /*      7 - 9600    17 - 57600 */
                                       /*      8 - 12000   18 - 64000 */
                                       /*      9 - 14400   19 - 115200 */
    word active;                       /* % activity */
    word calls;                        /* # of calls */
    word newusers;                     /* # of new users */
    word pubpost;                      /* # of public posts */
    word privpost;                     /* # of private posts */
    word netpost;                      /* # of netmail posts */
    word criterr;                      /* # of critical errors */
    word uploads;                      /* # of uploads */
    word downloads;                    /* # of downloads */
    longint uk;                        /* amount ULed in KB */
    longint dk;                        /* amount DLed in KB */
    byte reserved[16];                 /* RESERVED */
}
historyrec;

/*---------------------------------------------------------------------------*/

typedef struct          /* IEMSI.DAT - IEMSI connection record */
{
    string realname[37];               /* User's Real Name */
    string handle[37];                 /* User's Handle */
    string location[31];               /* User's Location */
    string dataph[21];                 /* User's Data Phone # */
    string voiceph[21];                /* User's Voice Phone # */
    string password[21];               /* User's Password */
    unixtime birthdate;                /* User's Birthdate */
    byte linelen;                      /* Screen Width */
    byte pagelen;                      /* Screen Length */
    byte screentype;
    string protocols[11];              /* Protocol to use */
                                       /*      DZA* DirectZAP Zmodem
                                               ZAP* ZedZap Zmodem -> 8K
                                               ZMO  Zmodem -> 1K (Z)
                                               SLK* SEAlink
                                               KER* Kermit  */
    string capabilities[26];           /* System Capabilities */
                                       /*      CHT*    IEMSI chats
                                               MNU*    Image Downloading
                                               TAB*    TAB support
                                               ASCII8* 8-bit ASCII supprt */
    string requests[41];               /* Requests */
                                       /*      NEWS    Bulletins, news, etc.
                                               MAIL*   Logon - Mail Check
                                               FILE*   Logon - File Check
                                               HOT     Hot-Keys
                                               CLR     Screen clearing
                                               HUSH*   Do not disturb
                                               MORE    Page pausing
                                               FSED    Full-screen editor */
    string software[71];               /* Terminal Software */
}
iemsirec;

    /*
    *These items are are currently not supported in Telegard because they
    are things which were provided for systems with these capabilities.  They
    are listed here for convenience and so that utility authors can make
    use of them if neccessary.  Some of these options may be used in
    future versions of Telegard.

    (Z)The protocol that is selected by having the ZMO flag is protocol Z.
    If that protocol does not exist, it is not selected.  Protocol Z should
    be ZMODEM, otherwise the wrong protocol may be selected! */

/*---------------------------------------------------------------------------*/

typedef struct          /* LANGUAGE.DAT - Language records */
{
    string filename[9];                /* language filename */
    string desc[31];                   /* language description */
    acstring acs;                      /* language ACS */
    string textpath[76];               /* primary text path */
    string menuspath[76];              /* primary menus path */
                                       /*   '' = use default */
    boolean checktext;                 /* if primary path <> '' */
    boolean checkmenus;                /*   and file not found, check */
                                       /*   default path? */
}
languagerec;


/*---------------------------------------------------------------------------*/

typedef struct          /* LASTON.DAT  - Last callers records */
{
    longint caller;                    /* system caller number */
    string realname[37];               /* real name of caller */
    string handle[37];                 /* user name of caller */
    string location[31];               /* location of caller */
    longint logonspeed;                /* logon speed */
    unixtime logontime;                /* logon time */
    boolean newuser;                   /* was newuser? */
    byte reserved1;                    /* RESERVED */
    boolean hidden;                    /* hidden from display */
    byte node;                         /* node number */
    unixtime logofftime;               /* logoff time */
    word uploads;                      /* number of uploads */
    word downloads;                    /* number of downloads */
    longint uk;                        /* number of upload kB */
    longint dk;                        /* number of download kB */
    byte reserved2[8];                 /* RESERVED */
}
lcallers;

/*---------------------------------------------------------------------------*/

typedef struct          /* LEVELS.DAT - Membership/validation levels */
{
    string desc[51];                   /* Description */
    byte sl;                           /* SL level */
    acrqs flags1;                      /* Access flags - Set 1 */
    acrqs flags2;                      /* Access flags - Set 2 */
    uflags ac;                         /* Restriction flags */
    word addfp;                        /* Bonus FilePoinsts (added) */
    word addcredit;                    /* Bonus NetCredits (added) */
    word addtb;                        /* Bonus Timebank (added) */
    word expireday;                    /* Expire in ## days */
                                       /*      0 = Never */
    char tolevel;                      /* Expire to level A thru Z */
                                       /*      ! = Delete */
    byte reserved[25];                 /* RESERVED */
}
levelsrec;

/*---------------------------------------------------------------------------*/

typedef struct          /* MACRO.DAT - Keyboard macro records */
{
    longint userid;                    /* User-ID - from user record
                                            checked to verify that macro
                                            pointers are to the correct
                                            macros */
    string macro[4][241];              /* stored keystrokes */
}
macrorec;

/*---------------------------------------------------------------------------*/

typedef struct          /* MODEM.DAT/MODEMnnn.DAT status flags */
{
    bit xonxoff : 1;                /* XON/XOFF (software) flow ctl */
    bit ctsrts : 1;                 /* CTS/RTS (hardware) flow ctl */
    bit dtrdrop : 1;                /* drop DTR to hangup modem */
    bit fossilhot : 1;              /* FOSSIL active during DOS */
    bit int14 : 1;                  /* INT 14 driven (no fossil) */
}
modemflags;

typedef struct          /* MODEM.DAT/MODEMnnn.DAT - Modem configuration */
{
    string desc[51];                   /* modem reference description */
    byte comport;                      /* COM port number */
    longint waitbaud;                  /* modem bps rate */
    longint lockedbaud;                /* locked bps rate */
                                       /*    0 = Not Locked */
    string init[81];                   /* initialization command */
    string answer[41];                 /* answer command */
    string hangup[41];                 /* hangup command */
    string offhook[41];                /* phone off-hook command */
    string code_ok[17];                /* OK result code */
    string code_error[17];             /* ERROR result code */
    string code_ring[17];              /* RING result code */
    string code_nocarrier[17];         /* NO CARRIER result code */
    string code_arq[17];               /* error correction string */
    string code_connect[25][17];       /* connect strings */
                                       /*   1 - 300     11 - 19200
                                            2 - 1200    12 - 21600
                                            3 - 1275    13 - 24000
                                            4 - 2400    14 - 26400
                                            5 - 4800    15 - 28800
                                            6 - 7200    16 - 38400
                                            7 - 9600    17 - 57600
                                            8 - 12000   18 - 64000
                                            9 - 14400   19 - 115200
                                           10 - 16800  */
    byte reinittime;                   /* inactivity re-initialization */
    byte delay_cmd;                    /* delay after cmd (1/10th) */
    byte delay_answer;                 /* answer delay (1/10th) */
    byte delay_dtr;                    /* delay for DTR drop (1/10th) */
    modemflags flags;                  /* status flags (see above) */
    byte irq;                          /* irq for non-standard port */
    string address[5];                 /* base I/O address for port */
    byte ansrings;                     /* # rings before answering */
    byte ansreset;                     /* seconds before counter reset */
    byte reserved[67];                 /* RESERVED */
}
modemrec;

/*---------------------------------------------------------------------------*/

typedef struct          /* NETWORK.DAT status flags */
{
    bit nstrip : 1;                    /* strip message codes? */
    bit naddtear : 1;                  /* add tear/origin lines? */
    bit nholduser : 1;                 /* hold all non-SysOp Netmail? */
    bit nhold : 1;                     /* def Netmail to "hold"? */
    bit ncrash : 1;                    /* def NetMail to "crash"? */
    bit nkill : 1;                     /* def NetMail to "kill/sent"? */
    bit nstripcolour : 1;              /* strip TG color codes ? */
}
netflags;

typedef struct          /* NETWORK.DAT - Net Address */
{
    word zone, net, node, point;       /* Zone:Net/Node.Point */
}
netaddress;

typedef struct          /* NETWORK.DAT - Node Information */
{
    netaddress addr;                   /* Zone:Net/Node.Point */
    word akazone;                      /* aka matching Zone:Net */
    word akanet;                       /* if net=0, match Zone only */
    string replynet[9];                /* areaname of netreplies for AKA */
    byte reserved[18];                 /* RESERVED */
}
netaddrrec;

typedef struct          /* NETWORK.DAT - Network Information */
{
    netaddrrec netaddr[20];            /* network addresses */
    string origin[51];                 /* origin line */
    byte kludge_color;                 /* color of kludge line */
    byte quote_color;                  /* color of quoted text */
    byte tear_color;                   /* color of tear line */
    byte origin_color;                 /* color of origin line */
    netflags flags;                    /* status flags */
    acstring readacs;                  /* default read ACS */
    acstring postacs;                  /* default post ACS */
    byte text_color;                   /* color of text line */
    byte areaformat;                   /* default area format */
    byte areascan;                     /* default scan type */
    byte defaddr;                      /* default address */
    byte reserved1[37];                /* RESERVED */
    string nodepath[41];               /* Nodelist path */
    byte nodelisttype;                 /* Nodelist type
                                              0 : None
                                              1 : Version 6
                                              2 : Version 7
                                              3 : FrontDoor */
    netaddress UUCPgate;               /* Zone:Net/Node.Point */
    acstring sysopacs;                 /* default sysop ACS */
    byte reserved2[26];                /* RESERVED */
}
networkrec;

/*---------------------------------------------------------------------------*/

typedef struct          /* NODES.DAT : Who's Online status flags */
{
    bit ishidden : 1;                  /* user is hidden */     
    bit isquiet : 1;                   /* user not to be disturbed */
}
whosonflags;

typedef struct          /* NODES.DAT - Multi-Node setup */
{
    boolean active;                    /* node can accept calls */
    word logonbegin;                   /* logon starts (0-1440) */
    word logonend;                     /* logon ends (0-1440) */
    acstring logonacs;                 /* access to logon */
    longint logonbps;                  /* minimum logon bps */
    string nodephone[21];              /* Node Phone Number */
    byte reserved1[45];                /* RESERVED */

    string realname[37];               /* realname */
    string handle[37];                 /* handle */
    string location[31];               /* location */
    unixtime logontime;                /* logon time */
    byte statusid;                     /* 0 - waiting for call
                                          1 - unavailable (offline/down)
                                          2 - event
                                          3 - CONNECTED
                                          4 - waiting for reset */
		string status[37];                 /* status */
    longint bpsrate;                   /* bps rate */
    longint userid;                    /* user-ID */
    whosonflags flags;                 /* status flags */
    byte reserved2[45];                /* RESERVED */
}
nodesrec;

/*---------------------------------------------------------------------------*/

typedef struct          /* PROTOCOL.DAT - File transfer protocols */
{
    string desc[26];                   /* description */
    boolean active;                    /* active? */
    boolean batch;                     /* batch? (=filelist) */
    acstring acs;                      /* access control */
    string ulcmd[61];                  /* UL command line */
    string dlcmd[61];                  /* DL command line */
    string ulcode[3][7];               /* UL result code */
    string dlcode[3][7];               /* DL result code */
    string envcmd[61];                 /* environment command */
    string templog[26];                /* temporary log file */
    string flist[6];                   /* DL file list */
    byte logpf;                        /* log - word # (filename) */
    byte logpr;                        /* log - word # (result) */
    boolean success;                   /* results = success? */
    boolean bidirec;                   /* bi-directional */
}
protrec;

/*---------------------------------------------------------------------------*/

typedef struct          /* SHORTMSG.DAT -  Logon messages/receipts */
{
    longint userid;                    /* to user id (0=deleted) */
    string msg[156];                   /* message */
    byte msgid;                        /* msgid - INTERNAL USE
                                          should *always* be 0
                                          if set by external utils */
    byte reserved[4];                  /* RESERVED */
}
shortmsgrec;

/*---------------------------------------------------------------------------*/

typedef struct          /* SMACROS.DAT : SysOp Macros */
{
    string macro[10][121];             /* SysOp Macros F1..F10 */
}
smacrorec;

/*---------------------------------------------------------------------------*/

typedef struct          /* TIMELOG.DAT - Daily/hourly usage tracking */
{
    unixtime startdate;                /* date graph started */
    word busyperhour[24];              /* busy per hour */
    word busyperday[7][72];            /* busy per DOW, 20 minute intervals */
}
timelogrec;

/*---------------------------------------------------------------------------*/

typedef struct          /* VOTING.DAT - Voting records */
{
    boolean active;                    /* active? */
    string question[80];               /* voting question */
    acstring voteacs;                  /* voting ACS */
    acstring addacs;                   /* add answer ACS */
    word numusers;                     /* # of users answering */
    byte numans;                       /* # of active answers */
    struct
    {
        string desc[61];               /* answer description */
        word numres;                   /* # votes for this answer */
    }
    answer[NUMVOTEAS];
}
voterec;

/*****************************************************************************/
/* ---------------------- EXTERNAL DATA STRUCTURES ------------------------- */
/*****************************************************************************/

/*
    The following structures are all derived from external sources and are
    not internal to Telegard 3.0 (i.e. the same format listed below is used
    for all other compatible products using the same specifications).

    For more information on the structures which are listed below, please
    refer to the DEVEL300.DOC documentation, which contains contact
    information and further reference listings for these structures.
*/

/*****************************************************************************/
/* ------------ NODELIST FILE STRUCTURES ("VERSION 6" FORMAT) -------------- */
/*****************************************************************************/

typedef struct          /* NODELIST.DAT status flags */
{
    bit hub : 1;                       /* node is a net hub */
    bit host : 1;                      /* node is a net host */
    bit region : 1;                    /* node is a region coord */
    bit zone : 1;                      /* node is a zone coord
    bit cm : 1;                        /* runs continuous mail */
    bit ores1 : 1;                     /* reserved for Opus */
    bit ores2 : 1;                     /* reserved for Opus */
    bit ores3 : 1;                     /* reserved for Opus */
    bit ores4 : 1;                     /* reserved for Opus */
    bit ores5 : 1;                     /* reserved for Opus */
    bit nores1 : 1;                    /* reserved for non-Opus */
    bit nores2 : 1;                    /* reserved for non-Opus */
    bit nores3 : 1;                    /* reserved for non-Opus */
    bit nores4 : 1;                    /* reserved for non-Opus */
    bit nores5 : 1;                    /* reserved for non-Opus */
    bit nores6 : 1;                    /* reserved for non-Opus */
}
nodeflags;

typedef struct          /* NODELIST.DAT modem type flags */
{
    bit hst : 1;                       /* node uses a USRobotics HST modem */
    bit pep : 1;                       /* node uses a Telebit PEP modem */
    bit v32 : 1;                       /* node uses a V.32 modem */
    bit v32b : 1;                      /* node uses a V.32bis modem */
    bit h96 : 1;                       /* node uses a Hayes Express96 modem */
}
modemtypes;

typedef struct          /* NODELIST.DAT - Version 6 nodelist data */
{
    integer net;                       /* net number */
    integer node;                      /* node number */
    integer cost;                      /* cost per minute to call */
    byte name[34];                     /* node name */
    byte phone[40];                    /* phone number */
    byte city[30];                     /* city and state */
    byte password[8];                  /* password */
    integer realcost;                  /* phone company's charge */
    integer hubnode;                   /* node # of this nodes hub (0=none) */
    byte rate;                         /* actual bps rate divided by 300 */
    modemtypes modem;                  /* modem type codes */
    nodeflags flags;                   /* set of flags */
    byte res[2];                       /* RESERVED */
}
nodedatarec;

typedef struct          /* NODELIST.IDX - Version 6 nodelist index */
{
    integer node;                      /* node number */
    integer net;                       /* net number */
}
nodeindexrec;


/*****************************************************************************/
/* ------------------- QWK OFFLINE MAIL FILE STRUCTURES -------------------- */
/*****************************************************************************/

typedef struct          /* MESSAGES.DAT - Message file header record */
{
    char status;                       /* message status flag:
                                          ' ' = public, unread
                                          '-' = public, read
                                          '+' = private, unread
                                          '*' = private, read
                                          '~' = comment to SysOp, unread
                                          '`' = comment to SysOp, read
                                          '%' = password protected, unread
                                          '^' = password protected, read
                                          '!' = group password, unread
                                          '#' = group password, read
                                          '$' = group password to all */
    char number[7];                    /* message number */
    char date[8];                      /* date (MM-DD-YY) */
    char time[5];                      /* time (HH:MM) */
    char msgto[25];                    /* To (uppercase) */
    char msgfrom[25];                  /* From (uppercase) */
    char subject[25];                  /* Subject */
    char password[12];                 /* password */
    char reference[8];                 /* reference message number */
    char blocks[6];                    /* # of blocks in message,
                                           including header block */
    byte active;                       /* $E1=active, $E2=to be deleted */
    word areanum;                      /* QWK area number */
    byte res[2];                       /* RESERVED */
    char tagline;                      /* contains network tagline :
                                          '*' = network tagline present
                                          ' ' = no tagline present */
}
qdatrec;

typedef struct          /* *.NDX - Message area index record */
{
    longint recnum;                    /* record number in MESSAGES.DAT,
                                          stored in Microsoft MKS$ format */
    byte areanum;                      /* area number (unused) */
}
qndxrec;

/****************************************************************************/
/* --------------------------- JAM STRUCTURES ----------------------------- */
/****************************************************************************/

typedef struct          /* *.JHR - JAM message base header - first record */
{
    char signature[4];                 /* message signature
                                          <J><A><M> followed by <NUL> */
    longint datecreated;               /* creation date */
    longint modeifycount;              /* modification counter */
    longint activemsgs;                /* active messages */
    longint passwordCRC;               /* CRC of password, -1 = none */
    longint basemsgnum;                /* lowest number in index */
    char reserved[1000];               /* reserved by JAM authors */
}
jaminforec;

typedef struct          /*  JAM message base attributes */
{
    bit jlocal : 1;                    /* local */
    bit jintransit : 1;                /* in-transit */
    bit jprivate : 1;                  /* private */
    bit jread : 1;                     /* read by receiver */
    bit jsent : 1;                     /* sent */
    bit jkillsent : 1;                 /* kill msg/sent */
    bit jarchivesent : 1;              /* archive msg/sent */
    bit jhold : 1;                     /* hold */
    bit jcrash : 1;                    /* crash */
    bit jimmediate : 1;                /* immediate */
    bit jdirect : 1;                   /* direct */
    bit jgate : 1;                     /* gate *
    bit jfilereq : 1;                  /* file requests */
    bit jfileattach : 1;               /* file attached */
    bit jtruncfiles : 1;               /* truncate (0 len) sent file */
    bit jillfiles : 1;                 /* kill sent files */
    bit jreceiptreq : 1;               /* receipt requested */
    bit jconfirmreq : 1;               /* confirmation of receipt */
    bit jorphan : 1;                   /* orpahned message */
    bit jencrypt : 1;                  /* encrypted message(*) */
    bit jcompress : 1;                 /* compressed message(*) */
    bit jescaped : 1;                  /* escaped message(*) */
    bit jforcepickup : 1;              /* force pickup */
    bit jtypelocal : 1;                /* local only */
    bit jtypeecho : 1;                 /* for echo dist'n */
    bit jtypenet : 1;                  /* for netmai dist'n */
    bit jRESERVED : 1;                 /* 0x04000000L */
    bit jRESERVED1 : 1;                /* 0x08000000L */
    bit jRESERVED2 : 1;                /* 0x10000000L */
    bit jnomsgdisplay : 1;             /* no message display */
    bit jlocked : 1;                   /* locked message */
    bit jdeleted : 1;                  /* deleted message */
}
jammsgattr;


typedef struct          /* *.JHR - JAM message headers */
{
    char signature[4];                 /* message signature */
                                       /* <J><A><M> followed by <NUL> */
    word revision;                     /* JAM revision level */
    word reserved1;                    /* reserved by JAM authors */
    longint subfieldlen;               /* length of subfields */
    longint timesread;                 /* # times message read */
    longint msgidCRC;                  /* CRC-32 of MSGID line */
    longint replyCRC;                  /* CRC-32 of REPLY line */
    longint replyto;                   /* reply to # */
    longint reply1st;                  /* 1st reply number */
    longint replynext;                 /* reply next */
    unixtime date;                     /* date written */
    unixtime datercvd;                 /* date received */
    unixtime dateproc;                 /* date processed (tosser/scanner) */
    longint msgnum;                    /* message number */
    jammsgattr attribute;              /* attributes */
    longint reserved2;                 /* reserved by JAM authors */
    longint textoffset;                /* offset of text in *.JDT file */
    longint textlen;                   /* length of text */
    longint passwordCRC;               /* CRC-32 of password */
    longint cost;                      /* cost of message */
}
jamhdrrec;

typedef struct          /* *.JHR - subfield records */
{
    word fieldid;                      /* subfield ID */
    word reserved1;                    /* reserved by JAM authors */
    longint datalen;                   /* length of buffer */
}
jamsubfieldrec;

typedef struct          /* *.JDX - JAM quick index */
{
    longint userCRC;                   /* CRC-32 of receipients name (lower) */
    longint hdroffset;                 /* offset to jamhdrrec */
}
jamindexrec;

typedef struct          /* *.JLR - JAM last read storage */
{
    longint userCRC;                   /* CRC-32 of users name (lower) */
    longint userID;                    /* unique user-ID */
    longint lastread;                  /* lastread pointer */
    longint highread;                  /* high read pointer */
}
jamreadrec;

/****************************************************************************/
/* ------------------------- SQUISH STRUCTURES ---------------------------- */
/****************************************************************************/

typedef struct          /* *.SQD - Squish message base header - first record*/
{
    word len_sqbase;                   /* length of this structure */
    word reserved;                     /* RESERVED */
    longint nummsgs;                   /* number of messages */
    longint highmsg;                   /* highest message(=nummsgs) */
    longint keepmsgs;                  /* # of messages to keep */
    longint hwmsgid;                   /* High Water message msg-ID # */
    longint lastmsgid;                 /* Last message msg-ID # */
    char basename[80];                 /* basename for Squishfile */
    longint beginframe;                /* offset to first message header */
    longint lastframe;                 /* offset to last message header */
    longint freeframe;                 /* offset to first FREE header */
    longint lastfreeframe;             /* offset to last FREE header */
    longint endframe;                  /* offset to end of file */
    longint maxmsgs;                   /* maximum number of messages */
    word keepdays;                     /* days to keep messages */
    word sqhdrsize;                    /* sice of header record */
    byte reserved2[124];               /* RESERVED */
}
sqbaserec;

typedef struct          /* *.SQD - Message header */
{
    longint sqid;                      /* squish ID - $AFAE4453 */
    longint nextmsg;                   /* offset to last message */
    longint prevmsg;                   /* offset to previous message */
    longint framelength;               /* length of header & message */
    longint msglength;                 /* length of message */
    longint ctrllength;                /* length of control information */
    word headertype;                   /* Header type
                                          Message = 0
                                          Free    = 1 */
    word reserved;                     /* RESERVED */
}
sqhdrrec;

typedef struct          /* Squish Message Attributes */
{
    bit sprivate : 1;                  /* private */
    bit scrash : 1;                    /* crash */
    bit sread : 1;                     /* read by receiver */
    bit ssent : 1;                     /* sent */
    bit sfileattach : 1;               /* files attached */
    bit sintransit : 1;                /* in-transit */
    bit sorphan : 1;                   /* orphaned message */
    bit skillsent : 1;                 /* kill msg/sent */
    bit slocal : 1;                    /* local  */
    bit shold : 1;                     /* hold */
    bit sreserved : 1;                 /* reserved */
    bit sfilereq : 1;                  /* file requests */
    bit sreceiptreq : 1;               /* receipt requested */
    bit sconfirmreq : 1;               /* confirmation of receipt */
    bit saudit : 1;                    /* audit trail requested */
    bit supdate : 1;                   /* update request */
    bit sscanned : 1;                  /* echomail scanned */
    bit smsgid : 1;                    /* valid msgid? */
    bit sres1 : 1;                     /* reserved */
    bit sres2 : 1;
    bit sres3 : 1;
    bit sres4 : 1;
    bit sres5 : 1;
    bit sres6 : 1;
    bit sres7 : 1;
    bit sres8 : 1;
    bit sres9 : 1;
    bit sres10 : 1;
    bit sres11 : 1;
    bit sres12 : 1;
    bit sres13 : 1;
    bit sres14 : 1;
}
sqshmsgattr;


typedef struct          /* *.SQD - Message Info Header */
{
    sqshmsgattr attribute;             /* Message attributes */
    char msgfrom[36];                  /* Message from - NUL terminated */
    char msgto[36];                    /* Message to - NUL terminated */
    char subject[72];                  /* Message subject - NUL terminated */
    struct
    {
        word zone, net,
             node, point;
    } origaddr, destaddr;              /* Origin/Destination addresses */
    bitmapdate origdate;               /* Original date (utc) */
    bitmapdate msgdate;                /* Arrival (system) date (utc) */
    word utcoffset;                    /* Minutes offset of UTC */
    longint replyto;                   /* Reply-to msg-ID # */
    longint replies[9];                /* Replies msg-ID # */
    longint msgid;                     /* Message ID */
    char rawdate[20];                  /* ASCII date - NUL terminated */
}
sqxmsgrec;

typedef struct          /* *.SQI - Squish Message Index */
{
    longint msgptr;                    /* offset of sqfhdr record */
    longint msgid;                     /* msg-ID # */
    longint hash;                      /* hash of 'To' name */
}
sqindexrec;

typedef struct          /* *.SQL - Squish Last Read Index */
{
    longint msgid;                     /* msg-ID # */
}
sqreadrec;

/****************************************************************************/
/* ------------------------ TESTINFO.DAT FORMAT --------------------------- */
/****************************************************************************/


typedef struct          /* TESTINFO.DAT - individual file record */
{
    boolean sfx;                       /* is self-extracting file? */
    boolean exists;                    /* file exists */
    string full_path[61];              /* full file path */
    string path[61];                   /* file path */
    string drive[3];                   /* file drive (incl colon) */
    string name[9];                    /* filename (raw) */
    string ext[4];                     /* extension */
    string filetype[4];                /* file type(*) */
    longint date;                      /* file date_time (packed) */
    longint size;                      /* file size */
}
testinfofilerec;

typedef struct          /* TESTINFO.DAT */
{
    boolean processed;                 /* record has been processed */
    boolean desc_vendinfo;             /* vendinfo.diz description */
    boolean desc_import;               /* import descriptions? */
    boolean addtofbd;                  /* add file to file data base */
    boolean file_conv;                 /* file converted? */
    boolean user_ansi;                 /* detected ansi */
    boolean user_avatar;               /* detected avatar */
    boolean user_carrier;              /* carrier detected last check */
    byte reserved1[9];                 /* RESERVED */
    byte check_count;                  /* update/check count */
    byte bbs_type;                     /* BBS type (TG3.0 = 6) */
    byte user_comport;                 /* user com port */
    byte exit_level;                   /* exit level for test */
    byte revision;                     /* testinfo.dat revision level */
    byte reserved2[9];                 /* RESERVED */
    longint test_datetime;             /* testing date/time */
    byte reserved3[40];                /* RESERVED */
    string thd_options[61];            /* THDPRO command line options */
    string bbs_path[61];               /* path to BBS data files */
    string creator[61];                /* TESTINFO.DAT creator */
    string thd_log[61];                /* THDPRO log path */
    byte reserved4[183];               /* RESERVED */
    string ver_major[3];               /* creator - major version */
    string ver_minor[3];               /* creator - minor version */
    string thd_session[4];             /* THDPRO session number */
    string desc_filename[13];          /* description file filename */
    byte reserved5[39];                /* RESERVED */
    testinfofilerec file_original;     /* original file information */
    testinfofilerec file_finished;     /* finished file information */
    byte reserved6[10];                /* RESERVED */
    integer desc_length;               /* length of description */
    char desc[1500];                   /* description */
}
testinforec;

#endif
