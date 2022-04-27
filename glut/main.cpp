#include <GL/glut.h>
#include<stdio.h>
#include<math.h>

float x,y;
float PI=3.1416;

void draw_orbits(GLfloat radius, float x, float y)
{   
    //orbit
    glBegin(GL_LINE_LOOP);
    glColor3ub(255, 255, 255);

    int triangleAmount = 360;

    GLfloat twicePi = 2.0 * PI;

        for(int i = 0; i <= triangleAmount; i++) 
        {
        glVertex2f(
                    x + (radius * cos(i *  twicePi / triangleAmount)),
                    y + (radius * sin(i * twicePi / triangleAmount))
                  );
        }
    glEnd();
}

void draw_planets(GLfloat radius, float x, float y, int r, int g, int b)
{
    int triangleAmount = 360;
    GLfloat twicePi = 2.0 * PI;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(r, g, b);
   
    glVertex2f(x, y); // center of circle

    for(int i = 0; i <= triangleAmount;i++) {
     glVertex2f(
                    x + (radius * cos(i *  twicePi / triangleAmount)),
                    y + (radius * sin(i * twicePi / triangleAmount))
                );
    }
    glEnd();
}

float x_mercury;
float y_mercury;

float x_wenus;
float y_wenus;

float x_earth;
float y_earth;

float x_mars;
float y_mars;

float x_jupiter;
float y_jupiter;

float x_saturn;
float y_saturn;

float x_uranus;
float y_uranus;




void draw()
{
    //orbits
    for(int i=0; i<8;i++ )
        draw_orbits(20+i*10, 0, 0);

    draw_planets(10,0,0,255,255,0); //sun
    draw_planets(1, 20 * cos(2.5), 20 * sin(2.5), 204, 204, 204); //mercury
    draw_planets(2, 30 * cos(0.52), 30 * sin(0.52), 204, 204, 0); //wenus
    draw_planets(2, 40 * cos(0.8), 40 * sin(0.8), 0, 0, 255); //earth
    draw_planets(2, 50 * cos(3), 50 * sin(3), 255, 25, 25); //mars
    draw_planets(7, 60 * cos(5.2), 60 * sin(5.2), 255, 128, 0); //jupiter
    draw_planets(5, 70 * cos(1.3), 70 * sin(1.3), 217, 102, 15); //saturn
    draw_planets(4, 80 * cos(4.4), 80 * sin(4.4), 0, 229, 0); //uranus
    draw_planets(4, 90 * cos(2.8), 90 * sin(2.8), 0, 204, 76); //neptun

    //saturn rings
    for(int i=0; i<3;i++ )
        draw_orbits(7+(i/2), 70 * cos(1.3), 70 * sin(1.3));

    glutSwapBuffers();
}

void init(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glLoadIdentity();
    glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInitWindowSize(800,800);
    glutCreateWindow("Solar System");

    glutDisplayFunc(draw);
    init ();
    glutMainLoop();
    return 0;
}