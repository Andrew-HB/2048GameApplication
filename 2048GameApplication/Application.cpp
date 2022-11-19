#include "Application.h"
#include "ui_MainMenu.h"

Application::Application(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Application)
    , game(new Game)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/res/img/2048 icon.png"));
    this->setStyleSheet("background-color: #faf8ef;");

    ui->stackedWidget->addWidget(game);
}

Application::~Application()
{
    delete ui;
}


void Application::on_startButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void Application::on_exitButton_clicked()
{
    this->close();
}

