#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));

    FILE *arquivo;
    arquivo = fopen("imagem10.ppm", "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    fprintf(arquivo, "P3\n");
    fprintf(arquivo, "#imagem10.ppm\n");
    fprintf(arquivo, "60 100\n");
    fprintf(arquivo, "255\n");

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 60; j++)
        {
            int r, g, b;

            if (i < 20)
            {
                r = rand() % 56;
                g = rand() % 56;
                b = rand() % 56;
            }
            else if (i >= 20 && i < 40)
            {
                r = 45 + rand() % 61;
                g = 45 + rand() % 61;
                b = 45 + rand() % 61;
            }
            else if (i >= 40 && i < 60)
            {
                r = 95 + rand() % 61;
                g = 95 + rand() % 61;
                b = 95 + rand() % 61;
            }
            else if (i >= 60 && i < 80)
            {
                r = 145 + rand() % 61;
                g = 145 + rand() % 61;
                b = 145 + rand() % 61;
            }
            else if (i >= 80 && i < 100)
            {
                r = 195 + rand() % 61;
                g = 195 + rand() % 61;
                b = 195 + rand() % 61;
            }

            fprintf(arquivo, "%d %d %d ", r, g, b);
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);

    return 0;
}
