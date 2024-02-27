#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "squeue.h"

void initSqueue (Squeue ** squeue){
    (*squeue) = malloc(sizeof(Squeue));
    (*squeue)->first = NULL;
    (*squeue)->last = NULL;
}

bool isEmpty(const Squeue *squeue){
    if((squeue->first == NULL) && (squeue->last == NULL)){
        return true;
    }
    return false;
}

void addFront (Squeue *squeue, char* val){
    struct Node *new_node;
    new_node = malloc(sizeof(struct Node));
    new_node->val = malloc(strlen(val) + 1);
    strcpy(new_node->val, val);
    new_node->next = squeue->first;
    new_node->prev = NULL;
     
    if(isEmpty(squeue)){
        squeue->first = new_node;
        squeue->last = new_node;
    }
    else{
        squeue->first->prev = new_node;
        squeue->first = new_node;
    }
    
}

void addBack(Squeue *squeue, char *val){
    struct Node *new_node;
    new_node = malloc(sizeof(struct Node));
    new_node->val = malloc(strlen(val) + 1);
    strcpy(new_node->val, val);
    new_node->prev = squeue->last;
    new_node->next = NULL;
     
    if(isEmpty(squeue)){
        squeue->first = new_node;
        squeue->last = new_node;
    }
    else{
        squeue->last->next = new_node;
        squeue->last = new_node;
    }
}

void leaveFront(Squeue *squeue){
    assert(!isEmpty(squeue));
    struct Node *current_node;
    current_node = squeue->first;
    squeue->first = current_node->next;
    if(squeue->first != NULL){
        squeue->first->prev = NULL;
    }
    else{
        squeue->last = NULL;
    }
    free(current_node->val);
    //free(current_node->prev);
    free(current_node);
}

void leaveBack (Squeue *squeue){
    assert(!isEmpty(squeue));
    struct Node *current_node;
    current_node = squeue->last;
    squeue->last = current_node->prev;
    if(squeue->last == NULL && squeue->first->next == NULL){
        free(squeue->first->val);
        free(squeue->first);
        squeue->first = NULL;
        return;
    }
    if(squeue->last != NULL){
        free(squeue->last->next);
        squeue->last->next = NULL;
    }
    else{
        free(squeue->first);
        squeue->first = NULL;
    }
    free(current_node->val);
    free(current_node->prev);
    free(current_node);
}

char* peekFront (const Squeue *squeue){
    return squeue->first->val;
}

char* peekBack (const Squeue *squeue){
    return squeue->last->val;
}

void print (const Squeue *squeue, char direction){
    if(direction != 'f' && direction != 'r'){
        fprintf(stderr,"Error, illegal direction %c.\n",direction);
        return;
    }
    if(direction == 'f'){
        struct Node *current_node = squeue->first;
        fprintf(stdout,"squeue is:\n");
        while(current_node != NULL){
            fprintf(stdout,"\t%s\n",current_node->val);
            current_node = current_node->next;
        }
    }
    else if(direction == 'r'){
        struct Node *current_node = squeue->last;
        fprintf(stdout,"squeue is:\n");
        while(current_node != NULL){
            fprintf(stdout,"\t%s\n",current_node->val);
            current_node = current_node->prev;
        }
    }
}

void nuke(Squeue *squeue){
    struct Node *current_node, *next_node;
    current_node = squeue->first;
    while(current_node != NULL){
        next_node = current_node->next;
        free(current_node->val);
        free(current_node);
        current_node = next_node;
    }
    squeue->first = NULL;
    squeue->last = NULL;
}

void mergeFront(Squeue* squeue, char direction){
    int Number_of_nodes = 0;
    struct Node *current_node;
    if(direction != 'f' && direction != 'r'){
        fprintf(stderr,"Error, illegal direction %c.\n",direction);
        return;
    }
    current_node = squeue->first;
    while(current_node != NULL){
        current_node = current_node->next;
        Number_of_nodes++;
    }
    assert(Number_of_nodes >= 2);

    current_node = squeue->first->next;
    if(direction == 'f'){
        squeue->first->val = realloc(squeue->first->val,strlen(squeue->first->val) + strlen(current_node->val) + 1);
        strcat(squeue->first->val,current_node->val);
    }
    else if(direction == 'r'){
        char *temp;
        current_node->val = realloc(current_node->val,strlen(squeue->first->val) + strlen(current_node->val) + 1);
        strcat(current_node->val,squeue->first->val);
        temp = malloc(strlen(current_node->val)+1);
        strcpy(temp,current_node->val);
        free(squeue->first->val);
        squeue->first->val = malloc(strlen(temp) + 1);
        strcpy(squeue->first->val,temp);
        free(temp);
    }
    squeue->first->next  = current_node->next;
    if(Number_of_nodes == 2){
       squeue->last = squeue->first; 
       squeue->last->next = NULL;
    }
    free(current_node->val);
    free(current_node);

}

void mergeBack(Squeue* squeue, char direction){
    int Number_of_nodes = 0;
    struct Node *current_node;
    if(direction != 'f' && direction != 'r'){
        fprintf(stderr,"Error, illegal direction %c.\n",direction);
        return;
    }
    current_node = squeue->first;
    while(current_node != NULL){
        current_node = current_node->next;
        Number_of_nodes++;
    }
    assert(Number_of_nodes >= 2);

    current_node = squeue->last->prev;
    if(direction == 'f'){
        squeue->last->val = realloc(squeue->last->val,strlen(squeue->last->val) + strlen(current_node->val) + 1);
        strcat(squeue->last->val,current_node->val);
        //free(current_node->val);
        //free(current_node);
    }
    else if(direction == 'r'){
        char *temp;
        current_node->val = realloc(current_node->val,strlen(squeue->last->val) + strlen(current_node->val) + 1);
        strcat(current_node->val,squeue->last->val);
        temp = malloc(strlen(current_node->val)+1);
        strcpy(temp,current_node->val);
        free(squeue->last->val);
        squeue->last->val = malloc(strlen(temp) + 1);
        strcpy(squeue->last->val,temp);
        free(temp);
    }
    squeue->last->next  = NULL;
    squeue->last->prev = current_node->prev;
    if(Number_of_nodes == 2){
       squeue->last = squeue->first; 
       squeue->last->next = NULL;
    }
} 

void reverse(Squeue* squeue){
    struct Node *temp = NULL;
    struct Node *current_node = squeue->first;

    while (current_node != NULL) {
        temp = current_node->prev;
        current_node->prev = current_node->next;
        current_node->next = temp;
        current_node = current_node->prev;
    }

    temp = squeue->first;
    squeue->first = squeue->last;
    squeue->last = temp;
}

void destroySqueue(Squeue **squeue){
    struct Node *temp = NULL;
    struct Node *current_node = (*squeue)->first;
    while(current_node != NULL){
        temp = current_node->next;
        free(current_node->val);
        free(current_node);
        current_node = temp;
    }
    free(*squeue);
    *squeue = NULL;
}