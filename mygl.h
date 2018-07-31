#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"
#include "Pixel.h"

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************

/**
 * Rasterizes a single pixel in the video memory
 * @param *pxl The pixel to be drawn 
 */
void PutPixel(Pixel *pxl){
    FBptr[pxl->getX()*4 + pxl->getY()*4*IMAGE_WIDTH + 0]  = pxl->getR();
    FBptr[pxl->getX()*4 + pxl->getY()*4*IMAGE_WIDTH + 1]  = pxl->getG();
    FBptr[pxl->getX()*4 + pxl->getY()*4*IMAGE_WIDTH + 2]  = pxl->getB();
    FBptr[pxl->getX()*4 + pxl->getY()*4*IMAGE_WIDTH + 3]  = pxl->getA();
}

/**
 * Rasterizes a line in the window, using the Bresenham algorithm
 * @todo The other 7 regions
 */
void DrawLine(Pixel *pxli, Pixel *pxlf){
    int dx = pxlf->getX() - pxli->getX();
    int dy = pxlf->getY() - pxli->getY();
    int d = 2 * dy - dx;
    int incr_e = 2 * dy;
    int incr_ne = 2 * (dy - dx);
    Pixel newPixel = *pxli;
    PutPixel(&newPixel);
    while(newPixel.getX() < pxlf->getY()){
        if(d <= 0) {
            d += incr_e;
            newPixel.incrementX();
        } else {
            d += incr_ne;
            newPixel.incrementX();
            newPixel.incrementY();
        }
        PutPixel(&newPixel);
    }
}
#endif // _MYGL_H_

