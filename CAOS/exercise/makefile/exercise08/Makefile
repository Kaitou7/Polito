CC = gcc
FOLDER = build
CFLAGS= -Wall -Wextra -O2 -MMD -MP
TARGET = app
SRC = main.c util.c math.c
OBJS = $(SRC:%.c=$(FOLDER)/%.o)
DEPS = $(OBJS:.o=.d)
all: $(TARGET)

$(FOLDER)/:
	mkdir -p $(FOLDER)

.PHONY : dir

$(TARGET) : $(OBJS)
	$(CC) $^ -o $@

#| dice che deve essere costruito prima dei file .o, in più le modifiche alla directory non forzano una ricompilazione.

$(FOLDER)/%.o: %.c $(OBJS) | $(FOLDER)/
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -r -f $(FOLDER) $(TARGET)
-include $(DEPS)