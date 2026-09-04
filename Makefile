CC = gcc
CFLAGS = -Wall --std=c99
OBJECTS = main.o my_string.o unit_test.o test_def.o vector.o

string_driver:	$(OBJECTS)
	$(CC) $(CFLAGS) -o string_driver my_string.o main.o test_def.o vector.o
unit_test: my_string.o unit_test.o test_def.o
	$(CC) $(CFLAGS) -o unit_test unit_test.o test_def.o my_string.o
unit_test.o: unit_test.h unit_test.c
	$(CC) $(CFLAGS) -c unit_test.c -o unit_test.o
test_def.o: test_def.c
	$(CC) $(CFLAGS) -c test_def.c -o test_def.o
main.o: main.c
	$(CC) $(CFLAGS)	-c main.c -o main.o
my_string.o: my_string.h my_string.c
	$(CC) $(CFLAGS) -c my_string.c -o my_string.o
vector.o: generic_vector.h generic_vector.c
	$(CC) $(CFLAGS) -c generic_vector.c -o vector.o
clean:
	rm -f string_driver $(OBJECTS)

