#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"
#include "Pixel.h"

//*****************************************************************************
// Defina aqui as suas funÃ§Ãµes grÃ¡ficas
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
 * @param *pxli The starting pixel
 * @param *pxlf The last pixel
 */
void DrawLine(Pixel *pxli, Pixel *pxlf){
    int d, incr_e, incr_ne, dx, dy, dr, dg, db, da, Dr, Dg, Db, Da, R, G, B, A,vr,vg,vb,va;
    Pixel newPixel = *pxli;
    PutPixel(&newPixel);
    dx = abs(pxlf->getX() - newPixel.getX());
    dy = abs(pxlf->getY() - newPixel.getY());
    dr = abs(pxlf->getR() - newPixel.getR());
    dg = abs(pxlf->getG() - newPixel.getG());
    db = abs(pxlf->getB() - newPixel.getB());
    da = abs(pxlf->getA() - newPixel.getA());
    vr = dr;
    vg = dg;
    vb = db;
    va = da;
    Da = d/da;
    Dr = d/dr;
    Dg = d/dg;
    Db = d/db;
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
                if(pxli->getR() > pxlf->getR()){
                    R = pxlf->getR();
                       if(R == Dr){
                    newPixel.decrementR();
                    R--;
                    vr = vr - Dr;
                    }
                    else{
                        R--;
                    }
                } else {
                    R = pxli->getR();
                       if(R == Dr){
                    newPixel.incrementR();
                    R++;
                    vr = vr + Dr;
                    }
                    else{
                        R++;
                    }
                }
            if(pxli->getG() > pxlf->getG()){
                    G = pxlf->getG();
                       if(G == Dg){
                    newPixel.decrementG();
                    G--;
                    vg = vg - Dg;
                    }
                    else{
                        G--;
                    }
                } else {
                    G = pxli->getG();
                       if(G == Dg){
                    newPixel.incrementG();
                    G++;
                    vg = vg + Dg;
                    }
                    else{
                        G++;
                    }
                }
            if(pxli->getB() > pxlf->getB()){
                    B = pxlf->getB();
                       if(B == Db){
                    newPixel.decrementB();
                    B--;
                    vb = vb - Db;
                    }
                    else{
                        B--;
                    }
                  
                    
                } else {
                    B = pxli->getB();
                       if(B == Db){
                    newPixel.incrementB();
                    B++;
                    vb = vb + Db;
                    }
                    else{
                        B++;
                    }
                }
            if(pxli->getA() > pxlf->getA()){
                    A = pxlf->getA();
                       if(A == Da){
                    newPixel.decrementA();
                    A--;
                    va = va - Da;
                    }
                    else{
                        A--;
                    }
                  
                    
                } else {
                    A = pxli->getA();
                       if(A == Da){
                    newPixel.incrementA();
                    A++;
                    va = va + Da;
                    }
                    else{
                        A++;
                    }
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
            if(pxli->getR() > pxlf->getR()){
                    R = pxlf->getR();
                       if(R == Dr){
                    newPixel.decrementR();
                    R--;
                    vr = vr - Dr;
                    }
                    else{
                        R--;
                    }
                } else {
                    R = pxli->getR();
                       if(R == Dr){
                    newPixel.incrementR();
                    R++;
                    vr = vr + Dr;
                    }
                    else{
                        R++;
                    }
                }
            if(pxli->getG() > pxlf->getG()){
                    G = pxlf->getG();
                       if(G == Dg){
                    newPixel.decrementG();
                    G--;
                    vg = vg - Dg;
                    }
                    else{
                        G--;
                    }
                } else {
                    G = pxli->getG();
                       if(G == Dg){
                    newPixel.incrementG();
                    G++;
                    vg = vg + Dg;
                    }
                    else{
                        G++;
                    }
                }
            if(pxli->getB() > pxlf->getB()){
                    B = pxlf->getB();
                       if(B == Db){
                    newPixel.decrementB();
                    B--;
                    vb = vb - Db;
                    }
                    else{
                        B--;
                    }
                  
                    
                } else {
                    B = pxli->getB();
                       if(B == Db){
                    newPixel.incrementB();
                    B++;
                    vb = vb + Db;
                    }
                    else{
                        B++;
                    }
                }
            if(pxli->getA() > pxlf->getA()){
                    A = pxlf->getA();
                       if(A == Da){
                    newPixel.decrementA();
                    A--;
                    va = va - Da;
                    }
                    else{
                        A--;
                    }
                  
                    
                } else {
                    A = pxli->getA();
                       if(A == Da){
                    newPixel.incrementA();
                    A++;
                    va = va + Da;
                    }
                    else{
                        A++;
                    }
                }
            PutPixel(&newPixel);
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

