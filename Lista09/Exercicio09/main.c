#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));

    FILE *arquivo;
    arquivo = fopen("imagem9.pgm", "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    fprintf(arquivo, "P2\n");
    fprintf(arquivo, "#imagem9.pgm\n");
    fprintf(arquivo, "60 100\n");
    fprintf(arquivo, "255\n");

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 60; j++)
        {
            int n = 0;
            if (i < 20)
            {
                n = rand() % 56;
            }
            else if (i >= 20 && i < 40)
            {
                n = 45 + rand() % 61;
            }
            else if (i >= 40 && i < 60)
            {
                n = 95 + rand() % 61;
            }
            else if (i >= 60 && i < 80)
            {
                n = 145 + rand() % 61;
            }
            else if (i >= 80 && i < 100)
            {
                n = 195 + rand() % 61;
            }
            fprintf(arquivo, "%d ", n);
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);

    return 0;
}
