#include "main.h"

int addr;
int READ_SIZE = 0;

int main(int argc, char *argv[])
{
	char buf[4096];
	FILE *registre;
	File_base_bloc *fbc;
	Hive_bin_header *hbh;
	Key_node *nk;

	bzero(buf, 4096);
	registre = NULL;
//	registre = fopen("../../../registre/system", "r");
	registre = fopen("../../registre/system", "r");

	if(registre == NULL)
	{
		fprintf(stderr, "Erreur d'ouverture de fichier\n");
		exit(0);
	}

	read_file(registre, buf, 4, 0);
	read_file(registre, buf, nb_to_read(buf), 0);
	fbc = read_file_base_bloc(buf);

	read_file(registre, buf, nb_to_read(buf), 4096);
	hbh = read_hive_bin_header(buf);

	printf("Size: %d\n", read_cell(buf, 32));

	nk = read_key_node(buf, 32+4, read_cell(buf, 32));
//	print_hex(buf, 50);
	printf("%s\n", nk->key_name);
	

//	print_hex(buf, READ_SIZE);
	print_hex(buf, 4096);

	return 0;
}

int read_file(FILE *stream, char *tmp, int n, long offset)
{
	int size_read;

	READ_SIZE = n;

	fseek(stream, offset, SEEK_SET);

	size_read = fread(tmp, 1, n, stream);
	tmp[size_read] = 0;

	fseek(stream, 0, SEEK_END);

	return 0;
}

void print_hex(char *s, int count)
{
/*
	Print strings in hex format by 4 Bits bloc
	(16 Bits per line)
*/
	int i;

	printf("%08X   ", addr);

	for(i=0; i<count; i++, addr++)
	{
		print_hex_car(s[i]);

		if((i+1)%32 == 0 && i != 0)
		{
			printf("  ");
			print_display_strings(&s[i-31], 32);
			printf("\n");
			if(i < READ_SIZE)
				printf("%08X   ", addr);
		}
		else if((i+1)%4 == 0 && i !=0)
			printf("  ");
		else
			printf(" ");
	}

	printf("\t\t");
	print_display_strings(&s[i-(i%32)], i%32);
	printf("\n");
}

void print_display_strings(char *s, int count)
{
/*
	Print @count caracter to a printable format
	If non printable caracter print .

	riquiere library <ctype.h>
*/
	int i;

	for(i=0; i<count; i++)
	{
		if(isprint(s[i]))
			printf("%c", s[i]);
		else
			printf(".");
	}
}

void print_hex_car(char c)
{
/*
	Print a caracter in hex format
*/
	printf("%02X", c & 0xFF);
}
