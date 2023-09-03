cc = gcc
target = starwars
objects = for_loops.o print_arr.o main.o

$(target) : $(objects)
	$(cc) -o $(target) $(objects)

$(objects) : star.h

.PHONY : clean
clean :
	rm $(target) $(objects)
