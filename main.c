#include <stdio.h>
#include <stdlib.h>

typedef struct no_{
    int chave;
    struct no_ *esq, *dir;
} no;

no *criar_no (int valor){
    no *aux = (no*) malloc (sizeof(no));
    aux->dir=NULL;
    aux->esq=NULL;
    aux->chave = valor;
    return aux;
}


void inserir_filho (no *aux, double valor) {
    no *aux2;
    no *novo = criar_no (valor);

    int direcao;

    if (aux == NULL)
        aux = novo;

    while (aux != NULL){
        aux2 = aux;
        if (aux->esq != NULL){
            aux = aux->dir;
            direcao = 1;
        } else {
            aux = aux->esq;
            direcao = 0;
        }
    }
    if (direcao==1){
        aux2->dir = novo;
    } else {
        aux2->esq = novo;
    }
}

void imprimir_no (no *aux){
    if (aux != NULL)
        printf ("%d\n", aux->chave);
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

int busca (no *aux, int valor){

    if (aux == NULL) return 0;

    if (aux->chave == valor) return 1;

    return busca (aux->dir, valor);
    return busca (aux->esq, valor);
}

void imprimir_labelled (no *arv){

    printf ("[");
    if (arv != NULL){
        printf ("%d", arv->chave);
        imprimir_labelled (arv->esq);
        imprimir_labelled (arv->dir);
    }
    printf ("]");
}


void troca (no *remove, no *insere, no *ant){

    if (remove->dir != NULL){
        troca (remove->dir, insere, remove);
        return;
    }
    if (insere == ant){
        ant->esq = remove->esq;
    } else {
        ant->dir = remove->esq;
    }
    insere->chave = remove->chave;
    free (remove);
    remove = NULL;
}

void remove_val (no *raiz, no *rem, no *ant, int valor){
    no *prox;

    if(rem == NULL) return;

    if(rem->chave > valor){
        remove_val(raiz, rem->esq, rem, valor);
    } else {
        if(rem->chave < valor){
            remove_val(raiz, rem->dir, rem, valor);
        } else {

            if(rem->esq== NULL || rem->dir== NULL){

                if(rem->esq== NULL)
                    prox = rem->dir;
                else
                    prox = rem->esq;

                if(ant== NULL){
                    raiz = prox;
                } else {
                    if(rem == ant->esq)
                        ant->esq= prox;
                    else
                        ant->dir= prox;
                }

                free(rem);
                rem = NULL;
            } else {
                troca (rem->esq, rem, rem);
            }
        }
    }
}

void op_insere (no *arv){
    int i, n, valor;

    printf ("Digite o numero N de valores a serem inseridos: ");
    scanf ("%d", &n);

    printf ("\nDigite %d valores\n", n);

    for (i=0; i<n; i++){
        scanf ("%d", &valor);
        inserir_filho (arv, valor);
    }

    em_ordem (arv);
}

void op_remover (no *arv){
    int val;
    printf ("Valor a ser removido: ");
    scanf ("%d", &val);
    remove_val (arv, NULL, NULL, val);

}

void op_busca (no *arv){
    int val;
    printf ("Valor a ser buscado: ");
    scanf ("%d", &val);
    if (busca (arv, val))
        printf ("\nO valor esta inserido na arvore.\n");
    else
        printf ("\nO valor nao esta na arvore.\n");

}

void op_impressao (no *arv){
    int val;
    printf ("Digite 1 para impressao pre-ordem\nDigite 2 para impressao em-ordem\nDigite 3 para impressao pos-ordem\n");
    scanf ("%d", &val);

    switch (val){
    case 1: pre_ordem(arv);break;
    case 2: em_ordem(arv); break;
    case 3: pos_ordem(arv); break;
    }
}

int main(int argc, char *argv[]){
    int op, n, i, valor;

    printf ("Quantidade inicial de valores para colocar na arvore: ");
    scanf ("%d", &n);

    printf ("\nDigite %d valores\n", n);
    scanf ("%d", &valor);
    no *arv = criar_no (valor);

    for (i=1; i<n; i++){
        scanf ("%d", &valor);
        inserir_filho(arv, valor);
    }
    do {
        printf ("Digite 1 para inserir\n");
        printf ("Digite 2 para remover\n");
        printf ("Digite 3 para buscar\n");
        printf ("Digite 4 para imprimir\n");
        printf ("Digite 5 para imprimir labelled\n");

        scanf ("%d", &op);

        switch (op){
        case 1: op_insere (arv); break;
        case 2: op_remover (arv); break;
        case 3: op_busca (arv); break;
        case 4: op_impressao (arv); break;
        case 5: imprimir_labelled(arv); break;

        }

    } while (op != 0);

    return 0;
}

