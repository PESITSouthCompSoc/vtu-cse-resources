#include <iostream>
#include <GL/glut.h>

using namespace std;
float ambient[] = { 0.7,0.7,0.7 };
float diffuse[] = { 0.5,0.5,0.5 };
float specular[] = { 1.0,1.0,1.0 };
float shininess[] = {50.0};
float lightIntensity[] = {0.7,0.7,0.7,1.0};
float lightPosition[] = {2,2,2,0.0} ;

void wall(float thickness)
{
    glPushMatrix();
    glTranslated(0.5,0.5*thickness,0.5);
    glScaled(1.0,thickness,1.0);
    glutSolidCube(1.0);
    glPopMatrix();
}

void leg(float legThick, float legLen)
{
    glPushMatrix();
    glTranslated(0,legLen/2,0);
    glScaled(legThick,legLen,legThick);
    glutSolidCube(1.0);
    glPopMatrix();
}

//glPushMatrix();
//glutSolidCube(1.0);
//glPopMatrix();

void table(float topWidth, float topThick, float legThick, float legLen)
{
    double dist = 0.95*topWidth/2.0 - legThick/2.0; //dist from center of table
    //top
    glPushMatrix();
    glTranslated(0.0,legLen,0.0);
    glScaled(topWidth,topThick,topWidth);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(dist, 0, dist);
    leg(legThick, legLen);
    glTranslated(0,0,-2.0*dist);
    leg(legThick, legLen);
    glTranslated(-2.0*dist,0,0);
    leg(legThick, legLen);
    glTranslated(0,0,2.0*dist);
    leg(legThick, legLen);
    glPopMatrix();
}

void display()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

    glLoadIdentity();
    gluLookAt(2.3,1.3,2,0.0,0.0,0.0,0.0,1.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glTranslated(0.0,-0.25,0.0);

    wall(0.02);
    glPushMatrix();
    glRotated(90,0.0,0.0,1.0);
    wall(0.02);
    glPopMatrix();
    glPushMatrix();
    glRotated(-90,1.0,0.0,0.0);
    wall(0.02);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.4,0,0.4);
    table(0.55,0.02,0.02,0.4);
    glTranslated(0,0.02+0.4+(0.07/2),0);
    glutSolidTeapot(0.07);
    glPopMatrix();
    glFlush();


}



void reshape(int w, int h)
{
    int width = w < h ? w : h;
    glViewport(0,0,width,width);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1,1,-1,1,-50.0,50.0);
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(600,600);
    glutCreateWindow("07 - Simple Shaded Scene - Teapot on a Table");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glutMainLoop();
    return 0;
}

