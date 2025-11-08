#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10   
#define MAX_NOME 30    
#define MAX_TIPO 20    

// -------------------------------------------------------------------------
// Struct que representa um item do inventário
// -------------------------------------------------------------------------
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
} Item;

// -------------------------------------------------------------------------
// Função para limpar o buffer do teclado (evita problemas entre scanf e fgets)
// -------------------------------------------------------------------------
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// -------------------------------------------------------------------------
// Lê uma string do usuário (com remoção do '\n')
// -------------------------------------------------------------------------
void lerString(const char *mensagem, char *destino, int tamanho) {
    printf("%s", mensagem);
    fgets(destino, tamanho, stdin);
    destino[strcspn(destino, "\n")] = '\0';
}

// -------------------------------------------------------------------------
// Insere um novo item na mochila
// -------------------------------------------------------------------------
void inserirItem(Item mochila[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("\nMochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;
    limparBuffer(); // limpa buffer antes de ler strings

    lerString("Digite o nome do item: ", novo.nome, MAX_NOME);
    lerString("Digite o tipo do item (ex: arma, munição, cura): ", novo.tipo, MAX_TIPO);

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[*qtd] = novo;
    (*qtd)++;

    printf("\nItem cadastrado com sucesso!\n");
}

// -------------------------------------------------------------------------
// Remove um item da mochila pelo nome
// -------------------------------------------------------------------------
void removerItem(Item mochila[], int *qtd) {
    if (*qtd == 0) {
        printf("\nA mochila está vazia.\n");
        return;
    }

    char nome[MAX_NOME];
    limparBuffer();
    lerString("Digite o nome do item a ser removido: ", nome, MAX_NOME);

    int encontrado = -1;
    for (int i = 0; i < *qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("\nItem \"%s\" não encontrado.\n", nome);
        return;
    }

    for (int i = encontrado; i < *qtd - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*qtd)--;
    printf("\nItem \"%s\" removido com sucesso!\n", nome);
}

// -------------------------------------------------------------------------
// Lista todos os itens da mochila
// -------------------------------------------------------------------------
void listarItens(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("\nMochila vazia.\n");
        return;
    }

    printf("\n--- Itens da Mochila ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// -------------------------------------------------------------------------
// Busca um item pelo nome e exibe seus dados
// -------------------------------------------------------------------------
void buscarItem(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("\nA mochila está vazia.\n");
        return;
    }

    char nome[MAX_NOME];
    limparBuffer();
    lerString("Digite o nome do item a ser buscado: ", nome, MAX_NOME);

    for (int i = 0; i < qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\nItem encontrado:\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }

    printf("\nItem \"%s\" não encontrado.\n", nome);
}

// -------------------------------------------------------------------------
// Função principal (main) com menu
// -------------------------------------------------------------------------
int main() {
    Item mochila[MAX_ITENS];
    int qtd = 0;
    int opcao;

    do {
        printf("\n=== MENU INVENTÁRIO ===\n");
        printf("1. Cadastrar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(mochila, &qtd);
                break;

            case 2:
                removerItem(mochila, &qtd);
                break;

            case 3:
                listarItens(mochila, qtd);
                break;

            case 4:
                buscarItem(mochila, qtd);
                break;

            case 0:
                printf("\nSaindo do sistema...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

        // Exibe o estado da mochila após as operações principais
        if (opcao == 1 || opcao == 2) {
            listarItens(mochila, qtd);
        }

    } while (opcao != 0);

    return 0;
}
