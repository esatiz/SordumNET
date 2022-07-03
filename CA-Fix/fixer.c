#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_LEN 260

int byte = 0;

int ConvertTUR(int ch)
{
	switch (ch)
	{
		case 'C':
			return 'Ç';
		
		case 'G':
			return 'Ğ';
		
		case 'I':
			return 'İ';
		
		case 'O':
			return 'Ö';
		
		case 'S':
			return 'Ş';
		
		case 'U':
			return 'Ü';
		
		case 'c':
			return 'ç';
		
		case 'g':
			return 'ğ';
		
		case 'i':
			return 'ı';
		
		case 'o':
			return 'ö';
		
		case 's':
			return 'ş';
		
		case 'u':
			return 'ü';
		
		default:
			return ch;
	}
}

unsigned int w[] =
{
	0xCC, 0xA7, // çş
		  0x88, // öü
		  0x87, // İ
		  0x86  // ğ
};

void RotateLeft(unsigned char *str, int x)
{
	unsigned int i, j, temp;
	
	for (temp = str[j = x]; j + 1 < byte; j++)
	{
		str[j] = str[j + 1];
	}
	
	str[j] = temp;
}

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Turkish");
	
	char dosya_adi[MAX_LEN + 1];
	
	if (argc != 2)
	{
		printf("Lütfen dosya adını yazınız > ");
		gets(dosya_adi); // Lütfen çok uzun yazı yazmayınız!
	}
	else strcpy(dosya_adi, argv[1]);
	
	FILE *source = fopen(dosya_adi, "rb");
	
	if (source == NULL)
	{
		printf("Dosya açılamıyor!");
		
		getch();
		exit(0);
	}
	
	unsigned char k, *str = NULL;
	int i, j, counter = 0;
	
	while (k = fgetc(source) != EOF)
	{
		byte++;
	}
	
	str = (unsigned char*) malloc(byte * sizeof(char));
	
	rewind(source);
	
	for (i = 0; i < byte; i++)
	{
		str[i] = fgetc(source) & 255;
	}
	
	fclose(source);
	
	for (i = 0; i < byte; i++)
	{
		if (str[i] == 0xC3 && str[i + 1] == 0x87) // Ç
		{
			str[i] = 0xC7;
			str[i + 1] = 32;
			
			RotateLeft(str, i + 1);
			counter++;
		}
		else if (str[i] == 0xC3 && str[i + 1] == 0xB6) // ö
		{
			str[i] = 0xF6;
			str[i + 1] = 32;
			
			RotateLeft(str, i + 1);
			counter++;
		}
		else if (str[i] == 0xC3 && str[i + 1] == 0x96) // Ö
		{
			str[i] = 0xD6;
			str[i + 1] = 32;
			
			RotateLeft(str, i + 1);
			counter++;
		}
		else if (str[i] == 0xC4 && str[i + 1] == 0xB1) // ı
		{
			str[i] = 0xFD;
			str[i + 1] = 32;
			
			RotateLeft(str, i + 1);
			counter++;
		}
		else if (str[i] == 0xC3 && str[i + 1] == 0xBC) // ü
		{
			str[i] = 0xFC;
			str[i + 1] = 32;
			
			RotateLeft(str, i + 1);
			counter++;
		}
		else if (str[i] == 0xC4 && str[i + 1] == 0xB0) // İ
		{
			str[i] = 0xDD;
			str[i + 1] = 32;
			
			RotateLeft(str, i + 1);
			counter++;
		}
		else if (str[i] == 0xC5 && str[i + 1] == 0x9F) // ş
		{
			str[i] = 0xFE;
			str[i + 1] = 32;
			
			RotateLeft(str, i + 1);
			counter++;
		}
		else if (str[i] == 0xC4 && str[i + 1] == 0x9F) // ğ
		{
			str[i] = 0xF0;
			str[i + 1] = 32;
			
			RotateLeft(str, i + 1);
			counter++;
		}
		else if (str[i] == 0xC3 && str[i + 1] == 0x9C) // Ü
		{
			str[i] = 0xDC;
			str[i + 1] = 32;
			
			RotateLeft(str, i + 1);
			counter++;
		}
		else if (str[i] == 0xC3 && str[i + 1] == 0xA7) // ç
		{
			str[i] = 0xE7;
			str[i + 1] = 32;
			
			RotateLeft(str, i + 1);
			counter++;
		}
		else if ((str[i] == w[0] && str[i + 1] == w[1]) || (str[i] == w[0] && str[i + 1] == w[2]) || (str[i] == w[0] && str[i + 1] == w[3]) || (str[i] == w[0] && str[i + 1] == w[4]))
		{
			str[i - 1] = ConvertTUR(str[i - 1]);
			
			str[i] = str[i + 1] = 32;
			
			RotateLeft(str, i);
			RotateLeft(str, i);
			
			counter += 2;
			i--;
		}
	}
	
	char yeni_isim[MAX_LEN + 1];
	
	for (j = strlen(dosya_adi) - 1; dosya_adi[j] != '.'; j--);
	
	for (i = 0; i < j; i++)
	{
		yeni_isim[i] = dosya_adi[i];
	}
	
	strcat(yeni_isim, "_duzgun.txt");
	
	FILE *yeni = fopen(yeni_isim, "wb");
	
	if (yeni == NULL)
	{
		printf("Dosya oluşturulamıyor!");
		
		getch();
		exit(0);
	}
	
	for (i = 0; i < byte - counter; i++)
	{
		fprintf(yeni, "%c", str[i]);
	}
	
	fclose(yeni);
	
	return 0;
}
