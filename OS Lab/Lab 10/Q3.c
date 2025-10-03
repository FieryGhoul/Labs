#include <stdio.h>

typedef struct {
    int base;
    int limit;
} Segment;

int main() {
    Segment segTable[5];
    segTable[0] = (Segment){1000, 600};
    segTable[1] = (Segment){1600, 600};
    segTable[2] = (Segment){2200, 400};
    segTable[3] = (Segment){2600, 500};
    segTable[4] = (Segment){3100, 400};

    int seg, offset, phys;
    seg = 2; offset = 53;
    if (offset < segTable[seg].limit) {
        phys = segTable[seg].base + offset;
        printf("Physical Address = %d\n", phys);
    }

    seg = 3; offset = 852;
    if (offset < segTable[seg].limit) {
        phys = segTable[seg].base + offset;
        printf("Physical Address = %d\n", phys);
    }

    seg = 0; offset = 1222;
    if (offset < segTable[seg].limit) {
        phys = segTable[seg].base + offset;
        printf("Physical Address = %d\n", phys);
    }

    return 0;
}
