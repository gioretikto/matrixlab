CC = gcc
CFLAGS = -Wall -g -Wshadow -pedantic
LDFLAGS = -lm
OBJFILES = main.o functions.o determinant.o inverse.o read.o calculate.o
TARGET = freelab
all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(OBJFILES)
install:
	cp $(TARGET) /usr/local/bin
