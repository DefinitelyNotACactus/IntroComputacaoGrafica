#  Introdução à Computação Gráfica 2018.1

### Contents
[T1 - Rasterization](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica#t1---rasterization)

## T1 - Rasterization
### Introduction
For this task, we have implemented algorithms to rasterize pixels, lines and triangles on the screen, in order to simulate access to the video memory a framework was provided by the teacher using OpenGL and GLUT toolkit.

#### Contents
[1. Introduction](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica#introduction) <br>
[2. PutPixel](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica#function-putpixel) <br>
[3. DrawLine](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica#function-drawline) <br> 
[3.1 Color Interpolation](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica#color-interpolation) <br>
[4. DrawTriangle](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica#function-drawtriangle) <br>
[5. Conclusion](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica#conclusion) <br>
[6. References](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica#references)

#### Requirements
> * OpenGL 
> * GLUT (OpenGL Utility Toolkit) 
> * A C/C++ compiler
###### Note: In terms of environment, we've used the Windows operating system and NetBeans IDE with MinGW compiler.

### Function PutPixel
This function calculates the offset and draws a single pixel on the screen. A pixel has a pair of coordinates (x,y), and it's color (RGBA) value. On the framework used, a pixel memory position is simulated by the FBptr pointer, and the origin of the X and Y axis is at the window top-left, thus, in order to access the first position the following offset formula and FBptr syntax is used:

 ```C++
 Offset = (X*4)+(Y*4*Width)
 PBptr[Offset] = value;
 ```
 
 Where X and Y is the pixel coordinate and Width is the Window width.
 
 Since every color channel occupies one byte and the RGBA color scheme is composed of four channels we have to increment the position by one in order to access the next color channel:
 
 ![alt text](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica/raw/master/pictures/pixel.png)
 Thus, the FBptr needs to be called four times and the function changes to:
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

Now let's assume we want to draw a pixel in the (255, 255) coordinate with a white color (255,255,255,255). Here's the code:
```C++
Pixel pxl2(255, 255, 255, 255, 255, 255);
PutPixel(&pxl2);
```
And the output:

![alt text](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica/raw/master/pictures/img001.png "Image 1")
### Function DrawLine
This function receives two pixels and draws a line between them using the Bresenham algorithm.
The Bresenham algorithm calculates the position of the next pixel to be drawn using midpoint criteria (Consider a line that intersects two pixels columns, for each column there are two pixels that are closer to the line, one above and the other below):

![alt text](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica/raw/master/pictures/line.png "")

To decide between them, a decision variable d is used:
```C++
d = 2 * dy - dx;
```

Where dx is the X delta and dy is the y delta, and we repeat this by incrementing until the endpoint is reached.

This algorithm has proven to be efficient to rasterize lines as it doesn't involves operations with floating point.
```C++
void DrawLine(Pixel *pxli, Pixel *pxlf){//parameters changed
    int dx = pxlf->getX() - pxli->getX();
    int dy = pxlf->getY() - pxli->getY();
    int d = 2 * dy - dx;
    int incr_e = 2 * dy;
    int incr_ne = 2 * (dy - dx);
    Pixel newPixel = *pxli;
    PutPixel(&newPixel);
    while(newPixel.getX() != pxlf->getX()){
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

However, this code has some limitations, for instance, it's restricted to slopes where <b>0<=m<=1</b>, which is the first octant, and it only works if the delta x is greater than zero. In the following images we have two situations and the octants, respectively:

![alt text](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica/raw/master/pictures/situations.png "Image 2")

Where a line between (x1, y1) and (x2, y2) would successfully draw (a) and a line between (x2, y2) and (x1, y1) wouldn't plot.

![alt text](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica/raw/master/pictures/octants.png  "Image 3")

As we can see the (a) situation happens in the first octant while (b) is at the 5th octant.

In order to fix these issues, we have to consider that not always x1 and y1 will be greater than x2 and y2, respectively. So we have to call the abs() function to dx and dy variables, and if dx and/or dy is negative we have to decrement their respective coordinate instead of increment. So the code was changed to:
```C++
void DrawLine(Pixel *pxli, Pixel *pxlf){
    int dx = abs(pxlf->getX() - pxli->getX());
    int dy = abs(pxlf->getY() - pxli->getY());
    int d = 2 * dy - dx;
    int incr_e = 2 * dy;
    int incr_ne = 2 * (dy - dx);
    Pixel newPixel = *pxli;
    PutPixel(&newPixel);
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
}
```

Now we can handle the (b) situation seen before and negative slopes within the [-1, 0] range, but there's still one case which the line wouldn't draw that is when dy is greater than dx. For this all we have to do is switch the decrement/increment X to Y and vice versa (and the conditionals). So this is how our code ended:
```C++
void DrawLine(Pixel *pxli, Pixel *pxlf){
    int d, incr_e, incr_ne, dx, dy;
    Pixel newPixel = *pxli;
    PutPixel(&newPixel);
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
```

So let's use this function to draw lines on all eight octants.
    
And the lines succesfully drawn:

![alt text](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica/raw/master/pictures/lines.png "")
#### Color Interpolation 
As we can see in the code before, the starting pixel and end pixel (which in our tests was always the central pixel, pxlc) have different RGBA values, however, when we plot the line there's no transition between the colors, and as requested, the color of every pixel along the line must be obtained by linear interpolation. Interpolation consists of "filling a gap" between two numbers. In order to fix this, we have to get the initial and ending pixel colors and use the following formula on the pixel we are currently plotting:
```C++
 color = final_color + (initial_color - final_color) * t);
 ```
Where t is a value between [0,1] with 0 meaning we are on initial point and 1 on the last point. But how we calculate t? To start, every line has a X and a Y component, on the DrawLine function dx is the line X component and dy the Y component:
 
![alt text](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica/raw/master/pictures/components.png "")

In the image above, dx and dy forms an angle of 90 degrees, except for the cases when dx or dy is 0 (dt is simply the square root of the non-null component), and we can obtain the line lenght (dt) by using the Pythagorean Theorem:
 ```C++
  dt = sqrt((dx*dx)+(dy*dy)); //sqrt = Square root
  ```
dt is the numbers of steps we will have taken when the line is fully rasterized, so by creating a new variable called steps we can keep on track of how many steps we've taken, and dividing by dt we have the t, so this is how the function was implemented:
```C++
void Interpolate(Pixel *pxla, Pixel *pxli, Pixel *pxlf, float t){
    pxla->setR(pxlf->getR() + (pxli->getR() - pxlf->getR()) * t);
    pxla->setG(pxlf->getG() + (pxli->getG() - pxlf->getG()) * t);
    pxla->setB(pxlf->getB() + (pxli->getB() - pxlf->getB()) * t);
    pxla->setA(pxlf->getA() + (pxli->getA() - pxlf->getA()) * t);
}
```

And we have to call it in the DrawLine as well (parts of the code omitted):
```C++
void DrawLine(Pixel *pxli, Pixel *pxlf){
    //...
    double dt = sqrt((dx * dx) + (dy * dy));
    step = 0;
    if(dx >= dy){
        //...
        while(newPixel.getX() != pxlf->getX()){
            //...
            Interpolate(&newPixel, pxlf, pxli, step/dt);
            PutPixel(&newPixel);
            step++;
        }
    } else {
        //...
        while(newPixel.getY() != pxlf->getY()){
            //...
            Interpolate(&newPixel, pxlf, pxli, step/dt);
            PutPixel(&newPixel);
            step++;
        }
    }
}
```

Now let's test the function using the same parameters to draw in all eight octants, now interpolating colors:

![alt text](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica/raw/master/pictures/interpolated.png "")
### Function DrawTriangle
This function draws a triangle, a geometric shape which consists in three lines that share one vertex with another line. By using the DrawLine function we give three pixels that are the triangle vertices as parameters and we connect them using the DrawLine function:                                   
```C++                                  
void DrawTriangle(Pixel *pxla, Pixel *pxlb, Pixel *pxlc){
    DrawLine(pxla, pxlb);
    DrawLine(pxla, pxlc);
    DrawLine(pxlb, pxlc);
}
```

To draw a sample triangle, we will use the following parameters:
```C++
    Pixel pxla(261, 111, 255, 0, 0, 255);
    Pixel pxlb(411, 400, 0, 255, 0, 255);
    Pixel pxlcc(111, 400, 0, 0, 255, 255);
    
    DrawTriangle(&pxla, &pxlb, &pxlcc);
```
And the triangle drawn:

![alt text](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica/raw/master/pictures/triangle.png "")

### Conclusion
The presented work had the intention of increasing the knowledge we possess on openGL basics and primitive rasterization routines as a practice of programming. We could also through the end of the work emphasize a few enhancements that could be done in order to improve the code, for instance the inability to fill the triangle, and draw other kinds of objects. 
 
### References
[The Bresenham Line-Drawing Algorithm](https://www.cs.helsinki.fi/group/goa/mallinnus/lines/bresenh.html)<br>
[Using freeglut or GLUT with MinGW](https://www.transmissionzero.co.uk/computing/using-glut-with-mingw/)<br>
[The Secrets of Colour Interpolation](https://www.alanzucconi.com/2016/01/06/colour-interpolation/)<br>
