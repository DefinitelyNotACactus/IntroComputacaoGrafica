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
    int d, incr_e, incr_ne, dx, dy;
    Pixel newPixel = *pxli;
    //PutPixel(&newPixel);
    dx = abs(pxlf->getX() - newPixel.getX());
    dy = abs(pxlf->getY() - newPixel.getY());
    if(dx >= dy){
        d = 2 * dy - dx;
        incr_e = 2 * dy;
        incr_ne = 2 * (dy - dx);
        while(newPixel.getX() != pxlf->getX()){
            if(d <= 0) {
                d += incr_e;
            } else {
                d += incr_ne;
                if(pxli->getY() > pxlf->getY()){
                    newPixel.decrementY();
                } else {
                    newPixel.incrementY();
                }
            }
            if(pxli->getX() > pxlf->getX()){
                newPixel.decrementX();
            } else {
                newPixel.incrementX();
            }
            PutPixel(&newPixel);
        }
    } else {
        d = 2 * dx - dy;
        incr_e = 2 * dx;
        incr_ne = 2 * (dx - dy);
        while(newPixel.getY() != pxlf->getY()){
            if(d <= 0) {
                d += incr_e;
            } else {
                d += incr_ne;
                if(pxli->getX() > pxlf->getX()){
                    newPixel.decrementX();
                } else {
                    newPixel.incrementX();
                }
            }
            if(pxli->getY() > pxlf->getY()){
                newPixel.decrementY();
            } else {
                newPixel.incrementY();
            }
            PutPixel(&newPixel);
        }
    }
}
#endif // _MYGL_H_

