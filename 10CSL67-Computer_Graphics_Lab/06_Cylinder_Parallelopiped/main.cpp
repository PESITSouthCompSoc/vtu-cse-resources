#include <iostream>
#include <GL/glut.h>

/*the X and Y differences between successive rectangles and circles*/
#define X_INC 5
#define Y_INC 5

using namespace std;

int iterations=20;

struct {
  int x0, y0, x1, y1;
} quad;

struct {
    float center[2], radius;
} circle;

/* example values to give : -
quad.x0=50, quad.y0=50;
quad.x0=200, quad.y0=200;

circle.center[0]=400,circle.center[1]=400;
circle.radius=50;

*/

void symPixels(float h, float k, float x, float y)
{
    glBegin(GL_POINTS);
        glVertex2f(x+h,y+k);
        glVertex2f(-x+h,y+k);
        glVertex2f(-x+h,-y+k);
        glVertex2f(x+h,-y+k);

        glVertex2f(y+h,x+k);
        glVertex2f(-y+h,x+k);
        glVertex2f(-y+h,-x+k);
        glVertex2f(y+h,-x+k);
    glEnd();
}

void drawCircle(float h, float k, float r)//h,k center and r is the radius
{
    float d=1-r, x=r, y=0;
    while(x >= y)
    {
        symPixels(h,k,x,y);
        y++;

        //to accommodate for the error
        if(d<0)
            d += 2*y + 1;
        else
        {
            x--; //next x
            d += 2*(y-x) + 1;
        }

    }
}

void cylinder(float h, float k, float r)
{
    int i;
    for(i=0; i<iterations; i++)
    {
        drawCircle(h+(i*X_INC),k+(i*Y_INC),r); //for oblique cylinder
        //drawCircle(h+,k+(i*Y_INC),r); //upright cylinder
        //drawCircle(h+(i*X_INC),k,r); //cylinder lying down =P
    }
}

void parallelepiped()
{
    int i;
    for(i=0; i<iterations; i++)
    {
        //one rectangle at a time.
        glBegin(GL_LINE_LOOP);
            glVertex2f( quad.x0 +(i*X_INC) , quad.y0 + (i*Y_INC) );
            glVertex2f( quad.x1 +(i*X_INC) , quad.y0 + (i*Y_INC) );
            glVertex2f( quad.x1 +(i*X_INC) , quad.y1 + (i*Y_INC) );
            glVertex2f( quad.x0 +(i*X_INC) , quad.y1 + (i*Y_INC) );
        glEnd();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(236.0/255,0.0,140.0/255);
    cylinder(circle.center[0],circle.center[1],circle.radius);

    glColor3f(0.0,114.0/255,188.0/255);
    parallelepiped();

    glFlush();
}

int main(int argc, char ** argv)
{
    cout << "Co-ordinate system is between (1,1) and (600,600). Enter the following:-\n\n";

    cout << "Parallelepiped:\nxmin: ";
    cin >> quad.x0;
    cout << "ymin: ";
    cin >> quad.y0;
    cout << "xmax: ";
    cin >> quad.x1;
    cout << "ymax: ";
    cin >> quad.y1;

    cout << "\n\nCylinder:\nCenterX: ";
    cin >> circle.center[0];
    cout << "CenterY: ";
    cin >> circle.center[1];
    cout << "Radius: ";
    cin >> circle.radius;

    cout << "\n\n# of Iterations: ";
    cin >> iterations;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(600,600);
    glutCreateWindow("Program #6: Cylinder & Parallelepiped");
    glutDisplayFunc(display);

    /* initializations */
    glClearColor(34.0/255,34.0/255,34.0/255,1.0);//dark grey
    gluOrtho2D(1,600,1,600);


    glutMainLoop();
    return 0;
}
