# Practical Programming Methodology - Assignment 1

## Verbal Collaboration 
|Student name| CCID |
|------------|------|
|student 1   | none |

## TODOs

In this file you **must**:
- [ ] Fill out the verbal collaboration table above (fill in **none** if you did not collaborate with anyone). Please note that CCID is **different** from student number.
- [ ] Acknowledge all resources consulted (discussions, texts, urls, etc.) while working on an assignment. Non-detailed oral discussion with others is permitted as long as any such discussion is summarized and acknowledged by all parties.
- [ ] Provide clear installation and execution instructions that TAs must follow to execute your code.

## Execution
Use the following command in the current directory.

`./encrypt -t <mappingfile> -m <encryption mode> -i <inputfile>`
This is a program that encrypts or decrypts a user  text input using the user provided mapping file.
First of all type "makefile" into the terminal to automatically compile the encrypt.c code.
To execute the encryption mode of the program, please type the following commands into the terminal:
./encrypt -t mapping_encryption.csv -i input_encryption.txt -m 1
where:
"-t", is the name of the mappingfile to be provided by the user.
"-i" is the name of the input file to be encrypted.
"-m" the mode in which the program is to be executed.
The mode for encryption should be "1" and entering any other number can lead to an unexpected result or a crash in the program.

For the decryption mode, please enter the following commands into the terminal:
./encrypt -t mapping_decryption.csv -i input_decryption.txt -m 2
where:
"-t", is the name of the mappingfile to be provided by the user.
"-i" is the name of the input file to be decrypted.
"-m" the mode in which the program is to be executed.
The mode for decryption should be "2" and entering any other number can lead to an unexpected result or a crash in the program.

The product of the encryption or decryption should be printed on the terminal. Any unexpected errors will also be shown to the user.
The user can then call "make clean" into the terminal the remove the executable file.


## References and Resources 
* Provide all links of the external resources you used as reference. (e.g. stackoverflow, etc.)
This are the links i used to solve error i had with strcmp and other functions
//https://www.tek-tips.com/viewthread.cfm?qid=940347
//https://stackoverflow.com/questions/2603039/warning-comparison-with-string-literals-results-in-unspecified-behaviour

# Files

DO NOT DELETE ANY OF THE FILES BELOW FROM YOUR REPO.

* `LICENSE.md`: contains the CMPUT 201 license. Please replace `<student name>` with your name.
* `README.md`: this file
* `check_general_requirements.sh`: this is the checking script you can run that will check that all your required files are availble. If this script shows any warnings or errors, you are very likely to get a 0.
* `LocalTestScripts`: two scripts that you can run locally to test your code before pushing to github. There's a ReadMe file inside that folder that explains things.
* `sampletestcases`: a folder containing 2 sample test cases, one for encryption and one for decryption.

* 'mapping_decryption' and 'mapping_encryption' are the two files that i used to to create my own test cases for encryption and decryption.
* 'test_decryption' and 'test_encryption' are two shell files that i used to automaticaly execute the files needed for the test cases.
* 'makefile' is a make file that automatically compiles the code for execution
 
