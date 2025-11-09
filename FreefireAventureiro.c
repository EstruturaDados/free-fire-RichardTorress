#include <stdio.h>    // Funções de entrada e saída (printf, scanf, fgets)
#include <stdlib.h>   // Funções de alocação de memória (malloc, free)
#include <string.h>   // Funções para manipular strings (strcmp, strcpy, strncpy)

// ======================
// DEFINIÇÕES GERAIS
// ======================
#define MAX_STR_LEN 50  // Tamanho máximo de cada string (nome/tipo)
#define TAM_MAX 10      // Capacidade máxima da mochila estática (10 itens)

// ======================
// ESTRUTURAS DE DADOS
// ======================

// Estrutura que representa um item da mochila
typedef struct {
    char nome[MAX_STR_LEN];
    char tipo[MAX_STR_LEN];
    int quantidade;
} Item;

// Estrutura da mochila estática (usando vetor fixo)
typedef struct {
    Item itens[TAM_MAX];  // Vetor de itens
    int qntd;             // Quantidade atual de itens na mochila
} Mochila;

// Nó da lista encadeada (mochila dinâmica)
typedef struct No {
    Item dados;         // Dados do item
    struct No* proximo; // Ponteiro para o próximo nó
} No;

// =============================
// FUNÇÕES DA LISTA ESTÁTICA (VETOR)
// =============================

// Inicializa a mochila zerando a quantidade de itens
void inicializarMochila(Mochila *mochila) {
    mochila->qntd = 0;
}

// Insere um item na mochila (vetor)
void inserirItemVetor(Mochila *mochila, const char* nome, const char* tipo, int quantidade) {
    // Verifica se a mochila está cheia
    if (mochila->qntd >= TAM_MAX) {
        printf("\nMochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    // Copia o nome e o tipo do item para a posição livre
    strncpy(mochila->itens[mochila->qntd].nome, nome, MAX_STR_LEN - 1);
    mochila->itens[mochila->qntd].nome[MAX_STR_LEN - 1] = '\0'; // Garante o fim da string

    strncpy(mochila->itens[mochila->qntd].tipo, tipo, MAX_STR_LEN - 1);
    mochila->itens[mochila->qntd].tipo[MAX_STR_LEN - 1] = '\0';

    // Atribui a quantidade
    mochila->itens[mochila->qntd].quantidade = quantidade;
    mochila->qntd++; // Incrementa o contador

    printf("\nItem '%s' adicionado com sucesso!\n", nome);
}

// Remove um item da mochila pelo nome
void removerItemVetor(Mochila *mochila, const char* nome) {
    int pos = -1;

    // Procura o item no vetor
    for (int i = 0; i < mochila->qntd; i++) {
        if (strcmp(mochila->itens[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }

    // Se não encontrar o item
    if (pos == -1) {
        printf("\nItem '%s' nao encontrado.\n", nome);
        return;
    }

    // Desloca os itens após o removido para a esquerda
    for (int i = pos; i < mochila->qntd - 1; i++) {
        mochila->itens[i] = mochila->itens[i + 1];
    }

    mochila->qntd--; // Diminui a quantidade total
    printf("\nItem '%s' removido com sucesso!\n", nome);
}

// Lista todos os itens do vetor
void listarItensVetor(const Mochila *mochila) {
    if (mochila->qntd == 0) {
        printf("\nA mochila esta vazia.\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", mochila->qntd, TAM_MAX);
    printf("%-15s | %-15s | %-10s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("---------------------------------------------\n");

    for (int i = 0; i < mochila->qntd; i++) {
        printf("%-15s | %-15s | %-10d\n",
               mochila->itens[i].nome,
               mochila->itens[i].tipo,
               mochila->itens[i].quantidade);
    }
}

// Ordena os itens da mochila em ordem alfabética (Bubble Sort)
void ordenarItens(Mochila *mochila) {
    Item temp;
    for (int i = 0; i < mochila->qntd - 1; i++) {
        for (int j = 0; j < mochila->qntd - i - 1; j++) {
            if (strcmp(mochila->itens[j].nome, mochila->itens[j + 1].nome) > 0) {
                temp = mochila->itens[j];
                mochila->itens[j] = mochila->itens[j + 1];
                mochila->itens[j + 1] = temp;
            }
        }
    }
    printf("\nItens ordenados com sucesso (Bubble Sort).\n");
}

// Busca um item usando pesquisa sequencial
void buscarItemSequencial(const Mochila *mochila, const char* nome) {
    int comparacoes = 0;

    for (int i = 0; i < mochila->qntd; i++) {
        comparacoes++;
        if (strcmp(mochila->itens[i].nome, nome) == 0) {
            printf("\nItem encontrado: %s (%s), Quantidade: %d\n",
                   mochila->itens[i].nome,
                   mochila->itens[i].tipo,
                   mochila->itens[i].quantidade);
            printf("Comparacoes realizadas: %d\n", comparacoes);
            return;
        }
    }

    printf("\nItem '%s' nao encontrado.\n", nome);
    printf("Comparacoes: %d\n", comparacoes);
}

// Busca binária (só funciona se o vetor estiver ordenado)
void buscarItemBinaria(const Mochila *mochila, const char* nome) {
    int inicio = 0;
    int fim = mochila->qntd - 1;
    int comparacoes = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;

        int cmp = strcmp(mochila->itens[meio].nome, nome);
        if (cmp == 0) {
            printf("\nItem encontrado: %s (%s), Quantidade: %d\n",
                   mochila->itens[meio].nome,
                   mochila->itens[meio].tipo,
                   mochila->itens[meio].quantidade);
            printf("Comparacoes realizadas: %d\n", comparacoes);
            return;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("\nItem '%s' nao encontrado.\n", nome);
    printf("Comparacoes: %d\n", comparacoes);
}

// ======================
// FUNÇÕES LISTA ENCADEADA (DINÂMICA)
// ======================

// Insere novo item no início da lista
void inserirNovoItem(No **cabeca, const char* nome, const char* tipo, int quantidade) {
    // Cria novo nó
    No *novoNo = (No*) malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return;
    }

    // Preenche os dados do item
    strcpy(novoNo->dados.nome, nome);
    strcpy(novoNo->dados.tipo, tipo);
    novoNo->dados.quantidade = quantidade;

    // Faz o novo nó apontar para o antigo primeiro
    novoNo->proximo = *cabeca;
    *cabeca = novoNo; // Atualiza a cabeça

    printf("\nItem '%s' inserido com sucesso!\n", nome);
}

// Remove item da lista encadeada
void removerItemLista(No** cabeca, const char* nome) {
    No* atual = *cabeca;
    No* anterior = NULL;

    // Percorre até encontrar o item
    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("\nItem '%s' nao encontrado!\n", nome);
        return;
    }

    // Caso o item esteja no início
    if (anterior == NULL) {
        *cabeca = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual); // Libera memória
    printf("\nItem '%s' removido com sucesso!\n", nome);
}

// Exibe os itens da lista encadeada
void listarItensLista(const No *cabeca) {
    if (cabeca == NULL) {
        printf("\nA mochila esta vazia.\n");
        return;
    }

    printf("\n--- ITENS NA MOCHILA (LISTA ENCADEADA) ---\n");
    printf("%-15s | %-15s | %-10s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("---------------------------------------------\n");

    while (cabeca != NULL) {
        printf("%-15s | %-15s | %-10d\n",
               cabeca->dados.nome,
               cabeca->dados.tipo,
               cabeca->dados.quantidade);
        cabeca = cabeca->proximo;
    }
}

// Busca item na lista encadeada
void buscarItemLista(const No *cabeca, const char* nome) {
    int comparacoes = 0;

    while (cabeca != NULL) {
        comparacoes++;
        if (strcmp(cabeca->dados.nome, nome) == 0) {
            printf("\nItem encontrado: %s (%s), Quantidade: %d\n",
                   cabeca->dados.nome,
                   cabeca->dados.tipo,
                   cabeca->dados.quantidade);
            printf("Comparacoes realizadas: %d\n", comparacoes);
            return;
        }
        cabeca = cabeca->proximo;
    }

    printf("\nItem '%s' nao encontrado.\n", nome);
    printf("Comparacoes: %d\n", comparacoes);
}

// ======================
// MENUS DE INTERAÇÃO
// ======================

// Menu para manipular a mochila estática
void menuListaEstatica() {
    Mochila mochila;
    inicializarMochila(&mochila);

    int opcao;
    char nome[30], tipo[20];
    int quantidade;

    do {
        printf("\n==== MOCHILA (VETOR ESTATICO) ====\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Ordenar (Bubble Sort)\n");
        printf("5. Buscar Sequencial\n");
        printf("6. Buscar Binaria\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // Limpa buffer

        switch (opcao) {
            case 1:
                printf("Nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;

                printf("Tipo: ");
                fgets(tipo, sizeof(tipo), stdin);
                tipo[strcspn(tipo, "\n")] = 0;

                printf("Quantidade: ");
                scanf("%d", &quantidade);
                getchar();

                inserirItemVetor(&mochila, nome, tipo, quantidade);
                break;

            case 2:
                printf("Nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;

                removerItemVetor(&mochila, nome);
                break;

            case 3:
                listarItensVetor(&mochila);
                break;

            case 4:
                ordenarItens(&mochila);
                break;

            case 5:
                printf("Nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;

                buscarItemSequencial(&mochila, nome);
                break;

            case 6:
                ordenarItens(&mochila); // Binária precisa estar ordenada
                printf("Nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;

                buscarItemBinaria(&mochila, nome);
                break;
        }
    } while (opcao != 0);
}

// Menu para a mochila dinâmica (lista encadeada)
void menuListaEncadeada() {
    No *mochila = NULL;
    int opcao;
    char nome[30], tipo[20];
    int quantidade;

    do {
        printf("\n==== MOCHILA (LISTA ENCADEADA) ====\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;

                printf("Tipo: ");
                fgets(tipo, sizeof(tipo), stdin);
                tipo[strcspn(tipo, "\n")] = 0;

                printf("Quantidade: ");
                scanf("%d", &quantidade);
                getchar();

                inserirNovoItem(&mochila, nome, tipo, quantidade);
                break;

            case 2:
                printf("Nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;

                removerItemLista(&mochila, nome);
                break;

            case 3:
                listarItensLista(mochila);
                break;

            case 4:
                printf("Nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;

                buscarItemLista(mochila, nome);
                break;
        }
    } while (opcao != 0);

    // Libera toda a memória antes de sair
    No *temp;
    while (mochila != NULL) {
        temp = mochila;
        mochila = mochila->proximo;
        free(temp);
    }
}

// ======================
// FUNÇÃO PRINCIPAL
// ======================
int main() {
    int opcao;

    do {
        printf("\n===== MOCHILA DE SOBREVIVENCIA =====\n");
        printf("1. Mochila (Vetor Estatico)\n");
        printf("2. Mochila (Lista Encadeada)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                menuListaEstatica();
                break;

            case 2:
                menuListaEncadeada();
                break;

            case 0:
                printf("Saindo do programa...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
