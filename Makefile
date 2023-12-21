EXEC = exec

CC = cc

SRC_DIR = src
BUILD_DIR = build
INC_DIR = src

C_FILES = src/get_next_line.c src/get_next_line_utils.c src/main.c
H_FILES = src/get_next_line.h
OBJS := $(C_FILES:%=$(BUILD_DIR)/%.o)

CFLAGS  = -Wall -Wextra
#CFLAGS += -Werror
CFLAGS += -I$(INC_DIR)

__BUFFER_SIZE = 1024
#CFLAGS += -D BUFFER_SIZE=$(__BUFFER_SIZE)

.PHONY: all
all: run

.PHONY: run
run: $(BUILD_DIR)/$(EXEC)
	./$(BUILD_DIR)/$(EXEC)

.PHONY: build
build: $(BUILD_DIR)/$(EXEC)

.PHONY: re
re: clean all

$(BUILD_DIR)/$(EXEC): $(OBJS) $(H_FILES)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(BUILD_DIR)/%.c.o: %.c $(H_FILES)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

# LSP stuff, don't worry about it
.PHONY: update
update:
	make clean
	mkdir $(BUILD_DIR)
	bear --output $(BUILD_DIR)/compile_commands.json -- make build

