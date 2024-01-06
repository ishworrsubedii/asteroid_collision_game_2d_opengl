#include <GL/glut.h>
#include <cmath>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

// Structure to define a circle
struct Circle {
    float x, y, radius;
    bool active; // Indicates if the circle is active or not
};

// Global variables
float backgroundOffsetY = 0.0f;
float rectangleX = 0.0f, rectangleY = 0.0f, rectangleSize = 0.04f;
float rectangleWidth = 0.1f, rectangleHeight = 0.04f;
int score = 0;
const int numCircles = 10;
int elapsedTime = 0;
float starRotation = 0.0f;

// Vector to store circles
std::vector<Circle> circles;

// Function to draw a circle at specified position and radius
void drawCircle(float x, float y, float radius) {
    glBegin(GL_POLYGON);
    // Draw the circle using triangles
    for (int i = 0; i < 360; i++) {
        float degInRad = i * 3.14159 / 180;
        glVertex2f(x + cos(degInRad) * radius, y + sin(degInRad) * radius);
    }
    glEnd();

}
void drawText(float x, float y, const std::string& string) {
    glRasterPos2f(x, y);
    for (char c : string) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void updateStar(int value) {
    // Update the star rotation
    starRotation += 1.0f;
    if (starRotation > 360.0f) {
        starRotation -= 360.0f;
    }

    // Redraw the scene
    glutPostRedisplay();

    // Reset the timer
    glutTimerFunc(16, updateStar, 0);
}
void drawStar(float x, float y, float size) {
    glPushMatrix(); // Save the current transformation matrix

    // Translate to the star's position
    glTranslatef(x, y, 0.0f);

    // Rotate the star
    glRotatef(starRotation, 0.0f, 0.0f, 1.0f);

    // Draw the star using GL_LINES
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f); // Set star color
    for (int i = 0; i < 5; ++i) {
        // Calculate the angle in radians
        float angle = i * 2.0f * M_PI / 5.0f;
        // Draw a line from the center to the edge of the star
        glVertex2f(0.0f, 0.0f);
        glVertex2f(size * cos(angle), size * sin(angle));
    }
    glEnd();

    glPopMatrix(); // Restore the previous transformation matrix
}

// Function to draw a rectangle
void drawRectangle() {
    glColor3f(1.0f, 1.0f, 1.0f); // Set rectangle color
    glBegin(GL_QUADS);
    // Draw the rectangle using four vertices
    glVertex2f(rectangleX, rectangleY);
    glVertex2f(rectangleX + rectangleWidth, rectangleY);
    glVertex2f(rectangleX + rectangleWidth, rectangleY + rectangleHeight);
    glVertex2f(rectangleX, rectangleY + rectangleHeight);
    glEnd();
}

// Function to draw a wall made of bricks
void drawWall() {
    // Brick dimensions and number of bricks
    float brickWidth = 0.11f, brickHeight = 0.04f;
    int numBricksX = 20, numBricksY = 5;

    // Starting position of the wall
    float startX = -0.5f + (1.0f - numBricksX * brickWidth) / 2;
    float startY = -1.0f;

    // Loop to draw bricks row-wise
    for (int i = 0; i < numBricksY; i++) {
        for (int j = 0; j < numBricksX; j++) {
            float x = startX + j * brickWidth;
            float y = startY + i * brickHeight;

            // Alternate brick colors
            glColor3f((i + j) % 2 == 0 ? 0.8f : 0.6f, 0.4f, 0.2f);
            glBegin(GL_QUADS);
            // Draw a brick
            glVertex2f(x, y);
            glVertex2f(x + brickWidth, y);
            glVertex2f(x + brickWidth, y + brickHeight);
            glVertex2f(x, y + brickHeight);
            glEnd();

            // Draw brick outlines
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

// Function to draw grass
void drawGrass() {
    // Grass dimensions and number of grass tiles
    float grassWidth = 0.11f, grassHeight = 0.01f;
    int numGrassX = 20, numGrassY = 5;

    // Starting position of the grass tiles
    float startX = -0.5f + (1.0f - numGrassX * grassWidth) / 2;
    float startY = -0.85f + numGrassY * grassHeight;

    // Loop to draw grass tiles row-wise
    for (int i = 0; i < numGrassY; i++) {
        for (int j = 0; j < numGrassX; j++) {
            float x = startX + j * grassWidth;
            float y = startY + i * grassHeight;

            glColor3f(0.0f, 0.8f, 0.0f); // Set grass color
            glBegin(GL_QUADS);
            // Draw a grass tile
            glVertex2f(x, y);
            glVertex2f(x + grassWidth, y);
            glVertex2f(x + grassWidth, y + grassHeight);
            glVertex2f(x, y + grassHeight);
            glEnd();
        }
    }
}

// Function to end the game
void endGame(int value) {
    exit(0); // End the game
}

// Function to generate circles
void generateCircle(int value) {
    Circle circle;
    // Generate a circle with random x position at the top of the screen
    circle.x = (rand() % 200 - 100) / 100.0f;
    circle.y = 1.0f; // Start at the top
    circle.radius = 0.02f; // Set circle radius
    circle.active = true; // Activate the circle
    circles.push_back(circle); // Add the circle to the vector

    // Set timer to generate another circle in 3 seconds
    if (value > 0) {
        glutTimerFunc(3000, generateCircle, value - 1);
    }
}

// Function to draw all active circles
void drawCircles() {
    for (Circle& circle : circles) {
        if (circle.active) {
            glColor3f(1.0f, 1.0f, 1.0f); // Circle color
            drawCircle(circle.x, circle.y, circle.radius); // Draw the circle
            circle.y -= 0.007f; // Speed

            // Check for collision with rectangle
            if (circle.y - circle.radius <= rectangleY + rectangleSize &&
                circle.y + circle.radius >= rectangleY &&
                circle.x - circle.radius <= rectangleX + rectangleSize &&
                circle.x + circle.radius >= rectangleX) {
                circle.active = false; // Deactivate the circle
                score++; // Increase score
            }

            if (circle.y - circle.radius <= -1.0f) {
                circle.active = false; // Deactivate the circle if it goes below the screen
            }
        }
    }
}

// Function to handle keyboard input
void handleKeyPress(unsigned char key, int x, int y) {
    float moveDistance = 0.11f;
    float screenWidth = 2.1f;

    switch (key) {
        case 'w': // Move up
            rectangleY += moveDistance;
            backgroundOffsetY += moveDistance;
            break;
        case 'a': // Move left
            if (rectangleX - moveDistance >= -screenWidth / 2) {
                rectangleX -= moveDistance;
            }
            break;
        case 's': // Move down
            if (rectangleY - moveDistance >= -0.85f) {
                rectangleY -= moveDistance;
            }
            break;
        case 'd': // Move right
            if (rectangleX + rectangleSize + moveDistance <= screenWidth / 2) {
                rectangleX += moveDistance;
            }
            break;
    }

    glutPostRedisplay(); // Update the display
}

// Function to display score and timer
void displayScore() {
    glRasterPos2f(-0.9f, 0.9f); // Position of score text
    std::string scoreText = "Score: " + std::to_string(score);
    for (char c : scoreText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c); // Display score
    }

    glRasterPos2f(0.7f, 0.9f); // Position of timer text
    int timeInSeconds = static_cast<int>(elapsedTime / 62.5f);
    std::string timerText = "Time: " + std::to_string(timeInSeconds);
    for (char c : timerText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c); // Display timer
    }
}

// Function to update game elements
void update(int value) {
    elapsedTime++; // Update elapsed time
    drawCircles(); // Draw circles
    glutPostRedisplay(); // Update the display
    glutTimerFunc(16, update, 0); // Run update every ~16 milliseconds
}

// Function to display everything on the screen
void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    // Draw a black background
    glVertex2f(-0.5f, -1.0f + backgroundOffsetY);
    glVertex2f(0.5f, -1.0f + backgroundOffsetY);
    glVertex2f(0.5f, 1.0f + backgroundOffsetY);
    glVertex2f(-0.5f, 1.0f + backgroundOffsetY);
    glEnd();
    drawCircles(); // Draw circles
    drawStar(0.0f, 0.9f, 0.01f);
    drawStar(0.4f, 0.9f, 0.01f);
    drawStar(-0.4f, 0.9f, 0.01f);
    (-0.9f, -0.9f, "Made by Ishwor Subedi");

    



    drawWall(); // Draw wall
    drawRectangle(); // Draw rectangle
    drawGrass(); // Draw grass
    displayScore(); // Display score and timer

    glutSwapBuffers(); // Swap the buffers to display the rendered image
}
