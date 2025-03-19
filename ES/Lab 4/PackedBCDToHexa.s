		AREA RESET, DATA, READONLY
		EXPORT __Vectors
__Vectors
    DCD 0x10001000
    DCD Reset_Handler
	AREA mycode, CODE, READONLY
    ENTRY
    EXPORT Reset_Handler
Reset_Handler
    LDR R0, =0x12345678
    MOV R1, #0
    MOV R2, #1
	MOV R4,#10
LOOP
    AND R3, R0, #0x0F
    MOV R0, R0, LSR #4
	MLA R1, R3, R2, R1
    MUL R2, R2, R4
    CMP R0, #0
    BNE LOOP
STOP
    B STOP
    END
