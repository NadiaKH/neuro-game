#include "ai.hpp"

#include "table.hpp"
#include "ball.hpp"
#include "racket.hpp"
#include "collisions.hpp"


AI::AI(Racket * lr, Racket * rr, Ball * ball, Table const * table)
    : lracket_(lr)
    , rracket_(rr)
    , ball_   (ball)
    , table_  (table)
{
    assert(lr && rr && ball && table);

    connect(lracket_, &Racket::destroyed, this, &AI::delThis);
    connect(rracket_, &Racket::destroyed, this, &AI::delThis);
    connect(ball_,    &Ball::destroyed,   this, &AI::delThis);
    connect(table_,   &Table::destroyed,  this, &AI::delThis);

    start();
}


AI::~AI()
{
    disconnect(lracket_, &Racket::destroyed, this, &AI::delThis);
    disconnect(rracket_, &Racket::destroyed, this, &AI::delThis);
    disconnect(ball_,    &Ball::destroyed,   this, &AI::delThis);
    disconnect(table_,   &Table::destroyed,  this, &AI::delThis);
}


void AI::delThis()
{
    delete this;
}


void AI::start()
{
    lracket_->setPos({-5.0, 5.0, 0.0});
    rracket_->setPos({5.0, 5.0, 0.0});

    ball_->setPos({5.0, 5.85f, 0.0});
    ball_->setGravity(true);
    ball_->setBorderCrossNotifier({{-5, 5}});
    sendBallToOtherSide();

    connect(ball_, &Ball::reflected, this, &AI::ballReflected);
    connect(lracket_, &Racket::animationFinished, this, &AI::sendBallToOtherSide);
    connect(rracket_, &Racket::animationFinished, this, &AI::sendBallToOtherSide);

    connect(ball_, &Ball::borderCrossed, [](bool crossedInto) {
        if (crossedInto) {
            Clock::instance()->setDeceleration(100);
        } else {
            Clock::instance()->setDeceleration(30);
        }
    });
    connect(ball_, &Ball::destroyed, [] {
        Clock::instance()->setDeceleration(100);
    });

    new Collisions(ball_, table_);
}


QVector3D AI::genBallPosL() const
{
    float x = table_->x1 / 2;
    float y = table_->h;
    float z = (table_->z1 + table_->z2) / 2;
    return { x, y, z };
}


QVector3D AI::genBallPosR() const
{
    float x = table_->x2 / 2;
    float y = table_->h;
    float z = (table_->z1 + table_->z2) / 2;
    return { x, y, z };
}


void AI::sendBallToOtherSide()
{
    const Time flyTime = 800ms;

    if (ball_->pos().x() < 0) {
        ball_->setV(genBallPosR(), flyTime);
    } else {
        ball_->setV(genBallPosL(), flyTime);
    }
}


void AI::ballReflected(QVector3D newV)
{
    const Time t = 500ms;

    if (newV.x() > 0) {
        rracket_->runAnimation2(ball_->predictPos(t), t);
    } else {
        lracket_->runAnimation2(ball_->predictPos(t), t);
    }
}

























