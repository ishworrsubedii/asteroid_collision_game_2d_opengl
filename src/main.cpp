// src/main.cpp
#include "game.h"
#include <cstdlib>
#include <ctime>

int main(int argc, char** argv) {
    srand(time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1080, 1080);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Astroid Collision Game");
    glutDisplayFunc(display);
    glutTimerFunc(3000, generateCircle, 10); // 10 circles will be generated
    glutTimerFunc(30000, endGame, 0);
    glutTimerFunc(16, update, 0); // Start the update loop

    glutKeyboardFunc(handleKeyPress);
    glutMainLoop();

    return 0;
}
