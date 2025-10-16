CC = gcc
SFLAGS= -Wall
#indicate errors.
TARGET = program.elf
SRC = main.c utils.c
OBJS = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o:%.c
	$(CC) $(SFLAGS) -c $^ -o $@

clean : 
	rm -f $(TARGET) $(OBJS)