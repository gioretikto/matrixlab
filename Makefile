CC = gcc
CFLAGS = -Wall -g -Wshadow -pedantic -Wextra -std=c99
LDFLAGS = -lm
OBJFILES = main.o read.o display.o processing.o
TARGET = matrixlab
all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET)
install:
	cp $(TARGET) /usr/local/bin