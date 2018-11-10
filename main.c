#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define OK 0
#define ERROR 1

struct node{
    char name[4];
    int bit;
    struct node* left;
    struct node* right; 
};

typedef struct node NODE;

NODE* create_door(char entry[]){
    NODE* new;
    
    new=(NODE*)calloc(1, sizeof(NODE));
    new->bit=-1;
    new->left=NULL;
    new->right=NULL;
    strcpy(new->name, entry);

    return new;
}

void create_system(NODE** root){
    char entry[4];  //String que receberá do buffer se o nó é uma porta ou uma entrada e seu índice
    
    scanf("%s", entry);
    entry[3]='\0';
    getchar();
    
    *root=create_door(entry);

    if((*root)->name[0]=='E')   
        return;

    create_system(&(*root)->left);
    if((*root)->name[0]=='N'){
        return;
    }
    create_system(&(*root)->right);
}

void insert_bites(NODE** root){
    if((*root)->name[0]=='E'){
        (*root)->bit=getchar();
        getchar();
        return;
    }

    insert_bites(&(*root)->left);
    if((*root)->name[0]=='N'){
        return;
    }
    insert_bites(&(*root)->right);
}

int operations(NODE* root){
    char type;
    int left;
    int right;

    type=root->name[0];
    
    if(root->left!=NULL){
        left=operations(root->left);
    }
    if(root->right!=NULL){
        right=operations(root->right);
    }

    if(type=='E'){
        return root->bit;
    }else if(type=='A'){
        return left & right;
    }else if(type=='O'){
        return left | right;
    }else if(type=='D'){
        return ~(left & right);
    }else if(type=='R'){
        return ~(left | right);
    }else if(type=='X'){
        return left ^ right;
    }else if(type=='N'){
        return ~left;
    }
}

int main (int argc, char* argv[]) {
    NODE* root;     //Ponteiro de uma variável node que servirá como uma raiz da árvore
    int mode;       //Inteiro que conterá o modo em que será introduzido o sistema
    int lines;      //Número de linhas para o caso 3-a
    int loops;      //Número de vezes em que serão inseridas entradas diferentes

    root=(NODE*)calloc(1, sizeof(NODE));
    root->left=NULL;
    root->right=NULL;
    
    if(root==NULL){
        printf("Erro na alocação");
        return ERROR;
    }

    scanf("%d", &mode);
    getchar();
    
    if(mode==0){

    }else if(mode==1){
        create_system(&root);
    }

    scanf("%d", &loops);
    getchar();

    for(; loops>0; loops--){
        insert_bites(&root);
        printf("%d\n", operations(root));
    }

    free(root);
    return 0;
}