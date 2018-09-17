#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"
#include "Pixel.h"
#include "Math.h"

//*****************************************************************************
// Defina aqui as suas funÃ§Ãµes grÃ¡ficas
//*****************************************************************************

void ClearScreen(){
    for(int i = 0; i < IMAGE_HEIGHT; i++){
        for(int j = 0; j < IMAGE_WIDTH; j++){
            FBptr[i*4 + j*4*IMAGE_WIDTH + 0] = 0;
            FBptr[i*4 + j*4*IMAGE_WIDTH + 1] = 0;
            FBptr[i*4 + j*4*IMAGE_WIDTH + 2] = 0;
            FBptr[i*4 + j*4*IMAGE_WIDTH + 3] = 255;
        }
    }
}
void Interpolate(Pixel *pxla, Pixel *pxlb, Pixel *pxlc, float t){
    pxla->setR((pxlb->getR() - pxlc->getR()) * t + pxlc->getR());
    pxla->setG((pxlb->getG() - pxlc->getG()) * t + pxlc->getG());
    pxla->setB((pxlb->getB() - pxlc->getB()) * t + pxlc->getB());
    pxla->setA((pxlb->getA() - pxlc->getA()) * t + pxlc->getA());
}
/**
 * Rasterizes a single pixel in the video memory
 * @param *pxl The pixel to be drawn 
 */
void PutPixel(Pixel *pxl){
    if(pxl->getX() >= 0 && pxl->getY() >= 0 && pxl->getX() < IMAGE_WIDTH && pxl->getY() < IMAGE_HEIGHT){
        FBptr[pxl->getX()*4 + pxl->getY()*4*IMAGE_WIDTH + 0]  = pxl->getR();
        FBptr[pxl->getX()*4 + pxl->getY()*4*IMAGE_WIDTH + 1]  = pxl->getG();
        FBptr[pxl->getX()*4 + pxl->getY()*4*IMAGE_WIDTH + 2]  = pxl->getB();
        FBptr[pxl->getX()*4 + pxl->getY()*4*IMAGE_WIDTH + 3]  = pxl->getA();
    }
}

/**
 * Rasterizes a line in the window, using the Bresenham algorithm
 * @param *pxli The starting pixel
 * @param *pxlf The last pixel
 */
void DrawLine(Pixel *pxli, Pixel *pxlf){
    int d, incr_e, incr_ne, dx, dy, step;
    Pixel newPixel = *pxli;
    PutPixel(&newPixel);
    dx = abs(pxlf->getX() - newPixel.getX());
    dy = abs(pxlf->getY() - newPixel.getY());
    
    double dt = sqrt((dx * dx) + (dy * dy));
    step = 0;
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
            Interpolate(&newPixel, pxlf, pxli, step/dt);
            PutPixel(&newPixel);
            step++;
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
            Interpolate(&newPixel, pxlf, pxli, step/dt);
            PutPixel(&newPixel);
            step++;
        }
    }
}

/**
 * Rasterizes a triangle in the window by calling the DrawLine function for the three pixels.
 * @param pxla
 * @param pxlb
 * @param pxlc
 */
void DrawTriangle(Pixel *pxla, Pixel *pxlb, Pixel *pxlc){
    DrawLine(pxla, pxlb);
    DrawLine(pxla, pxlc);
    DrawLine(pxlb, pxlc);
}

#endif // _MYGL_H_

