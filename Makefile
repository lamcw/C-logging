CC = gcc
CFLAGS = -Wall -Werror -g
LIBS = -lm
# C files
SRC = $(wildcard src/*.c)
$(info source files are [${SRC}])
# object files
OBJ = $(patsubst src/%.c,obj/%.o,$(SRC))
$(info object files are [${OBJ}])

test: test/test_log.c obj/log.o
	$(CC) $(CFLAGS) $(LIBS) $^ -o test_log

obj/%.o: $(SRC)
	@mkdir -p obj
	$(CC) $(CFLAGS) $(LIBS) -c $^ -o $@

.PHONY: clean
clean:
	$(RM) -r $(OBJ) test.o src/core test_log obj
