CFLAGS= -Wall
TARGET = PA3

all: $(TARGET) docs

$(TARGET): filefunctions.o stringfunctions.o tree.o main.o
	gcc $(CFLAGS) filefunctions.o stringfunctions.o tree.o main.o -o $(TARGET)
	
main.o: main.c
	gcc $(CFLAGS) -c main.c

filefunctions.o: filefunctions.c
	gcc $(CFLAGS) -c filefunctions.c
	
stringfunctions.o: stringfunctions.c
	gcc $(CFLAGS) -c stringfunctions.c
	
tree.o: tree.c
	gcc $(CFLAGS) -c tree.c
	
docs:
	doxygen
	
clean:
	rm -f *.o $(TARGET)

