#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int main()
{
	int i, j, min, *dizi, sayi;
	
	printf("Kac tane sayi girmek istiyorsunuz? > ");
	scanf("%d", &sayi);
	
	printf("Lutfen diziyi giriniz\n\n");
	
	dizi = (int*) malloc(sizeof(int) * sayi); // RAM'de (4 * sayi) kadar byte yer ayrilir
	
	for (i = 0; i < sayi; i++) // DIZIYI DOLDURMA
	{
		scanf("%d", &dizi[i]);
	}
	
	// OPTIMIZED SELECTION SORT
	
	for (i = 0; i < sayi - 1; i++)
	{
		min = i;
		
		for (j = min; j < sayi; j++)
		{
			if (dizi[min] > dizi[j])
			{
				min = j;
			}
		}
		
		// TAKAS
		
		if (dizi[i] != dizi[min]) // Sayılar aynıysa XOR kapısının sonucu 0 olur! Sayılarımızın kaybolmasını istemeyiz!
		{
			dizi[i] ^= dizi[min];
			dizi[min] ^= dizi[i];
			dizi[i] ^= dizi[min];
		}
		
		// TAKAS
	}
	
	// OPTIMIZED SELECTION SORT
	
	printf("\n\nDizinin yeni hali : ");
	
	for (i = 0; i < sayi; i++)
	{
		printf("%d ", dizi[i]);
	}
	
	free(dizi); // MEMORY LEAK KORUMASI
	
	getch();
	return 0;
}
