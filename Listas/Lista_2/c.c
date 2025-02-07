#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 100000

int findLRU(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; i++){
        if (time[i] < min){
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int Q, N;
    scanf("%d", &Q);
    scanf("%d", &N);

    int *pages = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++){
        scanf("%d", &pages[i]);
    }

    int frames[MAX_FRAMES], time[MAX_FRAMES];
    int count = 0, page_faults = 0;

    for (int i = 0; i < N; i++){
        int page = pages[i], found = 0;

        for (int j = 0; j < count; j++){
            if (frames[j] == page) {
                found = 1;
                time[j] = i;
                break;
            }
        }

        if (!found){
            if (count < Q) {
                frames[count] = page;
                time[count] = i;
                count++;
            } else {
                int lru_pos = findLRU(time, Q);
                frames[lru_pos] = page;
                time[lru_pos] = i;
            }
            page_faults++;
        }
    }

    printf("%d\n", page_faults);
    free(pages);
    return 0;
}
