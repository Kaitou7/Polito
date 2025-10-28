CC = gcc
FLAGS1 = -Wall
FLAGS2 = -MMD -MP -I $(BUILD_SRC)

BUILD = build
BUILD_SRC = src

LIBRARY = libmylib.a
SRC_MAIN = main.c
SRC_OTHERS = $(BUILD_SRC)/bar.c $(BUILD_SRC)/foo.c

OBJ_MAIN= $(SRC_MAIN:%.c=$(BUILD)/%.o)
OBJ_OTHERS= $(patsubst %.c,$(BUILD)/%.o,$(notdir $(SRC_OTHERS)))
DEPS_MAIN = $(OBJ_MAIN:.o=.d)
DEPS_OTHERS = $(OBJ_OTHERS:.o=.d)
TARGET = app

all: $(TARGET)

$(TARGET) : $(OBJ_MAIN) $(LIBRARY) 
	$(CC) $(FLAGS1) $^ -o $@

$(LIBRARY) : $(OBJ_OTHERS)
	ar rcs $@ $^

$(BUILD)/%.o: $(BUILD_SRC)/%.c | $(BUILD)/
	$(CC) $(FLAGS1) $(FLAGS2) -c $< -o $@

$(OBJ_MAIN): $(SRC_MAIN) | $(BUILD)/
	$(CC) $(FLAGS1) $(FLAGS2) -c $< -o $@

$(BUILD)/ :
	mkdir $(BUILD)



clean:
	rm -r -f $(BUILD) $(TARGET) $(LIBRARY)
	