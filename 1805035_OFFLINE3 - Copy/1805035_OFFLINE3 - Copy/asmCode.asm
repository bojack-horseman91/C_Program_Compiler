.MODEL BIG
.STACK 400H
.DATA
FUNC_RETURN_VALUE DW ?
TEMPORARY_VALUE DW ?
t0 DW ?
t1 DW ?				
MY_STACK DW 15 dup(?)
MY_STACKOFFSET DW 0
MY_STACKINPUT DW ?				
MY_STACKOUTPUT DW ?
T3 DW ?
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


MY_PUSH PROC
						
	PUSH SI						
	PUSH BX						
	PUSH CX						
	PUSH DX						

	LEA SI,MY_STACK
							ADD SI,MY_STACKOFFSET
							MOV BX,MY_STACKINPUT
							MOV [SI],BX
							ADD MY_STACKOFFSET,2
						

	POP DX						
	POP CX						
	POP BX						
	POP SI						
	RET						
MY_PUSH ENDP

MY_POP PROC
						
	PUSH SI						
	PUSH BX						
	PUSH CX						
	PUSH DX						
	SUB MY_STACKOFFSET,2
						

	LEA SI,MY_STACK
							ADD SI,MY_STACKOFFSET
							MOV BX,[SI]
							MOV MY_STACKOUTPUT,BX
						

	POP DX						
	POP CX						
	POP BX						
	POP SI						
	RET						
MY_POP ENDP

DELAY PROC
						
	PUSH AX						
	PUSH BX						
	PUSH CX						
	PUSH DX						
MOV BX,5						
DELAY_LOOP:						
MOV     CX, 0FH						
MOV     DX, 4240H						
MOV     AH, 86H						
INT     15H						
DEC BX						
CMP BX,0						
JNE DELAY_LOOP						

	POP DX						
	POP CX						
	POP BX						
	POP AX						
	RET						
DELAY ENDP
MAIN PROC
	MOV AX, @DATA
	MOV DS, AX
	MOV BP,SP
	PUSH 0
;a,b
	PUSH 0
;a,b,c
	PUSH 0
;a,b,c,i
	PUSH 0
;int a,b,c,i;
; statement : var_declaration
	MOV SI,-4
	MOV DI,SI
	PUSH 0
; term : unary_expression
	POP AX 
; simple_expression : term
; rel_expression :  simple_expression
; logic_expression : rel_expression


;b=0
	;******************************
	MOV [BP+DI], AX
;EXPRESSION
	MOV SI,-6
	MOV DI,SI
	PUSH 1
; term : unary_expression
	POP AX 
; simple_expression : term
; rel_expression :  simple_expression
; logic_expression : rel_expression


;c=1
	;******************************
	MOV [BP+DI], AX
;EXPRESSION
	MOV SI,-8
	MOV DI,SI
	PUSH 0
; term : unary_expression
	POP AX 
; simple_expression : term
; rel_expression :  simple_expression
; logic_expression : rel_expression


;i=0
	;******************************
	MOV [BP+DI], AX
;EXPRESSION
L0:
	MOV SI,-8
	 PUSH [BP-SI] 
; term : unary_expression
	POP AX 
; simple_expression : term
MOV T3,AX
MOV AX,T1
	MOV MY_STACKINPUT,AX
MOV AX,T3
	CALL MY_PUSH
	MOV t1,AX
; rel_expression : simple_expression RELOP simple_expression
	PUSH 4
; term : unary_expression
	POP AX 
; simple_expression : term
	MOV DX,t1
CALL MY_POP
MOV T3,AX
MOV AX,MY_STACKOUTPUT
MOV T1,AX
MOV AX,T3
	CMP DX,AX
	JL L4
	MOV AX,0
	JMP L5
L4:	MOV AX,1
L5:
; logic_expression : rel_expression


; expression : logic_expression	

;EXPRESSION
	CMP AX,0
	JE L1
	JMP L2
L3:
	MOV SI,-8
	 PUSH [BP+SI] 
	INC [BP+SI]
; term : unary_expression
	POP AX 
; simple_expression : term
; rel_expression :  simple_expression
; logic_expression : rel_expression


; expression : logic_expression	

	JMP L0
L2:
	MOV SI,-2
	MOV DI,SI
	PUSH 3
; term : unary_expression
	POP AX 
; simple_expression : term
; rel_expression :  simple_expression
; logic_expression : rel_expression


;a=3
	;******************************
	MOV [BP+DI], AX
;EXPRESSION
;WHILE LPAREN EXPRESSION RPAREN
	L6:
	MOV SI,-2
	 PUSH [BP+SI] 
	DEC [BP+SI]
; term : unary_expression
	POP AX 
; simple_expression : term
; rel_expression :  simple_expression
; logic_expression : rel_expression


; expression : logic_expression	

	CMP AX,0
	JE L7
	MOV SI,-4
	 PUSH [BP+SI] 
	INC [BP+SI]
; term : unary_expression
	POP AX 
; simple_expression : term
; rel_expression :  simple_expression
; logic_expression : rel_expression


; expression : logic_expression	

;EXPRESSION
	JMP L6
	L7:
	JMP L3
L1:
;OK SAKIN
; PRINT STATEMENT
	MOV AX,[BP-2]
	CALL PRINT_FUNC
; PRINT STATEMENT
	MOV AX,[BP-4]
	CALL PRINT_FUNC
; PRINT STATEMENT
	MOV AX,[BP-6]
	CALL PRINT_FUNC
MAIN ENDP
END MAIN
