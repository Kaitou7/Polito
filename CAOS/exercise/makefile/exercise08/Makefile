CC = gcc
FOLDER_DEPS = build
FLAGS = -Wall -MMD -MP 
SRC = main.c math.c util.c
OBJ = $(SRC:%.c=$(FOLDER_DEPS)/%.o)
DEPS = $(OBJ:.o=.d)
TARGET = app

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(CC) -Wall $^ -o $@

$(FOLDER_DEPS)/%.o : %.c | $(FOLDER_DEPS)/
	$(CC) $(FLAGS) -c $< -o $@

$(FOLDER_DEPS)/: 
	mkdir $(FOLDER_DEPS)

clean:
	rm -r -f $(TARGET) $(FOLDER_DEPS)

-include $(DEPS)