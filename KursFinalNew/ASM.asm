.586
.MODEL FLAT, C
PUBLIC sum
.CODE

sum PROC C stroka1:DWORD, stroka2:DWORD, stroka3:DWORD  ; конкатенация двух строк (результат записывается в 3-ью)  

push ESI
push EDI
push EBX
push ECX
push EDX


mov ESI, stroka1					; указатель на начало 1-ой строки
mov EDI, stroka2					; указатель на начало 2-ой строки 

jmp SLEN							; считаем длины строк ( в EDX и EBX)
return:

mov EAX, stroka3					; указатель на начало результирующей строки

mov ECX, EDX						; в счетчик записываем длину 1-ой (EDX)
sum1:
	mov DL, [ESI]					; символ из 1-ой строки
	mov [EAX] , DL					; копируем в результирующую строку
	inc ESI							; следующий символ 1-ой строки
	inc EAX							; следующий символ результирующей строки

loop sum1							; в начало цикла 1

mov ECX, EBX						; в счетчик записываем длину 2-ой (EBX)

sum2:
	mov DL, [EDI]					; символ из 2-ой строки
	mov [EAX] , DL					; копируем в результирующую строку
	inc EDI							; следующий символ 1-ой строки
	inc EAX							; следующий символ результирующей строки

loop sum2							; в начало цикла 2

 mov DL,0h							; записываем
 mov [EAX], DL						; конец строки


jmp the_end


SLEN:
	push ESI
	push EDI
	push EAX

	mov ESI, stroka1					; указатель на начало 1-ой строки

	xor EDI,EDI						    ; длина строки (0)

	metka2:								; цикл
		mov AL, [ESI]					; смотрим символ
		cmp AL, 0h						; сравниваем с '\0'
		je skip1							; если равны, вылетаем
		inc EDI							; если нет, смотрим следующий символ
		inc ESI							; увеличиваем длину на 1
	loop metka2							; в начало цикла

	skip1:
		mov EDX, EDI					; возвращаем длину 1-ой строки


	mov ESI, stroka2					; указатель на начало 2-ой строки
	xor EAX,EAX							; обнуление регистра вывода
	xor EDI,EDI						    ; длина строки (0)

	metka3:								; цикл
		mov AL, [ESI]					; смотрим символ
		cmp AL, 0h						; сравниваем с '\0'
		je skip3						; если равны, вылетаем
		inc EDI							; если нет, смотрим следующий символ
		inc ESI							; увеличиваем длину на 1
	loop metka3							; в начало цикла

	skip3:
		mov EBX, EDI					; возвращаем длину 2-ой строки

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