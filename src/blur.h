#ifndef BLUR_H
#define BLUR_H

#define RED 0
#define GREEN 1
#define BLUE 2

#include "imageprocessing.h"

struct arg_struct {
    imagem *img;
    imagem *filtrada;
    char canal;
};

void blur_line(imagem *img, imagem *filtrada, char canal, int linha);
float calcula_pixel(imagem *img, char canal, int linha, int coluna);

#endif
