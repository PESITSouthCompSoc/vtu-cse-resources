#include <iostream>
#include <GL/glut.h>
#include<math.h>

using namespace std;

float house[3][9] = {{600,900,900,600,700,800,800,700,750},{600,600,900,900,600,600,700,700,1100},{1,1,1,1,1,1,1,1,1}};
float rot_house[3][9];
float rotMat[3][3];
float angle=0;
int h=600;
int k=600;


void multiply()
{
    int i,j,k;
    rotMat[0][0]=rotMat[1][1]=cos(angle);
    rotMat[1][0]=sin(angle);
    rotMat[0][1]=-1*sin(angle);
    rotMat[2][0]=rotMat[2][1]=0;
    rotMat[2][2]=1;
    rotMat[0][2]=-h*cos(angle)+k*sin(angle)+h;
    rotMat[1][2]=-h*sin(angle)-k*cos(angle)+k;
    for(i=0;i<3;i++)
    {
        for(j=0;j<9;j++)
        {
            rot_house[i][j]=0;
            for(k=0;k<3;k++)
            {
                rot_house[i][j]+=rotMat[i][k]*house[k][j];
            }
        }
    }

}
void draw(float figure[][9])
{
    glBegin(GL_LINE_LOOP);
        glVertex2f(figure[0][0],figure[1][0]);
        glVertex2f(figure[0][1],figure[1][1]);
        glVertex2f(figure[0][2],figure[1][2]);
        glVertex2f(figure[0][3],figure[1][3]);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(figure[0][4],figure[1][4]);
        glVertex2f(figure[0][5],figure[1][5]);
        glVertex2f(figure[0][6],figure[1][6]);
        glVertex2f(figure[0][7],figure[1][7]);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(figure[0][3],figure[1][3]);
        glVertex2f(figure[0][2],figure[1][2]);
        glVertex2f(figure[0][8],figure[1][8]);
    glEnd();
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    int i,j;
    glColor3f(1.0,0.0,0.0);
    multiply();
    draw(house);
    glColor3f(0.0,1.0,0.0);
    draw(rot_house);
    glFlush();
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            cout<<rot_house[i][j]<<"\t";
        }
        cout<<endl;
    }
}


int main(int argc, char** argv)
{
    cout<<endl<<"Enter the angle: ";
    cin>>angle;
    angle = angle*(355.0/113.0)/180.0;
    cout<<angle;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(600,600);
    glutCreateWindow("04 House Rotate");
    gluOrtho2D(0.0,1500.0,0.0,1500.0);
    glClearColor(1.0,1.0,1.0,1.0);
    glutDisplayFunc(display);
    glutMainLoop();
}
