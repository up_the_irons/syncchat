/*
 *   X00API.C: X00 FOSSIL driver
 *
 *   Created by R.F. Pels.
 *   modified by Bob Stout
 *   Placed in the public domain by R.F. Pels.
 *   Later modified by Garry Dolley (AKA Prophet) for use with SyncChat +
 *   XSDK (Synchronet Development Kit) - 4-23-96
 */

#include "x00api.h"
#include <dos.h>
/* #include "mk_fp.h" */

static union  REGS  x00regs;
static struct SREGS x00sregs;
int                 x00error = 0;

extern int local;
extern unsigned long com_rate;
extern int extended;

#if defined(__cplusplus) && __cplusplus
 extern "C" {
#endif

#ifndef MK_FP
 #define MK_FP(seg,offset) \
	((void _far *)(((unsigned long)(seg)<<16) | (unsigned)(offset)))
#endif

#if defined(__TURBOC__) || defined (__POWERC)
 #define PEEK(s,o) peek(s,o)
#else /* MSC or ZTC */
 #define PEEK(s,o) *((unsigned _far *)(MK_FP((s),(o))))
#endif

unsigned int  x00_detect(void)
{
	unsigned int segofx00;
	unsigned int ofsofx00;

				/* Peek in interrupt vector table for start of FOSSIL */

	ofsofx00 = PEEK(0, X00_VECTOR * 4);
	segofx00 = PEEK(0, (X00_VECTOR * 4) + 2);

	/* Peek in start of FOSSIL + X00_IDOFFSET */

	return (PEEK(segofx00, ofsofx00 + X00_IDOFFSET));
}

FOSSILSTATUS  x00_set(unsigned char set, PORT port)
{
	FOSSILSTATUS retval;

	/* New - allows "enhanced" locked baud rates - 57600 and 115200 */
	if( (set == BAUD57600) || (set == BAUD115200) )
	  {
	  x00regs.x.bx = 0x69DC;
	  x00regs.x.cx = 0x69DC;
		}
  /* End */
  /* x00regs.x.ax = SET_BAUDRATE | set; */
																	 /* FIDOSETTING = 8,N,1 */
	x00regs.x.ax = SET_BAUDRATE | set | FIDOSETTING;
	x00regs.x.dx = port;
	int86(X00_VECTOR, &x00regs, &x00regs);
	retval.statusword = x00regs.x.ax;
	return retval;
}

FOSSILSTATUS  x00_tx_char(unsigned char c, PORT port)
{
				FOSSILSTATUS retval;

				x00regs.x.ax = TX_CHAR | c;
				x00regs.x.dx = port;
				int86(X00_VECTOR, &x00regs, &x00regs);
				retval.statusword = x00regs.x.ax;
				return retval;
}

unsigned char  x00_rx_char(PORT port)
/* Recieve char with wait (destructive - duh) - remote
   AH = Line Status
   AL = Input character (ASCII I believe)
*/
{
	/* If remote key... */
				x00regs.x.ax = RX_CHAR;
				x00regs.x.dx = port;
				int86(X00_VECTOR, &x00regs, &x00regs);
				return (unsigned char)(x00regs.x.ax & 0xff);
  /* If local key... DO NOTHING - ONLY WORKS REMOTE (DUH!!) */
	/* ... */
}

FOSSILSTATUS  x00_status(PORT port)
{
	FOSSILSTATUS retval;

	x00regs.x.ax = STATUS;
	x00regs.x.dx = port;
	int86(X00_VECTOR, &x00regs, &x00regs);
	retval.statusword = x00regs.x.ax;
	return retval;
}

/* New */
int x00_carrier_detect(PORT port)
/* Returns 0 if no carrier, 1 if carrier */
{
	FOSSILSTATUS retval;

  if(local)
    return(1);
	x00regs.x.ax = STATUS;
	x00regs.x.dx = port;
	int86(X00_VECTOR, &x00regs, &x00regs);
  if((x00regs.h.al & 0x80) != 0)
		return(1);
  else
    return(0);
}
/* End */

/*
FOSSILINIT    x00_init(PORT port, unsigned char far *ctlc_flagbyte)
{
	FOSSILINIT retval;

	x00regs.x.ax = INITIALIZE;
	if (ctlc_flagbyte != (unsigned char far *)0)
	{
		x00regs.x.dx = 0x00ff;
		x00regs.x.bx = 0x4F50;
    segread(&x00sregs);
		x00sregs.es  = FP_SEG(ctlc_flagbyte);
    x00regs.x.cx = FP_OFF(ctlc_flagbyte);
	}
	else
	{
		x00regs.x.bx = 0x0000; /* in any case _NOT_ 0x4f50 *
		x00regs.x.dx = port;
	}
	int86x(X00_VECTOR, &x00regs, &x00regs, &x00sregs);
	retval.result       = x00regs.x.ax;
	retval.max_function = (unsigned char)(x00regs.x.bx & 0xff);
	retval.revision     = (unsigned char)(x00regs.x.bx >> 8);
	return retval;
}
*/

FOSSILINIT  x00_init(PORT port)
{
  FOSSILINIT retval;

	if(local)
		return retval;

	x00regs.x.ax = INITIALIZE;
	x00regs.x.dx = port;

	int86x(X00_VECTOR, &x00regs, &x00regs, &x00sregs);

	if(x00regs.x.ax != 0x1954)
    {
    puts("No FOSSIL driver found.");
    exit(0);
		}
	/* Else, com port activated :) */

	switch(com_rate) {
		case 300    : x00_set(BAUD300, port);  break;
		case 1200   : x00_set(BAUD1200, port); break;
		case 2400   : x00_set(BAUD2400, port); break;
		case 4800   : x00_set(BAUD4800, port); break;
		case 9600   : x00_set(BAUD9600, port); break;
		case 19200  : x00_set(BAUD19200, port); break;
		case 38400  : x00_set(BAUD38400, port); break;
		case 57600  : x00_set(BAUD57600, port); break;
		case 115200 : x00_set(BAUD115200, port); break;
		}
	retval.result       = x00regs.x.ax;
	retval.max_function = (unsigned char)(x00regs.x.bx & 0xff);
	retval.revision     = (unsigned char)(x00regs.x.bx >> 8);
	return retval;
}

void          x00_deinit(PORT port)
{
	if(local)
		return;

	x00regs.x.ax = DEINITIALIZE;
	x00regs.x.dx = port;
	int86(X00_VECTOR, &x00regs, &x00regs);
}

unsigned int  x00_raise_dtr(PORT port)
{
	unsigned int retval;

	x00regs.x.ax = RAISE_DTR;
	x00regs.x.dx = port;
	int86(X00_VECTOR, &x00regs, &x00regs);
	if ((x00regs.x.ax & 0x0001) == 1)
	{
		retval = X00_DTR_HIGH;
	}
	else    retval = X00_DTR_LOW;
	return retval;
}

unsigned int  x00_lower_dtr(PORT port)
{
	unsigned int retval;

	x00regs.x.ax = LOWER_DTR;
	x00regs.x.dx = port;
	int86(X00_VECTOR, &x00regs, &x00regs);
	if ((x00regs.x.ax & 0x0001) == 1)
	{
		retval = X00_DTR_HIGH;
	}
	else    retval = X00_DTR_LOW;
	return retval;
}

FOSSILSYSINFO x00_sysinfo(void)
{
	FOSSILSYSINFO retval;

	x00regs.x.ax = GET_SYS_INFO;
	int86(X00_VECTOR, &x00regs, &x00regs);
	retval.tick_number        = (unsigned char)(x00regs.x.ax & 0xff);
	retval.ticks_per_second   = (unsigned char)(x00regs.x.ax >> 8);
				retval.approx_ms_per_tick = x00regs.x.dx;
	return retval;
}

void          x00_flush_output(PORT port)
{
	x00regs.x.ax = FLUSH_OUTPUT;
	x00regs.x.dx = port;
	int86(X00_VECTOR, &x00regs, &x00regs);
}

void          x00_purge_output(PORT port)
{
	x00regs.x.ax = PURGE_OUTPUT;
	x00regs.x.dx = port;
	int86(X00_VECTOR, &x00regs, &x00regs);
}

void          x00_purge_input(PORT port)
{
				x00regs.x.ax = PURGE_INPUT;
	x00regs.x.dx = port;
	int86(X00_VECTOR, &x00regs, &x00regs);
}

unsigned int  x00_tx_char_nowait(unsigned char c, PORT port)
{
	unsigned int retval;

	x00regs.x.ax = TX_CHAR_NOWAIT | c;
	x00regs.x.dx = port;
	int86(X00_VECTOR, &x00regs, &x00regs);
	if ((x00regs.x.ax & 0x0001) == 1)
	{
		retval = X00_OK;
				}
	else    retval = X00_CHAR_NOT_SENT;
	return retval;
}

unsigned int  x00_peek_ahead_input(PORT port)
/* Read no wait (non-destructive) - remote (but now works local too)
	 AH = 00 - char available
	 AL = Next character available
	 AX = FFFF - no char available
	 */
{
				if(!local)
					{
					x00regs.x.ax = PEEK_AHEAD_INPUT;
					x00regs.x.dx = port;
					int86(X00_VECTOR, &x00regs, &x00regs);
					}
				else
					x00regs.x.ax = 0xffff;	 /* Force local check if local */
				/* New */
				if(x00regs.x.ax == 0xffff) /* No char available remotely so, */
					x00regs.x.ax = _bios_keybrd(1); /* check local keyboard */
				/* End New */
				if(x00regs.x.ax == 0)
					x00regs.x.ax = 0xffff;
/*	bprintf("\r\nx00_peek_ahead_input() - x00regs.h.al = %i", x00regs.h.al);
		bprintf("\r\nx00_peek_ahead_input() - x00regs.x.ax = %i", x00regs.x.ax);
*/

				if(x00regs.x.ax == 0xffff)
					return(0);
				return x00regs.x.ax;
}

unsigned int   x00_peek_ahead_kbd(void)
/* Read no wait (non-desctructive) - local keyboard
	 AX = FFFF - no char available
	 AX = Next char available - scan code */
{
				x00regs.x.ax = PEEK_AHEAD_KBD;
				int86(X00_VECTOR, &x00regs, &x00regs);
/*	bprintf("\r\nx00_peek_ahead_kbd() - x00regs.h.al = %i", x00regs.h.al);
		bprintf("\r\nx00_peek_ahead_kbd() - x00regs.x.ax = %i", x00regs.x.ax); */
				if(x00regs.x.ax == 0xffff)
					return(0);
				return x00regs.x.ax;
}

unsigned int   x00_read_kbd(void)
/* Read wait (destructive) - local keyboard
	 Returns scan code
	 AX = Char - scan code */
{
	x00regs.x.ax = READ_KBD;
	int86(X00_VECTOR, &x00regs, &x00regs);
/*	if(x00regs.h.al == 0)
		{
		extended = 1;
		bprintf("\r\nextened = %i", extended);
		} */
/*	bprintf("\r\nx00_read_kbd() - x00regs.h.al = %i", x00regs.h.al);
		bprintf("\r\nx00_read_kbd() - x00regs.x.ax = %i", x00regs.x.ax); */
	if(x00regs.x.ax == 0)
		x00regs.x.ax = 0xffff;
	return x00regs.x.ax;
}

void          x00_flow_control(FOSSILFLOWCTRL f, PORT port)
{
	x00regs.x.ax = FLOW_CONTROL | 0xf0 | f.flowword;
	x00regs.x.dx = port;
	int86(X00_VECTOR, &x00regs, &x00regs);
}

unsigned int  x00_ctlc_ctlk_check(FOSSILCTLCCTLK c, PORT port)
{
	x00regs.x.ax = CTLC_CTLK_CHECK | c.checkword;
	x00regs.x.dx = port;
	int86(X00_VECTOR, &x00regs, &x00regs);
	return x00regs.x.ax;
}

void          x00_set_cup(unsigned char row, unsigned char col)
{
	x00regs.x.ax = SET_CUP;
	x00regs.x.dx = (row << 8) | col;
	int86(X00_VECTOR, &x00regs, &x00regs);
}

void          x00_get_cup(unsigned char *row, unsigned char *col)
{
	x00regs.x.ax = GET_CUP;
	int86(X00_VECTOR, &x00regs, &x00regs);
	*col = (unsigned char)(x00regs.x.dx & 0xff);
	*row = (unsigned char)(x00regs.x.dx >> 8);
}

void          x00_write_ANSI_char(unsigned char c)
{
	x00regs.x.ax = WRITE_ANSI_CHAR | c;
	int86(X00_VECTOR, &x00regs, &x00regs);
}

void          x00_enable_watchdog(PORT port)
{
	x00regs.x.ax = ENABLE_WATCHDOG;
	x00regs.x.dx = port;
	int86(X00_VECTOR, &x00regs, &x00regs);
}

void          x00_disable_watchdog(PORT port)
{
	x00regs.x.ax = DISABLE_WATCHDOG;
	x00regs.x.dx = port;
	int86(X00_VECTOR, &x00regs, &x00regs);
}

void          x00_write_BIOS_char(unsigned char c)
{
	x00regs.x.ax = WRITE_BIOS_CHAR | c;
	int86(X00_VECTOR, &x00regs, &x00regs);
}

unsigned int  x00_insert_tick_func(void (far *tickfunc)())
{
	unsigned int retval;

	x00regs.x.ax = INSERT_TICK_FUNC;
	x00regs.x.dx = FP_OFF(tickfunc);
	segread(&x00sregs);
	x00sregs.es  = FP_SEG(tickfunc);
	int86x(X00_VECTOR, &x00regs, &x00regs, &x00sregs);
	if (x00regs.x.ax == 0x0000)
	{
		retval = X00_OK;
	}
	else    retval = X00_INS_TICK;
	return retval;
}

unsigned int  x00_delete_tick_func(void (far *tickfunc)())
{
	unsigned int retval;

	x00regs.x.ax = DELETE_TICK_FUNC;
	x00regs.x.dx = FP_OFF(tickfunc);
	segread(&x00sregs);
	x00sregs.es  = FP_SEG(tickfunc);
	int86x(X00_VECTOR, &x00regs, &x00regs, &x00sregs);
	if (x00regs.x.ax == 0x0000)
	{
		retval = X00_OK;
	}
	else    retval = X00_DEL_TICK;
	return retval;
}

void          x00_boot_machine(unsigned int boottype)
{
	x00regs.x.ax = BOOT_MACHINE | (boottype & 0x0001);
	int86(X00_VECTOR, &x00regs, &x00regs);
}

unsigned int  x00_read_block(unsigned int count, void far *buf, PORT port)
{
	x00regs.x.ax = READ_BLOCK;
	x00regs.x.cx = count;
	x00regs.x.dx = port;
	segread(&x00sregs);
	x00sregs.es  = FP_SEG(buf);
	x00regs.x.di = FP_OFF(buf);
	int86x(X00_VECTOR, &x00regs, &x00regs, &x00sregs);
	return x00regs.x.ax;
}

unsigned int  x00_write_block(unsigned int count, void far *buf, PORT port)
{
	x00regs.x.ax = WRITE_BLOCK;
	x00regs.x.cx = count;
	x00regs.x.dx = port;
	segread(&x00sregs);
	x00sregs.es  = FP_SEG(buf);
	x00regs.x.di = FP_OFF(buf);
	int86x(X00_VECTOR, &x00regs, &x00regs, &x00sregs);
	return x00regs.x.ax;
}

void          x00_start_break_signal(PORT port)
{
	x00regs.x.ax = START_BREAK_SIGNAL;
	x00regs.x.dx = port;
	int86(X00_VECTOR, &x00regs, &x00regs);
}

void          x00_stop_break_signal(PORT port)
{
	x00regs.x.ax = STOP_BREAK_SIGNAL;
	x00regs.x.dx = port;
	int86(X00_VECTOR, &x00regs, &x00regs);
}

unsigned int  x00_get_driverinfo(void far *buf, PORT port)
{
	x00regs.x.ax = GET_DRIVER_INFO;
	x00regs.x.cx = sizeof(FOSSILINFO);
	segread(&x00sregs);
	x00sregs.es  = FP_SEG(buf);
	x00regs.x.di = FP_OFF(buf);
	x00regs.x.dx = port;
	int86x(X00_VECTOR, &x00regs, &x00regs, &x00sregs);
	return x00regs.x.ax;
}

unsigned int  x00_install_appendage(unsigned char appcode,
					      void (far *appfunc)())
{
	unsigned int retval;

	x00regs.x.ax = INSTALL_APPENDAGE | appcode;
	segread(&x00sregs);
	x00sregs.es  = FP_SEG(appfunc);
	x00regs.x.dx = FP_OFF(appfunc);
	int86x(X00_VECTOR, &x00regs, &x00regs, &x00sregs);
	if (x00regs.x.ax == X00_PRESENT)
	{
		if ((x00regs.x.bx & 0xff00) == 1)
		{
			retval = X00_OK;
		}
		else    retval = X00_INS_APP;
	}
	else    retval = X00_NOT_HERE;
	return retval;
}

unsigned int  x00_remove_appendage(unsigned char appcode,
					     void (far *appfunc)())
{
	unsigned int retval;

	x00regs.x.ax = REMOVE_APPENDAGE | appcode;
	segread(&x00sregs);
	x00sregs.es  = FP_SEG(appfunc);
	x00regs.x.dx = FP_OFF(appfunc);
	int86x(X00_VECTOR, &x00regs, &x00regs, &x00sregs);
	if (x00regs.x.ax == X00_PRESENT)
	{
		if ((x00regs.x.bx & 0xff00) == 1)
		{
			retval = X00_OK;
		}
		else    retval = X00_REM_APP;
	}
	else    retval = X00_NOT_HERE;
	return retval;
}

#if defined(__cplusplus) && __cplusplus
 }
#endif
