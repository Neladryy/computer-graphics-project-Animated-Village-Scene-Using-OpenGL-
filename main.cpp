#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

// -------- GLOBAL --------
float sunX = -11;
float sunY = -2;
float cloudX1 = -10, cloudX2 = -5;
float carX = -10;
float boatX = -10;

int isDay = 1;
int isRaining = 0;
float rainX[400], rainY[400];

// -------- CIRCLE --------
void drawCircle(float cx, float cy, float r)
{
    glBegin(GL_POLYGON);
    for(int i=0; i<100; i++) {
        float angle = 2 * 3.1416 * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();
}

// -------- SUN / MOON (ARC MOVEMENT) --------
void drawSunMoon()
{
    if(isDay) {
        glColor3f(1.0, 0.8, 0.0); // Sun
        drawCircle(sunX, sunY, 1.0);
    } else {
        glColor3f(0.9, 0.9, 0.9); // Moon
        drawCircle(sunX, sunY, 0.8);
    }
}

// -------- RAIN --------
void drawRain()
{
    glLineWidth(2.0);
    glColor3f(0.4, 0.4, 0.9);
    glBegin(GL_LINES);
    for(int i = 0; i < 400; i++) {
        glVertex2f(rainX[i], rainY[i]);
        glVertex2f(rainX[i] + 0.1, rainY[i] - 0.5);
    }
    glEnd();
    glLineWidth(1.0);
}

// -------- MOUNTAINS --------
void drawMountains()
{
    glBegin(GL_TRIANGLES);
    glColor3f(0.2, 0.2, 0.2);
    glVertex2f(-12, -2); glVertex2f(-1, -2); glVertex2f(-6.5, 1.8);
    glColor3f(0.25, 0.25, 0.25);
    glVertex2f(-6, -2); glVertex2f(6, -2); glVertex2f(0, 3.2);
    glColor3f(0.22, 0.22, 0.22);
    glVertex2f(2, -2); glVertex2f(12, -2); glVertex2f(7.5, 2.2);
    glEnd();
}

// -------- GRASS, ROAD, RIVER --------
void drawGrass() {
    glColor3f(0.2, 0.7, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(-10, -10); glVertex2f(10, -10);
    glVertex2f(10, -2); glVertex2f(-10, -2);
    glEnd();
}

void drawRoad() {
    glColor3f(0.2, 0.20, 0.20);
    glBegin(GL_QUADS);
    glVertex2f(-10, -5); glVertex2f(10, -5);
    glVertex2f(10, -3.5); glVertex2f(-10, -3.5);
    glEnd();
    glColor3f(1, 1, 1);
    for(float i=-10; i<10; i+=2) {
        glBegin(GL_LINES);
        glVertex2f(i, -4.25); glVertex2f(i+1, -4.25);
        glEnd();
    }
}

void drawRiver() {
    glColor3f(0.1, 0.4, 0.8);
    glBegin(GL_QUADS);
    glVertex2f(-10, -8); glVertex2f(10, -8);
    glVertex2f(10, -5.5); glVertex2f(-10, -5.5);
    glEnd();
}

// -------- HOUSE (Bigger Roof) --------
void drawHouse(float x, float y) {
    glColor3f(0.8, 0.4, 0.2); // Body
    glBegin(GL_QUADS);
    glVertex2f(x, y); glVertex2f(x + 3.5, y);
    glVertex2f(x + 3.5, y + 2.5); glVertex2f(x, y + 2.5);
    glEnd();

    glColor3f(0.3, 0.1, 0.0); // Door
    glBegin(GL_QUADS);
    glVertex2f(x + 1.2, y); glVertex2f(x + 2.3, y);
    glVertex2f(x + 2.3, y + 1.2); glVertex2f(x + 1.2, y + 1.2);
    glEnd();

    glColor3f(0.5, 0, 0); // Triangle Roof
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 0.8, y + 2.5); glVertex2f(x + 4.3, y + 2.5);
    glVertex2f(x + 1.75, y + 5.0);
    glEnd();
}

// -------- TREE --------
void drawTree(float x, float y, float trunkHeight, float leafScale) {
    glColor3f(0.3, 0.15, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(x, y); glVertex2f(x + 0.3, y);
    glVertex2f(x + 0.3, y + trunkHeight); glVertex2f(x, y + trunkHeight);
    glEnd();
    glColor3f(0, 0.5, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 1.2 * leafScale, y + trunkHeight);
    glVertex2f(x + 1.5 * leafScale, y + trunkHeight);
    glVertex2f(x + 0.15, y + trunkHeight + 2.0 * leafScale);
    glVertex2f(x - 1.0 * leafScale, y + trunkHeight + 1.0 * leafScale);
    glVertex2f(x + 1.3 * leafScale, y + trunkHeight + 1.0 * leafScale);
    glVertex2f(x + 0.15, y + trunkHeight + 3.0 * leafScale);
    glEnd();
}

// -------- CLOUD --------
void drawCloud(float cx, float cy, float size) {
    if(isRaining) glColor3f(0.5, 0.5, 0.5);
    else glColor3f(1, 1, 1);
    drawCircle(cx, cy, size);
    drawCircle(cx + size, cy + 0.2, size * 1.2);
    drawCircle(cx + (size * 2), cy, size);
}

// -------- BEAUTIFUL CAR (HEADLIGHT & TAILLIGHT ADDED) --------
void drawCar() {
    float yOffset = 0.5;

    // Wheels
    glColor3f(0, 0, 0);
    drawCircle(carX + 0.5, -4.8 + yOffset, 0.35);
    drawCircle(carX + 1.8, -4.8 + yOffset, 0.35);

    // Body
    glColor3f(0.94, 0.35, 0.35);
    glBegin(GL_POLYGON);
    glVertex2f(carX - 0.2, -4.8 + yOffset); glVertex2f(carX + 2.5, -4.8 + yOffset);
    glVertex2f(carX + 2.5, -4.2 + yOffset); glVertex2f(carX - 0.2, -4.2 + yOffset);
    glEnd();

    // Roof
    glBegin(GL_QUADS);
    glVertex2f(carX + 0.3, -4.2 + yOffset); glVertex2f(carX + 2.0, -4.2 + yOffset);
    glVertex2f(carX + 1.7, -3.7 + yOffset); glVertex2f(carX + 0.6, -3.7 + yOffset);
    glEnd();

    // Door Line
    glColor3f(0.4, 0.1, 0.3);
    glBegin(GL_LINES);
    glVertex2f(carX + 1.15, -4.8 + yOffset); glVertex2f(carX + 1.15, -4.2 + yOffset);
    glEnd();

    // Headlight (Yellow in Night)
    if(isDay) glColor3f(0.7, 0.7, 0.0);
    else glColor3f(1.0, 1.0, 0.0);
    drawCircle(carX + 2.4, -4.5 + yOffset, 0.1);

    // Taillight (Red)
    glColor3f(1.0, 0.0, 0.0);
    drawCircle(carX - 0.1, -4.5 + yOffset, 0.08);
}

// -------- BOAT (With MAN ADDED) --------
void drawBoat() {
    float y = -6.7;

    // Base Boat
    glColor3f(0.4, 0.2, 0.1);
    glBegin(GL_POLYGON);
    glVertex2f(boatX + 0.2, y - 0.2); glVertex2f(boatX + 1.8, y - 0.2);
    glVertex2f(boatX + 2.5, y + 0.6); glVertex2f(boatX - 0.5, y + 0.6);
    glEnd();

    // Triangular Sail
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLES);
    glVertex2f(boatX + 1.1, y + 2.4); glVertex2f(boatX + 1.1, y + 0.8); glVertex2f(boatX + 2.3, y + 1.3);
    glEnd();

    // Boatman (The Man Added)
    // Mathematical Coordinates based on Boat position
    float manX = boatX + 0.6;
    float manY = y + 0.6; // Sitting on boat floor

    glColor3f(1, 0.8, 0); // Blue-gray shirt color
    glBegin(GL_POLYGON); // Torso/Body
    glVertex2f(manX - 0.1, manY);     glVertex2f(manX + 0.3, manY);
    glVertex2f(manX + 0.25, manY + 0.6); glVertex2f(manX - 0.05, manY + 0.6);
    glEnd();

    glColor3f(0, 0, 0); // Skin Tone matha
    drawCircle(manX + 0.1, manY + 0.8, 0.15);
}

// -------- DISPLAY --------
void display()
{
    if(isDay) glClearColor(0.5, 0.8, 1, 1);
    else glClearColor(0.05, 0.05, 0.15, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    drawSunMoon();
    drawMountains();

    drawCloud(cloudX1, 6.5, 0.8);
    drawCloud(cloudX2, 5.5, 1.1);

    drawTree(-9.5, -2, 3.5, 0.7);
    drawTree(-4.5, -2, 5.0, 1.0);
    drawTree(0.5, -2, 5.0, 1.0);
    drawTree(7.5, -2, 3.5, 0.7);

    drawGrass();
    drawRiver();
    drawRoad();
    drawHouse(-8, -2);
    drawHouse(-2.5, -2);
    drawCar(); // Beautiful Car with lights
    drawBoat(); // Boat with Man

    if(isRaining) drawRain();

    glutSwapBuffers();
}

// -------- UPDATE --------
void update()
{
    sunX += 0.002; // Slow Sunset
    if(sunX > 11) {
        sunX = -11;
        isDay = !isDay;
    }
    sunY = 7.0 - (sunX * sunX) / 10.0; // Arc movement

    cloudX1 += 0.001; cloudX2 += 0.001;
    carX += 0.005; boatX += 0.003;

    if(cloudX1 > 11) cloudX1 = -13;
    if(cloudX2 > 11) cloudX2 = -13;
    if(carX > 11) carX = -13;
    if(boatX > 11) boatX = -13;

    if(cloudX2 > -8 && cloudX2 < 8) isRaining = 1;
    else isRaining = 0;

    for(int i = 0; i < 400; i++) {
        rainY[i] -= 0.1;
        if(rainY[i] < -10) {
            rainY[i] = 10;
            rainX[i] = (rand() % 200 - 100) / 10.0;
        }
    }
    glutPostRedisplay();
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -10, 10);
    for(int i = 0; i < 400; i++) {
        rainX[i] = (rand() % 200 - 100) / 10.0;
        rainY[i] = (rand() % 200 - 100) / 10.0;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 700);
    glutCreateWindow("Animated Village Scene Using OpenGL");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutMainLoop();
    return 0;
}
