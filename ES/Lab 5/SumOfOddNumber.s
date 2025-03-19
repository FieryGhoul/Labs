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
	MOV R0,#20           ; Load n 
	MUL R2,R0,R0         ; Calculate n^2 
	LDR R3,=RESULT
	STR R2,[R3]          ; Store the result in memory
STOP 
	B STOP
RESULT DCD 0X00000000  ; Result storage
	END
