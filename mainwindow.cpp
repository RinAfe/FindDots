#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), label(new QLabel(this)),
    movie(new QMovie(":/res/gifff.gif")),
    startButton(new QPushButton(this)),
    closeButton(new QPushButton(this)),
    minimizeButton(new QPushButton(this))
{
    ui->setupUi(this);

    setWindowTitle(" ");
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(800, 750);
    setWindowIcon(QIcon(":/res/icon.png"));
    setStyleSheet("background-color: black;");

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    centralWidget->setStyleSheet("background-color: black; border: none;");

    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    label->setGeometry(this->geometry());
    label->setAlignment(Qt::AlignCenter);

    if(!movie->isValid()){
        return;
    }
    label->setMovie(movie);
    layout->addWidget(label);

    QGraphicsBlurEffect* blur = new QGraphicsBlurEffect(this);
    blur->setBlurRadius(1.5f);

    label->setGraphicsEffect(blur);

    movie->setScaledSize(label->size());
    movie->start();
    movie->setSpeed(100);

    //Кнопка Старта
    startButton->raise();
    startButton->setGeometry(300, 575, 200, 50);
    startButton->setText("НАЧАТЬ");
    startButton->setStyleSheet(
        "QPushButton {"
        "    text-align: center;"                    // Центровка текста
        "    color: white;"                         // Цвет текста
        "    background-color: rgba(0, 0, 0, 120);" // Полупрозрачный фон
        "    font-size: 24px;"                      // Размер шрифта
        "    font-weight: bold;"                    // Жирный текст
        "    letter-spacing: 4px;"                  // Межбуквенный интервал
        "    border: 2px solid rgba(255, 255, 255, 80);" // Тонкая рамка
        "    border-radius: 10px;"                  // Скруглённые углы
        "}"
        "QPushButton:hover {"
        "    color: black;"                         // Цвет текста при наведении
        "    background-color: rgba(255, 255, 255, 180);" // Светлый фон при наведении
        "    border: 2px solid rgba(255, 255, 255, 200);" // Более заметная рамка
        "}"
        "QPushButton:pressed {"
        "    color: white;"                         // Цвет текста при нажатии
        "    background-color: rgba(200, 200, 200, 150);" // Тёмный фон при нажатии
        "    border: 2px solid rgba(255, 255, 255, 120);" // Ослабленная рамка
        "}"
        );
    startButton->setVisible(false);
    //Кнопка Закрытия
    closeButton->raise();
    closeButton->setGeometry(757, 0, 40, 20);
    closeButton->setText("X");
    closeButton->setStyleSheet(
        "QPushButton {"
        "    color: rgba(255, 255, 255, 0);"        // Цвет текста кнопки
        "    font-size: 15px;"                      // Размер шрифта
        "    font-weight: bold;"                    // Жирный текст
        "    background-color: rgba(255, 255, 255, 0);" // Прозрачный фон
        "}"
        "QPushButton:hover {"
        "    background-color: rgba(255, 0, 0, 180);"  // Фон при наведении
        "    color: white;"
        "}"
        );
    //Кнопка Свернуть
    minimizeButton->raise();
    minimizeButton->setGeometry(717, 0, 40, 20);
    minimizeButton->setText("–");
    minimizeButton->setStyleSheet(
        "QPushButton {"
        "    color: rgba(255, 255, 255, 0);"        // Цвет текста кнопки
        "    font-size: 15px;"                      // Размер шрифта
        "    font-weight: bold;"                    // Жирный текст
        "    background-color: rgba(255, 255, 255, 0);" // Прозрачный фон
        "}"
        "QPushButton:hover {"
        "    background-color: rgba(145, 145, 145, 100);"  // Фон при наведении
        "    color: gray;"
        "}"
        );

    //Затемнение заднего фона
    QWidget* overlay = new QWidget(label);

    overlay->setGeometry(this->geometry());
    overlay->setStyleSheet("background-color: rgba(0, 0, 0, 180);");
    overlay->setVisible(true);

    // Приветственные надписи
    QLabel* greetingLabel1 = new QLabel(this);
    greetingLabel1->setGeometry(10, 220, this->width(), 150);
    greetingLabel1->setAlignment(Qt::AlignCenter);
    greetingLabel1->setStyleSheet("color: white; font-size: 37px; letter-spacing: 20px; font-weight: bold; background-color: rgba(255, 255, 255, 0);");

    QLabel* greetingLabel2 = new QLabel(this);
    greetingLabel2->setGeometry(10, 310, this->width(), 150);
    greetingLabel2->setAlignment(Qt::AlignCenter);
    greetingLabel2->setStyleSheet("color: gray; font-size: 25px; letter-spacing: 10px; font-weight: bold; background-color: rgba(255, 255, 255, 0);");

    QString message1 = "ДОБРО ПОЖАЛОВАТЬ";
    QString message2 = "Давайте начнем погружение\nв мир математики";
    int currentIndex = 0;  // Общий индекс
    int state = 0;         // Состояние: 0 - первая строка, 1 - вторая строка

    QTimer* textTimer = new QTimer(this);

    connect(textTimer, &QTimer::timeout, this, [=]() mutable {
        if (state == 0) {  // Первая строка
            if (currentIndex < message1.length()) {
                greetingLabel1->setText(message1.left(currentIndex + 1));
                currentIndex++;
            } else {
                state = 1;        // Переходим ко второй строке
                currentIndex = 0; // Сбрасываем индекс
            }
        } else if (state == 1) { // Вторая строка
            if (currentIndex < message2.length()) {
                greetingLabel2->setText(message2.left(currentIndex + 1));
                currentIndex++;
            } else {
                textTimer->stop(); // Останавливаем таймер после завершения
            }
        }
    });

    textTimer->start(200);

    connect(startButton, &QPushButton::clicked,this, [](){
        qDebug("Кнопка нажата!");
    });

    connect(closeButton, &QPushButton::clicked, this, &QMainWindow::close);

    connect(minimizeButton, &QPushButton::clicked, this, &QMainWindow::showMinimized);

    QTimer::singleShot(12300, this,[this](){

        // Устанавливаем эффект прозрачности
        QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(startButton);
        startButton->setGraphicsEffect(opacityEffect);

        // Создаем анимацию прозрачности
        QPropertyAnimation* fadeAnimation = new QPropertyAnimation(opacityEffect, "opacity", this);
        fadeAnimation->setDuration(1000); // Длительность анимации - 1 секунда
        fadeAnimation->setStartValue(0.0); // Начальная прозрачность
        fadeAnimation->setEndValue(1.0);   // Конечная прозрачность

        // Показываем кнопку и запускаем анимацию
        startButton->setVisible(true);
        fadeAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


