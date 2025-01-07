#include <stdio.h>
#include <stdlib.h>

typedef struct Processo {
    int pid;
    int tempo;
    int turnaround;
    struct Processo *prox;
} Processo;

Processo* criarProcesso(int pid, int tempo) {
    Processo *novo = (Processo *)malloc(sizeof(Processo));
    novo->pid = pid;
    novo->tempo = tempo * 1000; // segundos -> milissegundos
    novo->turnaround = 0;
    novo->prox = NULL;
    return novo;
}

Processo* removerProcesso(Processo *anterior, Processo *atual) {
    if (atual == atual->prox) {
        free(atual);
        return NULL;
    } else {
        anterior->prox = atual->prox;
        free(atual);
        return anterior->prox;
    }
}

int main() {
    int n, janela;
    Processo *inicio = NULL, *atual, *anterior;

    int tempoAtual = 0;
    int processosRestantes;

    scanf("%d", &n);
    scanf("%d", &janela);

    for (int i = 0; i < n; i++) {
        int pid, t;
        scanf("%d %d", &pid, &t);
        Processo *novo = criarProcesso(pid, t);

        if (inicio == NULL) {
            inicio = novo;
            inicio->prox = inicio;
        } else {
            novo->prox = inicio->prox;
            inicio->prox = novo;
            inicio = novo;
        }
    }

    processosRestantes = n;
    anterior = inicio;
    atual = inicio->prox;

    while (processosRestantes > 0) {
        if (atual->tempo > 0) {
            if (atual->tempo <= janela) {
                tempoAtual += atual->tempo;
                atual->turnaround = tempoAtual;
                atual->tempo = 0;
                processosRestantes--;

                printf("%d (%d)\n", atual->pid, atual->turnaround);

                atual = removerProcesso(anterior, atual);
            } else {
                atual->tempo -= janela;
                tempoAtual += janela;
                anterior = atual;
                atual = atual->prox;
            }
        } else {
            anterior = atual;
            atual = atual->prox;
        }
    }

    return 0;
}
