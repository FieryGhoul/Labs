    AREA RESET, DATA, READONLY
    EXPORT __Vectors
__Vectors
    DCD 0x10001000
    DCD Reset_Handler
    AREA mycode, CODE, READONLY
    ENTRY
    EXPORT Reset_Handler
Reset_Handler
    LDR R0, =hex1
    LDR R1, [R0]
    LDR R0, =hex2
    LDR R2, [R0]
    MOV R3, #0
    MOV R4, #0
LOOP
    AND R5, R1, #0x0F
    AND R6, R2, #0x0F
    ADD R7, R5, R6
    ADD R7, R7, R4
    CMP R7, #9
    BLE LOOP2
    ADD R7, R7, #6
LOOP2
    MOV R4, #0
    CMP R7, #10
    BGE CARRY
    MOV R4, #0
CARRY
    MOV R4, #1
    ORR R3, R3, R7, LSL #4
    LSR R1, R1, #4
    LSR R2, R2, #4
    CMP R1, #0
    CMP R2, #0
    BNE LOOP
STOP
    B STOP

hex1 DCD 0x1234
hex2 DCD 0x5678

END
