#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************
class Color{
    
public:
    int r, g, b, a;
    
    Color(int r, int g, int b, int a){
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
};

class Pair{
    
public:
    int x, y;
    
    Pair(int x, int y){
        this->x = x;
        this->y = y;
    }
};

/**
 * Rasterizes a single pixel in the video memory
 * @param *xy The coordinated pair of this pixel
 * @param *clr The Color of this pixel 
 */
void PutPixel(Pair *pair, Color *clr){
    FBptr[pair->x*4 + pair->y*4*IMAGE_WIDTH + 0]  = clr->r;
    FBptr[pair->x*4 + pair->y*4*IMAGE_WIDTH + 1]  = clr->g;
    FBptr[pair->x*4 + pair->y*4*IMAGE_WIDTH + 2]  = clr->b;
    FBptr[pair->x*4 + pair->y*4*IMAGE_WIDTH + 3]  = clr->a;
}

/**
 * Rasterizes a line in the window, using the Bresenham algorithm
 * @todo The other 7 regions
 */
void DrawLine(Pair *pair0, Pair *pair1, Color *clr0, Color *clr1){
    int dx = pair1->x - pair0->x;
    int dy = pair1->y - pair0->y;
    int d = 2 * dy - dx;
    int incr_e = 2 * dy;
    int incr_ne = 2 * (dy - dx);
    Pair newPair(pair0->x, pair0->y);
    PutPixel(&newPair, clr1);
    while(newPair.x < pair1->x){
        if(d <= 0) {
            d += incr_e;
            newPair.x++;
        } else {
            d += incr_ne;
            newPair.x++;
            newPair.y++;
        }
        PutPixel(&newPair, clr1);
    }
}
#endif // _MYGL_H_

