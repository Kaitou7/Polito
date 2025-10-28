CC = gcc
FLAGS = -Wall
SRC = main.c math_utils.c
OBJ = $(SRC:.c=.o)
TARGET = math_program.elf


all: $(TARGET)

$(TARGET) : $(OBJ)
	$(CC) $(FLAGS) $^ -o $@

math_utils.o : math_utils.c math_utils.h
	$(CC) $(FLAGS) -c math_utils.c -o math_utils.o

%.o : %.c math_utils.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)