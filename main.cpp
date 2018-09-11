#include "main.h"
#include "definitions.h"
#include "Pixel.h"

#include "objTester/objLoader.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/matrix.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as fun��es do mygl.h
	//*************************************************************************
    objLoader *objData = new objLoader();
    objData->load("C:/Users/David/Documents/NetBeans Projects/IntroComputacaoGrafica/monkey_head2.obj");
    
    Pixel *pxla;
    Pixel *pxlb;
    Pixel *pxlc;
    
    for(int i = 0; i < objData->faceCount; i++){
        obj_face* obj = objData->faceList[i];
        for(int j = 0; j < 3; j++){           
            glm::vec4 vertex(objData->vertexList[obj->vertex_index[j]]->e[0], objData->vertexList[obj->vertex_index[j]]->e[1], objData->vertexList[obj->vertex_index[j]]->e[2], 1.0f);
            //printf("%f %f %f %f\n", vertex.x, vertex.y, vertex.z, vertex.w);
            glm::mat4 mModel(1.0f, 0.0f, 0.0f, 0.0f,
                             0.0f, 1.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 1.0f, 0.0f,
                             0.0f, 0.0f, 0.0f, 1.0f);

            glm::vec3 camera_pos(1.3f, 2.1f, 2.5f);
            glm::vec3 camera_lookat(0.0f, 0.0f, 0.0f);
            glm::vec3 camera_up(0.0f, 1.0f, 0.0f);

            glm::vec3 camera_dir = camera_lookat - camera_pos;
            
            glm::vec3 z_camera = -(camera_dir)/glm::normalize(camera_dir);     
            glm::vec3 x_camera = glm::cross(camera_up, z_camera)/glm::normalize(glm::cross(camera_up, z_camera));
            x_camera.y = 0.0f;
            printf("%f %f %f %f\n", x_camera.x, x_camera.y, x_camera.z, vertex.w);
            glm::vec3 y_camera = glm::cross(z_camera, x_camera);
                        printf("%f %f %f %f\n", y_camera.x, y_camera.y, y_camera.z, vertex.w);

            
            glm::mat4 Bt(x_camera.x, x_camera.y, x_camera.z, 0.0f,
                         y_camera.x, y_camera.y, y_camera.z, 0.0f,
                         z_camera.x, z_camera.y, z_camera.z, 0.0f,
                         0.0f, 0.0f, 0.0f, 1.0f);

            glm::mat4 T(1.0f, 0.0f, 0.0f, -camera_pos.x,
                        0.0f, 1.0f, 0.0f, -camera_pos.y,
                        0.0f, 0.0f, 1.0f, -camera_pos.z,
                        0.0f, 0.0f, 0.0f, 1.0f);

            glm::mat4 mView = Bt * T;

            float d = 1.0f;

            glm::mat4 mProjection(1.0f, 0.0f, 0.0f, 0.0f,
                                  0.0f, 1.0f, 0.0f, 0.0f,
                                  0.0f, 0.0f, 1.0f, d,
                                  0.0f, 0.0f, -(1.0f/d), 0.0f);

            glm::mat4 mModelViewProjection = mProjection * mView * mModel;

            vertex = mModelViewProjection * vertex;
            vertex = vertex/vertex.w;
            //printf("%f %f %f %f\n", vertex.x, vertex.y, vertex.z, vertex.w);

            glm::mat4 S1(1.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, -1.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 1.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 1.0f);

            T = glm::mat4(1.0f, 0.0f, 0.0f, 1.0f,
                          0.0f, 1.0f, 0.0f, 1.0f,
                          0.0f, 0.0f, 1.0f, 0.0f,
                          0.0f, 0.0f, 0.0f, 1.0f);

            glm::mat4 S2((IMAGE_WIDTH-1.0f)/2.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, (IMAGE_HEIGHT-1.0f)/2.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 1.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 1.0f);

            glm::mat4 mViewport = S2 * T * S1;

            vertex = mViewport * vertex;
            
            switch(j%3){
                case 0:
                    pxla = new Pixel((int) vertex.x, (int) vertex.y, 0, 255, 0, 255);
                    break;
                case 1:
                    pxlb = new Pixel((int) vertex.x, (int) vertex.y, 0, 255, 0, 255);
                    break;
                case 2:
                    pxlc = new Pixel((int) vertex.x, (int) vertex.y, 0, 255, 0, 255);
                    break;
            }
        }
        DrawTriangle(pxla, pxlb, pxlc);
    }
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

