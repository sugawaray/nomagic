TARGET = test
OBJS = test.o

RM = /bin/rm

all : $(TARGET)

clean : 
	@-$(RM) $(TARGET) $(OBJS)

test.cpp : nomagic.h
