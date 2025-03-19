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
	LDR R0,=list
	LDR R1,=count
	MOV R2,#10
	MOV R3,#0	;Even Counter
	MOV R4,#0	;Odd Counter
	MOV R5,#0	;Greater than 10
LOOP
	LDR R6,[R0],#4	;Load from list & +4
	ANDS R7,R6,#1
	BEQ EVEN
	ADD R4,R4,#1
	B CHECKER
EVEN 
	ADD R3,R3,#1
CHECKER
	CMP R6,#10
	BLE SKIP
	ADD R5,R5,#1
SKIP
	SUBS R2,R2,#1
	BNE LOOP
	
	STR R3,[R1]
	STR R4,[R1,#4]
	STR R5,[R1,#8]

	B END
list DCD 2,15,8,23,7,16,12,14,9,5,12
count DCD 0, 0, 0          ; Space for 3 values (Even, Odd, Greater than 10 counters)

END
