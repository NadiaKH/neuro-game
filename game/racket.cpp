#include "racket.hpp"

#include "scene.hpp"


Racket::Racket(Qt3DCore::QEntity * parent)
    : entity_(new Qt3DCore::QEntity(parent))
    , transform_(new Qt3DCore::QTransform)
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
    transform_->setTranslation(pos);
}


QVector3D Racket::pos() const
{
    return transform_->translation();
}


Qt3DCore::QTransform * Racket::transform()
{
    return transform_;
}













