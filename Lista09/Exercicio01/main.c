#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n = 0;
    srand(time(NULL));

    FILE *arquivo;
    arquivo = fopen("imagem.pbm", "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    fprintf(arquivo, "P1\n");
    fprintf(arquivo, "#imagem.pbm\n");
    fprintf(arquivo, "100 100\n");

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            n = rand() % 2;
            fprintf(arquivo, "%d", n);
        }
        printf("\n");
    }

    fclose(arquivo);

    return 0;
}