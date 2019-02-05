C := gcc
CFLAGS := -Wall
HEADERS := priorityQ.h
OBJECTS := priorityQ.o main.o
TARGET := arg010_Scheduler

all: $(TARGET)

$(TARGET): $(OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(TARGET) *~

