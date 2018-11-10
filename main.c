#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define ERROR 1

struct node{                                            //Struct que representa cada nó da árvore
    char name[4];                                          //String na qual está presente a identificação da porta ou entrada
    struct node* left;                                     //Ponteiro que aponta para o filho da esquerda        
    struct node* right;                                    //Ponteiro que aponta para o filho da direita
};

typedef struct node NODE;                               //typedef para simplificar o tipo da struct

NODE* create_door(char entry[]){                        //Função que cria uma porta ou entrada e já insere sua identificação
    NODE* new;                                              //Ponteiro que receberá essa nova entrada
    
    new=(NODE*)calloc(1, sizeof(NODE));                     //Alocação da memória
    if(new==NULL){                                          //Verificação para ver se a memória foi alocada
        printf("Erro na alocacao, memoria insuficiente");
        return NULL;
    }
    new->left=NULL;                                     
    new->right=NULL;
    strcpy(new->name, entry);                               //Inserção da identificação na porta ou entrada nova

    return new;
}

void search(NODE** root, NODE** cursor, char entry[]){  //Função que localiza uma determinada porta ou entrada com base na sua identificação para o caso 3-a
    if((*cursor)!=NULL)                                     //Como funciona com recursão, esse comando serve para interromper e terminar a recursão caso a porta ou entrada já tenha sido encontrada
        return;

    if(strcmp(entry, (*root)->name)==0){                    //Compara a identificação que temos com a identificação do nó para ver se são as mesmas
        *cursor=*root;
        return;
    }

    if((*root)->name[0]=='E')                               //Caso o nó seja uma entrada, retorna pois a entrada não tem filhos
        return;
    
    if((*root)->left!=NULL)                                 //Se o filho da esquerda for diferente de nulo, chama a função para procurar nesse filho
        search(&(*root)->left, cursor, entry);
    
    if((*root)->name[0]!='N' && (*root)->right!=NULL)      //Se o nó não for um do tipo NOT e o filho da direita não for nulo, chama a função para procurar nesse filho
        search(&(*root)->right, cursor, entry);
}

int create_system_a(NODE** root){                      //Função que cria o sistema baseado no modo 3-a
    NODE* cursor = NULL;                                    //Ponteiro que receberá o nó em que serão inseridos as novas portas ou entradas
    char entry[3][4];                                       //Strings que receberão do buffer a identificação do pai e dos filhos

    scanf("%s", entry[0]);                                  //Identifica qual é o nó pai
    entry[0][3]='\0';
    getchar();

    if(*root==NULL){                                        //Caso a árvore não tenha nenhum nó, cria o novo nó sendo o nó pai identificado
        *root=create_door(entry[0]);
        cursor=*root;                                       //Determina o nó pai como o cursor
    }else{                                                  
        search(root, &cursor , entry[0]);                   //Caso a árvore já tenha sido criada, localiza o nó pai na árvore e o cursor recebe o seu endereço
        if(cursor==NULL){
            printf("Nó não encontrado");    
            return ERROR;
        }
    }
    
    scanf("%s", entry[1]);                                  //Identifica o nome do filho da esquerda
    entry[1][3]='\0';
    getchar();
    
    cursor->left=create_door(entry[1]);                     //Insere o filho da esquerda na árvore
    if(cursor->left==NULL)
        return ERROR;
    
    if(cursor->name[0]!='N'){                               //Caso o pai não seja do tipo NOT, o pai terá um filho da direita
        scanf("%s", entry[2]);                              //Identifica o filho da direita
        entry[2][3]='\0';
        getchar();
        
        cursor->right=create_door(entry[2]);                //Insere o filho da direita na árvore 
        if(cursor->right==NULL)
            return ERROR;
    }
    return OK;
}

int create_system_b(NODE** root){                      //Função que usa de recursão para criar a árvore baseada no modo 3-b
    char entry[4];                                          //String que receberá do buffer a identificação do nó
    
    scanf("%s", entry);                                     //Identifica o nó a ser criado
    entry[3]='\0';
    getchar();
    
    *root=create_door(entry);                               //Cria o nó na árvore
    if(*root==NULL)                                         //Caso a memória não tenha sido alocada, retorna ERROR
        return ERROR;

    if((*root)->name[0]=='E')                               //Caso o nó seja uma entrada, retorna OK pois ela não terá filho
        return OK;

    if(create_system_b(&(*root)->left)==ERROR)              //Chama a função para criar o nó do filho da esquerda
        return ERROR;

    if(&(*root)->left==NULL)                                //Caso a memória não tenha sido alocada, retorna ERROR
        return ERROR;

    if((*root)->name[0]!='N'){                              //Caso o nó não seja do tipo NOT, chama a função para criar o nó do filho da direita
        if(create_system_b(&(*root)->right)==ERROR)
            return ERROR;

        if(&(*root)->right==NULL)                           //Caso a memória não tenha sido alocada, retorna ERROR
            return ERROR;
    }
    return OK;
}

int operations(NODE* root){                             //Função que com base nas entradas, calcula a saída do sistema
    char type;                                              //Char auxiliar que recebe o primeiro digito da identificação do nó para sabermos qual operação fazer
    int left;                                               //Inteiro que receberá a saída do filho da esquerda
    int right;                                              //Inteiro que receberá a saída do filho da direita
    int result;                                             //Inteiro que receberá a saída final do nó

    if(root==NULL){
        printf("Não há nenhuma árvore alocada");
        return -1;
    }

    type=root->name[0];                                     //Auxiliar recebendo o tipo do nó
    
    if(root->left!=NULL)                                    //Caso o filho da esquerda seja diferente de nulo, chama a função para calcular sua saída
        left=operations(root->left);
    if(root->right!=NULL)                                   //Caso o filho da direita seja diferente de nulo, chama a função para calcular sua saída
        right=operations(root->right);
    
    if(type=='E'){                                          //Se o nó for uma entrada, a saída dele será o digito que estará no buffer
        scanf("%d", &result);
        getchar();
    }else if(type=='A'){                                    //Operação para o nó AND
        result = left & right;
    }else if(type=='O'){                                    //Operação para o nó OR
        result = left | right; 
    }else if(type=='D'){                                    //Operação para o nó NAND
        result = (~(left & right) & 1);
    }else if(type=='R'){                                    //Operação para o nó NOR
        result = (~(left | right) & 1);
    }else if(type=='X'){                                    //Operação para o nó XOR
        result = left ^ right;
    }else if(type=='N'){                                    //Operação para o nó NOT
        result = (~left & 1);                               
    }
    return result;
}

void free_all(NODE** root){                             //Função que liberá toda a memória alocada para a formação do sistema
    if(*root==NULL)                                         //Caso a árvore esteja vazia, retorna
        return;

    if((*root)->name[0]=='E'){                              //Caso o nó seja uma entrada, libera a memória do nó, torna o seu ponteiro nulo e retorna
        free(*root);
        *root=NULL;
        return;
    }

    free_all(&(*root)->left);                               //Chama a função para liberar a memória do filho da esquerda
    
    if((*root)->name[0]!='N')                               //Caso o nó seja diferente de um NOT, haverá um filho da direita, logo chama a função para liberar a memória dele
        free_all(&(*root)->right);

    if((*root)->left==NULL && (*root)->right==NULL){        //Após toda a memória dos filhos for liberada, liberá a memória do próprio nó
        free(*root);
        *root=NULL;
        return;
    }
}

int main (int argc, char* argv[]) {
    NODE* root = NULL;                                      //Ponteiro de uma variável node que servirá como uma raiz da árvore
    int mode;                                               //Inteiro que conterá o modo em que será introduzido o sistema
    int lines;                                              //Número de linhas para o caso 3-a
    int loops;                                              //Número de vezes em que serão inseridas entradas diferentes
    int final;                                              //Recebe a saída final dado um grupo de entradas                                      

    do{ scanf("%d", &mode);                                     //Identifica o modo em que será introduzido o sistema
        getchar();
        if(mode!=0 && mode!=1)
            printf("Não há essa opção");
    }while(mode!=0 && mode!=1);
    
    if(mode==0){                                            //Caso para o modo 3-a
        scanf("%d", &lines);                                //Identifica o número de linhas para a criação do sistema
        getchar();
        
        for( ; lines>0; lines--){                            //Cria o sistema com base no modo 3-a
            if(create_system_a(&root)==ERROR)
                return ERROR;
        }
    }else{                                      //Caso para o modo 3-b
        if(create_system_b(&root)==ERROR)                       //Cria o sistema com base no modo 3-b
            return ERROR;                          
    }

    scanf("%d", &loops);                                    //Identifica quantos grupos de entradas serão inseridos no sistema
    getchar();

    for( ; loops>0; loops--){
        final=operations(root);
        if(final!=-1){           
            printf("%d\n", final);                   //Faz a operação para cada grupo de entrada e já imprime o resultado final
        }else{
            break;
        }
    }
    free_all(&root);                                        //Libera toda a memória alocada para a formação do sistema
    return OK;
}