#ifndef _H_ARVORES
#define _H_ARVORES

// Estrutura para o nó da árvore binária
typedef struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
} No;

// Funções para a árvore binária (não balanceada)
No* inserir_no_binaria(No* raiz, int valor);
No* remover_no_binaria(No* raiz, int valor);
void liberar_arvore_binaria(No* raiz);

// Estrutura para o nó da árvore AVL
typedef struct NoAVL {
    int valor;
    int altura;
    struct NoAVL* esquerda;
    struct NoAVL* direita;
} NoAVL;

// Funções para a árvore AVL (balanceada)
NoAVL* inserir_no_avl(NoAVL* raiz, int valor);
NoAVL* remover_no_avl(NoAVL* raiz, int valor);
int altura(NoAVL* no);
int fator_balanceamento(NoAVL* no);
NoAVL* rotacao_direita(NoAVL* y);
NoAVL* rotacao_esquerda(NoAVL* x);
NoAVL* balancear_avl(NoAVL* raiz);
void liberar_arvore_avl(NoAVL* raiz);

#endif // _H_ARVORES
