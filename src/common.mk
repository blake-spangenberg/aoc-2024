MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

# Directories
TOP_DIR ?= $(abspath $(MAKEFILE_DIR)/..)
SRC_DIR ?= $(TOP_DIR)/src
BUILD_DIR ?= $(TOP_DIR)/build
OBJ_DIR ?= $(BUILD_DIR)/obj
BIN_DIR ?= $(BUILD_DIR)/bin

# Compiler Configuration
GCC ?= gcc
CFLAGS ?= -std=c2x -Wall -Werror -O2 -MMD -MP
LDFLAGS ?=

# Dependencies
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.c.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(PROJECT_DIR)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Common Targets
$(BUILD_DIR) $(OBJ_DIR) $(BIN_DIR) $(OBJ_DIR)/$(PROJECT_NAME):
	@mkdir -p $@

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)

# Project Targets

BIN := $(BIN_DIR)/$(PROJECT_NAME)

.PHONY: $(PROJECT_NAME)
$(PROJECT_NAME): $(BUILD_DIR) $(BIN_DIR) $(OBJ_DIR) $(OBJ_DIR)/$(PROJECT_NAME) $(BIN)

$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.c.o:
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $(patsubst $(OBJ_DIR)/%.c.o,$(SRC_DIR)/%.c,$@) -o $@

-include $(DEPS)
