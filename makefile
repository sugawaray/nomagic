TARGETCPP = testcpp
OBJSCPP = testcpp.o

TARGETC = testc
OBJSC = testc.o nomagicc.o

CPPFLAGS = -I./
LD = gcc

RM = /bin/rm

all : $(TARGETCPP) $(TARGETC)

clean : 
	@-$(RM) $(TARGETCPP) $(OBJSCPP) $(TARGETC) $(OBJSC)

$(TARGETC): $(OBJSC)
	$(LD) -o $@ $(OBJSC) $(LDFLAGSC)

.c.o:
	$(CC) -c -o $@ $(CFLAGS) $(CPPFLAGS) $<

testcpp.cpp : nomagic.h
testc.o: testc.c nomagicc.h
nomagicc.o: nomagicc.c nomagicc.h
