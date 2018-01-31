CC = g++        # compile using g++
CFLAGS = -O3    # optimize a lot
TARGET = assign # the binary to build

all: $(TARGET)

$(TARGET): assign.h console.cpp course.h parser.h student.h
	$(CC) $(CFLAGS) -Idlib -o $(TARGET) console.cpp

clean:
	$(RM) $(TARGET)
