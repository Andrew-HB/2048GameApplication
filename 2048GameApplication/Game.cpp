#include "Game.h"
#include "ui_Game.h"

#include <QKeyEvent>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QTimer>
#include <QPixmap>

Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game),
    m_Score(0),
    m_PrevMoveScore(0),
    m_isFreeMode(false)
{
    ui->setupUi(this);

    QPixmap pix(":/res/img/Controls.png");
    int w = ui->controlLabel->width();
    int h = ui->controlLabel->height();
    ui->controlLabel->setPixmap(pix.scaled(w + 100, h + 100, Qt::KeepAspectRatio));

    ui->scoreLabel->setStyleSheet("font: 700 16pt \"Tahoma\";color: #776e65;");

    QTimer* timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &Game::PrintField);
    timer->start(15);

    Init();
}

Game::~Game()
{
    delete ui;
}

void Game::Init() {
    memset(m_GameField, 0, sizeof m_GameField);
    memset(m_PrevMoveGameField, 0, sizeof m_PrevMoveGameField);

    m_Score = 0;
    m_PrevMoveScore = 0;

    //m_GameField[0][0] = 1024;
    //m_GameField[0][1] = 1024;

    SetRandomNum(3);
}

void Game::PrintField() {
    if (m_GameField[0][0] != 0) ui->label_00->setText(QString::number(m_GameField[0][0])); else ui->label_00->setText("");
    if (m_GameField[0][1] != 0) ui->label_01->setText(QString::number(m_GameField[0][1])); else ui->label_01->setText("");
    if (m_GameField[0][2] != 0) ui->label_02->setText(QString::number(m_GameField[0][2])); else ui->label_02->setText("");
    if (m_GameField[0][3] != 0) ui->label_03->setText(QString::number(m_GameField[0][3])); else ui->label_03->setText("");
    if (m_GameField[1][0] != 0) ui->label_10->setText(QString::number(m_GameField[1][0])); else ui->label_10->setText("");
    if (m_GameField[1][1] != 0) ui->label_11->setText(QString::number(m_GameField[1][1])); else ui->label_11->setText("");
    if (m_GameField[1][2] != 0) ui->label_12->setText(QString::number(m_GameField[1][2])); else ui->label_12->setText("");
    if (m_GameField[1][3] != 0) ui->label_13->setText(QString::number(m_GameField[1][3])); else ui->label_13->setText("");
    if (m_GameField[2][0] != 0) ui->label_20->setText(QString::number(m_GameField[2][0])); else ui->label_20->setText("");
    if (m_GameField[2][1] != 0) ui->label_21->setText(QString::number(m_GameField[2][1])); else ui->label_21->setText("");
    if (m_GameField[2][2] != 0) ui->label_22->setText(QString::number(m_GameField[2][2])); else ui->label_22->setText("");
    if (m_GameField[2][3] != 0) ui->label_23->setText(QString::number(m_GameField[2][3])); else ui->label_23->setText("");
    if (m_GameField[3][0] != 0) ui->label_30->setText(QString::number(m_GameField[3][0])); else ui->label_30->setText("");
    if (m_GameField[3][1] != 0) ui->label_31->setText(QString::number(m_GameField[3][1])); else ui->label_31->setText("");
    if (m_GameField[3][2] != 0) ui->label_32->setText(QString::number(m_GameField[3][2])); else ui->label_32->setText("");
    if (m_GameField[3][3] != 0) ui->label_33->setText(QString::number(m_GameField[3][3])); else ui->label_33->setText("");

    ui->label_00->setStyleSheet("border-radius: 10px;font-size: 60px;font: small-caps bold 24px/1 sans-serif;" + GetTileColor(0, 0));
    ui->label_01->setStyleSheet("border-radius: 10px;font-size: 60px;font: small-caps bold 24px/1 sans-serif;" + GetTileColor(0, 1));
    ui->label_02->setStyleSheet("border-radius: 10px;font-size: 60px;font: small-caps bold 24px/1 sans-serif;" + GetTileColor(0, 2));
    ui->label_03->setStyleSheet("border-radius: 10px;font-size: 60px;font: small-caps bold 24px/1 sans-serif;" + GetTileColor(0, 3));
    ui->label_10->setStyleSheet("border-radius: 10px;font-size: 60px;font: small-caps bold 24px/1 sans-serif;" + GetTileColor(1, 0));
    ui->label_11->setStyleSheet("border-radius: 10px;font-size: 60px;font: small-caps bold 24px/1 sans-serif;" + GetTileColor(1, 1));
    ui->label_12->setStyleSheet("border-radius: 10px;font-size: 60px;font: small-caps bold 24px/1 sans-serif;" + GetTileColor(1, 2));
    ui->label_13->setStyleSheet("border-radius: 10px;font-size: 60px;font: small-caps bold 24px/1 sans-serif;" + GetTileColor(1, 3));
    ui->label_20->setStyleSheet("border-radius: 10px;font-size: 60px;font: small-caps bold 24px/1 sans-serif;" + GetTileColor(2, 0));
    ui->label_21->setStyleSheet("border-radius: 10px;font-size: 60px;font: small-caps bold 24px/1 sans-serif;" + GetTileColor(2, 1));
    ui->label_22->setStyleSheet("border-radius: 10px;font-size: 60px;font: small-caps bold 24px/1 sans-serif;" + GetTileColor(2, 2));
    ui->label_23->setStyleSheet("border-radius: 10px;font-size: 60px;font: small-caps bold 24px/1 sans-serif;" + GetTileColor(2, 3));
    ui->label_30->setStyleSheet("border-radius: 10px;font-size: 60px;font: small-caps bold 24px/1 sans-serif;" + GetTileColor(3, 0));
    ui->label_31->setStyleSheet("border-radius: 10px;font-size: 60px;font: small-caps bold 24px/1 sans-serif;" + GetTileColor(3, 1));
    ui->label_32->setStyleSheet("border-radius: 10px;font-size: 60px;font: small-caps bold 24px/1 sans-serif;" + GetTileColor(3, 2));
    ui->label_33->setStyleSheet("border-radius: 10px;font-size: 60px;font: small-caps bold 24px/1 sans-serif;" + GetTileColor(3, 3));

    ui->scoreLabel->setText("SCORE: " + QString::number(m_Score));
}

void Game::MakeMove(int dir) {
     // 0 - Right
     // 1 - Down
     // 2 - Left
     // 3 - Up

    memcpy(m_PrevMoveGameField, m_GameField, sizeof m_PrevMoveGameField);
    m_PrevMoveScore = m_Score;

    switch(dir) {
    case MoveDir::RIGHT:
        for (int k = 0; k < 3; k++) {
            for (int j = FIELD_SIZE - 2; j >= 0; j--) {
                for (int i = 0; i < FIELD_SIZE; i++) {
                    if (m_GameField[i][j] == 0) continue;

                    if (m_GameField[i][j + 1] == 0) {
                        m_GameField[i][j + 1] = m_GameField[i][j];
                        m_GameField[i][j] = 0;
                    }

                    if (m_GameField[i][j + 1] == m_GameField[i][j]) {
                        m_GameField[i][j + 1] *= 2;
                        m_Score += m_GameField[i][j];
                        m_GameField[i][j] = 0;
                    }
                }
            }
        }
        break;
    case MoveDir::DOWN:
        for (int k = 0; k < 3; k++) {
            for (int i = FIELD_SIZE - 2; i >=0; i--) {
                for (int j = 0; j < FIELD_SIZE; j++) {
                    if (m_GameField[i][j] == 0) continue;

                    if (m_GameField[i + 1][j] == 0) {
                        m_GameField[i + 1][j] = m_GameField[i][j];
                        m_GameField[i][j] = 0;
                    }

                    if (m_GameField[i + 1][j] == m_GameField[i][j]) {
                        m_GameField[i + 1][j] *= 2;
                        m_Score += m_GameField[i][j];
                        m_GameField[i][j] = 0;
                    }
                }
            }
        }
        break;
    case MoveDir::LEFT:
        for (int k = 0; k < 3; k++) {
            for (int j = 1; j < FIELD_SIZE; j++) {
                for (int i = 0; i < FIELD_SIZE; i++) {
                    if (m_GameField[i][j] == 0) continue;

                    if (m_GameField[i][j - 1] == 0) {
                        m_GameField[i][j - 1] = m_GameField[i][j];
                        m_GameField[i][j] = 0;
                    }

                    if (m_GameField[i][j - 1] == m_GameField[i][j]) {
                        m_GameField[i][j - 1] *= 2;
                        m_Score += m_GameField[i][j];
                        m_GameField[i][j] = 0;
                    }
                }
            }
        }
        break;
    case MoveDir::UP:
        for (int k = 0; k < 3; k++) {
            for (int i = 1; i < FIELD_SIZE; i++) {
                for (int j = 0; j < FIELD_SIZE; j++) {
                    if (m_GameField[i][j] == 0) continue;

                    if (m_GameField[i - 1][j] == 0) {
                        m_GameField[i - 1][j] = m_GameField[i][j];
                        m_GameField[i][j] = 0;
                    }

                    if (m_GameField[i - 1][j] == m_GameField[i][j]) {
                        m_GameField[i - 1][j] *= 2;
                        m_Score += m_GameField[i][j];
                        m_GameField[i][j] = 0;
                    }
                }
            }
        }
        break;
    }

    CheckWinLose();
    SetRandomNum(1);
}

void Game::SetRandomNum(int count) {
    for (int i = 0; i < count; i++) {
        bool isFreeCellsExist = false;
        for (int i = 0; i < FIELD_SIZE; i++) {
            for (int j = 0; j < FIELD_SIZE; j++) {
                if (m_GameField[i][j] == 0) isFreeCellsExist = true;
            }
        }

        if (isFreeCellsExist == false) continue;

        int index = QRandomGenerator::global()->generate() % (FIELD_SIZE * FIELD_SIZE);
        while(m_GameField[index / FIELD_SIZE][index % FIELD_SIZE] != 0) {
            if (index == (FIELD_SIZE * FIELD_SIZE) - 1) index = 0;
            index++;
        }

        if(1 + QRandomGenerator::global()->generate() % 101 <= 15)
            m_GameField[index / FIELD_SIZE][index % FIELD_SIZE] = 4;
        else
            m_GameField[index / FIELD_SIZE][index % FIELD_SIZE] = 2;
    }
}

QString Game::GetTileColor(int i, int j) {
    switch (m_GameField[i][j]) {
    case 0:
        return "background-color: #d6cdc4;";
    case 2:
        return "background-color: #eee4da; color: #6f675c;";
    case 4:
        return "background-color: #ece0c8; color: #6f675c;";
    case 8:
        return "background-color: #f2b179; color: #ffffff;";
    case 16:
        return "background-color: #f59563; color: #ffffff;";
    case 32:
        return "background-color: #f57c5f; color: #ffffff;";
    case 64:
        return "background-color: #f65d3b; color: #ffffff;";
    case 128:
        return "background-color: #edce71; color: #ffffff;";
    case 256:
        return "background-color: #edcc61; color: #ffffff;";
    case 512:
        return "background-color: #ecc850; color: #ffffff;";
    case 1024:
        return "background-color: #edc53f; color: #ffffff;";
    case 2048:
        return "background-color: #eec22f; color: #ffffff;";
    default:
        return "background-color: black; color: #ffffff;";
    }

}

void Game::CheckWinLose() {
    if (!m_isFreeMode) {
        // Win
        for (int i = 0 ; i < FIELD_SIZE; i++) {
            for (int j = 0; j < FIELD_SIZE; j++) {
                if (m_GameField[i][j] == 2048) {
                    QMessageBox::StandardButton resBtn = QMessageBox::question(this, "2048",
                                                                                   tr("You Win!\nDo you want to continue?"),
                                                                                   QMessageBox::No | QMessageBox::Yes,
                                                                                   QMessageBox::Yes);
                    if (resBtn == QMessageBox::No) {
                        this->Init();
                    } else {
                        m_isFreeMode = true;
                    }

                }
            }
        }
    }

    //Lose
    bool isFreeCellsExist = false;

    for (int i = 0 ; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            if (m_GameField[i][j] == 0) isFreeCellsExist = true;
        }
    }

    if (isFreeCellsExist) {
        return;
    }

    for (int i = 1; i < FIELD_SIZE - 1; i++) {
        for (int j = 1; j < FIELD_SIZE - 1; j++) {
            if      (m_GameField[i][j] == m_GameField[i - 1][j]) { return; }
            else if (m_GameField[i][j] == m_GameField[i][j - 1]) { return; }
            else if (m_GameField[i][j] == m_GameField[i + 1][j]) { return; }
            else if (m_GameField[i][j] == m_GameField[i][j + 1]) { return; }
        }
    }

    if (m_GameField[0][0] == m_GameField[0][1] || m_GameField[0][0] == m_GameField[1][0] ||
        m_GameField[0][FIELD_SIZE - 1] == m_GameField[0][FIELD_SIZE - 2] || m_GameField[0][FIELD_SIZE - 1] == m_GameField[1][FIELD_SIZE - 1] ||
        m_GameField[FIELD_SIZE - 1][0] == m_GameField[FIELD_SIZE - 2][0] || m_GameField[FIELD_SIZE - 1][0] == m_GameField[FIELD_SIZE - 1][1] ||
        m_GameField[FIELD_SIZE - 1][FIELD_SIZE - 1] == m_GameField[FIELD_SIZE - 2][FIELD_SIZE - 1] || m_GameField[FIELD_SIZE - 1][FIELD_SIZE - 1] == m_GameField[FIELD_SIZE - 1][FIELD_SIZE - 2])
       { return; }

    QMessageBox::StandardButton resBtn = QMessageBox::question(this, "2048",
                                                                   tr("You Lose!\nDo you want to play again?"),
                                                                   QMessageBox::No | QMessageBox::Yes,
                                                                   QMessageBox::Yes);
    if (resBtn == QMessageBox::No) {
        this->close();
    } else {
        this->Init();
    }
}

void Game::keyPressEvent(QKeyEvent* event) {

    if      (event->key() == Qt::Key_Right) MakeMove(MoveDir::RIGHT);
    else if (event->key() == Qt::Key_Down)  MakeMove(MoveDir::DOWN);
    else if (event->key() == Qt::Key_Left)  MakeMove(MoveDir::LEFT);
    else if (event->key() == Qt::Key_Up)    MakeMove(MoveDir::UP);

    else if (event->key() == Qt::Key_Backspace) {
        m_Score = m_PrevMoveScore;

        memset(m_GameField, 0, sizeof m_GameField);
        memcpy(m_GameField, m_PrevMoveGameField, sizeof m_GameField);
    }
}
