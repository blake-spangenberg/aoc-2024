MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
PROJECT_DIR := $(MAKEFILE_DIR)
PROJECT_NAME := $(notdir $(patsubst %/,%,$(dir $(PROJECT_DIR))))

SRCS := $(shell find $(PROJECT_DIR) -name '*.c')

$(PROJECT_NAME): input.h
input.h: input.py
	python $^

-include $(MAKEFILE_DIR)/../common.mk
