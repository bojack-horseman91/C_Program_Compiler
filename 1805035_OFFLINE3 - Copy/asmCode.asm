.MODEL BIG
.STACK 400H
.DATA
FUNC_RETURN_VALUE DW ?
TEMPORARY_VALUE DW ?
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

MAIN PROC
	MOV AX, @DATA
	MOV DS, AX
	MOV BP,SP
	PUSH 0
	PUSH 0
	PUSH 0
	MOV SI,-2
	MOV DI,SI
	PUSH 3
	POP AX 
	;******************************
	MOV [BP+DI], AX
	MOV SI,-4
	MOV DI,SI
	PUSH 8
	POP AX 
	;******************************
	MOV [BP+DI], AX
	MOV SI,-6
	MOV DI,SI
	PUSH 6
	POP AX 
	;******************************
	MOV [BP+DI], AX
	MOV SI,-2
	 PUSH [BP-SI] 
	POP AX 
	MOV DX,AX
	PUSH 3
	POP AX 
	CMP DX,AX
	JE L0
	MOV AX,0
	JMP L1
L0:	MOV AX,1
L1:
	CMP AX,0
	JE L2
	MOV BP,SP
	MOV AX,[BP-4]
	CALL PRINT_FUNC
	L2:
	MOV SI,-4
	 PUSH [BP-SI] 
	POP AX 
	MOV DX,AX
	PUSH 8
	POP AX 
	CMP DX,AX
	JL L3
	MOV AX,0
	JMP L4
L3:	MOV AX,1
L4:
	CMP AX,0
	JE L5
	MOV BP,SP
	MOV AX,[BP-2]
	CALL PRINT_FUNC
	JMP L6
	L5:
	MOV BP,SP
	MOV AX,[BP-6]
	CALL PRINT_FUNC
;condition statements3
	L6:
	MOV SI,-6
	 PUSH [BP-SI] 
	POP AX 
	MOV DX,AX
	PUSH 6
	POP AX 
	CMP DX,AX
	JNE L7
	MOV AX,0
	JMP L8
L7:	MOV AX,1
L8:
	CMP AX,0
	JE L9
	MOV BP,SP
	MOV AX,[BP-6]
	CALL PRINT_FUNC
	JMP L10
	L9:
	MOV SI,-4
	 PUSH [BP-SI] 
	POP AX 
	MOV DX,AX
	PUSH 8
	POP AX 
	CMP DX,AX
	JG L11
	MOV AX,0
	JMP L12
L11:	MOV AX,1
L12:
	CMP AX,0
	JE L13
	MOV BP,SP
	MOV AX,[BP-4]
	CALL PRINT_FUNC
	JMP L14
	L13:
	MOV SI,-2
	 PUSH [BP-SI] 
	POP AX 
	MOV DX,AX
	PUSH 5
	POP AX 
	CMP DX,AX
	JL L15
	MOV AX,0
	JMP L16
L15:	MOV AX,1
L16:
	CMP AX,0
	JE L17
	MOV BP,SP
	MOV AX,[BP-2]
	CALL PRINT_FUNC
	JMP L18
	L17:
	MOV BP,SP
	MOV SI,-6
	MOV DI,SI
	PUSH 0
	POP AX 
	;******************************
	MOV [BP+DI], AX
	MOV AX,[BP-6]
	CALL PRINT_FUNC
;condition statements3
	L18:
;condition statements3
	L18:
;condition statements3
	L18:
	PUSH 0
	POP AX 
	MOV FUNC_RETURN_VALUE,AX
MOV AH, 4CH
MOV AL, 01 ;your return code.
INT 21H
MAIN ENDP
END MAIN