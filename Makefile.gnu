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

# $Id: GNUmakefile,v 1.22 2004/04/07 20:03:32 rswindell Exp $

# Macros
SBBS_ROOT   = /home/garry/sbbs
XSDK		=	$(SBBS_ROOT)/xtrn/sdk
ifndef XPDEV
 XPDEV		=	$(SBBS_ROOT)/src/xpdev
endif
ifndef SBBS_SRC
 SBBS_SRC	:=	$(XPDEV)/../sbbs3
endif
NEED_THREADS	:=	1
include $(XPDEV)/Common.gmake
include $(SBBS_SRC)/Common.gmake

ifeq ($(os),sunos)
 LDFLAGS	+=	-lsocket -lnsl -lrt
endif

vpath %.c $(XSDK)

CFLAGS	+=	-I$(XSDK)

$(EXEODIR)$(SLASH)syncchat: $(OBJS) 
	@echo Linking $@
	$(QUIET)$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

#SMBIO	=	$(LIBODIR)/genwrap.o $(LIBODIR)/filewrap.o $(LIBODIR)/dirwrap.o \
#		$(LIBODIR)/smblib.o $(LIBODIR)/lzh.o
#
#$(EXEODIR)$(SLASH)sbl2smb: $(LIBODIR)$(SLASH)sbl2smb.o $(SMBIO)
#	@echo Linking $@
#	$(QUIET)$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)
#
#$(EXEODIR)$(SLASH)smb2sbl: $(LIBODIR)$(SLASH)smb2sbl.o $(SMBIO)
#	@echo Linking $@
#	$(QUIET)$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)
#
#$(EXEODIR)$(SLASH)sblpack: $(LIBODIR)$(SLASH)sblpack.o $(LIBODIR)$(SLASH)/filewrap.o
#	@echo Linking $@
#	$(QUIET)$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)