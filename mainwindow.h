#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QLabel>
#include <QVBoxLayout>
#include <QMovie>
#include <QPushButton>
#include <QGraphicsBlurEffect>
#include <QHBoxLayout>
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

protected:

private:

    QLabel* label;
    QMovie* movie;

    QPushButton* startButton;
    QPushButton* closeButton;
    QPushButton* minimizeButton;
};
#endif // MAINWINDOW_H
