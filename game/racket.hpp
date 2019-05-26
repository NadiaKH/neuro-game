#pragma once

#include "stdafx.hpp"
#include "time.hpp"
#include "racketanimation1.hpp"
#include "racketanimation2.hpp"
#include "racketanimation2_copy.hpp"
#include <math.h>

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
    QVector3D pos() const;

    Qt3DCore::QTransform * transform();

    /**
     * @brief Runs racket animation and emmits animationFinished() at the end.
     * @param endPos Where ball will be to return a ball.
     * @param dt Time in which ball reach endPos.
     */
    void runAnimation1(QVector3D newPos, Time dt);
    void runAnimation2(QVector3D newPos, Time dt);
    void runAnimation10(QVector3D newPos, Time dt);

    void rotateX(float x);
    void rotateY(float y);
    void rotateZ(float z);

signals:
   void animationFinished();

private:
    Qt3DCore::QEntity * entity_;
    Qt3DCore::QTransform * transform_;
    QVector3D shift_;
};

