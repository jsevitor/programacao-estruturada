#include <stdio.h>

void escreverCabecalho(FILE *arquivo, int largura, int altura, int v_max, char *comentario)
{
    fprintf(arquivo, "P3\n");                     // Tipo de imagem
    fprintf(arquivo, "# %s", comentario);         // Comentário
    fprintf(arquivo, "%d %d\n", largura, altura); // Largura e altura
    fprintf(arquivo, "%d\n", v_max);              // Valor máximo de cor
}

void copiarPixels(FILE *saida, int matriz[][3], int largura)
{
    for (int j = 0; j < largura; j++)
    {
        for (int k = 0; k < 3; k++)
        {
            fprintf(saida, "%d ", matriz[j][k]);
        }
    }
    fprintf(saida, "\n");
}

int main()
{
    FILE *entrada;
    entrada = fopen("tucano.ppm", "r");
    if (entrada == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int i, j, k;
    int largura, altura, v_max;
    char buffer[255];

    // Leitura do cabeçalho
    fgets(buffer, 255, entrada); // P3
    char comentario[255];
    fgets(comentario, 255, entrada); // Comentário

    fscanf(entrada, "%d %d", &largura, &altura); // Largura e altura
    fscanf(entrada, "%d", &v_max);               // Valor máximo

    // Dimensões dos quadrantes
    int metadeLargura = largura / 2;
    int metadeAltura = altura / 2;

    // Abertura dos arquivos de saída
    FILE *saida1 = fopen("superior_esquerdo.ppm", "w");
    FILE *saida2 = fopen("superior_direito.ppm", "w");
    FILE *saida3 = fopen("inferior_esquerdo.ppm", "w");
    FILE *saida4 = fopen("inferior_direito.ppm", "w");

    // Escrever cabeçalho nos arquivos de saída
    escreverCabecalho(saida1, metadeLargura, metadeAltura, v_max, comentario);
    escreverCabecalho(saida2, metadeLargura, metadeAltura, v_max, comentario);
    escreverCabecalho(saida3, metadeLargura, metadeAltura, v_max, comentario);
    escreverCabecalho(saida4, metadeLargura, metadeAltura, v_max, comentario);

    int linha[largura][3];

    // Leitura e divisão da imagem
    for (i = 0; i < altura; i++)
    {
        for (j = 0; j < largura; j++)
        {
            for (k = 0; k < 3; k++)
            {
                fscanf(entrada, "%d", &linha[j][k]);
            }
        }

        if (i < metadeAltura)
        {
            // Metade superior
            copiarPixels(saida1, linha, metadeLargura);                 // Superior esquerdo
            copiarPixels(saida2, &linha[metadeLargura], metadeLargura); // Superior direito
        }
        else
        {
            // Metade inferior
            copiarPixels(saida3, linha, metadeLargura);                 // Inferior esquerdo
            copiarPixels(saida4, &linha[metadeLargura], metadeLargura); // Inferior direito
        }
    }

    printf("Imagens quadrantes geradas com sucesso.\n");

    // Fechamento dos arquivos
    fclose(entrada);
    fclose(saida1);
    fclose(saida2);
    fclose(saida3);
    fclose(saida4);

    return 0;
}
