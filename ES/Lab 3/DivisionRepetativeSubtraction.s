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
	MOV R1,#32;	divide 32 by 7
	MOV R2,#7
	MOV R3,#0;	quotient=0
Loop
	CMP R1,R2;	checking if 32<7
	BLT DONE;	if yes go to done
	SUB R1,R1,R2;	else r1=r1-r2(repetative Sub)
	ADD R3,R3,#1;	add one to quotient
	B Loop; 		branch loop
DONE
	LDR R0,=0X0000000F
	STR R3,[R0]
STOP 
	B STOP
	END
	
