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
#include <windows.h> /* Required for Sleep() call, to slow down the spinning. Windows Specific. */
/* You must remove this and the corresponding Sleep() call if you wish to execute this code on Linux. */

using namespace std;

//define a cube with 0,0,0 as center (each edge is therefor 2 units in length)
float vertex[8][3] =    {   {-1,-1,1},{1,-1,1},{1,1,1},{-1,1,1},
                            {-1,-1,-1},{1,-1,-1},{1,1,-1},{-1,1,-1},
                        };

//taking [4] to be black and [2] to be white
//[5] as Red, [7] as Green and [0] as Blue
float color[8][3] = {   {0,0,1}, {1,0,1}, {1,1,1}, {0,1,1},
                        {0,0,0}, {1,0,0}, {1,1,0}, {0,1,0}
                    };

int axis=1; //the default axis of rotation (Y)
int theta[3] = {0};

void face(int a, int b, int c, int d)
{
    //each vertex and it's assigned color
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
    //6 faces of a cube - be careful about the front and back faces, give order of vertices accordingly

    //front faces (anti-clockwise):
    face(0,1,2,3);
    face(1,5,6,2);
    face(3,2,6,7);

    //back faces (clockwise):
    face(4,7,6,5);
    face(0,4,5,1);
    face(0,3,7,4);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //3 angles of rotation, about X-axis, Y-axis and Z-axis respectively
    glRotated(theta[0],1,0,0);
    glRotated(theta[1],0,1,0);
    glRotated(theta[2],0,0,1);

    cube();

    glutSwapBuffers();
}

void idleSpin() // to keep the cube spinning in the chosen direction
{
    //increase theta in increments of 2
    theta[axis] = (theta[axis]+2) % 360;

    //sleep for 10 ms
    Sleep(10);

    //re-draw cube
    glutPostRedisplay();
}

void reshape(int w, int h)
{
    //to maintain a square-shaped viewport
    int width = w<h ? w:h;
    glViewport(0,0,width,width);
}

void mouse(int btn, int state, int x, int y) //3 mouse buttons to select 3 different axes
{
    if(state == GLUT_DOWN)
    {
        switch(btn)
        {
        case GLUT_LEFT_BUTTON:
            axis=0;
            break;
        case GLUT_RIGHT_BUTTON:
            axis=1;
            break;
        case GLUT_MIDDLE_BUTTON:
            axis=2;
            break;
        default:
            axis=1;
        }
    }
}

int main(int argc, char ** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600,600);
    glutCreateWindow("03 - Spinning Color Cube");

    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(idleSpin);

    glEnable(GL_DEPTH_TEST);

    glClearColor(10.0/255,10.0/255,10.0/255,1.0); //dark grey
    glMatrixMode(GL_PROJECTION);
    glOrtho(-4,4,-4,4,-4,4);
    glMatrixMode(GL_MODELVIEW);

    glutMainLoop();
    return 0;
}
