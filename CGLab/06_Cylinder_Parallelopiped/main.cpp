#include <iostream>
#include <GL/glut.h>

#define XSTEP 5
#define YSTEP 5

using namespace std;

void display();
void initialize();


int cx=300, cy=300, radius=50;
int xmin=20, ymin=20, xmax=200, ymax=200;
int iterations=15;

void rectangle(float a, float b, float c, float d)
{
    glBegin(GL_LINE_LOOP);
        glVertex2f(a,b);
        glVertex2f(c,b);
        glVertex2f(c,d);
        glVertex2f(a,d);
    glEnd();
}

void parallelopiped()
{
    int i, step;
    for(i=0, step=0; i<iterations; i++, step+=YSTEP)
    {
        rectangle(xmin+step,ymin+step,xmax+step,ymax+step);
    }
}

void symPixels(float h, float k, float x, float y)
{

}

void circle(float h, float k, float r)
{
    float d=1-r, x=r, y=0;
    while(x>=y)
    {
        symPixels(h,k,x,y);
        y++;
        if(d<0)
            d+= 2*y + 1;
        else
        {
            x--;
            d+= 2*(y-x)+1;
        }
    }
}


void cylinder()
{
    int i, step;

    for(i=0, step=0; i<iterations; i++, step+=YSTEP)
    {
        circle(cx+step,cy+step,radius);
    }
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(600,600);
    glutCreateWindow("Program #0: Title");
    initialize();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0,0.0,0.0);
    parallelopiped();

    glFlush();
}

void initialize()
{
    //CARARRA F2F1EF 242, 241, 239
    glClearColor(242.0/255.0,241.0/255.0,239.0/255.0,1.0);
    glPointSize(1.0);
    gluOrtho2D(0.0,599.0,0.0,599.0);
}

