# Macros para compilacao
CC = gcc
CFLAGS = -I./ -lfreeimage -lpthread
DIR = src
FILENAME = $(DIR)/main.c
TARGET = ./main
SRCS := $(shell find $(DIR) -name '*.c')
OBJS = $(SRCS:.c=.o)


# Macros para teste
BASH = sh
TEST_SCRIPT = test.sh
VERBOSE ?= 1

all:$(TARGET)

$(TARGET):$(SRCS)
	$(CC) -o$(TARGET) $(SRCS) $(CFLAGS)


test:all
	$(BASH) $(TEST_SCRIPT) $(TARGET) $(VERBOSE)

clean:
	$(RM) ./$(TARGET)
	$(RM) $(DIR)/*.o
	$(RM) ./results/*.jpg
