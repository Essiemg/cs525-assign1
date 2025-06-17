CC = gcc
CFLAGS = -g -Wall
SOURCES = storage_mgr.c dberror.c test_assign1_1.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = test_assign1

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
