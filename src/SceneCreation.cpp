#include <GL/glut.h>
#include <cmath>
#include <string>
#include <vector>
#include <cstdlib>

struct Circle {
    float x, y, radius;
    bool active;
};

float backgroundOffsetY = 0.0f;
float rectangleX = 0.0f, rectangleY = 0.0f, rectangleSize = 0.05f;
int score = 0;
const int numCircles = 10;

std::vector<Circle> circles(numCircles);

void drawCircle(float x, float y, float radius) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float degInRad = i * 3.14159 / 180;
        glVertex2f(x + cos(degInRad) * radius, y + sin(degInRad) * radius);
    }
    glEnd();
}

void drawRectangle() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(rectangleX, rectangleY);
    glVertex2f(rectangleX + rectangleSize, rectangleY);
    glVertex2f(rectangleX + rectangleSize, rectangleY + rectangleSize);
    glVertex2f(rectangleX, rectangleY + rectangleSize);
    glEnd();
}

void drawWall() {
    float brickWidth = 0.11f, brickHeight = 0.04f;
    int numBricksX = 20, numBricksY = 5;

    float startX = -0.5f + (1.0f - numBricksX * brickWidth) / 2;
    float startY = -1.0f;

    for (int i = 0; i < numBricksY; i++) {
        for (int j = 0; j < numBricksX; j++) {
            float x = startX + j * brickWidth;
            float y = startY + i * brickHeight;

            glColor3f((i + j) % 2 == 0 ? 0.8f : 0.6f, 0.4f, 0.2f);
            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + brickWidth, y);
            glVertex2f(x + brickWidth, y + brickHeight);
            glVertex2f(x, y + brickHeight);
            glEnd();

            glColor3f(0.0f, 0.0f, 0.0f);
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
    float grassWidth = 0.11f, grassHeight = 0.01f;
    int numGrassX = 20, numGrassY = 5;

    float startX = -0.5f + (1.0f - numGrassX * grassWidth) / 2;
    float startY = -0.85f + numGrassY * grassHeight;

    for (int i = 0; i < numGrassY; i++) {
        for (int j = 0; j < numGrassX; j++) {
            float x = startX + j * grassWidth;
            float y = startY + i * grassHeight;

            glColor3f(0.0f, 0.8f, 0.0f);
            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + grassWidth, y);
            glVertex2f(x + grassWidth, y + grassHeight);
            glVertex2f(x, y + grassHeight);
            glEnd();
        }
    }
}

void drawCircles() {
    for (Circle& circle : circles) {
        if (circle.active) {
            glColor3f(1.0f, 1.0f, 1.0f);
            drawCircle(circle.x, circle.y, circle.radius);
            circle.y -= 0.01f;

            if (circle.y - circle.radius <= rectangleY + rectangleSize &&
                circle.y + circle.radius >= rectangleY &&
                circle.x - circle.radius <= rectangleX + rectangleSize &&
                circle.x + circle.radius >= rectangleX) {
                circle.active = false;
                score++;
            }
        }
    }
}

void displayScore() {
    glRasterPos2f(-0.9f, 0.9f);
    std::string scoreText = "Score: " + std::to_string(score);
    for (char c : scoreText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void handleKeyPress(unsigned char key, int x, int y) {
    float moveDistance = 0.11f;
    float screenWidth = 2.1f;

    switch (key) {
        case 'w':
            rectangleY += moveDistance;
            backgroundOffsetY += moveDistance;
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

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, -1.0f + backgroundOffsetY);
    glVertex2f(0.5f, -1.0f + backgroundOffsetY);
    glVertex2f(0.5f, 1.0f + backgroundOffsetY);
    glVertex2f(-0.5f, 1.0f + backgroundOffsetY);
    glEnd();

    drawWall();
    drawRectangle();
    drawGrass();
    drawCircles();
    displayScore();

    glFlush();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1080, 800);
    glutInitWindowPosition(100, 100);

    for (Circle& circle : circles) {
        circle.x = (rand() % 200 - 100) / 100.0f;
        circle.y = (rand() % 50 + 100) / 100.0f;
        circle.radius = 0.02f;
        circle.active = true;
    }

    glutCreateWindow("Moving Background with Rectangle");
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeyPress);
    glutMainLoop();

    return 0;
}
