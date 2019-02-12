OMPFLAGS = -fopenmp
OMPLIBS = -lgomp

CC = gcc
CPPFLAGS = -g -Wall
LDFLAGS = -g -Wall
LDLIBS = $(OMPLIBS) -lm

MPICC = mpicc
MPICH = /usr/lib64/openmpi/1.4-gcc
CFLAGS = -I$(MPICH)/include -I/usr/include/openmpi-x86_64 -I/usr/include/openmpi-1.10-x86_64

all: combined

combined: combined.o 
	$(MPICC)  $(OMPFLAGS) -o $@ $(LDFLAGS) $^ $(LDLIBS)

clean:
	rm -f *.o combined
