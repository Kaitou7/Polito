CC = gcc
CFLAGS= -Wall -Wextra -O2 -MMD -MP
#MMD crea file .d facendo un analisi delle dipendenze e li scrive in quel file; con -M includerei in <stdio.h> 
#MP crea per tutti quindi anche main.d, dato che non ha dipendenze lo ignora e va avanti 
#indicate errors, -Wextra aggiunge più avvisi estendendo -Wall, -O2 è per ottimizzare .
TARGET = app
SRC = main.c util.c
OBJS = $(SRC:.c=.o)
DEPS = $(OBJS:.o=.d)


all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $^ -o $@

run : $(TARGET)
	./$(TARGET)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

#execute everytime clean and all
.PHONY :clean run all
#se nella directory avessi un file chiamato clean, non lo eseguerebbe questa regola, facendo così la esegue (vede che il file esiste già e non la esegue)

clean: 
	rm -f $(TARGET) $(OBJS) $(DEPS)