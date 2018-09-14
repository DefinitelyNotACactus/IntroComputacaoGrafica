#  Introdução à Computação Gráfica 2018.1

### Contents
[T1 - Rasterization](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica#t1---rasterization)<br>
[T2 - Graphic Pipeline](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica#t2---graphic-pipeline)

## T1 - Rasterization
### Introduction
For this task, we have implemented algorithms to rasterize pixels, lines and triangles on the screen, in order to simulate access to the video memory a framework was provided by the teacher using OpenGL and GLUT toolkit.

#### Contents
[1. Introduction](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica#introduction-1) <br>
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
Content seen on the ICG class. (Teacher Christian Azambuja)

## T2 - Graphic Pipeline
### Introduction
In the previous task, we have implemented an algorithm to rasterize primitives which is one of the last steps of the graphic pipeline, now we have to implement the full pipeline, by getting the vertices from a object from the object space and take them to the screen space, by doing a series of transformations, and then using the rasterization algorithm to display the object on the screen. In order to import a Wavefront .obj file we've used the [kixor obj loader](http://www.kixor.net/dev/objloader/)

![alt text](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica/raw/master/pictures/pipeline.png "")

#### Contents
[1. Introduction](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica#introduction-1) <br>
[2. Object Space to Universe Space](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica#object-space-to-universe-space) <br>
[3. Universe Space to Camera Space](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica#universe-space-to-camera-space) <br>
[4. Camera Space to Clipping Space](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica#camera-space-to-clipping-space) <br>
[5. Clipping Space to Canonical Space](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica#clipping-space-to-canonical-space) <br>
[6. Canonical Space to Screen Space](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica#canonical-space-to-screen-space) <br>
[7. Conclusion](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica#conclusion-1) <br>
[8. References](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica#references-1) <br>

### Object Space to Universe Space
The first transformation consists in taking the vertices, originally at the object space, to the universe space, at this step we can apply some geometric tansformations to the object and in the end we get the model matrix. Since some of the transformations we will see cannot be represented by a matrix we have to use the homogenous coordinates.

Note: before/after pictures on this section have been taken after all the pipeline steps were implemented.

#### Geometric Transformations
#### Scale
This transformation changes the object vertices by a scale factor, it can change length and direction. The matrix form for this transformation is:

![alt text](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica/blob/master/pictures/scale.png "")

Let's assume we want to shrink our object by a factor of two, the matrix will be:
```C++
    glm::mat4 scale(0.5, 0, 0, 0,
                    0, 0.5, 0, 0,
                    0, 0, 0.5, 0,
                    0, 0, 0, 1);
                    
    mModel = mModel * scale;             
```
And the before and after the transformation :

![alt text](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica/blob/master/pictures/scaled.png "")

#### Shear
A shear fixes all the points along a given line L and shifts the others by a distance proportional to their perpendicular distance from L.

![alt text](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica/blob/master/pictures/shear.png "")

To demonstrate this transformation we will, change our object a amount proportional to 1 unit of Y:
```C++
    glm::mat4 shear(1, 1, 0, 0,
                    0, 1, 0, 0,
                    0, 1, 1, 0,
                    0, 0, 0, 1);
                    
    mModel = mModel * shear;             
```
![alt text](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica/blob/master/pictures/sheared.png "")

#### Rotation
This transformation rotates the object by a given angle counterclockwise around the coordinate system origin and about an axis. In the 3D space we have three possibilities of rotations (about the X, Y or Z axis):

![alt text](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica/blob/master/pictures/rotation.png "")

Now let's rotate our head by 45 degrees about the X axis, here's our matrix:
```C++
    #define PI 3.14159265
    
    float theta = 45.0f;
    glm::mat4 rotation(1, 0, 0, 0,
                       0, cos((theta * PI)/ 180), -sin((theta * PI)/ 180), 0,
                       0, sin((theta * PI)/ 180), cos((theta * PI)/ 180), 0,
                       0, 0, 0, 1);
    mModel = mModel * rotation;             
```
![alt text](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica/blob/master/pictures/rotated.png "")

And a demonstration using other model (hat.Obj) rotating about the Y axis:
<p align="center">
 <img src="https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica/blob/master/pictures/rotation.gif">
 </p>

#### Translation
A translation transformation consists on moving the object, however, this transformation is an affine transformation and to represent it in a matrix we need to do a linear transformation to a space that have N+1 dimension, followed by a translation:

![alt text](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica/blob/master/pictures/translate.png "")

To demonstrate this, we will translate the head by 1 in the X axis:
```C++
    glm::mat4 translate(1, 0, 0, 1,
                        0, 1, 0, 0,
                        0, 0, 1, 0,
                        0, 0, 0, 1);
                    
    mModel = mModel * translate;             
```
![alt text](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica/blob/master/pictures/translated.png "")

#### Composing transformations
The representation of geometric transformations with matrices allows the composition of them using matrix product. However, since the matrix product is not comutative, the order of them matters, the most to the right matrix will be applied first.
(Note: In the glm library the most the left matrix is applied first.)

### Universe Space to Camera Space
At this stage of the graphic pipeline, we have to change the vertices from a coordinate system to another, in this case, the camera space with a change of basis. In the end of this transformation we get the View matrix which contains a rotation and a translation.

![alt text](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica/blob/master/pictures/basis.png "")

The new basis need to have linear independence, orthogonality and needs to be a orthonormal basis. To build this basis we need to receive three parameters (Position, Look at, Up). The position is where the camera is located at the universe space, while the Look At is where the camera is looking at and the up is the unit vector at the Y axis. Let's assume we want to create a camera looking at the origin while located at the P = (0,0,3). Our parameters would be:
```C++
    glm::vec3 camera_pos(0, 0, 3);
    glm::vec3 camera_lookat(0, 0, 0);
    glm::vec3 camera_up(0, 1, 0);
```

The camera's direction is at the opposite side of it's z axis. So we have to subtract the Look at with the position vector:
```C++
    glm::vec3 camera_dir = camera_lookat - camera_pos;
```

However this stage is not done yet, after this we have to get the (X,Y,Z) of the new basis:
```C++
    glm::vec3 camera_dir = camera_lookat - camera_pos;
    
    glm::vec3 z_camera = -glm::normalize(camera_dir);
    glm::vec3 x_camera = glm::normalize(glm::cross(camera_up, z_camera));
    glm::vec3 y_camera = glm::normalize(glm::cross(z_camera, x_camera));
```

We can now create the View matrix, which is composed by a rotation matrix Bt and a translation matrix T:
```C++
    glm::mat4 Bt(x_camera.x, x_camera.y, x_camera.z, 0,
                 y_camera.x, y_camera.y, y_camera.z, 0,
                 z_camera.x, z_camera.y, z_camera.z, 0,
                 0, 0, 0, 1);
    
    glm::mat4 T(1, 0, 0, -camera_pos.x,
                0, 1, 0, -camera_pos.y,
                0, 0, 1, -camera_pos.z,
                0, 0, 0, 1);
    
    glm::mat4 mView = Bt * T;
```    
### Camera Space to Clipping Space
After building the View matrix, we now move to the clipping space where triangles outside the frustum are cut into smaller triangles. At this stage we get the Projection matrix.

To build the Projection matrix, we have to move the camera a distance d on the positive direction of Z and project a P point at the camera space on the view plane, with this we can find the coordinates of P on the clipping space and represent it with a matrix:
![alt text](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica/blob/master/pictures/clipping.png "")

```C++
    p(x,y,z,1);
    //Parts of the code omitted
    float d = 1.0f;
    
    glm::mat4 mP(1, 0, 0, 0,
                 0, 1, 0, 0,
                 0, 0, 1, 0,
                 0, 0, -1/d, 0); 
    p = p * mP;                      
```

However, we still need to apply a translation of d units on P's Z coordinate, to move the camera back to the origin, we can do the product of the mP and mT matrices and combine them into a single matrix, the Projection matrix, after this we do the product of Model, View and Project matrices(in this order!) to get the ModelViewProjection matrix:
```C++
    glm::mat4 mProjection(1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 1, d,
                          0, 0, -1/d, 0);

    glm::mat4 mModelViewProjection = mModel * mView * mProjection;
```
After this step, the W coordinate may have a value different than 1.

### Clipping Space to Canonical Space
The canonical space consists of a cube limited by unit coordinates, it contains our scene. To do this we have to define a bounding volume around the scene somehow in the camera space, the volume will become the canonical space. This is done in two steps:

1. Homogenize, we divide the vertex by W.
2. Multiply by a matrix that contains the translation and scale that defines the canonical cube.

![alt text](https://github.com/DefinitelyNotACactus/IntroComputacaoGrafica/blob/master/pictures/canonical.png "")

(In progress) 


### Canonical Space to Screen Space
(In progress)

### Conclusion
This assignment has helped us to understand the steps of the graphic pipeline, how to implement it and the use of .obj files, there's some improvements that can be done, for instance, the triangles drawn are not filled. In terms of difficulties found, we had some issues at using the glm library, for instance the product of matrices is done in a opposite order and the glm::normalize() function needs to be called before the glm::cross() when getting the camera vectors.

### References
[Shear](http://mathworld.wolfram.com/Shear.html)<br>
[3D Transformation](https://www.tutorialspoint.com/computer_graphics/3d_transformation.htm)<br>
[The Perspective and Orthographic Projection Matrix](https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/projection-matrix-GPU-rendering-pipeline-clipping)
Content seen on the ICG class. (Teacher Christian Azambuja)
