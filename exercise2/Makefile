CC := gcc
CFLAGS := -I.
OBJS := implement.o calc.o

all: $(OBJS)
	$(CC) -o calc $^ $(CFLAGS)
clean:
	rm -f *.o calc
