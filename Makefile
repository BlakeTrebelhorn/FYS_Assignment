CC = g++        # compile using g++
CFLAGS = -O3    # optimize a lot
TARGET = assign # the binary to build
OUT = -o

ifeq ($(OS),Windows_NT)
    CC = cl
    CCFLAGS = -O2
    TARGET = assign.exe
    OUT = -Fe
endif

all: $(TARGET)

$(TARGET): assign.h console.cpp course.h parser.h student.h
	$(CC) $(CFLAGS) -Idlib $(OUT) $(TARGET) console.cpp

clean:
	$(RM) $(TARGET)