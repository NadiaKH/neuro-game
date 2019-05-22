#pragma once

#include "stdafx.hpp"
#include "time.hpp"


class Racket;

class RacketAnimation1 final
        : public QObject {
    Q_OBJECT

public:
    RacketAnimation1(Racket * r, QVector3D finPos, Time dt);
    ~RacketAnimation1();

private:
    void update(Time dt);

private:
    Racket * racket_;
    // ...
};
