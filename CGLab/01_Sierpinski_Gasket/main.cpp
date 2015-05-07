#include <iostream>
#include<GL/glut.h>

using namespace std;

float vertex[][3] = { {0.0,0.0,0.66}, {0.0,0.66,-1.0}, {0.5,-0.33,-1.0}, {-0.5,-0.33,-1} };

void triangle(float * a, float *b, float *c)
{
    glBegin(GL_TRIANGLES);
        glVertex3fv(a);
        glVertex3fv(b);
        glVertex3fv(c);
    glEnd();
    glFlush();
}

void divide_triangle(float *a, float *b, float *c, int m)
{
    if(m>0)
    {
        float abMid[3], bcMid[3], caMid[3];
        int i;
        for(i=0; i<3; i++)
        {
            abMid[i]=(a[i]+b[i])/2.0;
            bcMid[i]=(b[i]+c[i])/2.0;
            caMid[i]=(c[i]+a[i])/2.0;
        }
        divide_triangle(a,abMid,caMid,m-1);
        divide_triangle(abMid,b,bcMid,m-1);
        divide_triangle(caMid,bcMid,c,m-1);
    }
    else
        triangle(a,b,c);
}

void tetrahedron(int m)
{
    glColor3f(1.0,1.0,0.0);
    divide_triangle(vertex[0],vertex[3],vertex[1],m);
    glColor3f(1.0,0.0,0.0);
    divide_triangle(vertex[3],vertex[2],vertex[1],m);
    glColor3f(0.0,1.0,0.0);
    divide_triangle(vertex[0],vertex[2],vertex[3],m);
    glColor3f(0.0,0.0,1.0);
    divide_triangle(vertex[0],vertex[1],vertex[2],m);
}

void display()
{
    glOrtho(-1.0,1.0,-1.0,1.0,-2.0,2.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPolygonMode(GL_BACK,GL_FILL);
    tetrahedron(2);
    glFlush();
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("01 - Sierpinski Gasket");
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0,1.0,1.0,1.0);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
