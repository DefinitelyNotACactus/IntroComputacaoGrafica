#include "main.h"
#include "Pixel.h"

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as fun��es do mygl.h
	//*************************************************************************
    /*Pixel pxlc(255, 255, 0, 255, 0, 255);
    
    Pixel pxl2(0, 0, 0, 0, 255, 255);
    Pixel pxl3(0, 255, 0, 0, 255, 255);
    Pixel pxl4(0, 511, 0, 0, 255, 255);
    Pixel pxl5(255, 511, 0, 0, 255, 255);
    Pixel pxl6(511, 511, 0, 0, 255, 255);
    Pixel pxl7(511, 255, 0, 0, 255, 255);
    Pixel pxl8(511, 0, 0, 0, 255, 255);
    Pixel pxl9(255, 0, 0, 0, 255, 255);

    Pixel pxla(100, 120, 255, 255, 255, 255);
    Pixel pxlb(450, 300, 255, 255, 255, 255);
    Pixel pxlcc(190, 200, 255, 255, 255, 255);
    
    DrawLine(&pxl2, &pxlc);
    DrawLine(&pxl3, &pxlc);
    DrawLine(&pxl4, &pxlc);
    DrawLine(&pxl5, &pxlc);
    DrawLine(&pxl6, &pxlc);
    DrawLine(&pxl7, &pxlc);
    DrawLine(&pxl8, &pxlc);
    DrawLine(&pxl9, &pxlc);
    
    DrawTriangle(&pxla, &pxlb, &pxlcc);
    */
    //Pixel pxl1 = new Pixel(155, 155, 255, 0, 0, 255);
    //Pixel pxl2()
    Pixel pxl2(255, 255, 255, 255, 255, 255);
    PutPixel(&pxl2);
    //Pixel
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;	

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

