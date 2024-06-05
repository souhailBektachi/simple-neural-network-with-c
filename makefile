CC = gcc
CFLAGS = -Wall -Wextra  -g -I include 
LDFLAGS = 

TARGET = exe
SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
SRC_FILES += main.c
OBJ_DIR = build
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_FILES) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	del /Q $(OBJ_DIR)\*.o

debug: CFLAGS += -DDEBUG
debug: all
