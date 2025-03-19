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
    LDR R0, =array
    LDR R1, =length
    LDR R1, [R1]
    MOV R2, #0               ;outer loop counter
outer_loop
    CMP R2, R1
    BGE end_sort             ; If i >= length, end sorting
    MOV R3, R2
    ADD R4, R2, #1           ; Initialize j to i + 1
inner_loop
    CMP R4, R1
    BGE swap_elements        ; If j >= length, swap elements
    LDR R5, [R0, R3, LSL #2] ; Load a[min] into R5
    LDR R6, [R0, R4, LSL #2] ; Load a[j] into R6
    CMP R5, R6               ; Compare a[min] with array[j]
    BLE skip_update          ; If a[min] <= a[j], skip update
    MOV R3, R4               ; Update min to j
skip_update
    ADD R4, R4, #1           ; Increment j
    B inner_loop             ; Repeat inner loop
swap_elements
    CMP R2, R3               ; Compare i with min_index
    BEQ skip_swap            ; If i == min_index, skip swap
    LDR R7, [R0, R2, LSL #2] ; Store a[i] in temporary register R7
    LDR R5, [R0, R3, LSL #2] ; Load a[min] into R5
    STR R5, [R0, R2, LSL #2] ; Store a[min] at array[i]
    STR R7, [R0, R3, LSL #2] ; Store value from R7 (a[i]) at a[min]
skip_swap
    ADD R2, R2, #1           ; Increment i
    B outer_loop             ; Repeat outer loop
end_sort
    B END                                  

array  DCD 64, 25, 12, 22, 11, 90, 34, 50  
length DCD 8
END
