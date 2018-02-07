CC = g++        	# compile using g++
CFLAGS = -O3 -std=c++11	# optimize a lot, use C++11 standards
TARGET = assign.exe 	# the binary to build
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
