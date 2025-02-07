#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 100000

int main() {
    int Q, N;
    scanf("%d", &Q);
    scanf("%d", &N);

    int *pages = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++){
        scanf("%d", &pages[i]);
    }

    int frames[MAX_FRAMES];
    int front = 0, size = 0, page_faults = 0;

    for (int i = 0; i < N; i++){
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < size; j++){
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found){
            if (size == Q) {
                for (int j = 0; j < Q - 1; j++) {
                    frames[j] = frames[j + 1];
                }
                frames[Q - 1] = page;
            } else {
                frames[size++] = page;
            }
            page_faults++;
        }
    }

    printf("%d\n", page_faults);
    free(pages);
    return 0;
}
