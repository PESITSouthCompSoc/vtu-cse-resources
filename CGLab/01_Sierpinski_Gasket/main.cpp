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

int n; //for the number of iterations
float vertex[][3] = { {0,0,1},{-0.5,-1.0/3,-1},{0.5,-1.0/3,-1},{0,2.0/3,-1} };

//draw a single triangle
void triangle(float *a, float *b, float *c)
{
    glBegin(GL_POLYGON);
        glVertex3fv(a);
        glVertex3fv(b);
        glVertex3fv(c);
    glEnd();
}

//a recursive function to divide each face of the tetrahedron successively
void divide_triangle(float *a, float *b, float *c, int m)
{
    if(m>0)
    {
        float abMid[3], bcMid[3], caMid[3];
        int i;
        for(i=0; i<3; i++) //find the mid-point of each of the edges
        {
            abMid[i]=(a[i]+b[i])/2.0;
            bcMid[i]=(b[i]+c[i])/2.0;
            caMid[i]=(c[i]+a[i])/2.0;
        }

        //recursively sub-divide the triangles, excluding the middle one
        divide_triangle(a,abMid,caMid,m-1);
        divide_triangle(abMid,b,bcMid,m-1);
        divide_triangle(caMid,bcMid,c,m-1);
    }
    else //stop dividing when m=0
        triangle(a,b,c);
}

void tetrahedron(int m)
{
    //each face of the tetrahedron gets a different color
    glColor3f(135.0/255,129.0/255,189.0/255);
    divide_triangle(vertex[1],vertex[2],vertex[0],m);

    glColor3f(236.0/255,0.0,140.0/255);
    divide_triangle(vertex[2],vertex[3],vertex[0],m);

    glColor3f(0.0,114.0/255,188.0/255);
    divide_triangle(vertex[3],vertex[1],vertex[0],m);

    glColor3f(102.0/255,45.0/255,145.0/255);
    divide_triangle(vertex[1],vertex[2],vertex[3],m);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    //set the co-ordinate system
    glOrtho(-1,1,-1,1,-2,20);

    tetrahedron(n);

    glFlush();
}

int main(int argc, char ** argv)
{
    cout << "Enter number iterations: ";
    cin >> n;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);

    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("01 - Sierpinski Gasket");
    glEnable(GL_DEPTH_TEST);
    glClearColor(34.0/255,34.0/255,34.0/255,1.0);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
