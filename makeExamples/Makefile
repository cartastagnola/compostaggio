CC=g++
CFLAGS=-I.
DEPS = helloWorld.h
OBJS = helloWorld.o printFunc.o
.SECONDARY: $(OBJS)

# the $@ set to name %.o like the %.c
# the $< is the first item in the dependency list (right part of :)
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# the $^ is the right part of the :
helloWorld: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm helloWorld *.o
