/*******************************************
encrypt.c
 Author: Bammijoko Oluwaseyfunmi 
 Last updated: 2/12/2023
 *******************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "license.h"
void process_input_file( FILE *input_file, char *mode,
                        char mapping_decryption[][3]);
void error_checker(int argc, char *argv[]);


void error_checker(int argc, char  *argv[]){
    //This functioon checks the user provided arguements for validity that prevents issue on the code 
    //It returns nothing
    int mode_pos = 0, file_name_pos =  0, mapping_file_pos = 0, i, j, k, valid_mapping_file = 1;
    char *mode, word;
    char mapping_decryption[26][3];
    int  line_count = 0;
    FILE *mapping_file_opened, *input_file;
        //This section enables the code tp receive the arguements in any order
        for(i = 1; i <= 6; i++){
            if((strcmp( argv[i], "-m") == 0) && mode_pos == 0){//checks if the mode arguement is present and assigns it 
                mode_pos = i; 
                mode = argv[i + 1 ];
            }

            else if((strcmp( argv[i], "-i") == 0) && file_name_pos == 0){//checks if the input arguement is present and assigns it 
                file_name_pos = i;
            }

            else if((strcmp( argv[i], "-t") == 0) && mapping_file_pos == 0){//checks if the mapping file arguement is present and assigns it 
                mapping_file_pos = i;
                
            }
        
        }
        if (argc != 7 || mode_pos == 0 || file_name_pos == 0 || mapping_file_pos == 0){// checks if the arguements are in the right format
                printf("%d",line_count);
                fprintf(stderr, "Usage: ./encrypt -t <mappingfile> -m <encryption mode> -i <inputfile>\n");
                exit(7);
            }
            
        mapping_file_opened = fopen(argv[mapping_file_pos + 1], "r");
        input_file = fopen(argv[file_name_pos + 1], "r");
        if (mapping_file_opened == NULL ){
            fprintf(stderr, "Error: Mapping file %s does not exist\n", argv[mapping_file_pos + 1]);//checks if the mapping file exhists
            exit(3);
            fclose(mapping_file_opened);
           
        }

       if (input_file == NULL){ 
            fprintf(stderr, "ERROR: Input word file %s does not exist\n", argv[file_name_pos + 1]);//checks if the input file exhists
            exit(5);
            fclose(input_file);
            
            }

        if((atoi(mode) != 1) && (atoi(mode) != 2)){
            fprintf(stderr, "You entered %s . Sorry, your mode must be 1 for encryption or 2 for decryption\n", mode);
            //fclose(fp);
            exit(6);
        }    
            //This part serves as a line counter for my mapping file and it also stores the mapping file into an array
            for (i = 0; i < 26; i++){
                for (k = 0; k < 3; k++){
             word = fgetc(mapping_file_opened);
                mapping_decryption[i][k] = word;
                }
                line_count++;
                fgetc(mapping_file_opened);
            }

                //This portion of the code checks if the mapping file provided is valid 
                for(i = 0; i < 26; i++){
                    for(j = 0; j < 26; j++){
                        if((mapping_decryption[i][0] == mapping_decryption[j][0] && i != j) || (mapping_decryption[i][0] < 97 && mapping_decryption[i][0] > 122)){
                            valid_mapping_file = 0;
                            break;
                        }
                         if((mapping_decryption[i][2] == mapping_decryption[j][2] && i != j) || (mapping_decryption[i][2] < 97 && mapping_decryption[i][2] > 122 )){
                            valid_mapping_file = 0;
                            break;
                        }
                    }
                       if (mapping_decryption[i][1] != ','){
                            valid_mapping_file = 0;
                             break;
                        }
                        if ((mapping_decryption[i][0] < 97 || mapping_decryption[i][0] > 122) ||(mapping_decryption[i][2] < 97 || mapping_decryption[i][2] > 122)){
                            valid_mapping_file = 0;
                             break;
                        }
                    
                }
            if (line_count != 26 && valid_mapping_file == 0){
                printf("%d",line_count);
                fprintf(stderr, "ERROR: The format of mapping file %s  is incorrect\n", argv[mapping_file_pos + 1]);
                exit(4);
                fclose(input_file);
    
            }

            if (valid_mapping_file == 0){
                printf("%d",line_count);
                fprintf(stderr, "ERROR: The format of mapping file %s  is incorrect\n", argv[mapping_file_pos + 1]);
                exit(4);
                fclose(input_file);
                
            }
        process_input_file(input_file,mode, mapping_decryption);
}
void process_input_file( FILE *input_file, char *mode, char mapping_decryption[][3]) {
        int i, j, k, l, number_of_lines = 1;
        char word = ' ';
        //This function encrypts the files provided and it prints them out into the terminal
        //It returns nothing 
    

        //This portion of code simply computes the number of lines of the input file 
        while(word != EOF){
             word = fgetc(input_file);
             if(word == '\n'){
                number_of_lines++;
             }
        }

        char processed_output[number_of_lines][20], seperated_input[number_of_lines][20];
        rewind(input_file);//make the program read files from the beginning 
        //this portion of code simply converts the input file into an array 
        word = ' ', i = 0, j = 0;
        while(word != EOF){
             word = fgetc(input_file);
             if (word == EOF){
                seperated_input[i][j] = '`';//tried to find a way to mark the end of the file, so that no errors occur
             }
             else if (word != '\n'){
            seperated_input[i][j] = word;//adds a newline to the end of each line
            j++;
             }
             else{
                seperated_input[i][j] = '\n';
                i++;
                j = 0;
             }
        }
        
            // this portion of my code encrypts or decrypts the user file based on the mode provided
            for(i = 0; i < number_of_lines;i++){
                    for(j=0; j < 20; j++){
                        if(seperated_input[i][j] == '\n' || seperated_input[i][j] == '`'){//"j" is incremented until we reach a newline or the end of the file.
                            break;
                            }
                    }

                processed_output[i][j] = '\n';//i added a newline to the end of the line and began to encrypt or decrypt in reverse 
                j--;
                k = 0, l = 0;
                while(j >= 0){
                    if(atoi(mode) == 1 ){
                    for(k = 0; k < 26; k++){
                        if(seperated_input[i][j] == mapping_decryption[k][0]){//looks for the character in the mapping encrypted file and add its encrypted character to output
                            processed_output[i][l] = mapping_decryption[k][2];
                            l++;
                            j--;
                            break;
                        }
                     }
                    }

                    if(atoi(mode) == 2 ){
                    for(k = 0; k < 26; k++){
                        if(seperated_input[i][j] == mapping_decryption[k][2]){//looks for the character in the mapping decrypted file and add its decrypted character to output
                            processed_output[i][l] = mapping_decryption[k][0];
                            l++;
                            j--;
                            break;
                        }
                     }
                    }
                    
                }

            }

             //this portion of the code prints our processed output to the terminal
             for(i = 0; i < number_of_lines; i++){
                j = 0;
                while(processed_output[i][j] != '\n' && processed_output[i][j]!='`'){
                    fprintf( stdout, "%c",processed_output[i][j]);
                    j++;
                }   
                    fprintf( stdout, "\n");
                //}                    
            }
    }
int main(int argc, char * argv[])
{
        //this main function executes the funtions needed by the program
        error_checker(argc, argv);
    return 0;
}
