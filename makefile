CC = gcc
CFLAGS = -Wall -Wextra  -g  -I include 
LDFLAGS = -lm

TARGET = exe
SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
SRC_FILES += main.c
OBJ_DIR = build
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

ifeq ($(OS),Windows_NT)
    RM := del /Q $(OBJ_DIR)\*.o
else
    RM := rm -f $(OBJ_DIR)/*.o 
endif

.PHONY: all clean debug

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_FILES) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) 

debug: CFLAGS += -DDEBUG
debug: all
