all: fact exe


fact:
	clang factorial.c -o fact -ggdb

exe:
	clang exe.c -o exe -ggdb

