#This is the Makefile for the Phenomenon Game Engine static library
#Please note that it uses implict rules for compilation.

LIB=libphenomenon.a

CXXFLAGS = -I/usr/include/SDL -O2 -Wall

# Objects consist of all .cpp in phenomenon and all .c in extern. (just stb_image)

objects := $(patsubst %.cpp,%.o,$(wildcard ./phenomenon/*.cpp)) $(patsubst %.c,%.o,$(wildcard ./extern/*.c))

all : $(objects)
	echo $(objects)
	$(AR) r $(LIB) $(objects)

clean:
	rm $(objects) $(LIB)

rmobjs:
	rm $(objects)
