#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));

    FILE *arquivo;
    arquivo = fopen("imagem6.pgm", "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    fprintf(arquivo, "P2\n");
    fprintf(arquivo, "#imagem6.pgm\n");
    fprintf(arquivo, "100 100\n");
    fprintf(arquivo, "255\n");

    for (int i = 0; i < 100; i++)
    {
        int n = rand() % 256;
        for (int j = 0; j < 100; j++)
        {
            fprintf(arquivo, "%d ", n);
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);

    return 0;
}
