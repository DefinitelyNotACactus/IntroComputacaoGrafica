#include "objTester/objLoader.h"

#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <stdio.h>

GLuint object;
float rot = 0.0f;
int z = 0;

void loadObj()
{
    objLoader *objData = new objLoader();
    objData->load("mario_head.obj");
    int faceCount = objData->faceCount;
    object = glGenLists(1);
    glNewList(object, GL_COMPILE);
    {
        glPushMatrix();
        for(int i = 0; i < faceCount; i++){
            obj_face *o = objData->faceList[i];
            glBegin(GL_LINES);
            glm::vec3 vertices[3];
            for(int j = 0; j < 3; j++){
                vertices[j] = glm::vec3(objData->vertexList[o->vertex_index[j]]->e[0], objData->vertexList[o->vertex_index[j]]->e[1], objData->vertexList[o->vertex_index[j]]->e[2]);
            }
            glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
            glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
            glEnd();
            glBegin(GL_LINES);
            glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
            glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
            glEnd();
            glBegin(GL_LINES);
            glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
            glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
            glEnd();
        }
        
    }
    glPopMatrix();
    glEndList();
}

void reshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
}

void draw()
{
    glPushMatrix();
    glTranslatef(0,-1,0);
    glRotatef(rot, 0, 1, 0);
    glColor3f(1.0,1.0,1.0);
    glCallList(object);
    glPopMatrix();
}

void display(void)
{
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    draw();
    glutSwapBuffers();
}

void keyPressed (unsigned char key, int x, int y) 
{  
    switch(key){
        case 'd':
            z = 0;
            rot+=1;
            break;
        case 'a':
            z = 0;
            rot -= 1;
            break;
        case 'w':
            z = 1;
            rot+=1;
            break;
        case 's':
            z = 1;
            rot -= 1;
            break;
    }
}  
int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(512,512);
    glutInitWindowPosition(20,20);
    glutCreateWindow("Obj Loader");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPressed);
    glutIdleFunc(display);
    loadObj();
    glutMainLoop();
    return 0;
}