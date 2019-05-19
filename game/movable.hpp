#pragma once

#include <functional>
#include "stdafx.hpp"
#include "time.hpp"


enum moveType { LINEAR_MOVE };


class Movable final : public QObject
{
    Q_OBJECT
public:
    Movable(Qt3DCore::QTransform * transform) :  transform_(transform) {
        connect(Clock::instance(), &Clock::fps60dt, this, &Movable::update);
    }


    void startMove(QVector3D newPos, Time dt, moveType = LINEAR_MOVE) {
        newPos_ = newPos;
        dt_ = dt;
        move_ = std::bind(&Movable::LinearMove, this);
    }

signals:
    void stop();

private:
    Time dt_;
    QVector3D newPos_;
    QVector3D v_;


    Qt3DCore::QTransform * transform_;
    std::function<void()> move_;


    void LinearMove() {
        QVector3D pos = transform_->translation();
        v_ = (newPos_ - pos) / timeToSec(dt_);
        transform_->setTranslation(pos + v_);

        if (dt_ <= Clock::dt60) {
            stop();
            delete this;
        }
        else
            dt_ -= Clock::dt60;
    }


    void update() {
        move_();
    }


};
