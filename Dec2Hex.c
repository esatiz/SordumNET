#include <stdio.h>
#include <conio.h>

char harf[16 + 1] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', '\0' };

void Dec2Hex(int sayi)
{
	if (sayi > 15)
	{
		Dec2Hex(sayi / 16);
	}

	printf("%c", harf[sayi % 16]);
}

int main()
{
	Dec2Hex(123);
	
	getch();
	return 0;
}
