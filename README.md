#  Introdução à Computação Gráfica 2018.1

## T1 - Rasterization
### Introduction
For this task, we have implemented algorithms to rasterize pixels, lines and triangles on the screen, to simulate access to the video memory a framework was provided by the teacher using OpenGL and GLUT toolkit.

### Requirements

> * OpenGL 
> * GLUT (OpenGL Utility Toolkit) 
> * A C/C++ compiler

###### Note: In terms of environment, we've used Windows operating system and NetBeans IDE with MinGW compiler.

### Function PutPixel
 A pixel has a pair of coordinates (x,y) and it's RGBA value, which gives it's position and color to be displayed. In the video memory the first position of a pixel is given by:
 `Offset = (X*4)+(Y*4*Width)`
 Since every color channel occupies one byte we have to increment the offset by one in order to access the next value of RGBA, thus, a implementation of the code would be:
 `void PutPixel(int x, int y, int r, int g, int b, int a){
    FBptr[x*4 + y*4*IMAGE_WIDTH + 0]  = r;
    FBptr[x*4 + y*4*IMAGE_WIDTH + 1]  = g;
    FBptr[x*4 + y*4*IMAGE_WIDTH + 2]  = b;
    FBptr[x*4 + y*4*IMAGE_WIDTH + 3]  = a;
}`

However, as we will see later, this function will be called every time in order to draw the pixels of a line and a triangle. Since it requires passing each of coordinates and RGBA values as a parameter, we decided to merge it into an object called Pixel, which stores the values mentioned earlier, with this the function has changed to:

