#include <GL/glut.h>
#include <cmath>



void drawWall() {
    float brickWidth = 0.11f;
    float brickHeight = 0.04f;
    int numBricksX = 20;
    int numBricksY = 5;

    float startX = -0.5f + (1.0f - numBricksX * brickWidth) / 2;
    float startY = -1.0f;

    for (int i = 0; i < numBricksY; i++) {
        for (int j = 0; j < numBricksX; j++) {
            float x = startX + j * brickWidth;
            float y = startY + i * brickHeight;

            if ((i + j) % 2 == 0) {
                glColor3f(0.8f, 0.4f, 0.2f); // Brick color
            } else {
                glColor3f(0.6f, 0.3f, 0.1f); // Brick color (alternate)
            }

            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + brickWidth, y);
            glVertex2f(x + brickWidth, y + brickHeight);
            glVertex2f(x, y + brickHeight);
            glEnd();

            glColor3f(0.0f, 0.0f, 0.0f); // Line color

            glBegin(GL_LINE_LOOP);
            glVertex2f(x, y);
            glVertex2f(x + brickWidth, y);
            glVertex2f(x + brickWidth, y + brickHeight);
            glVertex2f(x, y + brickHeight);
            glEnd();
        }
    }
}
void drawGrass() {
    float grassWidth = 0.11f;
    float grassHeight = 0.01f; // Decreased from 0.04f to 0.02f
    int numGrassX = 20;
    int numGrassY = 5; // Decreased from 5 to 3

    float startX = -0.5f + (1.0f - numGrassX * grassWidth) / 2;
    float startY = -0.85f + numGrassY * grassHeight;

    for (int i = 0; i < numGrassY; i++) {
        for (int j = 0; j < numGrassX; j++) {
            float x = startX + j * grassWidth;
            float y = startY + i * grassHeight;

            glColor3f(0.0f, 0.8f, 0.0f); // Grass color

            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + grassWidth, y);
            glVertex2f(x + grassWidth, y + grassHeight);
            glVertex2f(x, y + grassHeight);
            glEnd();
        }
    }
}

float rectangleX = 0.0f;
float rectangleY = 0.0f;
float rectangleSize = 0.05f;

void drawRectangle() {
    glColor3f(1.0f, 1.0f, 1.0f); // Rectangle color

    glBegin(GL_QUADS);
    glVertex2f(rectangleX, rectangleY);
    glVertex2f(rectangleX + rectangleSize, rectangleY);
    glVertex2f(rectangleX + rectangleSize, rectangleY + rectangleSize);
    glVertex2f(rectangleX, rectangleY + rectangleSize);
    glEnd();
}
void handleKeyPress(unsigned char key, int x, int y) {
    float moveDistance = 0.11f;
    float screenWidth = 2.0f; // Assuming the screen size is 2.0 units

    switch (key) {
        case 'w':
            rectangleY += moveDistance;
            break;
        case 'a':
            if (rectangleX - moveDistance >= -screenWidth / 2) {
                rectangleX -= moveDistance;
            }
            break;
        case 's':
            if (rectangleY - moveDistance >= -0.85f) {
                rectangleY -= moveDistance;
            }
            break;
        case 'd':
            if (rectangleX + rectangleSize + moveDistance <= screenWidth / 2) {
                rectangleX += moveDistance;
            }
            break;
    }

    glutPostRedisplay();
}


void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);

    drawWall();
    drawRectangle();
    drawGrass();

    glFlush();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1080, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Monkey Clever Banana Flavour");
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeyPress); // Register the keyboard callback function
    glutMainLoop();

}