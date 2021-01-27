;Name: Lucas Kehoe
;Date: 12/01/2020

	section .bss
character: resb 1			;1 byte is the size of 1 character
num: resb 11				;max signed 32-bit number is 2147483647
					;min signed 32-bit number is -2147483647 which is 11 characters
					;so there is possibility user can overflow

	section .data
buffer: db 0
endline: db 0xa

	section .text
	global _start
	
_start:
	mov eax, 0x0			;initialize eax = 0
mainloop:
	call readInput			;get user input
	call evaluateInput		;perform action if valid code
	
	cmp byte [character], 'q'	;check if quit	
	jne mainloop			;if not quit, loop back
quit:
	mov eax, 1
	mov ebx, 0
	int 0x80
	
readInput:
	mov esi, eax			;back up eax
	
	mov eax, 3			;read user input into character
	mov ebx, 0			;stdin
	mov ecx, character		;destination
	mov edx, 1			;length
	int 0x80	
	
	mov eax, esi			;restore eax
	ret
	
evaluateInput:
	cmp byte [character], 's'	;check if store
	je store
	cmp byte [character], 'n'	;check if negate
	je negate
	cmp byte [character], '+'	;check if add
	je add
	cmp byte [character], '-'	;check if subtract
	je subtract
	cmp byte [character], '*'	;check if multiply
	je multiply
	cmp byte [character], '/'	;check if divide
	je divide
	cmp byte [character], 'd'	;check if print base 10
	je printbase10
	cmp byte [character], 'b'	;check if print base 2
	je printbase2
	ret
	
store:
	call readEBX			;read value into ebx
	mov eax, ebx			;mov ebx -> eax
	ret
	
negate:
	neg eax			;negate eax
	ret
	
add:
	call readEBX			;read value into ebx
	add eax, ebx			;eax = eax+ebx
	ret
	
subtract:
	call readEBX			;read value into ebx
	sub eax, ebx			;eax = eax-ebx
	ret
	
multiply:
	call readEBX			;read value into ebx
	imul ebx			;eax = eax*ebx
	ret
	
divide:
	call readEBX			;read value into ebx
	cmp ebx, 0x0			;check if ebx is 0 -DIVIDE BY 0
	je quit			;if it is, quit
	mov edx, 0x0			;set edx = 0
	idiv ebx			;eax = eax/ebx
	ret
	
printbase10:
	call printEAX10		;print eax in base 10
	ret
	
printbase2:
	call printEAX2			;print eax in base 2
	ret

readEBX:
	mov edi, eax			;back up eax

	mov eax, 3			;read
	mov ebx, 0			;stdin
	mov ecx, num			;start of storage
	mov edx, 11			;# chars
	int 0x80
	
	mov ecx, edi			;mov edi(eax) -> ecx for safe keeping
	mov eax, 0x0			;set eax = 0
	mov edi, 0x0			;counter to 0
	
	movzx esi, byte [num+edi]	;mov first character into esi			
	cmp esi, '-'			;check if first character is '-'
	jne readpos			;if not jump to readpos
	inc edi			;counter++
readneg:
	movzx esi, byte [num+edi]	;mov next character into esi
	inc edi			;counter++
	
	cmp esi, 0x0			;check if null character
	je readneg			;loop back
	cmp esi, '0'			;check if digit<0
	jl endreadneg			;if <0 end
	cmp esi, '9'			;check if digit>9
	jg endreadneg			;if >9 end
	
	sub esi, '0'			;subtract '0'(48) from ascii value
	mov ebx, 0xa			;set ebx = 10
	mul ebx			;eax = eax*10
	add eax, esi			;eax = eax+digit
	
	jmp readneg			;loop
readpos:
	movzx esi, byte [num+edi]	;mov next character into esi
	inc edi			;counter++
	
	cmp esi, 0x0			;check if null character
	je readneg			;loop back
	cmp esi, '0'			;check if digit<0
	jl endreadpos			;if <0 end
	cmp esi, '9'			;check if digit>9
	jg endreadpos			;if >9 end
	
	sub esi, '0'			;subtract '0'(48) from ascii value
	mov ebx, 0xa			;set ebx = 10
	mul ebx			;eax = eax*10
	add eax, esi			;eax = eax+digit
	
	jmp readpos			;loop
endreadneg:
	neg eax			;negate eax
endreadpos:
	mov ebx, eax			;move eax -> ebx
	mov eax, ecx			;restore eax
	ret

printEAX10:
	mov esi, eax			;back up eax
	cmp eax, 0x0			;compare to 0
	jge dumpNumber			;jump to dumpNumber if >=0
	mov byte [buffer], '-'		;write '-'
	mov eax, 4			;write
	mov ebx, 1			;stdout
	mov ecx, buffer		;start of storage
	mov edx, 1			;# chars
	int 0x80
	mov eax, esi			;restore eax
	neg eax			;print pos version of eax
dumpNumber:
	mov edi, 0x0			;edi digit counter
extractDigit:
	inc edi			;edi++ (counter++)
	mov ebx, 0xa			;divisor == 10
	mov edx, 0x0			;set edx == 0
	div ebx			;eax/ebx, edx is remainder
	push rdx			;push next digit onto stack
	cmp eax, 0x0			;compare to 0
	jne extractDigit		;if not, attempt again
printDigitFromStack:
	pop rdx			;pop next digit from stack
	dec edi			;edi-- (counter--)
	add dl, '0'			;turn int into ascii character
	mov [buffer], dl		;get next digit from dl
	mov eax, 4			;write
	mov ebx, 1			;stdout
	mov ecx, buffer		;start of storage
	mov edx, 1			;# chars
	int 0x80
	cmp edi, 0x0			;compare to 0
	jne printDigitFromStack	;if not 0, pop next value

	mov eax, 4			;write -print new line
	mov ebx, 1			;stdout
	mov ecx, endline		;start of storage
	mov edx, 2			;# chars
	int 0x80
	
	mov eax, esi			;restore eax
	ret
	
printEAX2:
	mov esi, eax			;back up eax
	mov edi, 0x0			;edi digit counter
extractDigit2:
	inc edi			;edi++ (counter++)
	mov ebx, 0x2			;divisor == 2
	mov edx, 0x0			;set edx == 0
	div ebx			;eax/ebx, edx is remainder
	push rdx			;push next digit onto stack
	cmp edi, 0x20			;compare to 32
	jl extractDigit2		;if not, attempt again
	
printDigitFromStack2:
	pop rdx			;pop next digit from stack
	dec edi			;edi-- (counter--)
	add dl, '0'			;turn int into ascii character
	mov [buffer], dl		;get next digit from dl
	mov eax, 4			;write
	mov ebx, 1			;stdout
	mov ecx, buffer		;start of storage
	mov edx, 1			;# chars
	int 0x80
	cmp edi, 0x0			;compare to 0
	jne printDigitFromStack2	;if not 0, pop next value

	mov eax, 4			;write -print new line
	mov ebx, 1			;stdout
	mov ecx, endline		;start of storage
	mov edx, 2			;# chars
	int 0x80
	
	mov eax, esi			;restore eax
	ret
