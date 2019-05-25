#include "racketanimation1.hpp"
#include "stdafx.hpp"
#include "time.hpp"
#include "racket.hpp"


RacketAnimation1::RacketAnimation1(Racket * r, QVector3D newPos, Time dt)
    : racket_(r), time_(0), duration_(dt), newPos_(newPos)
{
    assert(r);
    connect(racket_, &Racket::destroyed, this, &RacketAnimation1::deleteLater);
    connect(Clock::instance(), &Clock::fps60dt, this, &RacketAnimation1::update);
}


RacketAnimation1::~RacketAnimation1()
{
    disconnect(racket_, &Racket::destroyed, this, &RacketAnimation1::deleteLater);
    disconnect(Clock::instance(), &Clock::fps60dt, this, &RacketAnimation1::update);
}


void RacketAnimation1::update(Time dt)
{
    Q_UNUSED(dt)
    move();
}

void RacketAnimation1::move() {

    //time_ += Clock::dt60;
    //if (time_ < duration_ / 3) return;

    static Time r = duration_ - time_;
    static Time t(0);
    static QVector3D dpos = (newPos_ - racket_->pos());
    //static float ax = -racket_->transform()->rotationX();
    //static float ay = -racket_->transform()->rotationY();
    //static float az = -racket_->transform()->rotationZ();
//    static float c = timeToSec(Clock::dt60)/timeToSec(r);

    //racket_->rotateX(ax * c);
    //racket_->rotateY(ay * c);
    //racket_->rotateZ(az * c);

    racket_->setPos(racket_->pos() + dpos);


    if (t >= r) {
        emit stop();
        delete this;
    }
    else
        t += Clock::dt60;
}
