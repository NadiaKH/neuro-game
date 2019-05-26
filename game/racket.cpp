#include "racket.hpp"

#include "scene.hpp"


Racket::Racket(Qt3DCore::QEntity * parent)
    : entity_(new Qt3DCore::QEntity(parent))
    , transform_(new Qt3DCore::QTransform)
    , shift_({0.0, -0.85f, 0.0})
{
    assert(parent);

    transform_->setRotation(
                QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), 90));

    auto * mesh = new Qt3DRender::QMesh;
    mesh->setSource({ASSETS "racket.obj"});

    auto * textureLoader = new Qt3DRender::QTextureLoader;
    textureLoader->setSource({ASSETS "racket.png"});
    auto * textures = new Qt3DExtras::QDiffuseMapMaterial;
    textures->setDiffuse(textureLoader);
    textures->setSpecular({0, 0, 0});
    textures->setAmbient({100, 100, 100});

    entity_->addComponent(mesh);
    entity_->addComponent(textures);
    entity_->addComponent(transform_);
}


Racket::~Racket()
{
    delete entity_;
}


void Racket::setPos(QVector3D pos)
{
    transform_->setTranslation(pos + transform_->rotation().rotatedVector(shift_));
}


QVector3D Racket::pos() const
{
    return transform_->translation() - transform_->rotation().rotatedVector(shift_);
}


Qt3DCore::QTransform * Racket::transform()
{
    return transform_;
}


void Racket::runAnimation1(QVector3D newPos, Time dt)
{
    auto ra = new RacketAnimation1(this, newPos, dt);
    connect(ra, &RacketAnimation1::stop, this, &Racket::animationFinished);
}


void Racket::runAnimation2(QVector3D newPos, Time dt)
{
    auto ra = new RacketAnimation2(this, newPos, dt);
    connect(ra, &RacketAnimation2::stop, this, &Racket::animationFinished);
}

void Racket::runAnimation10(QVector3D newPos, Time dt)
{
    auto ra = new RacketAnimation10(this, newPos, dt);
    connect(ra, &RacketAnimation10::stop, this, &Racket::animationFinished);
}


void Racket::rotateX(float x)
{
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


void Racket::rotateY(float y)
{
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


void Racket::rotateZ(float z)
{
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






