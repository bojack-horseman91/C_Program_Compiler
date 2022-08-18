.MODEL BIG
.STACK 400H
.DATA
FUNC_RETURN_VALUE DW ?
TEMPORARY_VALUE DW ?
a  DW ?
b  DW ?
c  DW ?
.CODE

PRINT_FUNC PROC						
	PUSH AX						
	PUSH BX						
	PUSH CX						
	PUSH DX						

	OR AX, AX						
	JGE END_IF1						
	PUSH AX						
	MOV DL,'-'						
	MOV AH, 2						
	INT 21H						
	POP AX						
	NEG AX						

END_IF1:						
	XOR CX, CX						
	MOV BX, 10D						

REPEAT1:						
	XOR DX, DX						
	DIV BX						
	PUSH DX						
	INC CX						

	OR AX, AX						
	JNE REPEAT1						

	MOV AH, 2						

PRINT_LOOP:						
	POP DX						
	OR DL, 30H						
	INT 21H						
	LOOP PRINT_LOOP						
	MOV AH, 2						
	MOV DL, 10						
	INT 21H						

	MOV DL, 13						
	INT 21H						

	POP DX						
	POP CX						
	POP BX						
	POP AX						
	RET						
PRINT_FUNC ENDP

func_a PROC
	MOV BP,SP
	LEA SI,a
	MOV DI,SI
	PUSH 7
	POP AX 
	;******************************
MOV [DI],AX

	RET
func_a ENDP

foo PROC
	MOV AX, [BP-0]
PUSH AX
	MOV BP,SP
	MOV SI,-0
	MOV DI,SI
	MOV SI,-0
	 PUSH [BP-SI] 
	POP AX 
	MOV CX,AX
	PUSH 3
	POP AX 
	ADD AX,CX
	;******************************
	MOV [BP+DI], AX
	MOV SI,-0
	 PUSH [BP-SI] 
	POP AX 
	MOV FUNC_RETURN_VALUE,AX

	RET
foo ENDP

bar PROC
	MOV AX, [BP-0]
PUSH AX
	MOV AX, [BP-2]
PUSH AX
	MOV BP,SP
	PUSH 0
	MOV SI,-4
	MOV DI,SI
	PUSH 4
	POP AX 
	MOV SI,-0
	 PUSH [BP-SI] 
	POP BX
	MUL BX 
	MOV CX,AX
	PUSH 2
	POP AX 
	MOV SI,-2
	 PUSH [BP-SI] 
	POP BX
	MUL BX 
	ADD AX,CX
	;******************************
	MOV [BP+DI], AX
	MOV SI,-4
	 PUSH [BP-SI] 
	POP AX 
	MOV FUNC_RETURN_VALUE,AX

	RET
bar ENDP

MAIN PROC
	MOV AX, @DATA
	MOV DS, AX
	MOV BP,SP
	PUSH 0
	PUSH 0
	PUSH 0
	PUSH 0
	MOV SI,-0
	MOV DI,SI
	PUSH 5
	POP AX 
	;******************************
	MOV [BP+DI], AX
	MOV SI,-2
	MOV DI,SI
	PUSH 6
	POP AX 
	;******************************
	MOV [BP+DI], AX
	MOV TEMPORARY_VALUE,BP
	MOV BP,SP
	CALL func_a
	MOV BP, TEMPORARY_VALUE
	PUSH FUNC_RETURN_VALUE
	POP AX 
	MOV AX,a
	CALL PRINT_FUNC
	MOV SI,-4
	MOV DI,SI
	MOV SI,-0
	 PUSH [BP-SI] 
	POP AX 
	PUSH AX
	MOV TEMPORARY_VALUE,BP
	MOV BP,SP
	CALL foo
	MOV BP, TEMPORARY_VALUE
	PUSH FUNC_RETURN_VALUE
	POP AX 
	;******************************
	MOV [BP+DI], AX
MOV AH, 4CH
MOV AL, 01 ;your return code.
INT 21H
MAIN ENDP
END MAIN
