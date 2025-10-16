# Build a static library (libmylib.a) and link with main.c                  
CC := gcc
AR := ar
ARFLAGS := rcs
#ar: Lo strumento archiver| rcs: Flag di operazione: r:(replace/insert): Inserisce i file oggetto o li rimpiazza se esistono già.
#c (create): Crea l'archivio se non esiste.
#s (symbol index): Scrive un indice dei simboli all'interno della libreria, essenziale per il linker.
SRC_DIR := src
CFLAGS := -Wall -Wextra -O2 -MMD -MP -I$(SRC_DIR)

BUILD := build
# Directory containing library source files,Root build directory for objects and deps
LIB := libmylib.a
LIB_SRCS := $(SRC_DIR)/foo.c $(SRC_DIR)/bar.c
LIB_OBJS := $(patsubst %.c,$(BUILD)/%.o,$(notdir $(LIB_SRCS)))
APP := app
APP_SRCS := main.c
APP_OBJS := $(APP_SRCS:%.c=$(BUILD)/%.o)
DEPS := $(LIB_OBJS:.o=.d) $(APP_OBJS:.o=.d)

all: $(APP)
	
$(APP) : $(APP_OBJS) $(LIB)
	$(CC) $(APP_OBJS) $(LIB) -o $@
	
$(APP_OBJS) : $(APP_SRCS) | $(BUILD)/
	$(CC) $(CFLAGS) -c $^ -o $@

$(LIB_OBJS) : $(LIB_SRCS) | $(BUILD)/
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB) : $(LIB_OBJS) | $(BUILD)/
	$(AR) $(ARFLAGS) $@ $^
$(BUILD)/:
	mkdir -p $(BUILD)

-include $(DEPS)

clean:
	rm -r -f $(BUILD) $(LIB) $(APP)