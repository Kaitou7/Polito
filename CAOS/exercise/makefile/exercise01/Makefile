CC = gcc
SRC = main.c utils.c
FLAGS = -Wall
TARGET = program.elf
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET) : $(OBJ)
	$(CC) $(FLAGS) $^ -o $@


%.o : %.c utils.h
	$(CC) $(FLAGS) -c $< -o $@

clean: 
	rm -f $(OBJ) $(TARGET)