
INCLUDES = -I
LDFLAGS  =
CFLAGS   = -O2
CXX      = g++
CC       = gcc

examples = async boost_test demo

CC_COMPILE = $(CC) $(CFLAGS) $(INCLUDES)
CXX_COMPILE = $(CXX) $(CFLAGS) $(INCLUDES)

all: $(examples)

async:
	$(CXX_COMPILE) -o thread_split thread_split.cpp $(LDFLAGS) 

boost_test:
	$(CC_COMPILE) -o thread_split_pthreads thread_split_pthreads.c $(LDFLAGS)

demo:
	$(CC_COMPILE) -o demo main.cpp $(LDFLAGS)

clean:
	-rm -f $(examples).o $(examples)
