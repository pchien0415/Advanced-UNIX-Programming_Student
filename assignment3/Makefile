CC = gcc
CFLAG = -std=c11 -O2 -Wall
TARGET = assignment33
SRCS = assignment33.c
OBJS = assignment33.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $(TARGET) $(OBJS)
 
%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
