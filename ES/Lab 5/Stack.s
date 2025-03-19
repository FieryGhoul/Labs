	AREA	RESET, DATA, READONLY
	EXPORT __Vectors
__Vectors
		DCD 0X10001000
		DCD Reset_Handler
		ALIGN 4
		AREA	mycode, CODE, READONLY
		ENTRY
		EXPORT Reset_Handler
Reset_Handler
    BL FF
    LDR R0, =SRC
    MOV SP, R0
    STMIA SP!, {R1-R10}     ; Store R1 to R10 values onto the stack

    MOV R1, #0              ; Outer loop counter (start from 0)
OUTER
    MOV R2, R1              ; Set min to i 
    ADD R3, R1, #4          ; Inner loop counter 
INNER
    LDR R4, [R0, R2]        ; Load a[min] into R4
    LDR R5, [R0, R3]        ; Load a[j] into R5
    CMP R5, R4              ; Compare a[j] with a[min]
    MOVLO R2, R3            ; If a[j] < a[min], update min
    ADD R3, #4              ; Increment inner loop
    CMP R3, #40
    BNE INNER

    LDR R6, [R0, R2]        ; Load the minimum element (a[min])
    LDR R7, [R0, R1]        ; Load the current element (a[i])
    STR R6, [R0, R1]        ; Store a[min] at a[i]
    STR R7, [R0, R2]        ; Store a[i] at a[min] swapping

    ADD R1, #4              ; Increment outer loop
    CMP R1, #36             ; Check if outer loop finished
    BNE OUTER

    LDMDB SP!, {R1-R10}     ; Load sorted values back TO R1-R10
    B End                  ; Halt the program

FF
    MOV R1, #2              ; Load initial values
    MOV R2, #4
    MOV R3, #7
    MOV R4, #1
    MOV R5, #3
    MOV R6, #9
    MOV R7, #0
    MOV R8, #6
    MOV R9, #5
    MOV R10, #8
    BX LR

SRC DCD 0

End	
	B END
	
END
