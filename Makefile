MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

all: projects

-include $(MAKEFILE_DIR)/src/common.mk

# Projects
PROJECT_DIRS ?= $(shell find "$(SRC_DIR)" -mindepth 1 -maxdepth 1 -type d)
PROJECT_NAMES ?= $(notdir $(PROJECT_DIRS))

# Targets
.PHONY: all projects $(PROJECT_NAMES)

projects: $(PROJECT_NAMES)

$(PROJECT_NAMES):
	@$(MAKE) --no-print-directory -C $(SRC_DIR)/$@ $@
