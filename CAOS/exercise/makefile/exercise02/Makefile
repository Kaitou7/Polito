CC = gcc
SFLAGS= -Wall
#indicate errors.
TARGET = math_program.elf
SRC = main.c math_utils.c
OBJS = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

main.o: main.c math_utils.h
	$(CC) $(SFLAGS) -c main.c -o main.o

math_utils.o : math_utils.c math_utils.h
	$(CC) $(SFLAGS) -c math_utils.c -o $@

%.o:%.c
	$(CC) $(SFLAGS) -c $^ -o $@

# Dipendenza esplicita del file oggetto da .h se viene modificato



.PHONY: clean

clean : 
	rm -f $(TARGET) $(OBJS)