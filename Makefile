TARGET=main.exe
TARGET+=read.exe

CXXFLAGS+=-Wall -Werror
CXXFLAGS+=-g -O0

QUAD=1
ifdef QUAD
CXXFLAGS+=-DQUAD
endif

all:$(TARGET)

objects.o:	objects.cpp render.hpp vmath.hpp
vmath.o:	vmath.cpp vmath.hpp
main.o:	main.cpp vmath.hpp render.hpp
main.exe: main.o objects.o vmath.o
read.exe: read.o objects.o vmath.o

%.exe: %.o
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) $(TARGET) *.o
