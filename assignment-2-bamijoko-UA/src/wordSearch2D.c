#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "puzzle2D.h"

int main(int argc, char * argv[])
{
    //clock_t start_time = clock();
    int puzzle_file_pos = 0, Wordlist_file_pos =  0, word_length_pos = 0, solution_file_pos = 0 , i;
    FILE *puzzle_file, * Wordlist_file;
    for(i = 0; i < argc; i++){
        if((strcmp(argv[i],"-p") == 0) && puzzle_file_pos == 0){
            puzzle_file_pos = i + 1;
        }

        else if((strcmp(argv[i],"-w") == 0) && Wordlist_file_pos == 0){
            Wordlist_file_pos = i + 1;
        }

        else if((strcmp(argv[i],"-l") == 0) && word_length_pos == 0){
            word_length_pos = i + 1;
        }

        else if((strcmp(argv[i],"-o") == 0) && solution_file_pos == 0){
            solution_file_pos = i + 1;
        }  
    }
        if(Wordlist_file_pos != 0 && puzzle_file_pos != 0 ){
        puzzle_file = fopen(argv[puzzle_file_pos], "r");
        Wordlist_file = fopen(argv[Wordlist_file_pos], "r");
        }

        if(puzzle_file_pos == 0 || Wordlist_file_pos == 0 || word_length_pos == 0){
            fprintf(stderr, "Usage: ./wordSearch2D -p <puzzle_file> -l <word_length> -w <wordlist_file> [-o <solution_file>]\n");//checks if the mapping file exhists
            exit(6);
        }
        if(puzzle_file == NULL ){
            fprintf(stderr, "Error: Puzzle file %s does not exist\n", argv[puzzle_file_pos]);
            exit(4);
        }

        if(Wordlist_file == NULL ){
            fprintf(stderr, "Error: Wordlist file %s does not exist\n", argv[Wordlist_file_pos]);
            exit(5);
        }

        if((solution_file_pos == 0 && argc != 7 ) || (solution_file_pos != 0 && argc != 9)){
            fprintf(stderr, "Usage: ./wordSearch2D -p <puzzle_file> -l <word_length> -w <wordlist_file> [-o <solution_file>]\n");//checks if the mapping file exhists
            exit(6);
        }
        
        //work on exit case 7 later
        
        //where the real work begins
        char word_list_array[100][(atoi(argv[word_length_pos])) + 1];
        word_list_initializer(Wordlist_file, (atoi(argv[word_length_pos])),word_list_array);
        int row,coloumn,word_line_count = 0;
        row = row_number_finder(puzzle_file);
        coloumn = row;
        char character_grid[row][coloumn];
        grid_initializer(puzzle_file,row,character_grid);

        for(int i = 0; i < 100; i ++){
            if(word_list_array[i][0] == '\0'){
                break;
            }
            word_line_count++;
        }

        int P = 7079, D = 256, h = 1,word_hash_list[word_line_count],temp_word_hash_value;
        for (int i = 0; i < word_line_count; i++) {
            word_hash_list[i] = 0;
        }
        for (int i = 0; i < atoi(argv[word_length_pos]) - 1; i++) {
          h = (h * D) % P;
        }
        
        for(int i = 0; i < word_line_count; i++){
            temp_word_hash_value = 0;
            for(int j = 0; j < atoi(argv[word_length_pos]); j++){
                temp_word_hash_value = (D * temp_word_hash_value + word_list_array[i][j]) % P;
            }
            word_hash_list[i] = temp_word_hash_value;
        }

        int result_storer[word_line_count][4];
        for(int i = 0; i < word_line_count; i++){
            for(int j = 0; j < 4; j++){
                result_storer[i][j] = 0;
            }
        }

        horizontally(D, P, h, row, atoi(argv[word_length_pos]), word_line_count, result_storer, character_grid, word_hash_list,word_list_array);
        vertically(D, P, h, row, atoi(argv[word_length_pos]), word_line_count, result_storer, character_grid, word_hash_list,word_list_array);
        bottom_left_to_top_right(D, P, h, row, atoi(argv[word_length_pos]), word_line_count, result_storer, character_grid, word_hash_list,word_list_array);
        top_right_backwards_to_bottom_left(D, P, h, row, atoi(argv[word_length_pos]), word_line_count, result_storer, character_grid, word_hash_list,word_list_array);
        bottom_right_backwards_to_top_left_diagonal(D, P, h, row, atoi(argv[word_length_pos]), word_line_count, result_storer, character_grid, word_hash_list,word_list_array);
        top_left_to_bottom_right_diagonal(D, P, h, row, atoi(argv[word_length_pos]), word_line_count, result_storer, character_grid, word_hash_list,word_list_array);
        //clock_t end_time = clock();
        //double elapsed_time = (double) (end_time - start_time) / CLOCKS_PER_SEC;

        if(solution_file_pos != 0){
            FILE *solution_file;
            solution_file = fopen(argv[solution_file_pos],"w");
                for(int i = 0; i < word_line_count; i++){
                    fprintf(solution_file,"%s;(%d,%d);%d\n",word_list_array[i],result_storer[i][0],result_storer[i][1],result_storer[i][2]);
            }
            fclose(solution_file);
        }
        else{
            FILE *solution_file;
            solution_file = fopen("output.txt","w");
            for(int i = 0; i < word_line_count; i++){
                    fprintf(solution_file,"%s;(%d,%d);%d\n",word_list_array[i],result_storer[i][0],result_storer[i][1],result_storer[i][2]);
                }
                fclose(solution_file);
            }
        //printf("Elapsed time: %.2f seconds\n", elapsed_time);
        //work on error code 7 later
        //write an error to check if the user input is actually up to 100
        //write an error to check the size of the row and the colum
        //check if the user arguement for word_length is accurate
        //handle cases where the user forgets to specify a file

    return 0;
}