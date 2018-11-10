#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR 1

struct node{
    char name[4];
    struct node* left;
    struct node* right; 
};

typedef struct node NODE;

NODE* create_door(char entry[]){
    NODE* new;
    
    new=(NODE*)calloc(1, sizeof(NODE));
    new->left=NULL;
    new->right=NULL;
    strcpy(new->name, entry);

    return new;
}

void search(NODE** root, NODE** cursor, char entry[]){
    if((*cursor)!=NULL)
        return;

    if(strcmp(entry, (*root)->name)==0){
        *cursor=*root;
        return;
    }
    
    if((*root)->name[0]=='E')
        return;
    
    if((*root)->left!=NULL){
        search(&(*root)->left, cursor, entry);
    }

    if((*root)->name[0]=='N')
        return;
    
    if((*root)->right!=NULL){
        search(&(*root)->right, cursor, entry);
    }
}

void create_system_a(NODE** root){
    NODE* cursor = NULL;
    char entry[4];  //String que receberá do buffer se o nó é uma porta ou uma entrada e seu índice
    char entry_l[4];
    char entry_r[4];

    scanf("%s", entry);
    entry[3]='\0';
    getchar();

    if(*root==NULL){
        *root=create_door(entry);
        cursor=*root;
    }else{
        search(root, &cursor , entry);
        if(cursor==NULL)    
            return;
    }
    scanf("%s", entry_l);
    entry_l[3]='\0';
    getchar();
    cursor->left=create_door(entry_l);

    if(cursor->name[0]!='N'){
        scanf("%s", entry_r);
        entry_r[3]='\0';
        getchar();
        cursor->right=create_door(entry_r);
    }
}

void create_system_b(NODE** root){
    char entry[4];  //String que receberá do buffer se o nó é uma porta ou uma entrada e seu índice
    
    scanf("%s", entry);
    entry[3]='\0';
    getchar();
    
    *root=create_door(entry);

    if((*root)->name[0]=='E')   
        return;

    create_system_b(&(*root)->left);
    if((*root)->name[0]=='N'){
        return;
    }
    create_system_b(&(*root)->right);
}

int operations(NODE* root){
    char type;
    int left;
    int right;
    int result;

    type=root->name[0];
    
    if(root->left!=NULL)
        left=operations(root->left);
    if(root->right!=NULL)
        right=operations(root->right);
    
    if(type=='E'){
        scanf("%d", &result);
        getchar();
    }else if(type=='A'){
        result = left & right;
    }else if(type=='O'){
        result = left | right;
    }else if(type=='D'){
        result = (~(left & right) & 1);
    }else if(type=='R'){
        result = (~(left | right) & 1);
    }else if(type=='X'){
        result = left ^ right;
    }else if(type=='N'){
        result = (~left & 1);
    }
    return result;
}

void free_all(NODE** root){
    if((*root)->name[0]=='E'){
        free(*root);
        *root=NULL;
        return;
    }

    free_all(&(*root)->left);
    if((*root)->name[0]=='N'){
        free(*root);
        *root=NULL;
        return;
    }
    free_all(&(*root)->right);
    
    if((*root)->left==NULL && (*root)->right==NULL){
        free(*root);
        *root=NULL;
        return;
    }
}

int main (int argc, char* argv[]) {
    NODE* root = NULL;     //Ponteiro de uma variável node que servirá como uma raiz da árvore
    int mode;       //Inteiro que conterá o modo em que será introduzido o sistema
    int lines;      //Número de linhas para o caso 3-a
    int loops;      //Número de vezes em que serão inseridas entradas diferentes

    scanf("%d", &mode);
    getchar();
    
    if(mode==0){
        scanf("%d", &lines);
        getchar();
        
        for( ; lines>0; lines--){
            create_system_a(&root);
        }
    }else if(mode==1){
        create_system_b(&root);
    }

    scanf("%d", &loops);
    getchar();

    for( ; loops>0; loops--){
        printf("%d\n", operations(root));
    }

    free_all(&root);
    return 0;
}