#include <stdio.h>     // Entrada e saída padrão
#include <string.h>    // Manipulação de strings (strcmp, strcpy, etc.)
#include <stdbool.h>   // Tipo bool (true/false)
#include <time.h>      // Medição de tempo

// ============================================
// CÓDIGO DA ILHA — Edição Free Fire 🏝️
// Nível: Mestre 🔥
// ============================================
// Gerencia uma mochila de componentes com:
// - Inserção e remoção de itens
// - Ordenações (Nome, Tipo, Prioridade)
// - Busca binária otimizada
// ============================================

#define MAX_STR_LEN 50  // Tamanho máximo de cada string (nome/tipo)
#define TAM_MAX 10      // Capacidade máxima da mochila

// Estrutura de um item individual
typedef struct {
    char nome[MAX_STR_LEN];
    char tipo[MAX_STR_LEN];
    int quantidade;
    int prioridade;
} Item;

// Estrutura da mochila
typedef struct {
    Item itens[TAM_MAX];
    int qntd;
    bool ordenadoNome;  // flag que indica se está ordenada por nome
} Mochila;

// -----------------------------------------------------------------------------
// Inicializa a mochila
// -----------------------------------------------------------------------------
void inicializarMochila(Mochila *mochila) {
    mochila->qntd = 0;
    mochila->ordenadoNome = false;
}

// -----------------------------------------------------------------------------
// Insere item na mochila
// -----------------------------------------------------------------------------
void inserirItemVetor(Mochila *mochila, const char* nome, const char* tipo, int quantidade, int prioridade) {

    if (mochila->qntd >= TAM_MAX) {
        printf("\nMochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    // Copia com segurança as strings
    strncpy(mochila->itens[mochila->qntd].nome, nome, MAX_STR_LEN - 1);
    mochila->itens[mochila->qntd].nome[MAX_STR_LEN - 1] = '\0';

    strncpy(mochila->itens[mochila->qntd].tipo, tipo, MAX_STR_LEN - 1);
    mochila->itens[mochila->qntd].tipo[MAX_STR_LEN - 1] = '\0';

    mochila->itens[mochila->qntd].quantidade = quantidade;
    mochila->itens[mochila->qntd].prioridade = prioridade;

    mochila->qntd++;
    mochila->ordenadoNome = false;
    printf("\nItem '%s' adicionado com sucesso!\n", nome);
}

// -----------------------------------------------------------------------------
// Remove um item da mochila
// -----------------------------------------------------------------------------
void removerItemVetor(Mochila *mochila, const char* nome) {
    int pos = -1;

    for (int i = 0; i < mochila->qntd; i++) {
        if (strcmp(mochila->itens[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("\nItem '%s' nao encontrado.\n", nome);
        return;
    }

    // Desloca os itens à esquerda para preencher o espaço
    for (int i = pos; i < mochila->qntd - 1; i++) {
        mochila->itens[i] = mochila->itens[i + 1];
    }

    mochila->qntd--;
    mochila->ordenadoNome = false;
    printf("\nItem '%s' removido com sucesso!\n", nome);
}

// -----------------------------------------------------------------------------
// Lista todos os itens
// -----------------------------------------------------------------------------
void listarItensVetor(const Mochila *mochila) {
    if (mochila->qntd == 0) {
        printf("\nA mochila esta vazia.\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    printf("\n--- INVENTARIO ATUAL (%d/%d) ---\n", mochila->qntd, TAM_MAX);
    printf("-------------------------------------------------------------\n");
    printf("%-15s | %-15s | %-10s | %-10s\n", "NOME", "TIPO", "QTD", "PRIORIDADE");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < mochila->qntd; i++) {
        printf("%-15s | %-15s | %-10d | %-10d\n",
               mochila->itens[i].nome,
               mochila->itens[i].tipo,
               mochila->itens[i].quantidade,
               mochila->itens[i].prioridade);
    }

    printf("-------------------------------------------------------------\n");
    printf("\nPressione Enter para continuar...");
    getchar();
}

// -----------------------------------------------------------------------------
// Ordena por nome (Bubble Sort)
// -----------------------------------------------------------------------------
void bubbleSortNome(Mochila *mochila) {
    clock_t inicio, fim;
    inicio = clock();

    if (mochila->qntd < 2) {
        mochila->ordenadoNome = true;
        return;
    }

    int comparacoes = 0;
    Item temp;
    for (int i = 0; i < mochila->qntd - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < mochila->qntd - i - 1; j++) {
            comparacoes++;
            if (strcmp(mochila->itens[j].nome, mochila->itens[j + 1].nome) > 0) {
                temp = mochila->itens[j];
                mochila->itens[j] = mochila->itens[j + 1];
                mochila->itens[j + 1] = temp;
                trocou = 1;
            }
        }
        if (!trocou) break;
    }

    fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    mochila->ordenadoNome = true;

    printf("\nMochila organizada por Nome.\n");
    printf("Comparacoes: %d\nTempo de execucao: %.6f s\n", comparacoes, tempo);
    listarItensVetor(mochila);
}

// -----------------------------------------------------------------------------
// Ordena por tipo (Insertion Sort)
// -----------------------------------------------------------------------------
void OrdenarPorTipo(Mochila *mochila) {
    clock_t inicio, fim;
    inicio = clock();

    int comparacoes = 0;
    for (int i = 1; i < mochila->qntd; i++) {
        Item chave = mochila->itens[i];
        int j = i - 1;

        while (j >= 0 && strcmp(mochila->itens[j].tipo, chave.tipo) > 0) {
            mochila->itens[j + 1] = mochila->itens[j];
            j--;
            comparacoes++;
        }
        mochila->itens[j + 1] = chave;
    }

    fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nItens ordenados por Tipo.\n");
    printf("Comparacoes: %d\nTempo: %.6f s\n", comparacoes, tempo);
    listarItensVetor(mochila);
}

// -----------------------------------------------------------------------------
// Ordena por prioridade (Selection Sort)
// -----------------------------------------------------------------------------
void OrdenarPorPrioridade(Mochila *mochila) {
    clock_t inicio, fim;
    inicio = clock();

    int comparacoes = 0;
    for (int i = 0; i < mochila->qntd - 1; i++) {
        int indiceMaior = i;
        for (int j = i + 1; j < mochila->qntd; j++) {
            comparacoes++;
            if (mochila->itens[j].prioridade > mochila->itens[indiceMaior].prioridade) {
                indiceMaior = j;
            }
        }
        if (indiceMaior != i) {
            Item temp = mochila->itens[i];
            mochila->itens[i] = mochila->itens[indiceMaior];
            mochila->itens[indiceMaior] = temp;
        }
    }

    fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("\nItens ordenados por Prioridade (Maior -> Menor).\n");
    printf("Comparacoes: %d\nTempo: %.6f s\n", comparacoes, tempo);
    listarItensVetor(mochila);
}

// -----------------------------------------------------------------------------
// Busca binária (requer vetor ordenado por nome)
// -----------------------------------------------------------------------------
void buscarItemBinaria(const Mochila *mochila, const char* nome) {
    int inicio = 0;
    int fim = mochila->qntd - 1;
    int comparacoes = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;
        int cmp = strcmp(mochila->itens[meio].nome, nome);

        if (cmp == 0) {
            printf("\n---------------------------------------------\n");
            printf("COMPONENTE ENCONTRADO!\n");
            printf("---------------------------------------------\n");
            printf("Nome: %s | Tipo: %s | Qtd: %d | Prioridade: %d\n",
                   mochila->itens[meio].nome,
                   mochila->itens[meio].tipo,
                   mochila->itens[meio].quantidade,
                   mochila->itens[meio].prioridade);
            return;
        }
        else if (cmp < 0) {
            // nome procurado vem DEPOIS do meio (lado direito)
            inicio = meio + 1;
        } else {
            // nome procurado vem ANTES do meio (lado esquerdo)
            fim = meio - 1;
        }
    }
    printf("\nItem '%s' nao encontrado.\n", nome);
}

// -----------------------------------------------------------------------------
// Função principal
// -----------------------------------------------------------------------------
int main() {
    Mochila mochila;
    inicializarMochila(&mochila);

    int opcao;
    char nome[MAX_STR_LEN];
    char tipo[MAX_STR_LEN];
    int quantidade;
    int prioridade;

    do {
        printf("\n=============================================\n");
        printf("   PLANO DE FUGA - CODIGO DA ILHA   \n");
        printf("=============================================\n");
        printf("ITENS NA MOCHILA (%d/%d)\n", mochila.qntd, TAM_MAX);
        printf("Status: %s\n", mochila.ordenadoNome ? "Ordenado por Nome" : "Desordenado");

        printf("\n1. Adicionar Componente\n");
        printf("2. Remover Componente\n");
        printf("3. Listar Componentes\n");
        printf("4. Ordenar Componentes\n");
        printf("5. Busca Binaria por Nome\n");
        printf("0. ATIVAR TORRE (Sair)\n");
        printf("-----------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa o \n

        switch (opcao) {
            case 1:
                printf("Nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Tipo: ");
                fgets(tipo, sizeof(tipo), stdin);
                tipo[strcspn(tipo, "\n")] = '\0';

                printf("Quantidade: ");
                scanf("%d", &quantidade);
                getchar();

                printf("Prioridade (1-5): ");
                scanf("%d", &prioridade);
                getchar();

                inserirItemVetor(&mochila, nome, tipo, quantidade, prioridade);
                break;

            case 2:
                printf("Nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                removerItemVetor(&mochila, nome);
                break;

            case 3:
                listarItensVetor(&mochila);
                break;

            case 4: {
                int criterio;
                printf("\n1. Por Nome (Bubble)\n2. Por Tipo (Insertion)\n3. Por Prioridade (Selection)\n0. Cancelar\n> ");
                scanf("%d", &criterio);
                getchar();

                if (criterio == 1) bubbleSortNome(&mochila);
                else if (criterio == 2) OrdenarPorTipo(&mochila);
                else if (criterio == 3) OrdenarPorPrioridade(&mochila);
                break;
            }

            case 5:
                if (!mochila.ordenadoNome) {
                    printf("\nA mochila precisa estar ordenada por nome antes da busca!\n");
                    printf("Use a opcao 4.\n");
                    printf("\nPressione Enter para continuar...");
                    getchar();
                    break;
                }
                printf("Nome do item a buscar: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                buscarItemBinaria(&mochila, nome);
                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 0:
                printf("\nAtivando a torre e escapando da ilha...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
