EXEC = exec

CC = cc

SRC_DIR = src
BUILD_DIR = build
INC_DIR = src

C_FILES = src/get_next_line.c src/get_next_line_utils.c src/main.c
H_FILES = src/get_next_line.h
OBJS := $(C_FILES:%=$(BUILD_DIR)/%.o)

CFLAGS  = -Wall -Wextra -g3
CFLAGS += -std=c99 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition
#CFLAGS += -Werror
CFLAGS += -I$(INC_DIR)

__BUFFER_SIZE = 1024
#CFLAGS += -D BUFFER_SIZE=$(__BUFFER_SIZE)

.PHONY: all
all: run

.PHONY: run
run: $(BUILD_DIR)/$(EXEC)
	@echo running binary
	@./$(BUILD_DIR)/$(EXEC)

.PHONY: build
build: $(BUILD_DIR)/$(EXEC)

.PHONY: re
re: clean all

$(BUILD_DIR)/$(EXEC): $(OBJS) $(H_FILES)
	@echo linking binary
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@printf "$(GREEN)===============BUILD COMPLETED===============$(NC)\n"

$(BUILD_DIR)/%.c.o: %.c $(H_FILES)
	@echo compile $(basename $<)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@echo cleanup
	@rm -rf $(BUILD_DIR)

# LSP stuff, don't worry about it
.PHONY: update
update:
	@make clean
	@mkdir "$(BUILD_DIR)"
	bear --output "$(BUILD_DIR)/compile_commands.json" -- make build

GREEN = \033[0;32m
NC = \033[0m

