cc = g++
target = a.out
objects = str.o main.o

$(target): $(objects)
	$(cc) -o $(target) $(objects)

$(objects) : Str.h

.PHONY : clean
clean :
	rm $(target) $(objects)

