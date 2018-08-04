#include "main.h"
#include "Pixel.h"

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as fun��es do mygl.h
	//*************************************************************************
    Pixel pxlc(256, 256, 0, 255, 0, 255);
    
    Pixel pxl2(0, 0, 0, 0, 255, 255);
    Pixel pxl3(0, 256, 0, 0, 255, 255);
    Pixel pxl4(0, 511, 0, 0, 255, 255);
    Pixel pxl5(256, 511, 0, 0, 255, 255);
    Pixel pxl6(511, 511, 0, 0, 255, 255);
    Pixel pxl7(511, 256, 0, 0, 255, 255);
    Pixel pxl8(511, 0, 0, 0, 255, 255);
    Pixel pxl9(256, 0, 0, 0, 255, 255);

    Pixel pxl10(0, 128, 0, 255, 0, 255);
    Pixel pxl11(0, 384, 0, 255, 0, 255);
    Pixel pxl12(128, 511, 0, 255, 0, 255);
    Pixel pxl13(384, 511, 0, 255, 0, 255);
    Pixel pxl14(511, 384, 0, 255, 0, 255);
    Pixel pxl15(511, 128, 0, 255, 0, 255);
    Pixel pxl16(384, 0, 0, 255, 0, 255);
    Pixel pxl17(128, 0, 0, 255, 0, 255);
    
    DrawLine(&pxl2, &pxlc);
    DrawLine(&pxl3, &pxlc);
    DrawLine(&pxl4, &pxlc);
    DrawLine(&pxl5, &pxlc);
    DrawLine(&pxl6, &pxlc);
    DrawLine(&pxl7, &pxlc);
    DrawLine(&pxl8, &pxlc);
    DrawLine(&pxl9, &pxlc);
    DrawLine(&pxl10, &pxlc);
    DrawLine(&pxl11, &pxlc);
    DrawLine(&pxl12, &pxlc);
    DrawLine(&pxl13, &pxlc);
    DrawLine(&pxl14, &pxlc);
    DrawLine(&pxl15, &pxlc);
    DrawLine(&pxl16, &pxlc);
    DrawLine(&pxl17, &pxlc);
    
    //Pixel pxl1 = new Pixel(155, 155, 255, 0, 0, 255);
    //Pixel pxl2()
    //Pixel pxl2(255, 255, 255, 255, 255, 255);
    //PutPixel(&pxl2);
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

