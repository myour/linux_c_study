
SRC := $(wildcard *.c)
OBJ := $(patsubst %.c,%,$SRC)

CC := gcc
CFLAGS := -g -Wall -O2
LDFLAGS :=



all:$(OBJ)

$(OBJ):$(SRC)
	$(CC) $(CFLAGS) $< -o $@

PHONY:
clean:
	-rm -rf $(OBJ)



