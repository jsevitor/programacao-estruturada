#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *arquivo;
    arquivo = fopen("imagem8.pgm", "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    fprintf(arquivo, "P2\n");
    fprintf(arquivo, "#imagem8.pgm\n");
    fprintf(arquivo, "60 100\n");
    fprintf(arquivo, "255\n");

    int tons[] = {0, 64, 128, 192, 255};

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            for (int k = 0; k < 60; k++)
            {
                fprintf(arquivo, "%d ", tons[i]);
            }
            fprintf(arquivo, "\n");
        }
    }

    fclose(arquivo);

    return 0;
}
