CC = gcc
SFLAGS= -Wall
#indicate errors.
TARGET = app
SRC = main.c
OBJS = $(SRC:.c=.o)

all : $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

run : $(TARGET)
	./$(TARGET)

%.o:%.c
	$(CC) $(SFLAGS) -c $^ -o $@

clean : 
	rm -f $(TARGET) $(OBJS)