.POSIX:

TARGET = libnomagicc.a
TESTTGTS = testc testcu
EOBJS = testc.o testcu.o
OBJS = nmutil.o nomagicc.o

all: $(TARGET) $(TESTTGTS)

clean : 
	-rm -f $(TARGET) $(TESTTGTS) $(OBJS) $(EOBJS)

$(TARGET): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

$(TESTTGTS): $(EOBJS) $(OBJS)
	$(LD) -o $@ ${@}.o $(OBJS) $(LDFLAGS)

testc.o: testc.c nomagicc.h
testcu.o: testcu.c nomagicc.h
nomagicc.o: nomagicc.c nomagicc.h
nmutil.o: nmutil.c nomagicc.h
