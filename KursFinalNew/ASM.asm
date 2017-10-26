.586
.MODEL FLAT, C
PUBLIC sum
.CODE

sum PROC C stroka1:DWORD, stroka2:DWORD, stroka3:DWORD  ; ������������ ���� ����� (��������� ������������ � 3-��)  

push ESI
push EDI
push EBX
push ECX
push EDX


mov ESI, stroka1					; ��������� �� ������ 1-�� ������
mov EDI, stroka2					; ��������� �� ������ 2-�� ������ 

jmp SLEN							; ������� ����� ����� ( � EDX � EBX)
return:

mov EAX, stroka3					; ��������� �� ������ �������������� ������

mov ECX, EDX						; � ������� ���������� ����� 1-�� (EDX)
sum1:
	mov DL, [ESI]					; ������ �� 1-�� ������
	mov [EAX] , DL					; �������� � �������������� ������
	inc ESI							; ��������� ������ 1-�� ������
	inc EAX							; ��������� ������ �������������� ������

loop sum1							; � ������ ����� 1

mov ECX, EBX						; � ������� ���������� ����� 2-�� (EBX)

sum2:
	mov DL, [EDI]					; ������ �� 2-�� ������
	mov [EAX] , DL					; �������� � �������������� ������
	inc EDI							; ��������� ������ 1-�� ������
	inc EAX							; ��������� ������ �������������� ������

loop sum2							; � ������ ����� 2

 mov DL,0h							; ����������
 mov [EAX], DL						; ����� ������


jmp the_end


SLEN:
	push ESI
	push EDI
	push EAX

	mov ESI, stroka1					; ��������� �� ������ 1-�� ������

	xor EDI,EDI						    ; ����� ������ (0)

	metka2:								; ����
		mov AL, [ESI]					; ������� ������
		cmp AL, 0h						; ���������� � '\0'
		je skip1							; ���� �����, ��������
		inc EDI							; ���� ���, ������� ��������� ������
		inc ESI							; ����������� ����� �� 1
	loop metka2							; � ������ �����

	skip1:
		mov EDX, EDI					; ���������� ����� 1-�� ������


	mov ESI, stroka2					; ��������� �� ������ 2-�� ������
	xor EAX,EAX							; ��������� �������� ������
	xor EDI,EDI						    ; ����� ������ (0)

	metka3:								; ����
		mov AL, [ESI]					; ������� ������
		cmp AL, 0h						; ���������� � '\0'
		je skip3						; ���� �����, ��������
		inc EDI							; ���� ���, ������� ��������� ������
		inc ESI							; ����������� ����� �� 1
	loop metka3							; � ������ �����

	skip3:
		mov EBX, EDI					; ���������� ����� 2-�� ������

		pop EAX
		pop EDI
		pop ESI
		jmp return

the_end:

pop EDX
pop ECX
pop EBX
pop EDI
pop ESI

RET
sum ENDP
END