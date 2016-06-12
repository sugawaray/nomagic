TARGETCPP = testcpp
OBJSCPP = testcpp.o

TARGETC = testc
TARGETCU = testcu
EOBJSC = testc.o testcu.o
OBJSC = nmutil.o nomagicc.o
TARGETCLIB = libnomagicc.a
TARGETCULIB = libnomagiccu.a

CFLAGS =
CPPFLAGS = -I./
LD = gcc
LDFLAGSC =

RM = /bin/rm

all : $(TARGETCPP) $(TARGETC) $(TARGETCLIB) $(TARGETCULIB) $(TARGETCU)

clean : 
	@-$(RM) $(TARGETCPP) $(OBJSCPP) $(TARGETC) $(OBJSC)	\
		$(TARGETCLIB) $(TARGETCULIB) $(TARGETCU) $(EOBJSC)

$(TARGETC): testc.o $(OBJSC)
	$(LD) -o $@ testc.o $(OBJSC) $(LDFLAGSC)

$(TARGETCU): testcu.o $(OBJSC)
	$(LD) -o $@ testcu.o $(OBJSC) $(LDFLAGSC)

$(TARGETCLIB): nomagicc.o
	$(AR) $(ARFLAGS) $@ nomagicc.o

$(TARGETCULIB): nmutil.o
	$(AR) $(ARFLAGS) $@ nmutil.o

.c.o:
	$(CC) -c -o $@ $(CFLAGS) $(CPPFLAGS) $<

testcpp.cpp : nomagic.h
testc.o: testc.c nomagicc.h
nomagicc.o: nomagicc.c nomagicc.h
nmutil.o: nmutil.c nomagiccu.h
