CC = gcc
CFLAGS= -Wall -Wextra -O2
#indicate errors, -Wextra aggiunge più avvisi estendendo -Wall, -O2 è per ottimizzare .
TARGET = app
SRC = main.c util.c
OBJS = $(SRC:.c=.o)

.PHONY : all
all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(OBJS) -o $@


.PHONY : run
run : $(TARGET)
	./$(TARGET)

%.o:%.c
	$(CC) $(SFLAGS) -c $^ -o $@

#execute everytime clean and all
.PHONY :clean
#se nella directory avessi un file chiamato clean, non lo eseguerebbe questa regola, facendo così la esegue (vede che il file esiste già e non la esegue)

clean: 
	rm -f $(TARGET) $(OBJS)