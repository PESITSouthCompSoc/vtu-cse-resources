#include <iostream>
#include <GL/glut.h>
#include <windows.h>
using namespace std;

float vertex[8][3] = { {-1,-1,1},{-1,1,1},{1,1,1}, {1,-1,1}, {-1,-1,-1}, {-1,1,-1}, {1,1,-1}, {1,-1,-1} };
float color[8][3] = { {0,1,0}, {0,1,1}, {1,1,1}, {1,1,0}, {0,0,0}, {0,0,1}, {1,0,1}, {1,0,0} };
float viewer[3]={0,0,5};
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
    glLoadIdentity();
    gluLookAt(viewer[0],viewer[1],viewer[2],0,0,0,0,1,0);
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
            theta[0]= (theta[0]+2)%360;
        else if(btn==GLUT_RIGHT_BUTTON)
            theta[1]= (theta[1]+2)%360;
        else if(btn=GLUT_MIDDLE_BUTTON)
            theta[2]= (theta[2]+2)%360;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    if(key=='x')
        viewer[0]+=0.1;
    else if(key=='X')
        viewer[0]-=0.1;
    glutPostRedisplay();
}
void reshape(int w, int h)
{
    glViewport(0,0,w,h);
    float Ratio = (w<=h)? h/w : w/h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-2.0,2.0,-2.0*Ratio,2.0*Ratio,2.0,20.0);
    glMatrixMode(GL_MODELVIEW);

}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("03 - Spin Cube");
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}

