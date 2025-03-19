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
	MOV R0,#20
	MOV R1,R0
	ADD R1,R1,#1
	MOV R2,#0
	MLA R2,R0,R1,R2;	R2=(R0*R1)+R2
	LSR R2,R2,#1;		divide by(2)
	LDR R3,=RESULT
	STR R2,[R3];		r2=210(sum of first n natural numbers)
STOP 
	B STOP
RESULT DCD 0X0000000F
	END
	
