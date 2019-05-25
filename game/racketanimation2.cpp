#include "racketanimation2.hpp"
#include "stdafx.hpp"
#include "time.hpp"
#include "racket.hpp"


RacketAnimation2::RacketAnimation2(Racket * r, QVector3D newPos, Time dt)
    : racket_(r), duration_(dt), time_(0), startPos_(r->pos()), newPos_(newPos)
{
    assert(r);
    connect(racket_, &Racket::destroyed, this, &RacketAnimation1::deleteLater);
    connect(Clock::instance(), &Clock::fps60dt, this, &RacketAnimation2::update);

}


RacketAnimation2::~RacketAnimation2()
{

    disconnect(racket_, &Racket::destroyed, this, &RacketAnimation2::deleteLater);
    disconnect(Clock::instance(), &Clock::fps60dt, this, &RacketAnimation2::update);
}


void RacketAnimation2::update(Time dt)
{
    move();
}

void RacketAnimation2::move() {

    static float startAngle = 0;
    static float amplitudeAngle = 60;
    static float prev = 0;
    float cur = cycle2(startAngle, amplitudeAngle);

    racket_->rotateX(cur - prev);
    prev = cur;



    static float rotAngle = newPos_.z() > startPos_.z() ? 0.3f : -0.3f;
    racket_->rotateZ(rotAngle);


    QVector3D p = semiCycle(startPos_, newPos_);
    racket_->setPos(p);


    if (time_ >= duration_) {
        emit stop();
        racket_->setPos(startPos_);
        QQuaternion rot = racket_->transform()->rotation();
        racket_->transform()->setRotation(rot.inverted());
        delete this;
    }
    else
        time_ += Clock::dt60;
}





QVector3D RacketAnimation2::semiCycle(QVector3D x0, QVector3D x1) {
    float t = timeToSec(time_) / timeToSec(duration_);
    QVector3D m = (x0 + x1) / 2;
    QVector3D a = (x0 - x1) / 2;
    return a * cosf(float(M_PI) * t) + m;
}

QVector3D RacketAnimation2::cycle(QVector3D x, QVector3D bound) {
    float t = timeToSec(time_) / timeToSec(duration_);
    QVector3D m = (x + bound) / 2;
    QVector3D a = (x - bound) / 2;
    return a * cosf(2 * float(M_PI) * t) + m;
}

float RacketAnimation2::semiCycle(float x0, float x1) {
    float t = timeToSec(time_) / timeToSec(duration_);
    float m = (x0 + x1) / 2;
    float a = (x0 - x1) / 2;
    return a * cosf(float(M_PI) * t) + m;
}

float RacketAnimation2::cycle(float x, float bound) {
    float t = timeToSec(time_) / timeToSec(duration_);
    float m = (x + bound) / 2;
    float a = (x - bound) / 2;
    return a * cosf(2 * float(M_PI) * t) + m;
}


float RacketAnimation2::cycle2(float x, float bound) {
    float t = timeToSec(time_) / timeToSec(duration_);
    float a = (x - bound);
    return -a * sqrt(abs(sinf(float(M_PI) * powf(t, 2)))) + x;
}
