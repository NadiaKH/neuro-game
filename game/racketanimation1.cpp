#include "racketanimation1.hpp"

#include "racket.hpp"


RacketAnimation1::RacketAnimation1(Racket * r, QVector3D finPos, Time dt)
    : racket_(r)
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
    // TODO
}
