#include <stdio.h>

#define SEGMENTS 5

typedef struct {
    int base;
    int limit;
} Segment;

int main() {
    Segment table[SEGMENTS] = {
        {1400, 1000},  // segment 0
        {6300, 600},   // segment 1
        {4700, 700},   // segment 2
        {4300, 400},   // segment 3
        {3200, 500}    // segment 4
    };

    int seg, offset, phys;

    printf("Enter segment number and offset: ");
    scanf("%d %d", &seg, &offset);

    if (seg >= SEGMENTS) {
        printf("Invalid segment number\n");
        return 0;
    }

    if (offset < table[seg].limit)
        printf("Physical Address = %d\n", table[seg].base + offset);
    else
        printf("Memory violation: offset %d exceeds limit %d\n", offset, table[seg].limit);

    return 0;
}




// #include <stdio.h>

// typedef struct {
//     int base;
//     int limit;
// } Segment;

// int main() {
//     Segment segTable[5];
//     segTable[0] = (Segment){1000, 600};
//     segTable[1] = (Segment){1600, 600};
//     segTable[2] = (Segment){2200, 400};
//     segTable[3] = (Segment){2600, 500};
//     segTable[4] = (Segment){3100, 400};

//     int seg, offset, phys;
//     seg = 2; offset = 53;
//     if (offset < segTable[seg].limit) {
//         phys = segTable[seg].base + offset;
//         printf("Physical Address = %d\n", phys);
//     }

//     seg = 3; offset = 852;
//     if (offset < segTable[seg].limit) {
//         phys = segTable[seg].base + offset;
//         printf("Physical Address = %d\n", phys);
//     }

//     seg = 0; offset = 1222;
//     if (offset < segTable[seg].limit) {
//         phys = segTable[seg].base + offset;
//         printf("Physical Address = %d\n", phys);
//     }

//     return 0;
// }
