#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzle2D.h"
void word_list_initializer(FILE *word_list, int word_length, char word_list_array[][word_length + 1]) {
    rewind(word_list);
    int counter = 0, word_list_row = 0;
    char letter;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < word_length + 1; j++) {
            word_list_array[i][j] = '\0';
        }
    }

    while((letter = fgetc(word_list)) != EOF){
        if(letter == '\n' || letter == ' '){
            counter = 0;
            word_list_row++;
        }
        else{
            word_list_array[word_list_row][counter] = letter;
            counter++;
        }
    }
}

int row_number_finder(FILE *puzzle_file){
    int rows = 1,counter = 0;
    char letter;
    while((letter = fgetc(puzzle_file)) != EOF){
    if(letter == '\n'){
      rows++,counter++;
    }
    else{counter = 0;
    }
  }
  if(counter > 0){
    return (rows - counter);
  }
  return rows;
}

void grid_initializer(FILE *puzzle_file, int row,char character_grid[][row]){
    rewind(puzzle_file);
    for(int i = 0; i < row; i++){
        for(int j = 0; j < row; j++){
            character_grid[i][j] = fgetc(puzzle_file);
        }
        fgetc(puzzle_file);
    }
}

void horizontally(int D, int P, int h,int row,int word_length,int word_line_count,int result_storer[][4], char character_grid[][row],int word_hash_list[word_line_count],char word_list_array[][word_length + 1]){
    int coloumn = row, current_hash_value = 0, o = 0;
    char temp_word[word_length + 1];
    temp_word[word_length] = '\0';
    for(int k = 0; k < row; k++){
        current_hash_value = 0;
        for(int l = 0; l <= (coloumn - word_length); l++){
          if(l == 0){
          for(int m = l; m < word_length; m++){
              current_hash_value = (D * current_hash_value + character_grid[k][m]) % P;
            }
          }
            else{
              current_hash_value = (D * (current_hash_value - character_grid[k][l - 1] * h) + character_grid[k][l + word_length - 1]) % P;
              
            }
            while(current_hash_value < 0){
              current_hash_value = P + current_hash_value;
            }
            o = 0;
            for(int n  = l; n < l + word_length; n++){
                temp_word[o] = character_grid[k][n];
                o++;
            }
            for(int n = 0; n < word_line_count; n++){
                if(current_hash_value == word_hash_list[n] && (strcmp(temp_word,word_list_array[n]) == 0)){
                    result_storer[n][0] = k, result_storer[n][1] = l, result_storer[n][2] = 1, result_storer[n][3] = 1;
                }
            }
        }
        //reverse
        current_hash_value = 0;
        for(int l = coloumn - 1; l >= (0 + word_length - 1); l--){
          if(l == coloumn - 1){
          for(int m = l; m >= (coloumn - word_length); m--){
              current_hash_value = (D * current_hash_value + character_grid[k][m]) % P;
            }
          }
            else{
              current_hash_value = (D * (current_hash_value - character_grid[k][l + 1] * h) + character_grid[k][l - word_length + 1]) % P;
            }
            while(current_hash_value < 0){
              current_hash_value = P + current_hash_value;
            }
            o = 0;
            for(int n  = l; n > l - word_length; n--){
                temp_word[o] = character_grid[k][n];
                o++;
            }
            for(int n = 0; n < word_line_count; n++){
                if(current_hash_value == word_hash_list[n] && (strcmp(temp_word,word_list_array[n]) == 0)){
                    result_storer[n][0] = k, result_storer[n][1] = l, result_storer[n][2] = 2, result_storer[n][3] = 1;
                }
            }
          
        }
    }
}

void vertically(int D, int P, int h,int row,int word_length,int word_line_count,int result_storer[][4], char character_grid[][row],int word_hash_list[word_line_count],char word_list_array[][word_length + 1]){
    int coloumn = row, current_hash_value = 0, o = 0;
    char temp_word[word_length + 1];
    temp_word[word_length] = '\0';
    for(int k = 0; k < coloumn; k++){
        current_hash_value = 0;
        for(int l = 0; l <= (row - word_length); l++){
          if(l == 0){
          for(int m = l; m < word_length; m++){
              current_hash_value = (D * current_hash_value + character_grid[m][k]) % P;
            }
          }
            else{
              current_hash_value = (D * (current_hash_value - character_grid[l - 1][k] * h) + character_grid[l + word_length - 1][k]) % P;
            }
            while(current_hash_value < 0){
              current_hash_value = P + current_hash_value;
            }

            o = 0;
            for(int n  = l; n < l + word_length; n++){
                temp_word[o] = character_grid[n][k];
                o++;
            }
            for(int n = 0; n < word_line_count; n++){
                if(current_hash_value == word_hash_list[n] && (strcmp(temp_word,word_list_array[n]) == 0)){
                    result_storer[n][0] = l, result_storer[n][1] = k, result_storer[n][2] = 3, result_storer[n][3] = 1;
                }
            }
        }
            //reverse
            current_hash_value = 0;
        for(int l = row - 1; l >= (0 + word_length - 1); l--){
          if(l == row - 1){
          for(int m = l; m >= (row - word_length - 1) + 1; m--){
              current_hash_value = (D * current_hash_value + character_grid[m][k]) % P;
            }
          }
            else{
              current_hash_value = (D * (current_hash_value - character_grid[l + 1][k] * h) + character_grid[l - word_length + 1][k]) % P;
            }
            while(current_hash_value < 0){
              current_hash_value = P + current_hash_value;
            }
            o = 0;
            for(int n  = l; n > l - word_length; n--){
                temp_word[o] = character_grid[n][k];
                o++;
            }
            for(int n = 0; n < word_line_count; n++){
                if(current_hash_value == word_hash_list[n] && (strcmp(temp_word,word_list_array[n]) == 0)){
                    result_storer[n][0] = l, result_storer[n][1] = k, result_storer[n][2] = 4, result_storer[n][3] = 1;
                }
            }
        }
    }
}

void bottom_left_to_top_right(int D, int P, int h,int row,int word_length,int word_line_count,int result_storer[][4], char character_grid[][row],int word_hash_list[word_line_count],char word_list_array[][word_length + 1]){
    int coloumn = row, current_hash_value = 0, q = 0,r = 0, s = 0;
    char temp_word[word_length + 1];
    temp_word[word_length] = '\0';
    int o = (row - 1), p = (coloumn - word_length), k = 0, l = 0, tracker = (row - 1),temp_row_counter;
    while (p >= 0) {
        current_hash_value = 0;
        k = o, l = p;
        temp_row_counter = k;
            if (k == row - 1 && l <= coloumn - word_length) {
                while (l < p + word_length) {
                    current_hash_value = (D * current_hash_value + character_grid[k][l]) % P;
                    l++, k--;
                }
                q = word_length - 1, r = k + 1, s = l - 1;
                for(int t = word_length - 1; t >= 0; t--){
                    temp_word[q] = character_grid[r][s];
                    r++,s--,q--;
                }
                for(int n = 0; n < word_line_count; n++){
                    if(current_hash_value == word_hash_list[n] && (strcmp(temp_word,word_list_array[n]) == 0)){
                        result_storer[n][0] = l - 1, result_storer[n][1] = k + 1, result_storer[n][2] = 7, result_storer[n][3] = 1;
                    }
                }
                
                if (temp_row_counter > tracker && word_length != row) {
                  while(temp_row_counter > tracker){
                    current_hash_value = (D * (current_hash_value - character_grid[k + word_length][l - word_length] * h) + character_grid[k][l]) % P;
                    k--, l++,temp_row_counter--;
                    q = word_length - 1, r = k + 1, s = l - 1;
                    for(int t = word_length - 1; t >= 0; t--){
                        temp_word[q] = character_grid[r][s];
                        r++,s--,q--;
                    }
                    while (current_hash_value < 0) {
                        current_hash_value = P + current_hash_value;
                    }
                    for(int n = 0; n < word_line_count; n++){
                        if(current_hash_value == word_hash_list[n] && (strcmp(temp_word,word_list_array[n]) == 0)){
                            result_storer[n][0] = r - 1, result_storer[n][1] = s + 1, result_storer[n][2] = 7, result_storer[n][3] = 1;
                        }
                    }
                  }
                }
                
            }
        p--, tracker--;
    }
    /************************/
    o = row - 2, p = 0; tracker++;
    while (o >= tracker) {
      current_hash_value = 0;
        k = o, l = p;
        temp_row_counter = k;
            if ((l == 0 && k >= row - word_length) || o >= tracker) {
                while (l < p + word_length) {
                    current_hash_value = (D * current_hash_value + character_grid[k][l]) % P;
                    k--, l++;
                    q = word_length - 1, r = k + 1, s = l - 1;
                    
                }
                for(int t = word_length - 1; t >= 0; t--){
                    temp_word[q] = character_grid[r][s];
                    r++,s--,q--;
                }
                for(int n = 0; n < word_line_count; n++){
                    if(current_hash_value == word_hash_list[n] && (strcmp(temp_word,word_list_array[n]) == 0)){
                        result_storer[n][0] = r - 1, result_storer[n][1] = s + 1, result_storer[n][2] = 7, result_storer[n][3] = 1;
                    }
                }
                if( o > tracker && word_length != row){
                  while(temp_row_counter > tracker){
                current_hash_value = (D * (current_hash_value - character_grid[k + word_length][l - word_length] * h) + character_grid[k][l]) % P;
                k--, l++,temp_row_counter--;
                while (current_hash_value < 0) {
                    current_hash_value = P + current_hash_value;
                }
                q = word_length - 1, r = k + 1, s = l - 1;
                for(int t = word_length - 1; t >= 0; t--){
                    temp_word[q] = character_grid[r][s];
                    r++,s--,q--;
                }
                for(int n = 0; n < word_line_count; n++){
                        if(current_hash_value == word_hash_list[n] && (strcmp(temp_word,word_list_array[n]) == 0)){
                            result_storer[n][0] = r - 1, result_storer[n][1] = s + 1, result_storer[n][2] = 7, result_storer[n][3] = 1;
                        }
                    }
                  }
                }
            }
        o--;
    }
}

void top_right_backwards_to_bottom_left(int D, int P, int h,int row,int word_length,int word_line_count,int result_storer[][4], char character_grid[][row],int word_hash_list[word_line_count],char word_list_array[][word_length + 1]){
    int coloumn = row, current_hash_value = 0, q = 0,r = 0, s = 0, temp_row_counter = 0;
    char temp_word[word_length + 1];
    temp_word[word_length] = '\0';
    int o = (row - word_length), p = (coloumn - 1), k = 0, l = 0, tracker = (coloumn - 1);

    while (o >= 0) {
        current_hash_value = 0;
        k = o, l = p;
        temp_row_counter = l;
            if (k >= 0 && l == coloumn - 1 ) {
                while (k < o + word_length) {
                    current_hash_value = (D * current_hash_value + character_grid[k][l]) % P;
                    l--, k++;
                }
                q = word_length - 1, r = k - 1, s = l + 1;
                for(int t = word_length - 1; t >= 0; t--){
                    temp_word[q] = character_grid[r][s];
                    r--,s++,q--;
                }
                for(int n = 0; n < word_line_count; n++){
                        if(current_hash_value == word_hash_list[n] && (strcmp(temp_word,word_list_array[n]) == 0)){
                            result_storer[n][0] = r + 1, result_storer[n][1] = s - 1, result_storer[n][2] = 8, result_storer[n][3] = 1;
                        }
                }
                if (p > tracker && word_length != row) {
                  k--,l++;
                  while(temp_row_counter > tracker){
                    current_hash_value = (D * (current_hash_value - character_grid[k - word_length + 1][l + word_length - 1 ] * h) + character_grid[k + 1][l - 1]) % P;
                    k++, l--,temp_row_counter--;
                    q = word_length - 1, r = k , s = l ;
                    for(int t = word_length - 1; t >= 0; t--){
                        temp_word[q] = character_grid[r][s];
                        r--,s++,q--;
                    }
                    while (current_hash_value < 0) {
                      current_hash_value = P + current_hash_value;
                    }
                    for(int n = 0; n < word_line_count; n++){
                        if(current_hash_value == word_hash_list[n] && (strcmp(temp_word,word_list_array[n]) == 0)){
                            result_storer[n][0] = r + 1, result_storer[n][1] = s - 1, result_storer[n][2] = 8, result_storer[n][3] = 1;
                        }
                    }
                  }
                  
                }
                
            }
        o--, tracker--;
    }
    /************************/
    o = 0, p = coloumn - 2, tracker++;
    while (p >= tracker && word_length != row) {
      current_hash_value = 0;
        k = o, l = p;
        temp_row_counter = l;
            if ((k == 0 && l >= coloumn - word_length) || p >= tracker ) {
                while (k < o + word_length) {
                    current_hash_value = (D * current_hash_value + character_grid[k][l]) % P;
                    k++, l--;
                    q = word_length - 1, r = k - 1, s = l + 1;
                        for(int t = word_length - 1; t >= 0; t--){
                        temp_word[q] = character_grid[r][s];
                        r--,s++,q--;
                    }
                    for(int n = 0; n < word_line_count; n++){
                        if(current_hash_value == word_hash_list[n] && (strcmp(temp_word,word_list_array[n]) == 0)){
                            result_storer[n][0] = r + 1, result_storer[n][1] = s - 1, result_storer[n][2] = 8, result_storer[n][3] = 1;
                        }
                    }
                    while (current_hash_value < 0) {
                      current_hash_value = P + current_hash_value;
                    }
                }

                if(temp_row_counter > tracker && word_length != row){
                  k--,l++;
                  while(temp_row_counter > tracker){
                    current_hash_value = (D * (current_hash_value - character_grid[k - word_length + 1][l + word_length - 1 ] * h) + character_grid[k + 1][l - 1]) % P;
                    k++, l--,temp_row_counter--;

                    while (current_hash_value < 0) {
                      current_hash_value = P + current_hash_value;
                    }
                    q = word_length - 1, r = k , s = l ;
                    for(int t = word_length - 1; t >= 0; t--){
                        temp_word[q] = character_grid[r][s];
                        r--,s++,q--;
                    }
                    for(int n = 0; n < word_line_count; n++){
                        if(current_hash_value == word_hash_list[n] && (strcmp(temp_word,word_list_array[n]) == 0)){
                            result_storer[n][0] = r + 1, result_storer[n][1] = s - 1, result_storer[n][2] = 8, result_storer[n][3] = 1;
                        }
                    }
                  }
                }
            }
        p--;
    }
}

void bottom_right_backwards_to_top_left_diagonal(int D, int P, int h,int row,int word_length,int word_line_count,int result_storer[][4], char character_grid[][row],int word_hash_list[word_line_count],char word_list_array[][word_length + 1]){
    int coloumn = row, current_hash_value = 0, q = 0,r = 0, s = 0, temp_row_counter = 0;
    char temp_word[word_length + 1];
    temp_word[word_length] = '\0';
    int o = (row - 1), p = word_length - 1, k = 0, l = 0, tracker = (row - 1);

    while (p <= coloumn - 1) {
        current_hash_value = 0;
        k = o, l = p;
        temp_row_counter = k;
            if (k == row - 1 && l >= coloumn - word_length) {
                if(word_length == row)
                p = word_length - 1,l = word_length - 1;
                while (l > p - word_length) {
                    current_hash_value = (D * current_hash_value + character_grid[k][l]) % P;
                    l--, k--;
                }
                q = word_length - 1, r = k + 1, s = l + 1;
                for(int t = word_length - 1; t >= 0; t--){
                    temp_word[q] = character_grid[r][s];
                    r++,s++,q--;
                }
                for(int n = 0; n < word_line_count; n++){
                    if(current_hash_value == word_hash_list[n] && (strcmp(temp_word,word_list_array[n]) == 0)){
                        result_storer[n][0] = r - 1, result_storer[n][1] = s - 1, result_storer[n][2] = 6, result_storer[n][3] = 1;
                    }
                }

                if (temp_row_counter > tracker && word_length != row) {
                  k++,l++;
                  while(temp_row_counter > tracker){
                    current_hash_value = (D * (current_hash_value - character_grid[k + word_length - 1][l + word_length - 1] * h) + character_grid[k - 1][l - 1]) % P;
                    k--, l--,temp_row_counter--;
                    while (current_hash_value < 0){
                      current_hash_value = P + current_hash_value;
                    }
                    q = word_length - 1, r = k, s = l;
                    for(int t = word_length - 1; t >= 0; t--){
                        temp_word[q] = character_grid[r][s];
                        r++,s++,q--;
                    }
                    for(int n = 0; n < word_line_count; n++){
                        if(current_hash_value == word_hash_list[n] && (strcmp(temp_word,word_list_array[n]) == 0)){
                            result_storer[n][0] = r - 1, result_storer[n][1] = s - 1, result_storer[n][2] = 6, result_storer[n][3] = 1;
                        }
                    }
                  }
                }
                
            }
            while (current_hash_value < 0) {
                current_hash_value = P + current_hash_value;
            }
        if (word_length == row)
        break;
        p++, tracker--;
    }
    /************************/
    o = row - 2, p = coloumn - 1, tracker = word_length - 1;
    while (o >= tracker && word_length != row) {
      current_hash_value = 0;
        k = o, l = p;
        temp_row_counter = k;
            if ((l == coloumn - 1 && k >= row - word_length) || o >= tracker) {
                while (l > p - word_length){
                    current_hash_value = (D * current_hash_value + character_grid[k][l]) % P;
                    k--, l--;
                }
                q = word_length - 1, r = k + 1, s = l + 1;
                for(int t = word_length - 1; t >= 0; t--){
                    temp_word[q] = character_grid[r][s];
                    r++,s++,q--;
                }
                for(int n = 0; n < word_line_count; n++){
                        if(current_hash_value == word_hash_list[n] && (strcmp(temp_word,word_list_array[n]) == 0)){
                            result_storer[n][0] = r - 1, result_storer[n][1] = s - 1, result_storer[n][2] = 6, result_storer[n][3] = 1;
                        }
                    }
                if(temp_row_counter >= tracker + 1 && word_length != row){
                  k++,l++;
                  while(temp_row_counter > tracker){
                    current_hash_value = (D * (current_hash_value - character_grid[k + word_length - 1][l + word_length - 1] * h) + character_grid[k - 1][l - 1]) % P;
                    k--, l--,temp_row_counter--;
                    while (current_hash_value < 0) {
                                    current_hash_value = P + current_hash_value;
                                }
                    q = word_length - 1, r = k, s = l;
                    for(int t = word_length - 1; t >= 0; t--){
                        temp_word[q] = character_grid[r][s];
                        r++,s++,q--;
                    }
                    for(int n = 0; n < word_line_count; n++){
                        if(current_hash_value == word_hash_list[n] && (strcmp(temp_word,word_list_array[n]) == 0)){
                            result_storer[n][0] = r - 1, result_storer[n][1] = s - 1, result_storer[n][2] = 6, result_storer[n][3] = 1;
                        }
                    }
                  }
                }
            }
        o--;
    }
}

void top_left_to_bottom_right_diagonal(int D, int P, int h,int row,int word_length,int word_line_count,int result_storer[][4], char character_grid[][row],int word_hash_list[word_line_count],char word_list_array[][word_length + 1]){
    int coloumn = row, current_hash_value = 0, q = 0,r = 0, s = 0, temp_row_counter = 0, tracker = 0;
    char temp_word[word_length + 1];
    temp_word[word_length] = '\0';
    int o = (coloumn - word_length), p = 0, k = 0, l = 0;
    while (o >= 0) {
        current_hash_value = 0;
        k = o, l = p;
        temp_row_counter = l;
            if (k >= 0 && l == 0) {
                while (k < o + word_length) {
                    current_hash_value = (D * current_hash_value + character_grid[k][l]) % P;
                    l++, k++;
                }
                q = word_length - 1, r = k - 1, s = l - 1;
                for(int t = word_length - 1; t >= 0; t--){
                    temp_word[q] = character_grid[r][s];
                    r--,s--,q--;
                }
                for(int n = 0; n < word_line_count; n++){
                        if(current_hash_value == word_hash_list[n] && (strcmp(temp_word,word_list_array[n]) == 0)){
                            result_storer[n][0] = r + 1, result_storer[n][1] = s + 1, result_storer[n][2] = 5, result_storer[n][3] = 1;
                        }
                    } 
                if (temp_row_counter < tracker && word_length != row) {
                  k--,l--;
                  while(temp_row_counter < tracker){
                    current_hash_value = (D * (current_hash_value - character_grid[k - word_length + 1][l - word_length + 1 ] * h) + character_grid[k + 1][l + 1]) % P;
                    k++, l++,temp_row_counter++;
                    while (current_hash_value < 0) {
                      current_hash_value = P + current_hash_value;
                    }
                    q = word_length - 1, r = k, s = l;
                    for(int t = word_length - 1; t >= 0; t--){
                        temp_word[q] = character_grid[r][s];
                        r--,s--,q--;
                    }
                    for(int n = 0; n < word_line_count; n++){
                            if(current_hash_value == word_hash_list[n] && (strcmp(temp_word,word_list_array[n]) == 0)){
                                result_storer[n][0] = r + 1, result_storer[n][1] = s + 1, result_storer[n][2] = 5, result_storer[n][3] = 1;
                            }
                        }
                  }
                }
            }
        o--, tracker++;
    }
    /************************/
    o = 0, p = 1, tracker = row - word_length;
    while (p <= coloumn - word_length) {
      current_hash_value = 0;
        k = o, l = p;
        temp_row_counter = l;
            if (k == 0 && l <= coloumn - word_length) {
                while (k < o + word_length) {
                    current_hash_value = (D * current_hash_value + character_grid[k][l]) % P;
                    k++, l++;  
                }
                q = word_length - 1, r = k - 1, s = l - 1;
                for(int t = word_length - 1; t >= 0; t--){
                    temp_word[q] = character_grid[r][s];
                    r--,s--,q--;
                }
                for(int n = 0; n < word_line_count; n++){
                        if(current_hash_value == word_hash_list[n] && (strcmp(temp_word,word_list_array[n]) == 0)){
                            result_storer[n][0] = r + 1, result_storer[n][1] = s + 1, result_storer[n][2] = 5, result_storer[n][3] = 1;
                        }
                    }

                if(temp_row_counter < tracker){
                  k--,l--;
                  while(temp_row_counter < tracker){
                    current_hash_value = (D * (current_hash_value - character_grid[k - word_length + 1][l - word_length + 1 ] * h) + character_grid[k + 1][l + 1]) % P;
                    k++, l++,temp_row_counter++;
                    while (current_hash_value < 0) {
                      current_hash_value = P + current_hash_value;
                    }
                    
                    q = word_length - 1, r = k, s = l;
                    for(int t = word_length - 1; t >= 0; t--){
                        temp_word[q] = character_grid[r][s];
                        r--,s--,q--;
                    }
                    for(int n = 0; n < word_line_count; n++){
                        if(current_hash_value == word_hash_list[n] && (strcmp(temp_word,word_list_array[n]) == 0)){
                            result_storer[n][0] = r + 1, result_storer[n][1] = s + 1, result_storer[n][2] = 5, result_storer[n][3] = 1;
                        }
                    }
                  }
                }
            }
        p++;
    }
}
//dont forget to handle 2 x 2 and 1x1 cases
//compute each indiviaul has function then match
//for every word found remove it from the list
//saves 