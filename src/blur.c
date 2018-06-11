#include "imageprocessing.h"
#include "blur.h"

void blur_line(imagem *img, imagem *filtrada, char canal, int linha) {
  int coluna;
  for (coluna = 0; coluna < ((*img).width); coluna++) {
    if (canal == RED) {
      (*filtrada).r[linha * ((*img).width) + coluna] = calcula_pixel(img, canal, linha, coluna);
    } else if (canal == GREEN) {
      (*filtrada).g[linha * ((*img).width) + coluna] = calcula_pixel(img, canal, linha, coluna);
    } else if (canal == BLUE) {
      (*filtrada).b[linha * ((*img).width) + coluna] = calcula_pixel(img, canal, linha, coluna);
    }
  }
}

float calcula_pixel(imagem *img, char canal, int linha, int coluna) {
  unsigned int tmp;
  tmp = 0;
  if (linha == 0) {
    if (coluna == 0) {
      if (canal == RED) {
        tmp = ((*img).r[linha * ((*img).width) + coluna] + (*img).r[linha * ((*img).width) + coluna + 1] + (*img).r[(linha + 1) * ((*img).width) + coluna] + (*img).r[(linha + 1) * ((*img).width) + (coluna + 1)])/4;
      } else if (canal == GREEN) {
        tmp = ((*img).g[linha * ((*img).width) + coluna] + (*img).g[linha * ((*img).width) + coluna + 1] + (*img).g[(linha + 1) * ((*img).width) + coluna] + (*img).g[(linha + 1) * ((*img).width) + (coluna + 1)])/4;
      } else if (canal == BLUE) {
        tmp = ((*img).b[linha * ((*img).width) + coluna] + (*img).b[linha * ((*img).width) + coluna + 1] + (*img).b[(linha + 1) * ((*img).width) + coluna] + (*img).b[(linha + 1) * ((*img).width) + (coluna + 1)])/4;
      }
    } else if (coluna == ((*img).width - 1)) {
      if (canal == RED) {
        tmp = ((*img).r[linha * ((*img).width) + coluna] + (*img).r[linha * ((*img).width) + coluna - 1] + (*img).r[(linha + 1) * ((*img).width) + coluna] + (*img).r[(linha + 1) * ((*img).width) + (coluna - 1)])/4;
      } else if (canal == GREEN) {
        tmp = ((*img).g[linha * ((*img).width) + coluna] + (*img).g[linha * ((*img).width) + coluna - 1] + (*img).g[(linha + 1) * ((*img).width) + coluna] + (*img).g[(linha + 1) * ((*img).width) + (coluna - 1)])/4;
      } else if (canal == BLUE) {
        tmp = ((*img).b[linha * ((*img).width) + coluna] + (*img).b[linha * ((*img).width) + coluna - 1] + (*img).b[(linha + 1) * ((*img).width) + coluna] + (*img).b[(linha + 1) * ((*img).width) + (coluna - 1)])/4;
      }
    } else {
      if (canal == RED) {
        tmp = ((*img).r[linha * ((*img).width) + coluna] + (*img).r[linha * ((*img).width) + coluna - 1] + (*img).r[linha * ((*img).width) + coluna + 1] + (*img).r[(linha + 1) * ((*img).width) + (coluna - 1)] + (*img).r[(linha + 1) * ((*img).width) + coluna] + (*img).r[(linha + 1) * ((*img).width) + (coluna + 1)])/6;
      } else if (canal == GREEN) {
        tmp = ((*img).g[linha * ((*img).width) + coluna] + (*img).g[linha * ((*img).width) + coluna - 1] + (*img).g[linha * ((*img).width) + coluna + 1] + (*img).g[(linha + 1) * ((*img).width) + (coluna - 1)] + (*img).g[(linha + 1) * ((*img).width) + coluna] + (*img).g[(linha + 1) * ((*img).width) + (coluna + 1)])/6;
      } else if (canal == BLUE) {
        tmp = ((*img).b[linha * ((*img).width) + coluna] + (*img).b[linha * ((*img).width) + coluna - 1] + (*img).b[linha * ((*img).width) + coluna + 1] + (*img).b[(linha + 1) * ((*img).width) + (coluna - 1)] + (*img).b[(linha + 1) * ((*img).width) + coluna] + (*img).b[(linha + 1) * ((*img).width) + (coluna + 1)])/6;
      }
    }
  } else if (linha == (*img).height - 1) {
    if (coluna == 0) {
      if (canal == RED) {
        tmp = ((*img).r[linha * ((*img).width) + coluna] + (*img).r[linha * ((*img).width) + coluna + 1] + (*img).r[(linha - 1) * ((*img).width) + coluna] + (*img).r[(linha - 1) * ((*img).width) + (coluna + 1)])/4;
      } else if (canal == GREEN) {
        tmp = ((*img).g[linha * ((*img).width) + coluna] + (*img).g[linha * ((*img).width) + coluna + 1] + (*img).g[(linha - 1) * ((*img).width) + coluna] + (*img).g[(linha - 1) * ((*img).width) + (coluna + 1)])/4;
      } else if (canal == BLUE) {
        tmp = ((*img).b[linha * ((*img).width) + coluna] + (*img).b[linha * ((*img).width) + coluna + 1] + (*img).b[(linha - 1) * ((*img).width) + coluna] + (*img).b[(linha - 1) * ((*img).width) + (coluna + 1)])/4;
      }
    } else if (coluna == ((*img).width - 1)) {
      if (canal == RED) {
        tmp = ((*img).r[linha * ((*img).width) + coluna] + (*img).r[linha * ((*img).width) + coluna - 1] + (*img).r[(linha - 1) * ((*img).width) + coluna] + (*img).r[(linha - 1) * ((*img).width) + (coluna - 1)])/4;
      } else if (canal == GREEN) {
        tmp = ((*img).g[linha * ((*img).width) + coluna] + (*img).g[linha * ((*img).width) + coluna - 1] + (*img).g[(linha - 1) * ((*img).width) + coluna] + (*img).g[(linha - 1) * ((*img).width) + (coluna - 1)])/4;
      } else if (canal == BLUE) {
        tmp = ((*img).b[linha * ((*img).width) + coluna] + (*img).b[linha * ((*img).width) + coluna - 1] + (*img).b[(linha - 1) * ((*img).width) + coluna] + (*img).b[(linha - 1) * ((*img).width) + (coluna - 1)])/4;
      }
    } else {
      if (canal == RED) {
        tmp = ((*img).r[linha * ((*img).width) + coluna] + (*img).r[linha * ((*img).width) + coluna - 1] + (*img).r[linha * ((*img).width) + coluna + 1] + (*img).r[(linha - 1) * ((*img).width) + (coluna - 1)] + (*img).r[(linha - 1) * ((*img).width) + coluna] + (*img).r[(linha - 1) * ((*img).width) + (coluna + 1)])/6;
      } else if (canal == GREEN) {
        tmp = ((*img).g[linha * ((*img).width) + coluna] + (*img).g[linha * ((*img).width) + coluna - 1] + (*img).g[linha * ((*img).width) + coluna + 1] + (*img).g[(linha - 1) * ((*img).width) + (coluna - 1)] + (*img).g[(linha - 1) * ((*img).width) + coluna] + (*img).g[(linha - 1) * ((*img).width) + (coluna + 1)])/6;
      } else if (canal == BLUE) {
        tmp = ((*img).b[linha * ((*img).width) + coluna] + (*img).b[linha * ((*img).width) + coluna - 1] + (*img).b[linha * ((*img).width) + coluna + 1] + (*img).b[(linha - 1) * ((*img).width) + (coluna - 1)] + (*img).b[(linha - 1) * ((*img).width) + coluna] + (*img).b[(linha - 1) * ((*img).width) + (coluna + 1)])/6;
      }
    }
  }
  else if (coluna == 0) {
    if (canal == RED) {
      tmp = ((*img).r[linha * ((*img).width) + coluna] + (*img).r[linha * ((*img).width) + coluna + 1] + (*img).r[(linha - 1) * ((*img).width) + coluna] + (*img).r[(linha - 1) * ((*img).width) + coluna + 1] + (*img).r[(linha + 1) * ((*img).width) + coluna] + (*img).r[(linha + 1) * ((*img).width) + (coluna + 1)])/6;
    } else if (canal == GREEN) {
      tmp = ((*img).g[linha * ((*img).width) + coluna] + (*img).g[linha * ((*img).width) + coluna + 1] + (*img).g[(linha - 1) * ((*img).width) + coluna] + (*img).g[(linha - 1) * ((*img).width) + coluna + 1] + (*img).g[(linha + 1) * ((*img).width) + coluna] + (*img).g[(linha + 1) * ((*img).width) + (coluna + 1)])/6;
    } else if (canal == BLUE) {
      tmp = ((*img).b[linha * ((*img).width) + coluna] + (*img).b[linha * ((*img).width) + coluna + 1] + (*img).b[(linha - 1) * ((*img).width) + coluna] + (*img).b[(linha - 1) * ((*img).width) + coluna + 1] + (*img).b[(linha + 1) * ((*img).width) + coluna] + (*img).b[(linha + 1) * ((*img).width) + (coluna + 1)])/6;
    }
  } else if (coluna == ((*img).width - 1)) {
    if (canal == RED) {
      tmp = ((*img).r[linha * ((*img).width) + coluna] + (*img).r[linha * ((*img).width) + coluna - 1] + (*img).r[(linha - 1) * ((*img).width) + coluna] + (*img).r[(linha - 1) * ((*img).width) + coluna - 1] + (*img).r[(linha + 1) * ((*img).width) + coluna] + (*img).r[(linha + 1) * ((*img).width) + (coluna - 1)])/6;
    } else if (canal == GREEN) {
      tmp = ((*img).g[linha * ((*img).width) + coluna] + (*img).g[linha * ((*img).width) + coluna - 1] + (*img).g[(linha - 1) * ((*img).width) + coluna] + (*img).g[(linha - 1) * ((*img).width) + coluna - 1] + (*img).g[(linha + 1) * ((*img).width) + coluna] + (*img).g[(linha + 1) * ((*img).width) + (coluna - 1)])/6;
    } else if (canal == BLUE) {
      tmp = ((*img).b[linha * ((*img).width) + coluna] + (*img).b[linha * ((*img).width) + coluna - 1] + (*img).b[(linha - 1) * ((*img).width) + coluna] + (*img).b[(linha - 1) * ((*img).width) + coluna - 1] + (*img).b[(linha + 1) * ((*img).width) + coluna] + (*img).b[(linha + 1) * ((*img).width) + (coluna - 1)])/6;
    }
  } else {
    if (canal == RED) {
      tmp = ((*img).r[linha * ((*img).width) + coluna] + (*img).r[(linha - 1) * ((*img).width) + coluna - 1] + (*img).r[(linha - 1) * ((*img).width) + coluna] + (*img).r[(linha - 1) * ((*img).width) + coluna + 1] + (*img).r[linha * ((*img).width) + (coluna - 1)] + (*img).r[linha * ((*img).width) + (coluna + 1)] + (*img).r[linha + 1 * ((*img).width) + coluna - 1] + (*img).r[(linha + 1) * ((*img).width) + coluna] + (*img).r[(linha + 1) * ((*img).width) + coluna + 1])/9;
    } else if (canal == GREEN) {
      tmp = ((*img).g[linha * ((*img).width) + coluna] + (*img).g[(linha - 1) * ((*img).width) + coluna - 1] + (*img).g[(linha - 1) * ((*img).width) + coluna] + (*img).g[(linha - 1) * ((*img).width) + coluna + 1] + (*img).g[linha * ((*img).width) + (coluna - 1)] + (*img).g[linha * ((*img).width) + (coluna + 1)] + (*img).g[linha + 1 * ((*img).width) + coluna - 1] + (*img).g[(linha + 1) * ((*img).width) + coluna] + (*img).g[(linha + 1) * ((*img).width) + coluna + 1])/9;
    } else if (canal == BLUE) {
      tmp = ((*img).b[linha * ((*img).width) + coluna] + (*img).b[(linha - 1) * ((*img).width) + coluna - 1] + (*img).b[(linha - 1) * ((*img).width) + coluna] + (*img).b[(linha - 1) * ((*img).width) + coluna + 1] + (*img).b[linha * ((*img).width) + (coluna - 1)] + (*img).b[linha * ((*img).width) + (coluna + 1)] + (*img).b[linha + 1 * ((*img).width) + coluna - 1] + (*img).b[(linha + 1) * ((*img).width) + coluna] + (*img).b[(linha + 1) * ((*img).width) + coluna + 1])/9;
    }
  }
  return tmp;
}
