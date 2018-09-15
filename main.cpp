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

#define PI 3.14159265

float theta = 0.0f; //degree
//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
    ClearScreen();
    objLoader *objData = new objLoader();
    objData->load("mario_head.obj");
    int faceCount = objData->faceCount;
    
    //Object Space
    glm::mat4 mModel(1);

    //Transformations
    //Scale by 0.5 (Isotropic scale)
    glm::mat4 scale(2, 0, 0, 0,
                    0, 2, 0, 0,
                    0, 0, 2, 0,
                    0, 0, 0, 1);
    
    //Shear matrix
    glm::mat4 shear(1, 1, 0, 0,
                    0, 1, 0, 0,
                    0, 1, 1, 0,
                    0, 0, 0, 1);
    
    //Rotation matrix
    glm::mat4 rotate(cos((theta * PI)/ 180), 0, sin((theta * PI)/ 180), 0,
                       0, 1, 0, 0,
                       -sin((theta * PI)/ 180), 0, cos((theta * PI)/ 180), 0,
                       0, 0, 0, 1);
    
    //Translation matrix
    glm::mat4 translate(1, 0, 0, 0,
                        0, 1, 0, -2,
                        0, 0, 1, 0,
                        0, 0, 0, 1);
    
    //mModel = mModel * translate * rotate * shear * scale;
    mModel = mModel * scale * translate * rotate;
    
    //Camera Space
    glm::vec3 camera_pos(0, 0, 5);
    glm::vec3 camera_lookat(0, 0, 0);
    glm::vec3 camera_up(0, 1, 0);
    
    glm::vec3 camera_dir = camera_lookat - camera_pos;
    
    glm::vec3 z_camera = -glm::normalize(camera_dir);
    glm::vec3 x_camera = glm::normalize(glm::cross(camera_up, z_camera));
    glm::vec3 y_camera = glm::normalize(glm::cross(z_camera, x_camera));

    glm::mat4 Bt(x_camera.x, x_camera.y, x_camera.z, 0,
                 y_camera.x, y_camera.y, y_camera.z, 0,
                 z_camera.x, z_camera.y, z_camera.z, 0,
                 0, 0, 0, 1);
    
    glm::mat4 T(1, 0, 0, -camera_pos.x,
                0, 1, 0, -camera_pos.y,
                0, 0, 1, -camera_pos.z,
                0, 0, 0, 1);
    
    glm::mat4 mView = Bt * T;
    
    //Projection
    float d = 2.5f;
    
    glm::mat4 mProjection(1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 1, d,
                          0, 0, -1/d, 0);

    glm::mat4 mModelViewProjection = mModel * mView * mProjection;

    //Viewport
    glm::mat4 S1(1, 0, 0, 0,
                 0, -1, 0, 0,
                 0, 0, 1, 0,
                 0, 0, 0, 1);

    T = glm::mat4(1, 0, 0, 1,
                  0, 1, 0, 1,
                  0, 0, 1, 0,
                  0, 0, 0, 1);

    glm::mat4 S2((IMAGE_WIDTH-1)/2, 0, 0, 0,
                 0, (IMAGE_HEIGHT-1)/2, 0, 0,
                 0, 0, 1, 0,
                 0, 0, 0, 1);
    
    glm::mat4 mViewport = S1 * T * S2;
    
    glm::vec4 vertices[3];
    
    //Get the faces
    for(int i = 0; i < faceCount; i++){
        obj_face *o = objData->faceList[i];
        for(int j = 0; j < 3; j++){
            //Get the vertex
            glm::vec4 aux(objData->vertexList[o->vertex_index[j]]->e[0], objData->vertexList[o->vertex_index[j]]->e[1], objData->vertexList[o->vertex_index[j]]->e[2], 1);
            //Move it to projection space
            aux = aux * mModelViewProjection;
            //Homogenize
            aux = aux/aux.w;
            //Move it to screen space
            aux = glm::round(aux * mViewport);
            vertices[j] = aux;
        }
        //Draw the face
        DrawTriangle(new Pixel(vertices[0].x, vertices[0].y, 255, 255, 255, 255), new Pixel(vertices[1].x, vertices[1].y, 255, 255, 255, 255), new Pixel(vertices[2].x, vertices[2].y, 255, 255, 255, 255));
    }
    //glutPostRedisplay();
    //glutTimerFunc(5, timer, 0);
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
        //glutTimerFunc( 5, timer, 0);
        //glutIdleFunc(idle);
	glutMainLoop();

	return 0;
}

