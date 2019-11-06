#include<stdio.h>
#include<stdlib.h>
#include "lista.h"

 
struct t_nodo {
    int elemento;
    struct t_nodo *prox;
};
typedef struct t_nodo t_nodo;

struct t_lista {
    t_nodo *ini;
    int tamanho;
};
typedef struct t_lista t_lista;






int cria_lista(t_lista *l){
	l = (t_lista *) malloc(sizeof(t_lista));
	l->ini = NULL;
	l->tamanho=0;
	return(1);
}

int lista_vazia(t_lista *l){
	if (l->ini == NULL) 
		return(1);
	else 
		return(0);
}

void destroi_lista(t_lista *l){
	t_nodo *p;

	if(lista_vazia(l)){
		printf("lista nao destruida: lista vazia\n");
		return;
	}
	while(l->ini->prox != NULL){
		p=l->ini;
		l->ini = l->ini->prox;
		l->tamanho--;
		free(p);
	}
	free (l->ini);
	l->tamanho--;
	l->ini = NULL;
}

int insere_inicio_lista(int x, t_lista *l){
	t_nodo *novo;
	novo = (t_nodo *) malloc(sizeof(t_nodo));
	/*cria novo nodo */
	if(novo == NULL)
		return 0;
	novo->elemento = x;
	l->tamanho++;

	if (lista_vazia(l))
		novo->prox = NULL;
	else 
		novo->prox = l->ini;
	return 1;
}

int insere_fim_lista(int x, t_lista *l){
	t_nodo *novo, *p;
	if (lista_vazia(l)){
		insere_inicio_lista(x,l);
		return 1;
	}
	novo = (t_nodo *) malloc(sizeof(t_nodo));
	if (novo == NULL)
		return 0;

	novo->elemento = x;
	novo->prox = NULL;
	l->tamanho++;

	p = l->ini;
	while (p->prox != NULL)
		p = p->prox;
	p->prox = novo;
	return 1; 
}
int insere_ordenado_lista(int x, t_lista *l){
	t_nodo *novo, *p;
	if (lista_vazia(l) || x < l->ini->elemento){
		if (! insere_inicio_lista(x,l))
			return 0;
		return 1;
	}

	novo = (t_nodo *) malloc(sizeof(t_nodo));
	if(novo == NULL)
		return 0;

	if(l->ini->prox == NULL){
		if(! insere_fim_lista (x,l))
			return 0;
		return 1;
	}

	p = l->ini;
	while (p->prox->prox != NULL && p->prox->elemento < x)
		p = p->prox;

	novo->elemento = x; 

	if (p->prox->prox ==NULL && x > p->prox->elemento){
		novo->prox =NULL;
		p->prox->prox = novo;
	}
	else{
		novo->prox =p->prox;
		p->prox =novo; 
	}
	l->tamanho++;
	return 1;
}

void imprime_lista(t_lista *l){
	t_nodo *novo;
   for (novo = l->ini; novo != NULL; novo = novo->prox)
      printf ("%d\n", novo->elemento);
}

int pertence_lista(int chave, t_lista *l){
	t_nodo *p;
	p = (t_nodo *) malloc(sizeof(t_nodo));
    p = l->ini;
    while (p != NULL && p->elemento != chave)
    	p = p->prox; 
    if (p == NULL)
    	return (0);
    else 
    	return(1);
}


int concatena_listas(t_lista *l, t_lista *m){
	t_nodo *p;
    p = l->ini;
    while (p->prox != NULL)
    	p = p->prox; 
    p->prox = m->ini; 
    m->ini = NULL;
    return 1;
}
int copia_lista(t_lista *l, t_lista *m){
	return 1; 
}

int remove_primeiro_lista(int *item, t_lista *l){
	int elemento;
	t_nodo *p;
	p = l->ini;
	elemento = p->elemento; 
	l->ini = p->prox;
	p->prox = NULL; 
	free(p);
	*item = elemento;
	l->tamanho--;
	return 1;

}

int remove_ultimo_lista(int *item, t_lista *l){ 
	t_nodo *p;
	t_nodo *t;
	p = l->ini;
	while (p->prox->prox != NULL){
		p = p->prox; 
	}
	t = p->prox;
	*item = t->elemento;
	p->prox = NULL; 
	l->tamanho--;
	free(t);
	return 1;
}

int remove_item_lista(int chave, int *item, t_lista *l){
	item = NULL;
	t_nodo *p;
	t_nodo *t;
	p = l->ini;
	while (p->elemento != chave || p->prox != NULL){
		p = p->prox;
	}
	item = p->elemento; 
	if (item != NULL){
		t = p;
		l->tamanho--;
		return 0;
	}	
	else 
		return 1;
}