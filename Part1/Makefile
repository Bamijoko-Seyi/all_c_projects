squeue_client: squeue.o squeue_client.o
	gcc -g -Wextra -Wall -std=c99 -o squeue squeue.o squeue_client.o

squeue.o: squeue.h squeue.c
	gcc -g -Wextra -Wall -std=c99 -c -o squeue.o squeue.c

squeue_client.o: squeue.h squeue_client.c
	gcc -g -Wextra -Wall -std=c99 -c -o squeue_client.o squeue_client.c

clean:
	rm -f *.o
	rm -f squeue