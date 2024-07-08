#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *arquivo;
    arquivo = fopen("imagem7.pgm", "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    fprintf(arquivo, "P2\n");
    fprintf(arquivo, "#imagem7.pgm\n");
    fprintf(arquivo, "100 256\n");
    fprintf(arquivo, "255\n");

    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            fprintf(arquivo, "%d ", i);
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);

    return 0;
}
