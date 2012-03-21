TARGET             = ./build/sudoku

SUCCESS_MSG        = '  [\e[32m DONE \e[0m]'

CC                 = gcc

nodebug: CFLAGS    = -std=c99 -Wall -Wextra
debug:   CFLAGS    = -std=c99 -Wall -Wextra -g3 -D DEBUG


all: nodebug

nodebug: build

debug: build

build: $(TARGET)


$(TARGET): ./src/lookup.h ./src/sudoku.c
	@echo 'Building target:'
	@mkdir -p build/
	@$(CC) $(CFLAGS) $^ -o $@
	@echo -e $(SUCCESS_MSG)

./src/lookup.h:
	@echo 'Building table:'
	@python ./src/lookup.py > ./src/lookup.h
	@echo -e $(SUCCESS_MSG)

clean:
	@echo 'Cleaning workspace:'
	@rm -rf ./build/
	@rm -rf ./src/lookup.h
	@echo -e $(SUCCESS_MSG)

rebuild: clean all
