# Directories
SRC_DIR := src
BUILD_DIR := build

# Compiler settings
GCC := gcc
CFLAGS := -std=c2x -Wall -Werror -O2 -MMD -MP
LDFLAGS :=

# Automatically find project directories
PROJECT_DIRS := $(shell find "$(SRC_DIR)" -mindepth 1 -maxdepth 1 -type d)
PROJECT_NAMES := $(notdir $(PROJECT_DIRS))

# Default target
all: $(addprefix $(BUILD_DIR)/,$(PROJECT_NAMES))

# Rule to compile each project into its own executable
$(BUILD_DIR)/%: $(shell find $(SRC_DIR)/$* -type f -name '*.c')
	@echo "Building Project $*..."
	@mkdir -p $(BUILD_DIR)
	@$(GCC) $(CFLAGS) $(shell find $(SRC_DIR)/$* -type f -name '*.c') -o $@ $(LDFLAGS)


# Include the dependency files that are auto-generated by GCC
-include $(foreach d,$(PROJECT_NAMES),$(wildcard $(BUILD_DIR)/$(d)/*.d))

# Clean up
clean:
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR)