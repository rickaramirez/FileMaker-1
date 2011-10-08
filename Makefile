CROSS	= 
CC	= $(CROSS)gcc
LD	= $(CROSS)ld
AR	= $(CROSS)ar
RANLIB  = $(CROSS)ranlib
STRIP   = $(CROSS)strip

CFLAGS  = -Wall -Wshadow -Wno-trigraphs -pipe 
LDLIBS = 

BIN		  = maker
SRCS		= $(wildcard *.c)
OBJS		= $(SRCS:.c=.o)

all: $(BIN)

$(OBJS): %.o: %.c
	$(CC) -c -g $(CFLAGS) $< -o $@

$(BIN): $(OBJS)
	$(CC) -lm $(OBJS) $(LDLIBS) -o $@
#	$(STRIP) frame_app
	
clean:
	rm -rf *.o
	rm -rf $(BIN)
	rm -rf *.o *.bak *.c.bak 
