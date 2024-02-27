wordSearch2D: src/wordSearch2D.o src/puzzle2D.o
		gcc -Wall -std=c99 -Wextra -Werror -o wordSearch2D src/wordSearch2D.o src/puzzle2D.o
wordSearch2D.o: src/wordSearch2D.c src/puzzle2D.h
		gcc -Wall -std=c99 -Wextra -Werror -c src/wordSearch2D.c
puzzle2D.o: src/puzzle2D.c src/puzzle2D.h
		gcc -Wall -std=c99 -Wextra -Werror -c src/puzzle2D.c
clean:
	rm -f src/*.o
	rm -f wordSearch2D
	rm -f src/puzzle2D
	rm -f *.txt