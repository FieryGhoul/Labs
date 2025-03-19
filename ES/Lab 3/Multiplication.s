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
	MOV R0,#32;	Move value 32 to R0
	MOV R1,#7;	Move Value 7 to R1
	UMULL R3,R2,R0,R1;	Unsigned 64-bit Multiplication	
STOP ;					R3 stores higher bits and R2 stores lower		
	B STOP
	END
	
