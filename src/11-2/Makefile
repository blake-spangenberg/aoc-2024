MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
PROJECT_DIR := $(MAKEFILE_DIR)
PROJECT_NAME := $(notdir $(patsubst %/,%,$(dir $(PROJECT_DIR))))

SRCS := $(shell find $(PROJECT_DIR) -name '*.c')

-include $(MAKEFILE_DIR)/../common.mk
