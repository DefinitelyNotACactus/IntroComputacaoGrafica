#  Introdução à Computação Gráfica 2018.1

## T1 - Rasterization
### Introduction
For this task, we have implemented algorithms to rasterize pixels, lines and triangles on the screen, to simulate access to the video memory a framework was provided by the teacher using OpenGL and GLUT toolkit.

#### Requirements
> * OpenGL 
> * GLUT (OpenGL Utility Toolkit) 
> * A C/C++ compiler
###### Note: In terms of environment, we've used the Windows operating system and NetBeans IDE with MinGW compiler.

### Function PutPixel
This function calculates the offset and draws a single pixel on the screen. A pixel has a pair of coordinates (x,y) and it's RGBA value, which gives it's position and color to be displayed, respectively. In the framework the position on the video memory is simulated by the FBptr pointer where it's position is calculated by:
 `Position = (X*4)+(Y*4*Width)`
 Since every color channel occupies one byte we have to increment the position by one in order to access the next value of RGBA, and thus, the FBptr needs to be called four times:
 ```C++
 void PutPixel(Pixel *pxl){
    FBptr[pxl->getX()*4 + pxl->getY()*4*IMAGE_WIDTH + 0]  = pxl->getR();
    FBptr[pxl->getX()*4 + pxl->getY()*4*IMAGE_WIDTH + 1]  = pxl->getG();
    FBptr[pxl->getX()*4 + pxl->getY()*4*IMAGE_WIDTH + 2]  = pxl->getB();
    FBptr[pxl->getX()*4 + pxl->getY()*4*IMAGE_WIDTH + 3]  = pxl->getA();
}
```
As a pixel has a coordinate and RGBA value, to avoid passing six parameters each time this function is called, we've created an class called Pixel which has the coordinates, RGBA values, and functions to access or modify their values.
```C++
class Pixel{
private:
    int x, y; //coordinate variables    
    int r, g, b, a; //color variables    
public:
    Pixel(int x, int y, int r, int g, int b, int a){
        this->x = x;
        this->y = y;
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
    //get and set functions omitted
};
```
So let's assume we want to draw a pixel in the 255, 255 coordinate with a white color (255,255,255,255). Here's the code:
```C++
Pixel pxl2(255, 255, 255, 255, 255, 255);
PutPixel(&pxl2);
```
And the output:

[logo]: https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica/raw/master/screenshots/img001.png "Image 1"

### Function DrawLine
This function receives two Pixels and draws a line between them using the Bresenham algorithm. The version of the algorithm seen on class had some limitations, for instance it was limited to slopes where <b>0<=m<=1</b>, thus, the 8th octant. Here's the early version of the code:

```C++
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
```

[logo]: https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica/raw/master/screenshots/octants.png  "Octants"


(To be continued)

#### Color Interpolation

(In progress)

### Function DrawTriangle

(In progress)

### Conclusion

(In progress)

### References

[The Bresenham Line-Drawing Algorithm](https://www.cs.helsinki.fi/group/goa/mallinnus/lines/bresenh.html)
