# Makefile for hello.c

CC = gcc
CFLAGS = -Wall -Wextra -g -O0
TARGET = hello
SRC = hello.c

.PHONY: all clean debug

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) $(TARGET).exe

# 用于 GDB 调试的目标
debug: $(TARGET)
	gdb ./$(TARGET)
