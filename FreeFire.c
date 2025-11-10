#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#define MAX_ITENS 10

struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};


struct No {
    struct Item dados;
    struct No* proximo;
};


struct Item mochilaVetor[MAX_ITENS];
int totalItensVetor = 0; 
int vetorOrdenado = 0;

struct No* mochilaLista = NULL; 


void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

struct Item lerDadosItem() {
    struct Item novoItem;
    
    printf("  Nome do item (sem espacos): ");
    scanf("%s", novoItem.nome);
    limparBufferEntrada();
    
    printf("  Tipo do item (ex: Arma, Pocao): ");
    scanf("%s", novoItem.tipo);
    limparBufferEntrada();
    
    printf("  Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    limparBufferEntrada();
    
    return novoItem;
}

void exibirItem(struct Item item) {
    printf("  - Nome: %s (Tipo: %s, Qtd: %d)\n", item.nome, item.tipo, item.quantidade);
}


void inserirItemVetor() {
    if (totalItensVetor >= MAX_ITENS) {
        printf("\n[ERRO] Mochila (Vetor) cheia! Nao e possivel inserir.\n");
        return;
    }

    printf("\nInserindo no Vetor:\n");
    struct Item item = lerDadosItem();
    
    mochilaVetor[totalItensVetor] = item;
    totalItensVetor++;
    
    vetorOrdenado = 0; 
    
    printf("Item '%s' inserido no vetor com sucesso.\n", item.nome);
}


void removerItemVetor() {
    char nomeBusca[30];
    printf("\nDigite o nome do item a remover (Vetor): ");
    scanf("%s", nomeBusca);
    limparBufferEntrada();

    int i, j;
    int encontrado = 0;

    for (i = 0; i < totalItensVetor; i++) {
        
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            encontrado = 1;
            
            for (j = i; j < totalItensVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }
            
            totalItensVetor--; 
            vetorOrdenado = 0;
            printf("Item '%s' removido do vetor.\n", nomeBusca);
            break; 
        }
    }

    if (!encontrado) {
        printf("Item '%s' nao encontrado no vetor.\n", nomeBusca);
    }
}

void listarItensVetor() {
    printf("\n--- Itens na Mochila (Vetor) [%d/%d] ---\n", totalItensVetor, MAX_ITENS);
    if (totalItensVetor == 0) {
        printf("Mochila vazia.\n");
        return;
    }
    
    if (vetorOrdenado) {
        printf("(Status: Ordenado)\n");
    } else {
        printf("(Status: Nao Ordenado)\n");
    }

    int i;
    for (i = 0; i < totalItensVetor; i++) {
        exibirItem(mochilaVetor[i]);
    }
    printf("----------------------------------------\n");
}

void buscarSequencialVetor(int* comparacoes) {
    char nomeBusca[30];
    printf("\nDigite o nome do item (Busca Sequencial Vetor): ");
    scanf("%s", nomeBusca);
    limparBufferEntrada();

    *comparacoes = 0; 
    int i;
    int encontrado = 0;

    for (i = 0; i < totalItensVetor; i++) {
        (*comparacoes)++; // Incrementa o contador a cada 'strcmp'
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado (Busca Sequencial)!\n");
            exibirItem(mochilaVetor[i]);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem '%s' nao encontrado.\n", nomeBusca);
    }
}


void ordenarVetor() {
    if (totalItensVetor == 0) {
        printf("\nMochila vazia. Nada a ordenar.\n");
        return;
    }

    printf("\nOrdenando vetor com Bubble Sort...\n");
    int i, j;
    struct Item temp; 

    for (i = 0; i < totalItensVetor - 1; i++) {
        for (j = 0; j < totalItensVetor - i - 1; j++) {
            
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                // Troca
                temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }

    vetorOrdenado = 1; 
    printf("Vetor ordenado com sucesso!\n");
}

void buscarBinariaVetor(int* comparacoes) {
    if (!vetorOrdenado) {
        printf("\n[ERRO] O vetor nao esta ordenado!\n");
        printf("Por favor, use a Opcao 5 (Ordenar Vetor) antes da busca binaria.\n");
        *comparacoes = 0;
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item (Busca Binaria Vetor): ");
    scanf("%s", nomeBusca);
    limparBufferEntrada();

    *comparacoes = 0; 
    int encontrado = 0;
    
    int esquerda = 0;
    int direita = totalItensVetor - 1;
    int meio;

    while (esquerda <= direita) {
        meio = esquerda + (direita - esquerda) / 2; 

        (*comparacoes)++; // Incrementa o contador de comparações
        int cmp = strcmp(nomeBusca, mochilaVetor[meio].nome);

        if (cmp == 0) {
            printf("\nItem encontrado (Busca Binaria)!\n");
            exibirItem(mochilaVetor[meio]);
            encontrado = 1;
            break;
        }

        if (cmp < 0) {
            direita = meio - 1;
        }
        else {
            esquerda = meio + 1;
        }
    }

    if (!encontrado) {
        printf("\nItem '%s' nao encontrado.\n", nomeBusca);
    }
}

void inserirItemLista() {
    printf("\nInserindo na Lista Encadeada:\n");
    struct Item item = lerDadosItem();

    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    if (novoNo == NULL) {
        printf("\n[ERRO] Falha ao alocar memoria (malloc)!\n");
        return;
    }

    
    novoNo->dados = item;
    
    novoNo->proximo = mochilaLista;
    
    mochilaLista = novoNo;

    printf("Item '%s' inserido na lista com sucesso.\n", item.nome);
}

void removerItemLista() {
    char nomeBusca[30];
    printf("\nDigite o nome do item a remover (Lista): ");
    scanf("%s", nomeBusca);
    limparBufferEntrada();

    struct No* atual = mochilaLista;
    struct No* anterior = NULL;
    int encontrado = 0;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            encontrado = 1;
            break;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    if (!encontrado) {
        printf("Item '%s' nao encontrado na lista.\n", nomeBusca);
        return;
    }

    if (anterior == NULL) {
        mochilaLista = atual->proximo; 
    }
    
    else {
        anterior->proximo = atual->proximo; 
    }

    free(atual); 
    printf("Item '%s' removido da lista.\n", nomeBusca);
}

void listarItensLista() {
    printf("\n--- Itens na Mochila (Lista) ---\n");
    if (mochilaLista == NULL) {
        printf("Mochila vazia.\n");
        return;
    }

    struct No* atual = mochilaLista;
    int contador = 0;

    while (atual != NULL) {
        contador++;
        exibirItem(atual->dados);
        atual = atual->proximo; 
    }
    printf("(Total de %d itens na lista)\n", contador);
    printf("-----------------------------------\n");
}


void buscarSequencialLista(int* comparacoes) {
    char nomeBusca[30];
    printf("\nDigite o nome do item (Busca Sequencial Lista): ");
    scanf("%s", nomeBusca);
    limparBufferEntrada();

    *comparacoes = 0; 
    int encontrado = 0;
    
    struct No* atual = mochilaLista;

    while (atual != NULL) {
        (*comparacoes)++; 
        
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            printf("\nItem encontrado (Busca Sequencial)!\n");
            exibirItem(atual->dados);
            encontrado = 1;
            break;
        }
        atual = atual->proximo;
    }

    if (!encontrado) {
        printf("\nItem '%s' nao encontrado.\n", nomeBusca);
    }
}

void limparLista() {
    struct No* atual = mochilaLista;
    struct No* temp;

    while (atual != NULL) {
        temp = atual; 
        atual = atual->proximo; 
        free(temp); 
    }
    mochilaLista = NULL; 
}


void menuVetor() {
    int escolha;
    int comparacoes = 0; 

    do {
        printf("\n--- Mochila (VETOR) ---");
        if (!vetorOrdenado) printf(" [NAO ORDENADO]");
        else printf(" [ORDENADO]");
        
        printf("\nEscolha a operacao:\n");
        printf("1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item (Sequencial)\n");
        printf("5. ORDENAR Vetor (Bubble Sort)\n");
        printf("6. Buscar Item (BINARIA) (Requer ordenacao)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Opcao: ");
        
        scanf("%d", &escolha);
        limparBufferEntrada();

        switch (escolha) {
            case 1:
                inserirItemVetor();
                break;
            case 2:
                removerItemVetor();
                break;
            case 3:
                listarItensVetor();
                break;
            case 4:
                buscarSequencialVetor(&comparacoes);
                printf(">> Total de Comparacoes (Sequencial): %d\n", comparacoes);
                break;
            case 5:
                ordenarVetor();
                break;
            case 6:
                buscarBinariaVetor(&comparacoes);
                printf(">> Total de Comparacoes (Binaria): %d\n", comparacoes);
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (escolha != 0);
}

void menuLista() {
    int escolha;
    int comparacoes = 0; // Variável para o contador

    do {
        printf("\n--- Mochila (LISTA ENCADEADA) ---\n");
        printf("Escolha a operacao:\n");
        printf("1. Inserir Item (no inicio)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item (Sequencial)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Opcao: ");
        
        scanf("%d", &escolha);
        limparBufferEntrada();

        switch (escolha) {
            case 1:
                inserirItemLista();
                break;
            case 2:
                removerItemLista();
                break;
            case 3:
                listarItensLista();
                break;
            case 4:
                buscarSequencialLista(&comparacoes);
                printf(">> Total de Comparacoes (Sequencial): %d\n", comparacoes);
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (escolha != 0);
}


int main() {
    int escolha;

    do {
        printf("\n\n*** Missao: Comparacao de Estruturas de Dados ***\n");
        printf("Qual implementacao de mochila deseja testar?\n");
        printf("1. Mochila com VETOR (Array)\n");
        printf("2. Mochila com LISTA ENCADEADA\n");
        printf("0. Sair do Programa\n");
        printf("Opcao: ");
        
        scanf("%d", &escolha);
        limparBufferEntrada();

        switch (escolha) {
            case 1:
                menuVetor();
                break;
            case 2:
                menuLista();
                break;
            case 0:
                printf("Saindo do programa. Limpando memoria...\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (escolha != 0);

    limparLista();

    return 0;
}