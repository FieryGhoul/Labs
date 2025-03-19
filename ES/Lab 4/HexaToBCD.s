	AREA RESET, DATA, READONLY
	EXPORT __Vectors
__Vectors
    DCD 0x10001000
    DCD Reset_Handler
	AREA mycode, CODE, READONLY
    ENTRY
    EXPORT Reset_Handler
Reset_Handler
    LDR R0, =hex
    LDRH R1, [R0]
    MOV R2, #0
    MOV R3, #0
LOOP
    AND R4, R1, #0x0F
    ADD R2, R2, R4, LSL #4
    LSR R1, R1, #4
    ADD R3, R3, #1
    CMP R3, #4
    BLT LOOP
STOP
    B STOP
hex DCD 0x1234

END
