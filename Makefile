CC=gcc
CFLAGS=-Wall -Wextra -Werror -ansi -pedantic -g
proj2: *.c 
proj2.zip: *.c 
	zip proj2.zip *.c *.h
clean::
	rm -f proj1 a.out *.o core tests/*.diff proj1.zip