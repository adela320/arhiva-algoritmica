#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		fprintf(stderr, "Nr incorect de argumente");
		exit(1);
	}
	for(int i = 1; i < argc; i ++)
	{
		for(int j = 0; argv[i][j] != '\0'; j ++)
		{
			if(!isdigit(argv[i][j]))
			{
			     fprintf(stderr, "Argumentele trebuie sa fie numere");
			     exit(1);
			}
		}
	}

	int s = 0;
	for(int i = 1; i < argc; i ++)
	{
		 int num = atoi(argv[i]);
         s = s + num;
	}
	printf("Suma este %d\n", s);
	return 0;
}
