	AREA	RESET, DATA, READONLY
	EXPORT __Vectors
__Vectors
	DCD 0X10001000
	DCD Reset_Handler
	ALIGN
	AREA	mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0,=SRC
	LDR R1,=DST
	LDR R2,=OPERAND
	LDR R3,[R2]
	STR R3,[R0]
	LDR R4,[R0]
	STR R4,[R1]
STOP 
	B STOP
OPERAND DCD 8
	AREA mydata, DATA, READWRITE
SRC DCD 0
DST DCD 0
	END
	
