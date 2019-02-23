
SRC := $(wildcard *.c)
OBJ := $(patsubst %.c,%,$(SRC))


CC := gcc
CFLAGS := -g -Wall -O2



all:$(OBJ)

#$(OBJ):$(SRC)
#	$(CC) $(CFLAGS) $< -o $@

%.o:%.c
	$(CC) $(CFLAGS)  $< -o $@

.PYONY:clean all

clean:
	-rm -f *.o $(OBJ)





