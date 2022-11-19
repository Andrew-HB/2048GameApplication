#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include <QStackedWidget>

#include <Game.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Application; }
QT_END_NAMESPACE

class Application : public QMainWindow
{
    Q_OBJECT

public:
    Application(QWidget *parent = nullptr);
    ~Application();

private slots:
    void on_startButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::Application *ui;
    Game* game;
};
#endif // APPLICATION_H
