#@ i target < prima dipendenza ^ tutte le dipendenze

CC = gcc
CFLAGS= -Wall -Wextra -O2
#indicate errors, -Wextra aggiunge più avvisi estendendo -Wall, -O2 è per ottimizzare .
TARGET = app
SRC = main.c util.c math.c
OBJS = $(SRC:.c=.o)

all: $(TARGET)
	
$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(TARGET) $(OBJS)

