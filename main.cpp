#include "main.h"
#include "Pixel.h"

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as fun��es do mygl.h
	//*************************************************************************
    Pixel pxl1(200, 200, 255, 255, 255, 255);
    Pixel pxl2(512, 512, 255, 255, 255, 255);
    DrawLine(&pxl1, &pxl2);

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

