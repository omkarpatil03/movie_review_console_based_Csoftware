
TARGET= main

CSRCS= $(TARGET).c SignUp/signup.c SignIn/signin.c Options/options.c
COBJS= $(CSRCS:.c=.o)

CC= gcc

CFLAGS= -Wall
LDFLAGS=

$(TARGET): $(COBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(TARGET)

clean:
	rm -r *.o 

.phony:	run clean
