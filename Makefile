CC = g++				# compile using g++
CFLAGS = -O3 -std=c++11	# optimize a lot, use C++11 standards
TARGET = assign.exe		# the binary to build
OUT = -o 				# set output var

# https://stackoverflow.com/questions/8270391/use-the-same-makefile-for-make-linux-and-nmakewindows
# \
!ifndef 0 # \
# nmake code here \
CC = cl # \
RM = del # \
CFLAGS = -O2 # \
OUT = -Fe # \
!else
# \
!endif

all: $(TARGET)

$(TARGET): assign.h console.cpp course.h parser.h student.h
	$(CC) $(CFLAGS) -Idlib $(OUT)$(TARGET) console.cpp

clean:
	$(RM) $(TARGET)
