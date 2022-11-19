#ifndef GAME_H
#define GAME_H

#include <QWidget>

#define FIELD_SIZE 4

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();
private:
    Ui::Game *ui;

    int m_GameField[FIELD_SIZE][FIELD_SIZE];
    int m_Score;

    int m_PrevMoveGameField[FIELD_SIZE][FIELD_SIZE];
    int m_PrevMoveScore;

    bool m_isFreeMode;

    enum MoveDir { RIGHT, DOWN, LEFT, UP };
private:
    void Init();
    void PrintField();
    void MakeMove(int dir);

    void SetRandomNum(int count);
    QString GetTileColor(int i, int j);
    void CheckWinLose();

    void keyPressEvent(QKeyEvent* event);
};

#endif // GAME_H
