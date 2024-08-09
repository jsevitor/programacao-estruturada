/*
 * Trabalho Final Parte 2 de Programação Estruturada
 *
 * Autores: José Vitor Oliveira Reis e Vinícius Nunes de Lima Gabriel
 * Data: 9 de agosto de 2024
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int escalaCinza()
{
    int largura, altura, valor_maximo;
    char buffer[255];

    FILE *arquivo = fopen("imagem.ppm", "r");
    FILE *saida = fopen("imagem_cinza.ppm", "w");

    if (arquivo == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        return 1;
    }

    // Leitura do cabeçalho do arquivo PPM
    fgets(buffer, sizeof(buffer), arquivo);
    fprintf(saida, "%s", buffer);

    fgets(buffer, sizeof(buffer), arquivo);
    fprintf(saida, "%s", buffer);

    fscanf(arquivo, "%d %d", &largura, &altura);
    fprintf(saida, "%d %d\n", largura, altura);

    fscanf(arquivo, "%d", &valor_maximo);
    fprintf(saida, "%d\n", valor_maximo);

    // Alocação dinâmica da matriz para evitar problemas de tamanho
    int ***matriz = (int ***)malloc(altura * sizeof(int **));
    for (int i = 0; i < altura; i++)
    {
        matriz[i] = (int **)malloc(largura * sizeof(int *));
        for (int j = 0; j < largura; j++)
        {
            matriz[i][j] = (int *)malloc(3 * sizeof(int));
        }
    }

    // Leitura dos pixels da imagem colorida
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            fscanf(arquivo, "%d %d %d", &matriz[i][j][0], &matriz[i][j][1], &matriz[i][j][2]);
        }
    }

    // Conversão para escala de cinza e escrita no arquivo de saída
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            int pixel = (matriz[i][j][0] + matriz[i][j][1] + matriz[i][j][2]) / 3;
            fprintf(saida, "%d %d %d ", pixel, pixel, pixel);
        }
        fprintf(saida, "\n");
    }

    // Liberação da memória alocada
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            free(matriz[i][j]);
        }
        free(matriz[i]);
    }
    free(matriz);

    printf("Imagem convertida com sucesso!\n");
    fclose(arquivo);
    fclose(saida);

    return 0;
}

int inverteHorizontal()
{
    FILE *entrada, *saida;
    entrada = fopen("imagem.ppm", "r");
    saida = fopen("imagem_virado_horizontal.ppm", "w");

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
        fgets(buffer, 255, entrada);
        fprintf(saida, "%s", buffer);
        fgets(buffer, 255, entrada);
        fprintf(saida, "%s", buffer);

        fscanf(entrada, "%d %d", &largura, &altura);
        fprintf(saida, "%d %d\n", largura, altura);
        fscanf(entrada, "%d", &v_max);
        fprintf(saida, "%d\n", v_max);

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

        // Escrita do arquivo de saída com espelhamento horizontal
        for (i = 0; i < altura; i++)
        {
            for (j = largura - 1; j >= 0; j--)
            {
                // Inverte horizontalmente
                for (k = 0; k < 3; k++)
                {
                    fprintf(saida, "%d ", matriz[i][j][k]);
                }
            }
            fprintf(saida, "\n");
        }

        printf("Imagem invertida com sucesso.\n");
        fclose(entrada);
        fclose(saida);
    }
    return 0;
}

int inverteVertical()
{
    FILE *entrada, *saida;
    entrada = fopen("imagem.ppm", "r");
    saida = fopen("imagem_virado_vertical.ppm", "w");

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
        fgets(buffer, 255, entrada);
        fprintf(saida, "%s", buffer);
        fgets(buffer, 255, entrada);
        fprintf(saida, "%s", buffer);

        fscanf(entrada, "%d %d", &largura, &altura);
        fprintf(saida, "%d %d\n", largura, altura);
        fscanf(entrada, "%d", &v_max);
        fprintf(saida, "%d\n", v_max);

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

        // Escrita do arquivo de saída com espelhamento vertical
        for (i = altura - 1; i >= 0; i--)
        {
            // Inverte verticalmente
            for (j = 0; j < largura; j++)
            {
                for (k = 0; k < 3; k++)
                {
                    fprintf(saida, "%d ", matriz[i][j][k]);
                }
            }
            fprintf(saida, "\n");
        }

        printf("Imagem inveritda com sucesso.\n");
        fclose(entrada);
        fclose(saida);
    }
    return 0;
}

int divisaoVertical()
{
    FILE *entrada, *saidaEsquerda, *saidaDireita;
    entrada = fopen("imagem.ppm", "r");
    saidaEsquerda = fopen("imagem_metade_esquerda.ppm", "w");
    saidaDireita = fopen("imagem_metade_direita.ppm", "w");

    if (entrada == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int largura, altura, v_max;
    char buffer[255];

    // Leitura do cabeçalho
    fgets(buffer, 255, entrada);
    fprintf(saidaEsquerda, "%s", buffer);
    fprintf(saidaDireita, "%s", buffer);

    fgets(buffer, 255, entrada);
    fprintf(saidaEsquerda, "%s", buffer);
    fprintf(saidaDireita, "%s", buffer);

    fscanf(entrada, "%d %d", &largura, &altura);
    fprintf(saidaEsquerda, "%d %d\n", largura / 2, altura);
    fprintf(saidaDireita, "%d %d\n", largura / 2, altura);

    fscanf(entrada, "%d", &v_max);
    fprintf(saidaEsquerda, "%d\n", v_max);
    fprintf(saidaDireita, "%d\n", v_max);

    int matriz[largura][3];

    // Processamento dos pixels
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                fscanf(entrada, "%d", &matriz[j][k]);
            }
        }

        // Gravar metade esquerda
        for (int j = 0; j < largura / 2; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                fprintf(saidaEsquerda, "%d ", matriz[j][k]);
            }
        }
        fprintf(saidaEsquerda, "\n");

        // Gravar metade direita
        for (int j = largura / 2; j < largura; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                fprintf(saidaDireita, "%d ", matriz[j][k]);
            }
        }
        fprintf(saidaDireita, "\n");
    }

    printf("Imagem dividida com sucesso.\n");

    fclose(entrada);
    fclose(saidaEsquerda);
    fclose(saidaDireita);

    return 0;
}

int divisaoHorizontal()
{
    FILE *entrada, *saidaSuperior, *saidaInferior;
    entrada = fopen("imagem.ppm", "r");
    saidaSuperior = fopen("imagem_metade_superior.ppm", "w");
    saidaInferior = fopen("imagem_metade_inferior.ppm", "w");

    if (entrada == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int largura, altura, v_max;
    char buffer[255];

    // Leitura do cabeçalho
    fgets(buffer, 255, entrada); // Tipo P3
    fprintf(saidaSuperior, "%s", buffer);
    fprintf(saidaInferior, "%s", buffer);

    fgets(buffer, 255, entrada); // Comentário
    fprintf(saidaSuperior, "%s", buffer);
    fprintf(saidaInferior, "%s", buffer);

    fscanf(entrada, "%d %d", &largura, &altura); // Largura e altura
    fprintf(saidaSuperior, "%d %d\n", largura, altura / 2);
    fprintf(saidaInferior, "%d %d\n", largura, altura / 2);

    fscanf(entrada, "%d", &v_max); // Valor máximo
    fprintf(saidaSuperior, "%d\n", v_max);
    fprintf(saidaInferior, "%d\n", v_max);

    int linha[largura][3];

    // Processamento dos pixels
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                fscanf(entrada, "%d", &linha[j][k]);
            }
        }

        if (i < altura / 2)
        {
            // Gravar metade superior
            for (int j = 0; j < largura; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    fprintf(saidaSuperior, "%d ", linha[j][k]);
                }
            }
            fprintf(saidaSuperior, "\n");
        }
        else
        {
            // Gravar metade inferior
            for (int j = 0; j < largura; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    fprintf(saidaInferior, "%d ", linha[j][k]);
                }
            }
            fprintf(saidaInferior, "\n");
        }
    }

    printf("Imagem dividida com sucesso.\n");

    fclose(entrada);
    fclose(saidaSuperior);
    fclose(saidaInferior);

    return 0;
}

int colorirArtificialmente()
{
    int largura, altura, valor_maximo;
    char buffer[255];

    // Abrindo o arquivo de imagem PPM para leitura e o arquivo de saída para escrita
    FILE *arquivo = fopen("imagem.ppm", "r");
    FILE *saida = fopen("imagem_colorida_artificial.ppm", "w");

    if (arquivo == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        return 1;
    }

    // Leitura do cabeçalho do arquivo PPM
    fgets(buffer, sizeof(buffer), arquivo);
    fprintf(saida, "%s", buffer);

    fgets(buffer, sizeof(buffer), arquivo);
    fprintf(saida, "%s", buffer);

    fscanf(arquivo, "%d %d", &largura, &altura);
    fprintf(saida, "%d %d\n", largura, altura);

    fscanf(arquivo, "%d", &valor_maximo);
    fprintf(saida, "%d\n", valor_maximo);

    // Alocação dinâmica para armazenar os pixels em escala de cinza
    int **cinza = (int **)malloc(altura * sizeof(int *));
    for (int i = 0; i < altura; i++)
    {
        cinza[i] = (int *)malloc(largura * sizeof(int));
    }

    // Geração de seis cores aleatórias
    int cores[6][3];
    srand(time(NULL));
    for (int i = 0; i < 6; i++)
    {
        cores[i][0] = rand() % 256; // Red
        cores[i][1] = rand() % 256; // Green
        cores[i][2] = rand() % 256; // Blue
    }

    // Conversão da imagem colorida para escala de cinza
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            int r, g, b;
            fscanf(arquivo, "%d %d %d", &r, &g, &b);
            cinza[i][j] = (r + g + b) / 3; // Cálculo do valor de cinza
        }
    }

    // Aplicação das cores artificiais
    int partHeight = altura / 6; // Divisão da imagem em seis partes
    for (int i = 0; i < altura; i++)
    {
        int colorIndex = i / partHeight;
        if (colorIndex >= 6)
            colorIndex = 5; // Ajuste para casos onde a altura não é múltipla de 6

        for (int j = 0; j < largura; j++)
        {
            int pixelCinza = cinza[i][j];
            fprintf(saida, "%d %d %d ",
                    (pixelCinza * cores[colorIndex][0]) / 255, // Aplicação da cor aleatória
                    (pixelCinza * cores[colorIndex][1]) / 255,
                    (pixelCinza * cores[colorIndex][2]) / 255);
        }
        fprintf(saida, "\n");
    }

    // Liberação da memória alocada
    for (int i = 0; i < altura; i++)
    {
        free(cinza[i]);
    }
    free(cinza);

    printf("Imagem colorida com sucesso!\n");
    fclose(arquivo);
    fclose(saida);

    return 0;
}

int rotacionar90direita()
{
    int largura, altura, valor_maximo;
    char buffer[255];

    // Abrindo o arquivo de imagem PPM para leitura e o arquivo de saída para escrita
    FILE *arquivo = fopen("imagem.ppm", "r");
    FILE *saida = fopen("imagem_rotacionada_direita.ppm", "w");

    if (arquivo == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        return 1;
    }

    // Leitura do cabeçalho do arquivo PPM
    fgets(buffer, sizeof(buffer), arquivo);
    fprintf(saida, "%s", buffer);

    fgets(buffer, sizeof(buffer), arquivo);
    fprintf(saida, "%s", buffer);

    fscanf(arquivo, "%d %d", &largura, &altura);
    fprintf(saida, "%d %d\n", altura, largura);

    fscanf(arquivo, "%d", &valor_maximo);
    fprintf(saida, "%d\n", valor_maximo);

    // Alocação dinâmica para armazenar os pixels da imagem original
    int ***pixels = (int ***)malloc(altura * sizeof(int **));
    for (int i = 0; i < altura; i++)
    {
        pixels[i] = (int **)malloc(largura * sizeof(int *));
        for (int j = 0; j < largura; j++)
        {
            pixels[i][j] = (int *)malloc(3 * sizeof(int)); // Alocando para RGB
        }
    }

    // Leitura dos pixels da imagem
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            fscanf(arquivo, "%d %d %d", &pixels[i][j][0], &pixels[i][j][1], &pixels[i][j][2]);
        }
    }

    // Rotacionando a imagem 90 graus para a direita
    for (int i = 0; i < largura; i++)
    {
        for (int j = 0; j < altura; j++)
        {
            fprintf(saida, "%d %d %d ",
                    pixels[altura - 1 - j][i][0],
                    pixels[altura - 1 - j][i][1],
                    pixels[altura - 1 - j][i][2]);
        }
        fprintf(saida, "\n");
    }

    // Liberação da memória alocada
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            free(pixels[i][j]);
        }
        free(pixels[i]);
    }
    free(pixels);

    printf("Imagem rotacionada sucesso!\n");
    fclose(arquivo);
    fclose(saida);

    return 0;
}

int rotacionar90esquerda()
{
    int largura, altura, valor_maximo;
    char buffer[255];

    // Abrindo o arquivo de imagem PPM para leitura e o arquivo de saída para escrita
    FILE *arquivo = fopen("imagem.ppm", "r");
    FILE *saida = fopen("imagem_rotacionada_esquerda.ppm", "w");

    if (arquivo == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        return 1;
    }

    // Leitura do cabeçalho do arquivo PPM
    fgets(buffer, sizeof(buffer), arquivo);
    fprintf(saida, "%s", buffer);

    fgets(buffer, sizeof(buffer), arquivo);
    fprintf(saida, "%s", buffer);

    fscanf(arquivo, "%d %d", &largura, &altura);
    fprintf(saida, "%d %d\n", altura, largura);

    fscanf(arquivo, "%d", &valor_maximo);
    fprintf(saida, "%d\n", valor_maximo);

    // Alocação dinâmica para armazenar os pixels da imagem original
    int ***pixels = (int ***)malloc(altura * sizeof(int **));
    for (int i = 0; i < altura; i++)
    {
        pixels[i] = (int **)malloc(largura * sizeof(int *));
        for (int j = 0; j < largura; j++)
        {
            pixels[i][j] = (int *)malloc(3 * sizeof(int)); // Alocando para RGB
        }
    }

    // Leitura dos pixels da imagem
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            fscanf(arquivo, "%d %d %d", &pixels[i][j][0], &pixels[i][j][1], &pixels[i][j][2]);
        }
    }

    // Rotacionando a imagem 90 graus para a esquerda
    for (int i = 0; i < largura; i++)
    {
        for (int j = 0; j < altura; j++)
        {
            fprintf(saida, "%d %d %d ",
                    pixels[j][largura - 1 - i][0],
                    pixels[j][largura - 1 - i][1],
                    pixels[j][largura - 1 - i][2]);
        }
        fprintf(saida, "\n");
    }

    // Liberação da memória alocada
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            free(pixels[i][j]);
        }
        free(pixels[i]);
    }
    free(pixels);

    printf("Imagem rotacionada com sucesso!\n");
    fclose(arquivo);
    fclose(saida);

    return 0;
}

int separarCamadasRGB()
{
    int largura, altura, valor_maximo;
    char buffer[255];

    // Abrindo o arquivo de imagem PPM para leitura
    FILE *arquivo = fopen("imagem.ppm", "r");
    if (arquivo == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        return 1;
    }

    // Criando arquivos de saída para cada camada
    FILE *arquivoR = fopen("imagem_R.ppm", "w");
    FILE *arquivoG = fopen("imagem_G.ppm", "w");
    FILE *arquivoB = fopen("imagem_B.ppm", "w");

    // Leitura do cabeçalho do arquivo PPM
    fgets(buffer, sizeof(buffer), arquivo);
    fprintf(arquivoR, "%s", buffer);
    fprintf(arquivoG, "%s", buffer);
    fprintf(arquivoB, "%s", buffer);

    fgets(buffer, sizeof(buffer), arquivo);
    fprintf(arquivoR, "%s", buffer);
    fprintf(arquivoG, "%s", buffer);
    fprintf(arquivoB, "%s", buffer);

    fscanf(arquivo, "%d %d", &largura, &altura);
    fprintf(arquivoR, "%d %d\n", largura, altura);
    fprintf(arquivoG, "%d %d\n", largura, altura);
    fprintf(arquivoB, "%d %d\n", largura, altura);

    fscanf(arquivo, "%d", &valor_maximo);
    fprintf(arquivoR, "%d\n", valor_maximo);
    fprintf(arquivoG, "%d\n", valor_maximo);
    fprintf(arquivoB, "%d\n", valor_maximo);

    // Alocação dinâmica para armazenar os pixels da imagem original
    int ***pixels = (int ***)malloc(altura * sizeof(int **));
    for (int i = 0; i < altura; i++)
    {
        pixels[i] = (int **)malloc(largura * sizeof(int *));
        for (int j = 0; j < largura; j++)
        {
            pixels[i][j] = (int *)malloc(3 * sizeof(int)); // Alocando para RGB
        }
    }

    // Leitura dos pixels da imagem
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            fscanf(arquivo, "%d %d %d", &pixels[i][j][0], &pixels[i][j][1], &pixels[i][j][2]);
        }
    }

    // Criando imagens para cada camada de cor
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            // Imagem da camada vermelha
            fprintf(arquivoR, "%d 0 0 ", pixels[i][j][0]);
            // Imagem da camada verde
            fprintf(arquivoG, "0 %d 0 ", pixels[i][j][1]);
            // Imagem da camada azul
            fprintf(arquivoB, "0 0 %d ", pixels[i][j][2]);
        }
        fprintf(arquivoR, "\n");
        fprintf(arquivoG, "\n");
        fprintf(arquivoB, "\n");
    }

    // Liberação da memória alocada
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            free(pixels[i][j]);
        }
        free(pixels[i]);
    }
    free(pixels);

    printf("Imagens geradas com sucesso!\n");

    // Fechando todos os arquivos
    fclose(arquivo);
    fclose(arquivoR);
    fclose(arquivoG);
    fclose(arquivoB);

    return 0;
}

int escalaCinzaParcial()
{
    int largura, altura, valor_maximo;
    char buffer[255];
    int x_inicial, y_inicial, largura_cinza, altura_cinza;

    // Abrir arquivo de entrada e arquivos de saída
    FILE *entrada = fopen("imagem.ppm", "r");
    FILE *saida = fopen("imagem_parcial_cinza.ppm", "w");

    if (entrada == NULL)
    {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }
    if (saida == NULL)
    {
        printf("Erro ao abrir o arquivo de saída.\n");
        fclose(entrada);
        return 1;
    }

    // Leitura do cabeçalho
    fgets(buffer, sizeof(buffer), entrada);
    fprintf(saida, "%s", buffer);
    fgets(buffer, sizeof(buffer), entrada);
    fprintf(saida, "%s", buffer);

    fscanf(entrada, "%d %d", &largura, &altura);
    fprintf(saida, "%d %d\n", largura, altura);

    fscanf(entrada, "%d", &valor_maximo);
    fprintf(saida, "%d\n", valor_maximo);

    // Definir a área que será convertida para escala de cinza
    x_inicial = largura / 4; // Começo da área cinza (exemplo)
    y_inicial = altura / 4;
    largura_cinza = largura / 2; // Largura da área cinza (exemplo)
    altura_cinza = altura / 2;

    // Alocar memória para armazenar os pixels
    int ***pixels = (int ***)malloc(altura * sizeof(int **));
    for (int i = 0; i < altura; i++)
    {
        pixels[i] = (int **)malloc(largura * sizeof(int *));
        for (int j = 0; j < largura; j++)
        {
            pixels[i][j] = (int *)malloc(3 * sizeof(int));
        }
    }

    // Ler os pixels da imagem original
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            fscanf(entrada, "%d %d %d", &pixels[i][j][0], &pixels[i][j][1], &pixels[i][j][2]);
        }
    }

    // Converter parte da imagem para escala de cinza e escrever no arquivo de saída
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            if (i >= y_inicial && i < y_inicial + altura_cinza && j >= x_inicial && j < x_inicial + largura_cinza)
            {
                // Converter para escala de cinza
                int gray = (pixels[i][j][0] + pixels[i][j][1] + pixels[i][j][2]) / 3;
                fprintf(saida, "%d %d %d ", gray, gray, gray);
            }
            else
            {
                // Manter a cor original
                fprintf(saida, "%d %d %d ", pixels[i][j][0], pixels[i][j][1], pixels[i][j][2]);
            }
        }
        fprintf(saida, "\n");
    }

    // Liberar memória
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            free(pixels[i][j]);
        }
        free(pixels[i]);
    }
    free(pixels);

    printf("Imagem cópia gerada com sucesso!\n");

    // Fechar arquivos
    fclose(entrada);
    fclose(saida);

    return 0;
}

int menu()
{
    int option;

    printf(" .:: MANIPULADOR DE IMAGENS ::. \n");
    printf("1. Converter imagem colorida para escala de cinza.\n");
    printf("2. Espelhar imagem horizontalmente.\n");
    printf("3. Espelhar imagem verticalmente.\n");
    printf("4. Dividir imagem em dois arquivos, metade esquerda e metade direita).\n");
    printf("5. Dividir imagem em dois arquivos, metade superior e metade inferior).\n");
    printf("6. Colorir imagem artificialmente.\n");
    printf("7. Rotacionar imagem 90 graus para a direita.\n");
    printf("8. Rotacionar imagem 90 graus para a esquerda.\n");
    printf("9. Gerar imagem cópia com parte em escala de cinza.\n");
    printf("10. Gerar imagens para cada camada (R, G e B).\n");
    printf("0. Sair\n");
    printf("Opção: ");
    scanf("%d", &option);

    return option;
}

int main()
{
    int option;
    do
    {
        option = menu();
        switch (option)
        {
        case 1:
            printf("\nConvertendo imagem para escala de cinza...\n");
            escalaCinza();
            break;
        case 2:
            printf("\nInvertendo imagem horizontalmente...\n");
            inverteHorizontal();
            break;
        case 3:
            printf("\nInvertendo imagem verticalmente...\n");
            inverteVertical();
            break;
        case 4:
            printf("\nDividindo a imagem em metade esquerda e metade direita...\n");
            divisaoVertical();
            break;
        case 5:
            printf("\nDividindo a imagem em metade superior e metade inferior...\n");
            divisaoHorizontal();
            break;
        case 6:
            printf("\nColorindo a imagem artificialmente...\n");
            colorirArtificialmente();
            break;
        case 7:
            printf("\nRotacionando a imagem 90º a direita...\n");
            rotacionar90direita();
            break;
        case 8:
            printf("\nRotacionando a imagem 90º a esquerda...\n");
            rotacionar90esquerda();
            break;
        case 9:
            printf("\nGerando cópia com parte em escala de cinza...\n");
            escalaCinzaParcial();
            break;
        case 10:
            printf("\nImagens geradas nas camadas R, G, B...\n");
            separarCamadasRGB();
            break;
        case 0:
            printf("\nSaindo...\n");
            break;
        default:
            printf("\nOpção Inválida!\n");
            break;
        }

        printf("\n\n");
    } while (option != 0);

    return 0;
}