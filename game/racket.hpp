#pragma once

#include "stdafx.hpp"
#include "time.hpp"
#include "movable.hpp"

class Racket final
        : public QObject {
    Q_OBJECT

public:
    explicit Racket(Qt3DCore::QEntity * parent);
    /**
      * @warning Racket should not be deleted after parent.
      */
    ~Racket() override;

    void setPos(QVector3D pos);
    /*
    void setRotation(...)
    */
    QVector3D pos() const;

    Qt3DCore::QTransform * transform();

    /**
     * @brief Runs racket animation and emmits animationFinished() at the end.
     * @param endPos Where ball will be to return a ball.
     * @param dt Time in which ball reach endPos.
     */
    void runAnimation1(QVector3D endPos, Time dt){
        Movable * m = new Movable(transform_);
        m->startMove(endPos, dt);
    }

//signals:
//   void animationFinished();

private:
    Qt3DCore::QEntity * entity_;
    Qt3DCore::QTransform * transform_;
};

