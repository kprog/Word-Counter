CC= gcc
LD= gcc
CFLAGS= -ansi -Wall -Wextra -pedantic -std=c99 -g -O0 -I sources

.PHONY: clean

all: unit_tests wordcount

unit_tests: avl_tree_test int_counts_test parser_test

int_counts_test: tests/test.o tests/int_counts_test.o sources/int_counts.o
	$(LD) $^ -o $@

avl_tree_test: tests/test.o tests/avl_tree_test.o sources/avl_tree.o
	$(LD) $^ -o $@

parser_test: tests/test.o tests/parser_test.o sources/parser.o
	$(LD) $^ -o $@


wordcount: sources/wordcount.o sources/avl_tree.o sources/int_counts.o sources/parser.o
	$(LD) $^ -o $@


%.o: %.c
	@$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
	@echo "CC $<"

run_tests: unit_tests
	valgrind --leak-check=full --show-reachable=yes ./avl_tree_test
	valgrind --leak-check=full --show-reachable=yes ./int_counts_test
	valgrind --leak-check=full --show-reachable=yes ./parser_test

run_tests2: wordcount
	cd tests && ./test.sh

clean:
	$(RM) tests/*.o sources/*.o avl_tree_test int_counts_test parser_test wordcount tests/*.try

