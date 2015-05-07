#include <iostream>
#include<GL/glut.h>

using namespace std;

float xmin=10, ymin=10, xmax=200, ymax=200, dx=10, dy=10;

void myInit()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0,1.0,1.0,1.0);
}

void display()
{
    float x, y;
    glColor3f(1.0,0.0,0.0);
    for(x=xmin; x<xmax; x+=dx)
    {
        for(y=ymin; y<ymax; y+=dy)
        {
            glBegin(GL_LINE_LOOP);
                glVertex2f(x,y);
                glVertex2f(x+dx,y);
                glVertex2f(x+dx,y+dy);
                glVertex2f(x,y+dy);
            glEnd();
        }
    }
    glFlush();
}

int main(int argc, char** argv)
{
        cout<<endl<<"Enter the following:-\n";
        cout<<"xmin: ";
        cin>>xmin;
        cout<<"ymin: ";
        cin>>ymin;
        cout<<"xmax: ";
        cin>>xmax;
        cout<<"ymax: ";
        cin>>ymax;
        cout<<"dx: ";
        cin >> dx;
        cout<<"dy: ";
        cin >> dy;

        glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
        glutInitWindowSize(600,600);
        glutInitWindowPosition(100,100);
        glutCreateWindow("Rectangular Mesh");
        myInit();
        gluOrtho2D(0,600,0,600);
        glutDisplayFunc(display);
        glutMainLoop();
}
