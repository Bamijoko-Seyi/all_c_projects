#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "bucketstack.h"

void initStack(int bucketSize, Stack **stack){
    (*stack) = malloc(sizeof(Stack));
    (*stack)->firstBucket = NULL;
    (*stack)->topElt = 0;
    (*stack)->bucketSize = bucketSize;
}

bool isEmpty (const Stack *stack){
    if(stack->firstBucket == NULL){
        return true;
    }
    return false;
}

void push (char* val, Stack *stack){
    if (stack->firstBucket == NULL) {
        stack->firstBucket = malloc(sizeof(struct NodeBucket));
        stack->firstBucket->next = NULL;
        stack->firstBucket->val = calloc(stack->bucketSize, sizeof(char *));
        stack->topElt = 0;
    }

    if(stack->topElt == stack->bucketSize){
        struct NodeBucket *new_bucket = malloc(sizeof(struct NodeBucket));
        new_bucket->val = malloc(stack->bucketSize * sizeof(char *));
        //new_bucket->size = 0;
        new_bucket->next = stack->firstBucket;
        stack->firstBucket = new_bucket;
        stack->topElt = 0;
    }
    stack->firstBucket->val[stack->topElt] = malloc(strlen(val) + 1);
    strcpy(stack->firstBucket->val[stack->topElt], val);
    stack->topElt++;
    //stack->firstBucket->size++;
}

void pop(Stack *stack){
    assert(isEmpty(stack) == false);
    if (stack->topElt == 1) {
        struct NodeBucket *current_bucket = stack->firstBucket;
        stack->firstBucket = stack->firstBucket->next;
        free(current_bucket->val[0]);
        free(current_bucket->val);
        free(current_bucket);
        if (stack->firstBucket == NULL) {
            stack->topElt = 0;
        } else {
            stack->topElt = stack->bucketSize;
        }
    } else {
        free(stack->firstBucket->val[stack->topElt - 1]);
        stack->firstBucket->val[stack->topElt - 1] = NULL;
        stack->topElt--;
    }
}

int size(const Stack *stack){
    int current_size;
    struct NodeBucket *current_bucket = stack->firstBucket;
    current_size = stack->topElt;
    if (stack == NULL) {
        return 0;
    }
    while(current_bucket != NULL && current_bucket->next != NULL){
        current_size = current_size + stack->bucketSize;
        current_bucket = current_bucket->next;
    }
    return current_size;
}

char* top(const Stack *stack){
    return stack->firstBucket->val[stack->topElt - 1];
}

void swap (Stack *stack){
    char *temp;
    if(stack->topElt == 1 && stack->firstBucket->next != NULL){
        temp = malloc(strlen(stack->firstBucket->val[stack->topElt - 1]) + 1);
        strcpy(temp, stack->firstBucket->val[stack->topElt - 1]);
    if (strlen(stack->firstBucket->next->val[stack->bucketSize - 1]) + 1 <= strlen(stack->firstBucket->val[stack->topElt - 1])) {
        strcpy(stack->firstBucket->val[stack->topElt - 1], stack->firstBucket->next->val[stack->bucketSize - 1]);
    } else {
        stack->firstBucket->val[stack->topElt - 1] = realloc(stack->firstBucket->val[stack->topElt - 1], strlen(stack->firstBucket->next->val[stack->bucketSize - 1]) + 1);
        strcpy(stack->firstBucket->val[stack->topElt - 1], stack->firstBucket->next->val[stack->bucketSize - 1]);
    }
    free(stack->firstBucket->next->val[stack->bucketSize - 1]);
    stack->firstBucket->next->val[stack->bucketSize - 1] = malloc(strlen(temp) + 1);
    strcpy(stack->firstBucket->next->val[stack->bucketSize - 1], temp);
    free(temp);
    }

    else{
    assert(stack->topElt >= 2);
    temp = malloc(strlen(stack->firstBucket->val[stack->topElt - 2]) + 1);
    strcpy(temp, stack->firstBucket->val[stack->topElt - 2]);
    if (strlen(stack->firstBucket->val[stack->topElt - 1]) + 1 <= strlen(stack->firstBucket->val[stack->topElt - 2])) {
        strcpy(stack->firstBucket->val[stack->topElt - 2], stack->firstBucket->val[stack->topElt - 1]);
    } else {
        stack->firstBucket->val[stack->topElt - 2] = realloc(stack->firstBucket->val[stack->topElt - 2], strlen(stack->firstBucket->val[stack->topElt - 1]) + 1);
        strcpy(stack->firstBucket->val[stack->topElt - 2], stack->firstBucket->val[stack->topElt - 1]);
    }
    free(stack->firstBucket->val[stack->topElt - 1]);
    stack->firstBucket->val[stack->topElt - 1] = malloc(strlen(temp) + 1);
    strcpy(stack->firstBucket->val[stack->topElt - 1], temp);
    free(temp);
    }
}

void print(const Stack *stack){
    printf("stack is:\n");
    if(stack->firstBucket == NULL){
        return;
    }
    struct NodeBucket *current_bucket = stack->firstBucket->next;
    for(int i = stack->topElt - 1; i >= 0; i--){
        fprintf(stdout,"\t%s\n", stack->firstBucket->val[i]); 
    }
    while(current_bucket != NULL){
        for(int i = stack->bucketSize - 1; i >= 0; i--){
            if(current_bucket->val[i] != NULL) {
                fprintf(stdout,"\t%s\n", current_bucket->val[i]);
            }
        }
        current_bucket = current_bucket->next;
    }
}

void clear(Stack *stack){
    struct NodeBucket *current_bucket = stack->firstBucket;
    while(current_bucket!=NULL){
        struct NodeBucket *temp = current_bucket->next;
        for(int i = 0; i< stack->bucketSize; i++){
            free(current_bucket->val[i]);
        }
        free(current_bucket->val);
        free(current_bucket);
        current_bucket = temp;
    }
    stack->firstBucket = NULL;
    stack->bucketSize = 0;
    stack->topElt = 0;
    //free(current_bucket);
}

void destroyStack(Stack **stack){
    struct NodeBucket *current_bucket = (*stack)->firstBucket;
    while(current_bucket!=NULL){
        struct NodeBucket *temp = current_bucket->next;
        for(int i = 0; i< (*stack)->bucketSize; i++){
            free(current_bucket->val[i]);
        }
        free(current_bucket->val);
        free(current_bucket);
        current_bucket = temp;
    }
    free((*stack));
    (*stack) = NULL;
}