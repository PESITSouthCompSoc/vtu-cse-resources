#include <iostream>
#include <GL/glut.h>

#define MAX 500

using namespace std;

void display();
void initialize();

float vertex[4][2] = { {50,50} , {400,150}, {450,450}, {200,350}  };
float le[MAX], re[MAX]={0};

void edgedetect(float x1, float y1, float x2, float y2)
{
    float mx, x, temp;
    int i;

    if( y2 < y1)
    {
        temp=y1; y1=y2; y2=temp;
        temp=x1; x1=x2; x2=temp;
    }
    if( (y2-y1)!=0 )
        mx = (x2-x1) / (y2-y1);
    else
        mx = (x2-x1);

    for(x=x1, i=y1; i<=y2; i++)
    {
        if(x < le[i])
            le[i]=x;
        if(x > re[i])
            re[i]=x;
        x+=mx;
    }
}

void scanfill()
{
    int y, x;

    edgedetect(vertex[0][0],vertex[0][1],vertex[1][0],vertex[1][1]);
    edgedetect(vertex[1][0],vertex[1][1],vertex[2][0],vertex[2][1]);
    edgedetect(vertex[2][0],vertex[2][1],vertex[3][0],vertex[3][1]);
    edgedetect(vertex[3][0],vertex[3][1],vertex[0][0],vertex[0][1]);

    glBegin(GL_POINTS);
    for(y=0; y<MAX; y++)
    {
        if(le[y] <= re[y])
        {
            for(x=le[y]+1; x<re[y]; x++)
                glVertex2f(x,y);
        }
    }
    glEnd();
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    glutCreateWindow("Program #0: Title");
    initialize();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP);
        glVertex2fv(vertex[0]);
        glVertex2fv(vertex[1]);
        glVertex2fv(vertex[2]);
        glVertex2fv(vertex[3]);
    glEnd();

    glColor3f(1,0,0);
    scanfill();

    glFlush();
}

void initialize()
{
    int i;
    //CARARRA F2F1EF 242, 241, 239
    glClearColor(242.0/255.0,241.0/255.0,239.0/255.0,1.0);
    glPointSize(1.0);
    gluOrtho2D(0.0,500.0,0.0,500.0);

    for(i=0; i<MAX; i++)
    {
        le[i]=MAX;
    }
}

