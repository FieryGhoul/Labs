#include <stdio.h>
#define FRAMES 3
#define PAGES 12

int main() {
    int pages[PAGES] = {1,2,3,2,4,1,5,2,1,2,3,4};
    int frame[FRAMES], ref[FRAMES] = {0};
    int i, j, k, ptr = 0, faults = 0, hits = 0;

    for (i = 0; i < FRAMES; i++) frame[i] = -1;

    for (i = 0; i < PAGES; i++) {
        int page = pages[i], found = 0;
        for (j = 0; j < FRAMES; j++) {
            if (frame[j] == page) { found = 1; hits++; ref[j] = 1; break; }
        }
        if (!found) {
            while (ref[ptr]) { ref[ptr] = 0; ptr = (ptr + 1) % FRAMES; }
            frame[ptr] = page;
            ref[ptr] = 1;
            ptr = (ptr + 1) % FRAMES;
            faults++;
        }
    }
    printf("Total Page Faults = %d\n", faults);
    printf("Hit Ratio = %.2f\n", (float)hits / PAGES);
    return 0;
}
