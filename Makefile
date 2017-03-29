CFLAGS+=-Wno-unused-parameter -Wno-unused-variable # Pour ne pas que les trous dans le code fassent des erreurs de compil
CC?=gcc
CFLAGS+=-Wextra -Wall -pedantic-errors -Werror -Wfatal-errors -Wcast-qual -Wcast-align -Wconversion -Wdouble-promotion -Wfloat-equal -Wshadow -Wpointer-arith

all: fat_cli

test: test_utils.o utils.o
	$(CC) -o $@ $^ $(CFLAGS)

fat_cli: fat_cli.c fat32_driver.o utils.o
	$(CC) -o $@ $^ $(CFLAGS)

fat32_driver.o: fat32_driver.c fat32_driver.h
	$(CC) -o $@ -c $< $(CFLAGS)

utils.o: utils.c utils.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o

.PHONY: clean
