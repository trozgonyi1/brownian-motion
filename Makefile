CC     = gcc
CFLAGS = -Wall -std=c11 -g

TARGET = main
OBJS   = main.o heap.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: src/main.c include/heap.h
	$(CC) $(CFLAGS) -c $<

heap.o: src/heap.c include/heap.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
