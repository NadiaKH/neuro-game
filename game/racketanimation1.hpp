#pragma once

#include "stdafx.hpp"
#include "time.hpp"

class Racket;


// TODO fix style
class RacketAnimation1 final
        : public QObject {
    Q_OBJECT

public:
    RacketAnimation1(Racket  * r, QVector3D newPos, Time dt);
    ~RacketAnimation1();



    QVector3D semiCycle(QVector3D x0, QVector3D x1) {
        float t = timeToSec(time_) / timeToSec(duration_);
        QVector3D m = (x0 + x1) / 2;
        QVector3D a = (x0 - x1) / 2;
        return a * cosf(float(M_PI) * t) + m;
    }

signals:
    void stop();

private:
    void update(Time dt);
    void move();

private:
    Racket * racket_;
    Time time_;
    Time duration_;
    QVector3D newPos_;
    QVector3D v_;

};
