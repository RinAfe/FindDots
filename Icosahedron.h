#ifndef ICOSAHEDRON_H
#define ICOSAHEDRON_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QVector3D>
#include <QTimer>

class Icosahedron : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
public:
    explicit Icosahedron(QWidget* parent = nullptr);
    ~Icosahedron();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    void drawIcosahedron();

    QMatrix4x4 projectionMatrix;
    QTimer* rotationTimer; // Таймер для анимации вращения
    float rotationAngle;   // Угол вращения
};

#endif // ICOSAHEDRON_H
