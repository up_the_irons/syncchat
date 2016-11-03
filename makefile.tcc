##########################
# Makefile for SyncChat  #
# For use with Turbo C++ #
# Tabstop=8              #
##########################

# Macros
CC      = tcc
LD      = tlink
SDK	= xsdk
INCLUDE = e:\tc\include;$(SDK)
LIB     = e:\tc\lib
MODEL = l
CFLAGS  = -d -m$(MODEL) -I$(INCLUDE)
LFLAGS  = /n /c
OBJS    = xsdk.obj xsdkvars.obj $(SDK)\mswait$(MODEL).obj x00api.obj imp.obj sysfunc.obj tg.obj hstr_i.obj sc2.obj rg.obj
HEADERS = $(SDK)\xsdk.h $(SDK)\xsdkdefs.h $(SDK)\xsdkvars.c
X00HEADERS = $(SDK)\x00api.h

# Implicit C Compile Rule
.c.obj:
			@echo Compiling $*.c to $*.obj ...
	$(CC) $(CFLAGS) -c $*.c

# Main EXE Link Rule
syncchat.exe: $(OBJS) syncchat.obj
			@echo Linking $< ...
	$(LD) $(LFLAGS) @&&!
$(LIB)\c0$(MODEL) $(OBJS) syncchat.obj
!, $*, $*, $(LIB)\c$(MODEL).lib $(LIB)\math$(MODEL).lib $(LIB)\emu.lib

# All .obj modules
sbl.obj: $(HEADERS)

xsdk.obj: $(SDK)\xsdk.c $(HEADERS)
	@echo Compiling $(SDK)\$*.c to $*.obj ...
	$(CC) $(CFLAGS) -c $(SDK)\$*.c

xsdkvars.obj: $(SDK)\xsdkvars.c $(SDK)\xsdkdefs.h
	@echo Compiling $(SDK)\$*.c to $*.obj ...
	$(CC) $(CFLAGS) -c $(SDK)\$*.c

registry.obj: registry.c
	@echo Compiling $*.c to $*.obj ...
	$(CC) $(CFLAGS) -c $*.c

x00api.obj: $(SDK)\x00api.c $(X00HEADERS)
	@echo Compiling $(SDK)\$*.c to $*.obj ...
	$(CC) $(CFLAGS) -c $(SDK)\$*.c

imp.obj: imp.c
	@echo Compiling $*.c to $*.obj ...
	$(CC) $(CFLAGS) -c $*.c

sysfunc.obj: sysfunc.c
	@echo Compiling $*.c to $*.obj ...
	$(CC) $(CFLAGS) -c $*.c

tg.obj: tg.c
	@echo Compiling $*.c to $*.obj ...
	$(CC) $(CFLAGS) -c $*.c

hstr_i.obj: hstr_i.c
	@echo Compiling $*.c to $*.obj ...
	$(CC) $(CFLAGS) -c $*.c

sc2.obj: sc2.c
	@echo Compiling $*.c to $*.obj ...
	$(CC) $(CFLAGS) -c $*.c

rg.obj: rg.c
	@echo Compiling $*.c to $*.obj ...
	$(CC) $(CFLAGS) -c $*.c

clean:
        del *.obj
        del *.exe
