CC=gcc
SRC=./src/a.c
BIN=./bin/a.out
CFLAGS=\
       -Wall \
       	-I./include \
	-L./lib 
$(BIN):$(SRC)
	@$(CC) \
		$(CFLAGS) \
		$(SRC) \
		-lpthread \
		-o $(BIN)
.phony:
	run \
	clean
run:
	@./bin/a.out
clean:
	@rm $(BIN)
