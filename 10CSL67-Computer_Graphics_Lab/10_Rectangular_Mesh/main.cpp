/*
Authored and Documented By:

   *    Aditi Anomita Mohanty
            aditi.anomita@gmail.com
            www.github.com/rheaditi

    *   Abinav Nithya Seelan
            abinav.n.seelan@gmail.com
            www.github.com/abinavseelan

    ( http://www.vanillalabs.me )
*/

#include <iostream>
#include <GL/glut.h>

using namespace std;

int xOrigin, yOrigin, xWidth, yWidth;
int numRows, numColumns;

/*
Example Values to Input:
    xOrigin = 50, yOrigin = 50;
    xWidth = 50 , yWidth = 50;
    numRows = 10, numColumns = 5;
*/

void display()
{
    int i, j;
    int x=xOrigin,y=yOrigin;

    glColor3f(102.0/255,45.0/255,145.0/255);

    //draws the mesh using line loops
    for(i=0; i<numRows; i++)
    {
        x=xOrigin;
        for(j=0; j<numColumns; j++)
        {
            glBegin(GL_LINE_LOOP);
                glVertex2f(x,y);
                glVertex2f(x+xWidth,y);
                glVertex2f(x+xWidth,y+yWidth);
                glVertex2f(x,y+yWidth);
            glEnd();

            x += xWidth;
        }
        y += yWidth;
    }

    glFlush();
}

int main(int argc, char ** argv)
{
    cout << "Co-ordinate system is between (1,1) and (600,600). Enter the following:-\n\n";

    cout << "Origin (bottom-left) co-ordinates:\n";
    cout << "x: ";
    cin >> xOrigin;

    cout << "y: ";
    cin >> yOrigin;

    cout << "\n\nWidth of each cell:\n";
    cout << "In x: ";
    cin >> xWidth;

    cout << "In y: ";
    cin >> yWidth;

    cout << "\n\nNumber of Rows: ";
    cin >> numRows;
    cout << "Number of Columns: ";
    cin >> numColumns;

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600,600);
    glutCreateWindow("Program #10: Rectangular Mesh");

    glutDisplayFunc(display);

    glClearColor(34.0/255,34.0/255,34.0/255,1.0);
    gluOrtho2D(1,600,1,600);

    glutMainLoop();
    return 0;
}
