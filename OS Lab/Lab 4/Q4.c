#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *source, *destination;
    int character;
    
    // Check command line arguments
    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }
    
    // Open source file for reading
    source = fopen(argv[1], "r");
    if (source == NULL) {
        printf("Error: Cannot open source file %s\n", argv[1]);
        return 1;
    }
    
    // Open destination file for writing
    destination = fopen(argv[2], "w");
    if (destination == NULL) {
        printf("Error: Cannot create destination file %s\n", argv[2]);
        fclose(source);
        return 1;
    }
    
    printf("Copying from %s to %s...\n", argv[1], argv[2]);
    
    // Copy character by character using fgetc() and fputc()
    while ((character = fgetc(source)) != EOF) {
        if (fputc(character, destination) == EOF) {
            printf("Error: Write failed\n");
            fclose(source);
            fclose(destination);
            return 1;
        }
    }
    
    // Check if we ended because of an error or EOF
    if (ferror(source)) {
        printf("Error: Read failed\n");
        fclose(source);
        fclose(destination);
        return 1;
    }
    
    printf("File copied successfully!\n");
    
    // Close both files
    fclose(source);
    fclose(destination);
    
    return 0;
}

/*
Alternative version using getc() and putc() (buffered I/O):

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *source, *destination;
    int character;
    
    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }
    
    source = fopen(argv[1], "r");
    if (source == NULL) {
        printf("Error: Cannot open source file %s\n", argv[1]);
        return 1;
    }
    
    destination = fopen(argv[2], "w");
    if (destination == NULL) {
        printf("Error: Cannot create destination file %s\n", argv[2]);
        fclose(source);
        return 1;
    }
    
    printf("Copying from %s to %s using buffered I/O...\n", argv[1], argv[2]);
    
    // Copy using getc() and putc() - faster due to buffering
    while ((character = getc(source)) != EOF) {
        putc(character, destination);
    }
    
    printf("File copied successfully!\n");
    
    fclose(source);
    fclose(destination);
    
    return 0;
}

Compilation and usage:
gcc -o file_copy file_copy.c
./file_copy source.txt destination.txt

Note: The difference between fgetc/fputc and getc/putc:
- fgetc() and fputc() are guaranteed to be functions
- getc() and putc() may be implemented as macros for better performance
- Both accomplish character-by-character copying using stdio.h functions
*/
