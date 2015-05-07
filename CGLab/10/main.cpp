#include <iostream>
#include<GL/glut.h>

using namespace std;

int numberOfRows;
int numberOfColumns;
int width;

int main(int argc, char** argv)
{
        cout<<endl<<"Enter Number Of Rows: ";
        cin>>numberOfRows;
        cout<<endl<<"Enter Number Of Columns: ";
        cin>>numberOfColumns;
        cout<<endl<<"Enter The Width Of Each Cell: ";
        cin>>width;

        glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
        glutInitWindowSize(600,600);
        glutInitWindowPosition(100,100);
        glutCreateWindow("Rectangular Mesh");
        myInit();
        glutDisplayFunc(display);
        glutMainLoop();
}

void myInit()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0,1.0,1.0,1.0);
    glPointSize(3.0);
}

void display()
{
    glBegin(GL_LINES);
        glVertex2d
}
