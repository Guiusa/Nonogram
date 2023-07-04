OBJS= memLib.c ioLib.c actionsLib.c

all:
	gcc main.c ${OBJS} -o nonogram

purge:
	rm -f nonogram
