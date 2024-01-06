// include/game.h
#pragma once

#include <GL/glut.h>
#include <cmath>
#include <string>
#include <vector>

struct Circle {
    float x, y, radius;
    bool active;
};

struct Star {
    float x, y, size;
    bool active;
};

void drawCircle(float x, float y, float radius);
void drawRectangle();
void drawWall();
void drawGrass();
void endGame(int value);
void generateCircle(int value);
void drawCircles();
void handleKeyPress(unsigned char key, int x, int y);
void displayScore();
void update(int value);
void display();
void drawStar(float x, float y, float size); // New function for drawing a star
void updateStar(int value);