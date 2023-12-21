LIB = libgnl.a

CC = cc

SRC_DIR = src
BUILD_DIR = build
INC_DIR = src

C_FILES = src/get_next_line.c src/get_next_line_utils.c
H_FILES = src/get_next_line.h
OBJS := $(C_FILES:%=$(BUILD_DIR)/%.o)

CFLAGS  = -Wall -Wextra
#CFLAGS += -Werror
CFLAGS += -I$(INC_DIR)

__BUFFER_SIZE = 100
CFLAGS += -D BUFFER_SIZE=$(__BUFFER_SIZE)

.PHONY: all
all: build

.PHONY: build
build: $(LIB)

.PHONY: re
re: fclean build

$(LIB): $(OBJS) $(H_FILES)
	ar rcs $@ $(OBJS)

$(BUILD_DIR)/%.c.o: %.c $(H_FILES)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean fclean
clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(LIB)
