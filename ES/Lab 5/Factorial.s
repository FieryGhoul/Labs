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
	MOV R0, #7
	BL FACTORIAL
STOP
	B STOP
FACTORIAL
	CMP R0, #0			; Base case R0 = 0
	MOVEQ R0, #1		; 0! = 1
	BXEQ LR				; Return base case
	STMDB SP!, {R0, LR}	; Push current input, LR value on stack
	SUB R0, R0, #1		; Update input
	BL FACTORIAL		; Function call (Recursive)
	LDMIA SP!, {R1, LR}	; Pop previous input and LR values
	MUL R0, R1, R0		; Calculate factorial
	BX LR				; Return
	END
