#include <iostream>
#include <GL/glut.h>

using namespace std;

struct line
{
    float x0;
    float y0;
    float x1;
    float y1;
};

line l1,l2,l3,l4;
float xmin,xmax,ymin,ymax,xvmin,xvmax,yvmin,yvmax;

bool cliptest(float p,float q,float* te,float* tl)
{
	float t=q/p;
	if(p<0.0)
	{
		if(t>*te)
			*te=t;
		else if(t>*tl)
			return false;
	}
	else if(p>0.0)
	{
		if(t<*tl)
			*tl=t;
		else if(t<*te)
			return false;
	}
	else if(p==0.0)
	{
		if(q<0.0)
			return false;
	}
	return true;
}

void liang(float x0,float y0, float x1, float y1)
{
    float dx=x1-x0,dy=y1-y0,te=0.0,t1=1.0;

	if(cliptest(-dx,x0-xmin,&te,&t1))
		if(cliptest(dx,xmax-x0,&te,&t1))
			if(cliptest(-dy,y0-ymin,&te,&t1))
				if(cliptest(dy,ymax-y0,&te,&t1))
				{
                    cout<<"te: "<<te;
                    cout<<endl<<"tl: "<<t1;
					if(t1<1.0)
					{
						x1=x0+t1*dx;
						y1=y0+t1*dy;
					}
					if(te>0.0)
					{
						x0=x0+te*dx;
						y0=y0+te*dy;
					}
					float sx=(xvmax-xvmin)/(xmax-xmin);
					float sy=(yvmax-yvmin)/(ymax-ymin);
					float vx0=xvmin+(x0-xmin)*sx;
					float vx1=xvmin+(x1-xmin)*sx;
					float vy0=yvmin+(y0-ymin)*sy;
					float vy1=yvmin+(y1-ymin)*sy;
					glColor3f(1,0,0);
					glBegin(GL_LINE_LOOP);
					glVertex2f(xvmin,yvmin);
					glVertex2f(xvmin,yvmax);
					glVertex2f(xvmax,yvmax);
					glVertex2f(xvmax,yvmin);
					glEnd();
					glColor3f(0,1,0);
					glBegin(GL_LINES);
					glVertex2f(vx0,vy0);
					glVertex2f(vx1,vy1);
					glEnd();
				}
}

void initialize()
{

    xmin = 30;
    xmax = 130;
    ymin = 30;
    ymax = 130;

    xvmin = 160;
    xvmax = 270;
    yvmin = 160;
    yvmax = 270;

    l1.x0 = 40;
    l1.y0 = 40;
    l1.x1 = 120;
    l1.y1 = 120;

    l2.x0 = 140;
    l2.y0 = 30;
    l2.x1 = 120;
    l2.y1 = 140;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(xmin,ymin);
        glVertex2f(xmax,ymin);
        glVertex2f(xmax,ymax);
        glVertex2f(xmin,ymax);
    glEnd();

    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(xvmin,yvmin);
        glVertex2f(xvmax,yvmin);
        glVertex2f(xvmax,yvmax);
        glVertex2f(xvmin,yvmax);
    glEnd();

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
        glVertex2f(l1.x0,l1.y0);
        glVertex2f(l1.x1,l1.y1);
        glVertex2f(l2.x0,l2.y0);
        glVertex2f(l2.x1,l2.y1);
    glEnd();
    glFlush();

    liang(l1.x0,l1.y0,l1.x1,l1.y1);
    liang(l2.x0,l2.y0,l2.x1,l2.y1);
    glFlush();
}


int main(int argc, char* argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(600,600);
    glutCreateWindow("02 Liang Barsky");
    gluOrtho2D(0.0,300.0,0.0,300.0);
    initialize();
    glClearColor(1.0,1.0,1.0,1.0);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
