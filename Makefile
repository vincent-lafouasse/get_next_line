EXEC = exec

CC = cc

SRC_DIR = src
BUILD_DIR = build
INC_DIR = src

C_FILES  = src/get_next_line.c 
C_FILES += src/get_next_line_utils.c
C_FILES += example/main.c

OBJS := $(C_FILES:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

CFLAGS  = -Wall -Wextra -g3
CFLAGS += -Werror
CFLAGS += -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition
CFLAGS += -I$(INC_DIR)
CFLAGS += -MMD -MP

__BUFFER_SIZE = 42
CFLAGS += -D BUFFER_SIZE=$(__BUFFER_SIZE)

.PHONY: all
all: run

.PHONY: run
run: $(BUILD_DIR)/$(EXEC)
	@echo running binary
	@./$(BUILD_DIR)/$(EXEC) input/all_star.txt

.PHONY: build
build: $(BUILD_DIR)/$(EXEC)

.PHONY: re
re: clean all

$(BUILD_DIR)/$(EXEC): $(OBJS)
	@echo linking binary
	@$(CC) $(CFLAGS) $^ -o $@
	@printf "$(GREEN)===============BUILD COMPLETED===============$(NC)\n"

$(BUILD_DIR)/%.c.o: %.c
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

-include $(DEPS)
