# Makefile para retos

CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11
LDFLAGS = -lpthread

PROGRAMS = Reto1 Reto2 Reto3 Reto4 Reto5 Reto6 Reto7

.PHONY: all clean

all: $(PROGRAMS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# ejecutar un reto con make runN por ejemplo make run3
run%: %
	./$<

clean:
	rm -f $(PROGRAMS) *.o
