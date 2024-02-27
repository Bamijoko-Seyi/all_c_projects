bucketstack_client: bucketstack.o bucketstack_client.o
	gcc -g -Wall -std=c99 -o bucketstack bucketstack.o bucketstack_client.o

bucketstack.o: bucketstack.h bucketstack.c
	gcc -g -Wall -std=c99 -c -o bucketstack.o bucketstack.c

bucketstack_client.o: bucketstack.h bucketstack_client.c
	gcc -g -Wall -std=c99 -c -o bucketstack_client.o bucketstack_client.c

clean:
	rm -f *.o
	rm -f bucketstack