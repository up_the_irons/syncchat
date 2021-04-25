
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

typedef byte colors [2] [10];          /*  Color tables  */
typedef int secrange [256];            /*  Access tables */

typedef byte mzscanr [32];             /*  Which message bases to scan  */
typedef byte fzscanr [32];             /*  Which file bases to scan     */
typedef long mhireadr [250];           /*  Lastread pointers            */



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
				struct nodeflags status;
        byte Room;                     /* What room are they in?     */
        word Channel;                  /* What channel are they in?  */
        char Invited [32];             /* Have they been invited ?   */
        char Booted [32];              /* Have they been kicked off? */
        char Forget [32];              /* Who are they forgetting?   */
    
        };

