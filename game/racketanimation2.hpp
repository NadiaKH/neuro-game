#pragma once

#include "stdafx.hpp"
#include "time.hpp"

class Racket;

class RacketAnimation2 final
        : public QObject {
    Q_OBJECT

public:
    RacketAnimation2(Racket  * r, QVector3D newPos, Time dt);
    ~RacketAnimation2();

signals:
    void stop();

private:
    void update(Time dt);
    void move();

    QVector3D semiCycle(QVector3D x0, QVector3D x1);
    QVector3D cycle(QVector3D x, QVector3D bound);

    float semiCycle(float x0, float x1);
    float cycle(float x, float bound);
    float cycle2(float x, float bound);

private:
    Racket * racket_;
    Time duration_;
    Time time_;
    QVector3D startPos_;
    QVector3D newPos_;
    QVector3D v_;
};
