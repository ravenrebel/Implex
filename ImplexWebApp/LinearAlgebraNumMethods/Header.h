#pragma once

void ASM(double** a, double** b, double** res, int n, int p, int m)
{
	// АСЕМБЛЕРНА ВСТАВКА (алгоритм множення матриць) 
   // Для зручності цикли записано на С++
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < p; j++)
		{
			__asm
			{
				// створити доступ до елемента res[i][j]
				mov edx, res // edx = res
				mov esi, i // esi = index k
				imul esi, 4 // *кі-сть байтів (0 * 4, 1 * 4...)
				add edx, esi // edx = &res[i] - адреса 
				push[edx] // заштовхуємо в стек нову адресу 
				pop edx // edx = res[i]

				mov esi, j
				imul esi, 4
				add edx, esi // edx = &res[i][j]
				push edx // заштовхуємо в стек нову адресу 
				xor esi, esi // esi = 0 

				mov ecx, m // к-сть проходів циклу

				start : // початок циклу

				// записуємо у регістри початкові елементи масивів
					mov eax, a // eax = a
					mov ebx, b

					a_to_eax :
					mov edx, i
					mov eax, [eax + 8 * edx] // eax = a[i] 
					mov edx, esi
					mov eax, [eax + 8 * edx] // eax = a[i][esi] 

					b_to_ebx :
					mov edx, esi
					mov ebx, [ebx + 8 * edx] // ebx = b[esi] 
					mov edx, j
					mov ebx, [ebx + 8 * edx] // ebx = b[esi][j]

					end :
					pop edx
					imul eax, ebx // eax = a[i][esi]*b[esi][j] 
					add[edx], eax
					push edx
					inc esi // ++
					loop start
					pop edx

					mov edx, res // edx = res
					mov esi, j // esi = index k
					imul esi, 4 // *кі-сть байтів (0 * 4, 1 * 4...)
					add edx, esi // edx = &res[i] - адреса 
					push[edx] // заштовхуємо в стек нову адресу 
					pop edx // edx = res[j]
					mov esi, i
					imul esi, 4
					add edx, esi // edx = &res[j][i]
					push edx // заштовхуємо в стек нову адресу 
					mov eax, res // eax = res
					mov edx, i
					mov eax, [eax + 8 * edx] // eax = res[i] 
					mov edx, j
					mov eax, [eax + 8 * edx] // eax = res[i][j] 
					pop edx

					mov ecx, j
					mov ebx, i
					cmp ebx, ecx
					jne equals
					jmp result

					equals :
					add[edx], eax // res[j][i] = res[i][j]

					result :
					push edx
					pop edx
			}
		}
	}
}