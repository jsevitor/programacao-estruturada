#include <stdio.h>

int main()
{
    FILE *entrada, *saida;
    entrada = fopen("tucano.ppm", "r");
    saida = fopen("tucano_negativo.ppm", "w");

    int i, j, k;
    int largura, altura, v_max;
    char buffer[255];

    if (entrada == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    else
    {
        // Leitura do cabeçalho
        fgets(buffer, 255, entrada);  // P3
        fprintf(saida, "%s", buffer); // Escreve P3 no arquivo de saída
        fgets(buffer, 255, entrada);  // Comentários
        fprintf(saida, "%s", buffer); // Escreve o comentário no arquivo de saída

        fscanf(entrada, "%d %d", &largura, &altura); // Largura e Altura
        fprintf(saida, "%d %d\n", largura, altura);  // Escreve largura e altura no arquivo de saída
        fscanf(entrada, "%d", &v_max);               // Valor máximo
        fprintf(saida, "%d\n", v_max);               // Escreve o valor máximo no arquivo de saída

        int matriz[altura][largura][3];

        // Leitura dos pixels da imagem
        for (i = 0; i < altura; i++)
        {
            for (j = 0; j < largura; j++)
            {
                for (k = 0; k < 3; k++)
                {
                    fscanf(entrada, "%d", &matriz[i][j][k]);
                }
            }
        }

        // Escrita do arquivo de saída com o negativo da imagem
        for (i = 0; i < altura; i++)
        {
            for (j = 0; j < largura; j++)
            {
                for (k = 0; k < 3; k++)
                {
                    fprintf(saida, "%d ", 255 - matriz[i][j][k]);
                }
            }
            fprintf(saida, "\n");
        }

        printf("Arquivo negativo gerado com sucesso.\n");
        fclose(entrada);
        fclose(saida);
    }
    return 0;
}
