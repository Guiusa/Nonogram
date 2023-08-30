OBJS= src/memLib.c src/ioLib.c src/actionsLib.c src/fileLib.c

all:
	gcc src/main.c ${OBJS} -o nonogram

teste:
	gcc src/test.c ${OBJS} -o tst

purge:
	@echo "Removing programs"
	@rm -f nonogram tst
