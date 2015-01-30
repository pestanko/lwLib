all:
	gcc -std=c99 -Wall -Wextra -pedantic -g -DDEBUG  *.c config/*.c -o test
