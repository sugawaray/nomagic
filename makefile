TARGETCPP = testcpp
OBJSCPP = testcpp.o

TARGETC = testc
OBJSC = testc.o nomagicc.o
TARGETCLIB = libnomagicc.a

CFLAGS =
CPPFLAGS = -I./
LD = gcc
LDFLAGSC =

RM = /bin/rm

all : $(TARGETCPP) $(TARGETC) $(TARGETCLIB)

clean : 
	@-$(RM) $(TARGETCPP) $(OBJSCPP) $(TARGETC) $(OBJSC)	\
		$(TARGETCLIB)

$(TARGETC): $(OBJSC)
	$(LD) -o $@ $(OBJSC) $(LDFLAGSC)

$(TARGETCLIB): nomagicc.o
	$(AR) $(ARFLAGS) $@ nomagicc.o

.c.o:
	$(CC) -c -o $@ $(CFLAGS) $(CPPFLAGS) $<

testcpp.cpp : nomagic.h
testc.o: testc.c nomagicc.h
nomagicc.o: nomagicc.c nomagicc.h
