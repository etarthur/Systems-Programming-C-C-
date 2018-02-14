CFLAGS= -Wall
TARGET = life

all: $(TARGET)

$(TARGET): life.o init.o
	gcc $(CFLAGS) life.o init.o -o $(TARGET)
	
life.o: life.h life.c
	gcc $(CFLAGS) -c life.c
	
init.o: life.h init.c
	gcc $(CFLAGS) -c init.c
	
clean:
	rm -f *.o $(TARGET)

