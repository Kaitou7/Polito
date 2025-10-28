CC:=gcc
SRC:= main.c
TARGET:=app
OBJ:=$(SRC:.c=.o)

all : $(TARGET)

$(TARGET):$(OBJ)
	$(CC) -Wall $^ -o $@

*.o : *.c
	$(CC) -Wall -c $< -o $@

run : $(TARGET)
	./$(TARGET)

clean: 
	rm -f $(TARGET)
