#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arvores.h"


//
// Função que lê o arquivo de instância e aplica as operações
//
void processar_instancia(const char *nome_arquivo, No **raiz_binaria, NoAVL **raiz_avl)
{
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de instância.\n");
        exit(1);
    }

    char operacao;
    int valor;

    while (fscanf(arquivo, " %c %d", &operacao, &valor) != EOF)
    {
        if (operacao == 'I')
        {
            // Inserir nas árvores que não forem nulas
            if (raiz_binaria != NULL)
            {
                *raiz_binaria = inserir_no_binaria(*raiz_binaria, valor);
            }
            if (raiz_avl != NULL)
            {
                *raiz_avl = inserir_no_avl(*raiz_avl, valor);
            }
        }
        else if (operacao == 'R')
        {
            // Remover nas árvores que não forem nulas
            if (raiz_binaria != NULL)
            {
                *raiz_binaria = remover_no_binaria(*raiz_binaria, valor);
            }
            if (raiz_avl != NULL)
            {
                *raiz_avl = remover_no_avl(*raiz_avl, valor);
            }
        }
    }

    fclose(arquivo);
}

    //////////////////////////////////////////////////////////
    //////////////// Funções para árvore Binária /////////////
    //////////////////////////////////////////////////////////

//
// Função de inserção
//
No *inserir_no_binaria(No *raiz, int valor)
{
    if (raiz == NULL)
    {
        No *novo = (No *)malloc(sizeof(No));
        novo->valor = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }
    if (valor < raiz->valor)
    {
        raiz->esquerda = inserir_no_binaria(raiz->esquerda, valor);
    }
    else if (valor > raiz->valor)
    {
        raiz->direita = inserir_no_binaria(raiz->direita, valor);
    }
    return raiz;
}


//
// Função de remoção
//
No *remover_no_binaria(No *raiz, int valor)
{
    if (raiz == NULL)
        return NULL;

    if (valor < raiz->valor)
    {
        raiz->esquerda = remover_no_binaria(raiz->esquerda, valor);
    }
    else if (valor > raiz->valor)
    {
        raiz->direita = remover_no_binaria(raiz->direita, valor);
    }
    else
    {
        if (raiz->esquerda == NULL)
        {
            No *temp = raiz->direita;
            free(raiz);
            return temp;
        }
        else if (raiz->direita == NULL)
        {
            No *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        No *temp = raiz->direita;
        while (temp->esquerda != NULL)
            temp = temp->esquerda;
        raiz->valor = temp->valor;
        raiz->direita = remover_no_binaria(raiz->direita, temp->valor);
    }
    return raiz;
}

//
// Liberação de memória alocada para a árvore binária
//
void liberar_arvore_binaria(No *raiz)
{
    if (raiz != NULL)
    {
        liberar_arvore_binaria(raiz->esquerda);
        liberar_arvore_binaria(raiz->direita);
        free(raiz);
    }
}

    ///////////////////////////////////////////////////////////
    /////////////////// Funções para árvore AVL ///////////////
    ///////////////////////////////////////////////////////////

//
// Auxiliar de altura 
// 
int altura(NoAVL *no)
{
    if (no == NULL)
        return 0;
    return no->altura;
}

//
//Auxiliar de Balanceamento
//
int fator_balanceamento(NoAVL *no)
{
    if (no == NULL)
        return 0;
    return altura(no->esquerda) - altura(no->direita);
}


//
// Funções de rotação
//
NoAVL *rotacao_direita(NoAVL *y)
{
    NoAVL *x = y->esquerda;
    NoAVL *T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = 1 + (altura(y->esquerda) > altura(y->direita) ? altura(y->esquerda) : altura(y->direita));
    x->altura = 1 + (altura(x->esquerda) > altura(x->direita) ? altura(x->esquerda) : altura(x->direita));

    return x;
}

NoAVL *rotacao_esquerda(NoAVL *x)
{
    NoAVL *y = x->direita;
    NoAVL *T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = 1 + (altura(x->esquerda) > altura(x->direita) ? altura(x->esquerda) : altura(x->direita));
    y->altura = 1 + (altura(y->esquerda) > altura(y->direita) ? altura(y->esquerda) : altura(y->direita));

    return y;
}


//
//Função de balanceamento AVL
//
NoAVL *balancear_avl(NoAVL *raiz)
{
    int balanco = fator_balanceamento(raiz);

    if (balanco > 1 && fator_balanceamento(raiz->esquerda) >= 0)
        return rotacao_direita(raiz);

    if (balanco > 1 && fator_balanceamento(raiz->esquerda) < 0)
    {
        raiz->esquerda = rotacao_esquerda(raiz->esquerda);
        return rotacao_direita(raiz);
    }

    if (balanco < -1 && fator_balanceamento(raiz->direita) <= 0)
        return rotacao_esquerda(raiz);

    if (balanco < -1 && fator_balanceamento(raiz->direita) > 0)
    {
        raiz->direita = rotacao_direita(raiz->direita);
        return rotacao_esquerda(raiz);
    }

    return raiz;
}


//
//Função de inserção AVL
//
NoAVL *inserir_no_avl(NoAVL *raiz, int valor)
{
    if (raiz == NULL)
    {
        NoAVL *novo = (NoAVL *)malloc(sizeof(NoAVL));
        novo->valor = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        novo->altura = 1;
        return novo;
    }
    if (valor < raiz->valor)
    {
        raiz->esquerda = inserir_no_avl(raiz->esquerda, valor);
    }
    else if (valor > raiz->valor)
    {
        raiz->direita = inserir_no_avl(raiz->direita, valor);
    }

    raiz->altura = 1 + (altura(raiz->esquerda) > altura(raiz->direita) ? altura(raiz->esquerda) : altura(raiz->direita));

    return balancear_avl(raiz);
}


//
//Função de remoção AVL
//
NoAVL *remover_no_avl(NoAVL *raiz, int valor)
{
    if (raiz == NULL)
        return NULL;

    if (valor < raiz->valor)
    {
        raiz->esquerda = remover_no_avl(raiz->esquerda, valor);
    }
    else if (valor > raiz->valor)
    {
        raiz->direita = remover_no_avl(raiz->direita, valor);
    }
    else
    {
        if (raiz->esquerda == NULL || raiz->direita == NULL)
        {
            NoAVL *temp = raiz->esquerda ? raiz->esquerda : raiz->direita;
            if (temp == NULL)
            {
                temp = raiz;
                raiz = NULL;
            }
            else
            {
                *raiz = *temp;
            }
            free(temp);
        }
        else
        {
            NoAVL *temp = raiz->direita;
            while (temp->esquerda != NULL)
                temp = temp->esquerda;
            raiz->valor = temp->valor;
            raiz->direita = remover_no_avl(raiz->direita, temp->valor);
        }
    }

    if (raiz == NULL)
        return raiz;

    raiz->altura = 1 + (altura(raiz->esquerda) > altura(raiz->direita) ? altura(raiz->esquerda) : altura(raiz->direita));

    return balancear_avl(raiz);
}

//
// Função para liberar a memória da árvore AVL
//
void liberar_arvore_avl(NoAVL *raiz)
{
    if (raiz != NULL)
    {
        liberar_arvore_avl(raiz->esquerda);
        liberar_arvore_avl(raiz->direita);
        free(raiz);
    }
}

//
// Função que processa as operações para a árvore binária não balanceada
//
double arvore_binaria(int instancia_num)
{
    double tempo = 0;
    clock_t begin = clock();
    No *raiz = NULL;

    // Simulação de inserções e remoções (com base na instância)
    
    for (int i = 0; i < 1000; i++)
    {
        raiz = inserir_no_binaria(raiz, i);
    }
    for (int i = 500; i < 1000; i++)
    {
        raiz = remover_no_binaria(raiz, i);
    }

    liberar_arvore_binaria(raiz);

    clock_t end = clock();
    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    tempo += (double)(end - begin) / CLOCKS_PER_SEC;
    return (tempo);
}

//
// Função que processa as operações para a árvore balanceada (AVL)
//
double arvore_balanceada(int instancia_num)
{
    double tempo = 0;
    clock_t begin = clock();
    NoAVL *raiz = NULL;

    // Simulação de inserções e remoções (com base na instância)
    for (int i = 0; i < 1000; i++)
    {
        raiz = inserir_no_avl(raiz, i);
    }
    for (int i = 500; i < 1000; i++)
    {
        raiz = remover_no_avl(raiz, i);
    }

    liberar_arvore_avl(raiz);

    clock_t end = clock();
    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    tempo += (double)(end - begin) / CLOCKS_PER_SEC;
    return (tempo);
}

int main(int argc, char *argv[])
{
    ///////////////////////////////////////////////////////////
    /////////////////// Leitor de instâncias //////////////////
    ///////////////// Não deve ser modificado /////////////////
    ///////////////////////////////////////////////////////////
    int instancia_num = -1;
    instancia_num = atoi(argv[1]);
    if (instancia_num <= 0 || instancia_num > 10)
    {
        printf("Para executar o código, digite ./arvores x\nonde x é um número entre 1 e 10 que simboliza a instância utilizada\n");
        return 1;
    }

    No *raiz_binaria = NULL;
    NoAVL *raiz_avl = NULL;

    // Gerar o nome do arquivo de instância com base no número
    char arquivo_instancia[20];
    snprintf(arquivo_instancia, sizeof(arquivo_instancia), "instancia%d.txt", instancia_num);

    double tempo_n_balanceada = 0;
    double tempo_balanceada = 0;

    // Processar a instância para a árvore binária
    clock_t begin = clock();
    processar_instancia(arquivo_instancia, &raiz_binaria, NULL); // Processar apenas a árvore binária
    clock_t end = clock();
    tempo_n_balanceada = (double)(end - begin) / CLOCKS_PER_SEC;

    // Processar a instância para árvore AVL
    begin = clock();
    processar_instancia(arquivo_instancia, NULL, &raiz_avl); // Processar apenas a árvore AVL
    end = clock();
    tempo_balanceada = (double)(end - begin) / CLOCKS_PER_SEC;

    // Exibindo os tempos gastos:
    printf("Tempo Árvore Binária: %f milisegundos\n", tempo_n_balanceada);
    printf("Tempo Árvore AVL (Balanceada): %f milisegundos\n", tempo_balanceada);

    // Liberaração da memória alocada para as árvores
    liberar_arvore_binaria(raiz_binaria);
    liberar_arvore_avl(raiz_avl);

    return 0;
}
