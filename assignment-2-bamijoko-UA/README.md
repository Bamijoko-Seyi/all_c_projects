# Assignment 2

Bamijoko Oluwaseyifunmi: wordSearch2D.c
***************************************
This program searches for the user provided words in the user provided character grid.
Both these required inputs  are inputed into the porgram using .txt files and the
output is gotten through .txt files.
To execute and use the program, please call the "make" function to automatically compile
the source codes need to run the program. Once done, type in your word and charecter list
using the following format:
Usage: ./wordSearch2D -p <puzzle_file> -l <word_length> -w <wordlist_file>[-o <solution_file>]
where: "-p" is the name of the character grid or puzzle file,"-l" is the length of the words
provided,"-w" is the name of the file that holds the words to be searched and "-o" is an 
optional field for the name of your output.
once executed call "make clean" to get rid of all the exceutables.
"wordSearch2D.c" contains the main functions needed to run the program. It consist of a single
main function.
"puzzle2D.c" contains the functions need by wordSearch2D.c to functions. It contains several
functions that deal with puzzle/character grid.
"puzzle2D.h" contains the function prototypes needed by both source files.

Please see [assignment2_description.md](assignment2_description.md) for the
instructions. Modify this file (README.md) with the requirements explained in
[assignment2_description.md](assignment2_description.md)
