#include <iostream>
#include <GL/glut.h>

#define RIGHT 8
#define LEFT 4
#define TOP 2
#define BOTTOM 1

#define outcode int

using namespace std;

void display();
void initialize();

float xmin, ymin, xmax, ymax, xvmin, yvmin, xvmax, yvmax;

struct line{
    float x0, y0, x1, y1;
};
line l1, l2;

outcode compute(float x, float y)
{
    outcode o=0;
    if(y>ymax)
        o|=TOP;
    else if(y<ymin)
        o|=BOTTOM;
    if(x>xmax)
        o|=RIGHT;
    else if(x<xmin)
        o|=LEFT;
    return o;
}

void CSClip(float x0, float y0, float x1, float y1)
{
    int accept=0, done=0;
    outcode oc0, oc1, ocOut;
    oc0=compute(x0,y0);
    oc1=compute(x1,y1);
    cout << "oc0: " << oc0 <<endl;
    cout << "oc1: " << oc1 <<endl;
    do
    {
        if( !(oc0|oc1) ) //if both are completely inside (both oc 0000
        {
            accept=1;
            done=1;
            cout <<"accepted\n";
        }
        else if( oc0&oc1 ) //they are in the same quadrant, trivially reject
        {
            done=1;
            cout <<"rejected\n";
        }
        else
        {
                double x, y;
                ocOut = oc0 ? oc0 : oc1; //pick either point,whichever is non zero
                if( ocOut & TOP ) //pt is above clip window
                {
                    x = x0 + (x1-x0)*(ymax-y0)/(y1-y0);
                    y = ymax;
                }
                else if( ocOut & BOTTOM )
                {
                    x = x0 + (x1-x0) * (ymin - y0) / (y1 - y0);
                    y = ymin;
                }
                else if( ocOut & RIGHT )
                {
                    x = xmax;
                    y = y0 + (y1-y0) * (xmax - x0) / (x1-x0);
                }
                else if( ocOut & LEFT )
                {
                    x = xmin;
                    y = y0 + (y1-y0) * (xmin - x0) / (x1-x0);
                }
                if(ocOut==oc0)//if we picked 1st point
                {
                    x0=x; y0=y;
                    oc0 = compute(x0,y0);
                }
                else
                {
                    x1=x, y1=y;
                    oc1 = compute(x1,y1);
                }
        }
    }while(!done);

    if(accept)
    {
        double sx, sy, vx0, vy0, vx1, vy1;

        sx = (xvmax-xvmin)/(xmax-xmin);
        sy = (yvmax-yvmin)/(ymax-ymin);

        vx0 = xvmin + (x0-xmin)*sx;
        vy0 = yvmin + (y0-ymin)*sy;

        vx1 = xvmin + (x1-xmin)*sx;
        vy1 = yvmin + (y1-ymin)*sy;

        glBegin(GL_LINES);
            glVertex2f(vx0,vy0);
            glVertex2f(vx1,vy1);
        glEnd();
    }
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(600,600);
    glutCreateWindow("05 - Cohen Sutherland Clipping");
    initialize();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0,0.0,1.0);
    //window
    glBegin(GL_LINE_LOOP);
        glVertex2f(xmin,ymin);
        glVertex2f(xmax,ymin);
        glVertex2f(xmax,ymax);
        glVertex2f(xmin,ymax);
    glEnd();

    glColor3f(0.0,1.0,0.0);
    //viewport
    glBegin(GL_LINE_LOOP);
        glVertex2f(xvmin,yvmin);
        glVertex2f(xvmax,yvmin);
        glVertex2f(xvmax,yvmax);
        glVertex2f(xvmin,yvmax);
    glEnd();

    //lines before clipping
    glBegin(GL_LINES);
        glVertex2f(l1.x0,l1.y0);
        glVertex2f(l1.x1,l1.y1);

        glVertex2f(l2.x0,l2.y0);
        glVertex2f(l2.x1,l2.y1);
    glEnd();

    glColor3f(1.0,0.0,1.0);
    CSClip(l1.x0,l1.y0,l1.x1,l1.y1);
    CSClip(l2.x0,l2.y0,l2.x1,l2.y1);
    glFlush();
}

void initialize()
{
    //CARARRA F2F1EF 242, 241, 239
    glClearColor(242.0/255.0,241.0/255.0,239.0/255.0,1.0);
    glPointSize(1.0);
    gluOrtho2D(0.0,600.0,0.0,600.0);

    xvmin=50, yvmin=50;
    xvmax=200, yvmax=200;

    xmin=300, ymin=300;
    xmax=550, ymax=550;

    l1.x0=400,l1.y0=200;
    l1.x1=450,l1.y1=580;
    l2.x0=500,l2.y0=400;
    l2.x1=500,l2.y1=500;

}

