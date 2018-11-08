#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define ERROR 1

struct node{
    char name[4];
    struct node* left;
    struct node* right; 
};

typedef struct node NODE;

NODE* create_door(char entry[]){
    NODE* new;
    
    new=(NODE*)malloc(sizeof(NODE));
    new->left=NULL;
    new->right=NULL;
    strcpy(new->name, entry);

    return new;
}

void create_system(NODE** root){
    NODE* cursor;
    char entry[4];
    
    scanf("%s", entry);
    getchar();
    

}

int main (int argc, char* argv[]) {
    NODE* root;     //Ponteiro de uma variável node que servirá como uma raiz da árvore
    char entry[4];  //String que receberá do buffer se o nó é uma porta ou uma entrada e seu índice
    int mode;       //Inteiro que conterá o modo em que será introduzido o sistema
    int lines;      //Número de linhas para o caso 3-a

    root=(NODE*)malloc(sizeof(NODE));
    root->left=NULL;
    root->right=NULL;
    
    if(root==NULL){
        printf("Erro na alocação");
        return ERROR;
    }

    scanf("%d", &mode);
    
    if(mode==0){

    }else{
        create_system(&root);
    }


    free(root);

    return 0;
}