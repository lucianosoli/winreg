#include "main.h"

int main(int argc, char *argv[])
{
	char buf[4096];
	FILE *registre;

	registre = NULL;
	registre = fopen("../../../registre/system", "r");

	if(registre == NULL)
	{
		fprintf(stderr, "Erreur d'ouverture de fichier\n");
		exit(0);
	}

	read_file(registre, buf, 4);

	printf("%d\n", nb_to_read(buf));

	return 0;
}

void read_file(FILE *stream, char *tmp, int n)
{
	int size_read;

	size_read = fread(tmp, 1, n, stream);
	tmp[size_read] = 0;
	rewind(stream);
}
