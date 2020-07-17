#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <GL/glut.h>
//#include SOIL.h
int FILAS;
int COLUMNAS;


int c = 0;
void init()
{
    // For displaying the window color
    glClearColor(1, 1, 1, 1);
    // Choosing the type of projection
    glMatrixMode(GL_PROJECTION);
    // for setting the transformation which here is 2D
    gluOrtho2D(0, COLUMNAS, 0, FILAS);//columnas y filas
}

void drawSquare(GLint x1, GLint y1, GLint x2, GLint y2, GLint y3)
{
    
    // if color is 1 then draw black box and change value of color = 0
  
    glColor3f(0, 0, 0); // black color value is 0 0 0
    
    // Draw Square
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(x2, y2);
    glVertex2i(x2, y3);
    glEnd();

    //glBegin(GL_LINES);
    //glVertex2i(x1, y3);
    //glVertex2i(x4, y4);
    //glEnd();
}



//void maze(int filas, int columnas)
void mazeboard()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear display window
    GLint x, y;

    for (x = 0; x < COLUMNAS; x += 100)
    {
        for (y = 0; y < FILAS; y+= 100)
        {
            drawSquare(x, y, x+100, y, y+100);
        
        }
    }


    glColor3f(1,0,0);
    
    glBegin(GL_LINES);
    glVertex2i(0,0);
    glVertex2i(0, FILAS);
    glEnd();


    glColor3f(1,0,0);
    
    glBegin(GL_LINES);
    glVertex2i(0,FILAS);
    glVertex2i(COLUMNAS, FILAS);
    glEnd();

    /*
    glColor3f(1,1,1); // white color

    glBegin(GL_LINES);
    glVertex2i(200,100);
    glVertex2i(300, 100);
    glEnd();*/

    // Process all OpenGL routine s as quickly as possible
    glFlush();
}

int main(int agrc, char **argv)
{
    FILAS = 1200;
    COLUMNAS = 1200;
    // Initialize GLUT
    glutInit(&agrc, argv);
    // Set display mode
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    // Set top - left display window position.
    glutInitWindowPosition(100, 100);
    // Set display window width and height
    glutInitWindowSize(5000, 5000);
    // Create display window with the given title
    glutCreateWindow("Maze solver using OpenGL in C");
    // Execute initialization procedure
    init();
    // Send graphics to display window
    glutDisplayFunc(mazeboard);
    // Display everything and wait.
    glutMainLoop();
}
