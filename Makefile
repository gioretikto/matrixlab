CC = gcc
CFLAGS = -Wall -g -Wshadow -pedantic -Wextra
LDFLAGS = -lm
OBJFILES = main.o functions.o determinant.o inverse.o read.o calculate.o
TARGET = matrixlab
all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET)
install:
	cp $(TARGET) /usr/local/bin