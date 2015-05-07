#include <iostream>
#include <GL/glut.h>
#include <windows.h>
using namespace std;

float vertex[8][3] = { {-1,-1,1},{-1,1,1},{1,1,1}, {1,-1,1}, {-1,-1,-1}, {-1,1,-1}, {1,1,-1}, {1,-1,-1} };
float color[8][3] = { {0,1,0}, {0,1,1}, {1,1,1}, {1,1,0}, {0,0,0}, {0,0,1}, {1,0,1}, {1,0,0} };
int theta[3]={0,0,0};
int axis=1;

void face(int a, int b, int c, int d)
{
    glBegin(GL_POLYGON);
        glColor3fv(color[a]);
        glVertex3fv(vertex[a]);
        glColor3fv(color[b]);
        glVertex3fv(vertex[b]);
        glColor3fv(color[c]);
        glVertex3fv(vertex[c]);
        glColor3fv(color[d]);
        glVertex3fv(vertex[d]);
    glEnd();
}

void cube()
{
    face(0,3,2,1);
    face(3,7,6,2);
    face(1,2,6,5);

    face(0,4,7,3);
    face(7,4,5,6);
    face(0,1,5,4);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(theta[0],1.0,0.0,0.0);
    glRotated(theta[1],0.0,1.0,0.0);
    glRotated(theta[2],0.0,0.0,1.0);

    cube();
    glutSwapBuffers();
}

void mouse(int btn, int state, int x, int y)
{
    if(state==GLUT_DOWN)
    {
        if(btn==GLUT_LEFT_BUTTON)
            axis=0;
        else if(btn==GLUT_RIGHT_BUTTON)
            axis=1;
        else if(btn=GLUT_MIDDLE_BUTTON)
            axis=2;
    }
}


void idleSpin()
{
    theta[axis] = (theta[axis]+2)%360;
    Sleep(50);
    glutPostRedisplay();
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("03 - Spin Cube");
    glutMouseFunc(mouse);
    glutDisplayFunc(display);
    glutIdleFunc(idleSpin);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-4,4,-4,4,-4,4);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(1.0,1.0,1.0,1.0);

    glutMainLoop();
    return 0;
}

