#pragma once

#include "stdafx.hpp"
#include "time.hpp"
#include "movable.hpp"
#include "racketanimation1.hpp"
#include "racketanimation2.hpp"
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
    void runAnimation1(QVector3D newPos, Time dt){
        RacketAnimation1 * ra = new RacketAnimation1(this, newPos, dt);
    }

    void runAnimation2(QVector3D newPos, Time dt){
        RacketAnimation2 * ra = new RacketAnimation2(this, newPos, dt);
    }
    
    void rotateX(float x) {
        x /= 2;
        x = x * float(M_PI)/ 180;

        QQuaternion rotX(cosf(x), {sinf(x), 0, 0});
        QQuaternion cur_rot(transform_->rotation());
        QQuaternion rotation = cur_rot * rotX;


        QVector3D curTransl = transform_->translation();

        QVector3D oldShift = cur_rot.rotatedVector(shift_);
        QVector3D newShift = rotation.rotatedVector(shift_);

        transform_->setTranslation(curTransl - oldShift + newShift);
        transform_->setRotation(rotation);

    }
    
    void rotateY(float y) {
        y /= 2;
        y = y * float(M_PI)/ 180;

        QQuaternion rotY(cosf(y), {0, sinf(y), 0});
        QQuaternion cur_rot(transform_->rotation());
        QQuaternion rotation = cur_rot * rotY;


        QVector3D curTransl = transform_->translation();

        QVector3D oldShift = cur_rot.rotatedVector(shift_);
        QVector3D newShift = rotation.rotatedVector(shift_);

        transform_->setTranslation(curTransl - oldShift + newShift);
        transform_->setRotation(rotation);

    }
    
    void rotateZ(float z) {
        z /= 2;
        z = z * float(M_PI)/ 180;

        QQuaternion rotZ(cosf(z), {0, 0, sinf(z)});
        QQuaternion cur_rot(transform_->rotation());
        QQuaternion rotation = cur_rot * rotZ;


        QVector3D curTransl = transform_->translation();

        QVector3D oldShift = cur_rot.rotatedVector(shift_);
        QVector3D newShift = rotation.rotatedVector(shift_);

        transform_->setTranslation(curTransl - oldShift + newShift);
        transform_->setRotation(rotation);
    }



//signals:
//   void animationFinished();

private:
    Qt3DCore::QEntity * entity_;
    Qt3DCore::QTransform * transform_;
    QVector3D shift_;
};

