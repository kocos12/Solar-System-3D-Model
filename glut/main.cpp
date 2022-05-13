#include <GL/glut.h>
#include<stdio.h>
#include<math.h>

#define PI 3.1416

void draw_orbits(float radius, float x, float y)
{   
    //orbit
    glBegin(GL_LINE_LOOP);
    glColor3ub(255, 255, 255);

    int triangleAmount = 360;

    float twicePi = 2.0 * PI;

        for(int i = 0; i <= triangleAmount; i++) 
        {
        glVertex2f(
                    x + (radius * cos(i *  twicePi / triangleAmount)),
                    y + (radius * sin(i * twicePi / triangleAmount))
                  );
        }
    glEnd();
}

void draw_planets(float radius, float x, float y, int r, int g, int b)
{
    int triangleAmount = 360;
    float twicePi = 2.0 * PI;

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

float xy_mercury = 2.5;
float xy_wenus = 0.52;
float xy_earth = 0.8;
float xy_mars = 3;
float xy_jupiter = 5.2;
float xy_saturn = 1.3;
float xy_uranus = 4.4;
float xy_neptun = 2.8;
float xy_moon = 2.8;

GLdouble zoom = 0.0f;

void draw()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLdouble ortho = 100 + zoom;
    glOrtho(-ortho, ortho, -ortho, ortho, -250, 250);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    
    glClear(GL_COLOR_BUFFER_BIT);
    //orbits
    for(int i=0; i<8;i++ )
        draw_orbits(20+i*10, 0, 0);

    draw_planets(10,0,0,255,255,0); //sun
    draw_planets(1,20 * cos(xy_mercury) ,20 * sin(xy_mercury), 204, 204, 204); //mercury
    draw_planets(2, 30 * cos(xy_wenus), 30 * sin(xy_wenus), 204, 204, 0); //wenus
    draw_planets(2, 40 * cos(xy_earth), 40 * sin(xy_earth) , 0, 0, 255); //earth
    draw_planets(2,50 * cos(xy_mars) ,50 * sin(xy_mars), 255, 25, 25); //mars
    draw_planets(7,60 * cos(xy_jupiter),60 * sin(xy_jupiter) , 255, 128, 0); //jupiter
    draw_planets(5, 70 * cos(xy_saturn), 70 * sin(xy_saturn), 217, 102, 15); //saturn
    draw_planets(4, 80 * cos(xy_uranus), 80 * sin(xy_uranus), 0, 229, 0); //uranus
    draw_planets(4, 90 * cos(xy_neptun), 90 * sin(xy_neptun), 0, 204, 76); //neptun
    
    //saturn rings
    for(int i=0; i<3;i++ )
        draw_orbits(7+(i/2), 70 * cos(xy_saturn), 70 * sin(xy_saturn));
    
    //earth moon
    draw_planets(0.5, 40 * cos(xy_earth) + 3 * cos(xy_moon), 40 * sin(xy_earth) + 3 * sin(xy_moon), 201, 201, 201);
    glutPostRedisplay();
    glutSwapBuffers();
}

void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glLoadIdentity();
    glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
}

void timer(int) {
    
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
    
    xy_mercury += 0.02;
    if(xy_mercury >= 2*PI){
        xy_mercury = 0;
    }

    xy_wenus += 0.008;
     if(xy_wenus >= 2*PI){
        xy_wenus = 0;
    }

    xy_earth += 0.005;
     if(xy_earth >= 2*PI){
        xy_earth = 0;
    }

    xy_mars += 0.002;
     if(xy_mars >= 2*PI){
         xy_mars = 0;
    }

     xy_jupiter += 0.002*0.15;
     if (xy_jupiter >= 2 * PI) {
         xy_jupiter = 0;
     }

     xy_saturn += 0.002 * 0.15*0.4;
     if(xy_saturn >= 2*PI){
         xy_saturn = 0;
    }

    xy_uranus += 0.002 * 0.15 * 0.4*0.35;
     if(xy_uranus >= 2*PI){
         xy_uranus = 0;
    }

    xy_neptun += 0.002 * 0.15 * 0.4 * 0.35*0.5;
     if(xy_neptun >= 2*PI){
         xy_neptun = 0;
    }

     xy_moon += 0.06;
     if (xy_moon >= 2 * PI) {
         xy_moon = 0;
     }
}

void mouse(int button, int state, int x, int y)
{
   // Wheel reports as button 3(scroll up) and button 4(scroll down)
    GLdouble min_z = -300.0;
    GLdouble max_z = 300.0;

   if ((button == 3) || (button == 4)) // It's a wheel event
   {
       // Each wheel event reports like a button click, GLUT_DOWN then GLUT_UP
       if (state == GLUT_UP) 
           return; // Disregard redundant GLUT_UP event
      
       if (button == 3 && zoom < max_z)
       {
           //oddalanie
           zoom += 5.0;
       }
       if (button == 4 && zoom > min_z)
       {
           //przyblizanie
           zoom -= 5.0;
       }
   }
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInitWindowSize(800,800);
    glutCreateWindow("Solar System");

    glutDisplayFunc(draw);

    glutTimerFunc(0, timer, 0);
    
    glutMouseFunc(mouse);
    init();
    glutMainLoop();
    return 0;
}