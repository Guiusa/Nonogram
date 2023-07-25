OBJS= src/memLib.c src/ioLib.c src/actionsLib.c

all:
	gcc src/main.c ${OBJS} -o nonogram

purge:
	@echo "Removing programs"
	@rm -f nonogram
