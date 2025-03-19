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
	LDR R0,=MEM1;	Pointer of Mem1 to R0
	LDR R1,[R0];	Load Mem1 to R0
	LDR R0,=MEM2;	Pointer of Mem2 to R0
	LDR R3,[R0];	Load Mem2 to R3
	SUBS R6,R1,R3;	Subtract values from R1 and R3 and store in R5
	LDR R2,=RESULT;	Load to pointer of result to R2
	STR R6,[R2];	Store the result in R6
STOP 
	B STOP
MEM1 DCD 0X10001001
MEM2 DCD 0X10101010
	AREA data,DATA,READWRITE
RESULT DCD 0	
	END
	
