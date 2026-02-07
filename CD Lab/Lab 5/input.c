#INCLUDE <STDIO.H>

INT MAIN() {
    INT I;
    CHAR MSG[] = "DONE";  
INT D=1;
    FOR (I = 1; I <= 10; I++) {      // LOOP
        IF (I % 2 == 0 && !D) {            // DECISION
            PRINTF("%D IS EVEN\n", I);
       
        } ELSE {
            PRINTF("%D IS ODD\n", I);
        D -=1;
        }
    }
  PRINTF("%S",MSG);
    RETURN 0;
}

