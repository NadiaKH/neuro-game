#include "collisions.hpp"

#include "table.hpp"
#include "ball.hpp"


Collisions::Collisions(Ball * ball, Table const * table)
    : ball_ (ball)
    , table_(table)
{
    assert(ball);
    assert(table);

    // It should not be connected to deleteLater,
    // dtor will throw std::bad_alloc in disconnect.
    connect(ball_, &Ball::destroyed, this, &Collisions::harakiri);
    connect(Clock::instance(), Clock::instance()->getTimerSignalDt(ball->dt()),
            this, &Collisions::update);
}


Collisions::~Collisions()
{
    disconnect(ball_, &Ball::destroyed, this, &Collisions::deleteLater);
}


void Collisions::update(Time dt)
{
    Q_UNUSED(dt)
    assert(ball_);
    assert(table_);

    if (auto n = table_->intersects(ball_)) {
        ball_->reflect(n.value());
    }
}


void Collisions::harakiri()
{
    delete this;
}
