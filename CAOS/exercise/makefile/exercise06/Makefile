CC := gcc
FLAGS1:= -Wall
FLAGS2 := -MMD -MP
SRC := main.c util.c
OBJ := $(SRC:.c=.o)
DEPS:=$(OBJ:.o=.d)
TARGET:=app

.PHONY : all, clean

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(CC) $(FLAGS) $^ -o $@

%.o : %.c
	$(CC) $(FLAGS1) $(FLAGS2) -c $< -o $@

clean:
	rm -f $(OBJ) $(DEPS) $(TARGET)

-include $(DEPS)