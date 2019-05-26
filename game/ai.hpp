#pragma once

#include "stdafx.hpp"


class Racket;
class Ball;
class Table;

class AI final
        : public QObject {
public:
    AI(Racket * lr, Racket * rr, Ball * ball, Table const * table);
    ~AI();

public slots:
    void delThis();

private:
    void start();
    QVector3D genBallPosL() const;
    QVector3D genBallPosR() const;

private slots:
    void sendBallToOtherSide();
    void ballReflected(QVector3D newV);

private:
    Racket * lracket_; // Negative x
    Racket * rracket_; // Positive x
    Ball   * ball_;
    Table const * table_;
};
