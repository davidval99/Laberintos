#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <GL/glut.h>
//#include SOIL.h

int c = 0;
void init()
{
    // For displaying the window color
    glClearColor(1, 1, 1, 1);
    // Choosing the type of projection
    glMatrixMode(GL_PROJECTION);
    // for setting the transformation which here is 2D
    gluOrtho2D(0, 800, 0, 600);
}

void drawSquare(GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3, GLint x4, GLint y4)
{
    
    // if color is 1 then draw black box and change value of color = 0
  
    glColor3f(0, 0, 0); // black color value is 0 0 0
    c = 0;
    
    // Draw Square
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(x2, y2);
    glVertex2i(x2, y3);

    //glBegin(GL_LINES);
    //glVertex2i(x1, y3);
    //glVertex2i(x4, y4);
    glEnd();
}
void chessboard()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear display window
    GLint x,y;

    for (x = 0; x <= 800; x += 100)
    {
        for (y = 0; y <= 600; y += 75)
        {
            drawSquare(x, y + 75, x + 100, y + 75, x + 100, y, x, y);
        
        }
    }
    // Process all OpenGL routine s as quickly as possible
    glFlush();
}

int main(int agrc, char **argv)
{
    // Initialize GLUT
    glutInit(&agrc, argv);
    // Set display mode
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    // Set top - left display window position.
    glutInitWindowPosition(100, 100);
    // Set display window width and height
    glutInitWindowSize(800, 600);
    // Create display window with the given title
    glutCreateWindow("Chess Board using OpenGL in C++");
    // Execute initialization procedure
    init();
    // Send graphics to display window
    glutDisplayFunc(chessboard);
    // Display everything and wait.
    glutMainLoop();
}
