#include <stdio.h>
#include <conio.h>

int main()
{
	int i;
	char text[255];
	
	fgets(text, 255, stdin);
	
	printf("\nhttps://drive.google.com/uc?export=download&id=");
	
	for (i = 32; text[i] != '/'; i++)
	{
		printf("%c", text[i]);
	}
	
	getch();
	return 0;
}
