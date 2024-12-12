MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
PROJECT_DIR := $(MAKEFILE_DIR)
PROJECT_NAME := $(notdir $(patsubst %/,%,$(dir $(PROJECT_DIR))))

SRCS := $(shell find $(PROJECT_DIR) -name '*.c')

$(PROJECT_NAME): ../9-1/input.h ../9-1/input_test.h
%.h: %.txt
	xxd -n INPUT -C -i $< > $@

-include $(MAKEFILE_DIR)/../common.mk
