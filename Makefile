OBJS= memLib.c ioLib.c actionsLib.c

all:
	gcc main.c ${OBJS} -o nonogram

teste:
	gcc teste.c -o teste

purge:
	rm -f nonogram teste
