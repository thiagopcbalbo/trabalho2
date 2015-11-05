#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct no_{
    char *chave;
    struct no_ *esq, *dir;
} no;

no *criar_no (char *valor){
    no *aux = (no*) malloc (sizeof(no));
    aux->dir=NULL;
    aux->esq=NULL;
    aux->chave = valor;
    return aux;
}

void imprimir_no (no *aux){
    if (aux != NULL)
        printf ("%s\n", aux->chave);
}

void imprimir_arvore (no *arv){

    if (arv == NULL) return;
    imprimir_no (arv);
    imprimir_arvore (arv->esq);
    imprimir_arvore (arv->dir);

}

void pre_ordem (no *aux){
    if (aux != NULL){
        imprimir_no (aux);
        pre_ordem(aux->esq);
        pre_ordem(aux->dir);
    }
}
void em_ordem (no *aux){
    if (aux != NULL){
        em_ordem(aux->esq);
        imprimir_no (aux);
        em_ordem(aux->dir);
    }
}
void pos_ordem (no *aux){
    if (aux != NULL){
        pos_ordem(aux->esq);
        pos_ordem(aux->dir);
        imprimir_no (aux);
    }
}
no *busca (no *arv, char *val){

    if (arv != NULL){
        if (!strcmp (val, arv->chave)){
            return arv;
        }

        no *aux = busca (arv->esq, val);

        if (aux == NULL)
            return busca (arv->dir, val);
        else
            return aux;
    }

    return NULL;

}

void inserir_tupla (no **arv, char *filho, char *pai, char *mae) {

    no *no_pai = criar_no (pai);
    no *no_mae = criar_no (mae);
    no *no_filho = busca(*arv, filho);

    if (no_filho == NULL){
        no_filho = criar_no (filho);
        *arv = no_filho;
    }

    no_filho->esq = no_pai;
    no_filho->dir = no_mae;

}


void entrar_tuplas (no **arv){

    char *filho = (char*) malloc (30);
    char *pai = (char*) malloc (30);
    char *mae = (char*) malloc (30);

    scanf ("%s %s %s", filho, pai, mae);
    inserir_tupla (arv, filho, pai, mae);
}

void imprimir_geracao (no *arv, int ger, int aux){
    if (arv == NULL) return;

    if (aux != ger){
        imprimir_geracao (arv->esq, ger, aux+1);
        imprimir_geracao (arv->dir, ger, aux+1);
        return;
    }

    printf ("%s ", arv->chave);
}

void op_imprimir_geracao (no *arv){
    int num;
    printf ("Digite a geracao desejada: ");
    scanf ("%d", &num);

    imprimir_geracao (arv, num, 1);
}

void op_imprimir_antepassados (no *arv){
    char *nome = (char*) malloc (30);
    printf ("Deseja imprimir os antepassados de qual nó? ");
    scanf ("%s", nome);

    //Para imprimir antepassados de um membro, basta imprimir as subarvores direita e esquerda de um dado no
    pre_ordem (busca (arv, nome)->esq);
    pre_ordem (busca (arv, nome)->dir);
}

void imprimir_labelled (no *arv){
    if (arv != NULL){
        printf ("[");
            printf ("%s", arv->chave);
            imprimir_labelled (arv->esq);
            imprimir_labelled (arv->dir);

        printf ("]");
    }
}


int altura_no(no *arv) {

    if (arv == NULL) return -1;
    int fe = altura_no (arv->esq);
    int fd = altura_no (arv->dir);
    if (fe > fd) return fe+1;
    else return fd+1;
}

void op_parentesco (no *arv){
    char *s1 = (char*)malloc(30);
    char *s2 = (char*) malloc (30);
    printf ("Digite os dois membros que deseja ver o parentesco: ");
    scanf ("%s %s", s1, s2);

    int alt1 = altura_no (busca (arv, s1));
    int alt2 = altura_no (busca (arv, s2));

    printf ("Grau de parentesco: %d\n", abs (alt1-alt2) );
}

int main (){
    no *arvore = NULL;
    int op, num, i;

    printf ("Digite o numero de N tuplas: ");
    scanf ("%d", &num);

    printf ("\nDigite %d tuplas:\n", num);
    for (i=0; i<num; i++){
        entrar_tuplas (&arvore);
    }

    do {
        printf ("Digite 1 para imprimir por geracao\n");
        printf ("Digite 2 para imprimir antepassados\n");
        printf ("Digite 3 para imprimir labelled\n");
        printf ("Digite 4 para ver parentesco entre dois membros\n");
        printf ("Digite 0 para sair\n");
        scanf ("%d", &op);

        switch (op){
        case 1: op_imprimir_geracao (arvore); break;
        case 2: op_imprimir_antepassados (arvore); break;
        case 3: imprimir_labelled (arvore); break;
        case 4: op_parentesco (arvore); break;
        }
    } while (op != 0);
    printf ("\n");

}
