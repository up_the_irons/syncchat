# Makefile.gnu

#########################################################################
# Makefile for SyncChat          										#
# For use with GNU make and GNU C Compiler								#
# @format.tab-size 4, @format.use-tabs true								#
#																		#
# Linux: make -f Makefile.gnu											#
# Win32: make -f Makefile.gnu os=win32									#
# FreeBSD: make -f Makefile.gnu os=freebsd								#
#########################################################################

SBBS_ROOT   = /home/garry/sbbs

XSDK		= $(SBBS_ROOT)/xtrn/sdk
SRC_ROOT	?=	$(SBBS_ROOT)/src
include $(SRC_ROOT)/build/Common.gmake

vpath %.c $(XSDK)

CFLAGS	+=	-I$(XSDK) -DUSE_XPDEV $(XPDEV-MT_CFLAGS)

$(SYNCCHAT): $(OBJS)
   ifndef bcc
	@echo Linking $@
   endif
	$(QUIET)$(CC) $(MT_LDFLAGS) $(XPDEV-MT_LDFLAGS) $(LDFLAGS) $^ -o $@ $(XPDEV-MT_LIBS)

reggie: reggie.o
	$(CC) -o reggie reggie.c
