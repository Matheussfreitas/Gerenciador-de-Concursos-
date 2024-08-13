CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lm

TARGET = mega_sena_manager
OBJS = main.o hash_table.o file_handler.o statistics.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

main.o: main.c hash_table.h statistics.h file_handler.h
	$(CC) $(CFLAGS) -c main.c

hash_table.o: hash_table.c hash_table.h
	$(CC) $(CFLAGS) -c hash_table.c

file_handler.o: file_handler.c file_handler.h hash_table.h
	$(CC) $(CFLAGS) -c file_handler.c

statistics.o: statistics.c statistics.h hash_table.h
	$(CC) $(CFLAGS) -c statistics.c

clean:
	rm -f $(TARGET) $(OBJS)
