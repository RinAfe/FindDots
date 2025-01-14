#include "Icosahedron.h"
#include <cmath>
#include <QDebug>

static const float X = 0.525731112119133606f; // 1 / sqrt(1 + phi^2)
static const float Z = 0.850650808352039932f; // phi / sqrt(1 + phi^2)
static const float N = 0.0f;                  // Просто 0 для удобства

// Вершины и индексы икосаэдра
static const GLfloat vertices[12][3] = {
    { -X, N,  Z }, {  X, N,  Z }, { -X, N, -Z }, {  X, N, -Z },
    {  N,  Z,  X }, {  N,  Z, -X }, {  N, -Z,  X }, {  N, -Z, -X },
    {  Z,  X,  N }, { -Z,  X,  N }, {  Z, -X,  N }, { -Z, -X,  N }
};

static const GLuint indices[20][3] = {
    { 0, 4, 1 }, { 0, 9, 4 }, { 9, 5, 4 }, { 4, 5, 8 }, { 4, 8, 1 },
    { 8, 10, 1 }, { 8, 3, 10 }, { 5, 3, 8 }, { 5, 2, 3 }, { 2, 7, 3 },
    { 7, 10, 3 }, { 7, 6, 10 }, { 7, 11, 6 }, { 11, 0, 6 }, { 0, 1, 6 },
    { 6, 1, 10 }, { 9, 0, 11 }, { 9, 11, 2 }, { 9, 2, 5 }, { 7, 2, 11 }
};

Icosahedron::Icosahedron(QWidget* parent)
    : QOpenGLWidget(parent), rotationAngle(0.0f) {
    rotationTimer = new QTimer(this);
    connect(rotationTimer, &QTimer::timeout, this, [this]() {
        rotationAngle += 1.0f;
        if (rotationAngle >= 360.0f)
            rotationAngle -= 360.0f;
        update();
    });
    rotationTimer->start(16); // Обновление ~60 FPS
}

Icosahedron::~Icosahedron() {}

void Icosahedron::initializeGL() {
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Белый фон
}

void Icosahedron::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(45.0f, GLfloat(w) / h, 0.1f, 100.0f);
}

void Icosahedron::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 modelViewMatrix;
    modelViewMatrix.translate(0.0f, 0.0f, -5.0f); // Смещение назад
    modelViewMatrix.rotate(rotationAngle, QVector3D(1.0f, 1.0f, 0.0f)); // Вращение

    QMatrix4x4 mvpMatrix = projectionMatrix * modelViewMatrix;
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(mvpMatrix.constData());

    drawIcosahedron();
}

void Icosahedron::drawIcosahedron() {
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 20; ++i) { // 20 треугольников икосаэдра
        for (int j = 0; j < 3; ++j) {
            glVertex3fv(vertices[indices[i][j]]);
        }
    }
    glEnd();
}
