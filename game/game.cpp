#include "game.hpp"

#include "ball.hpp"
#include "racket.hpp"
#include "collisions.hpp"


Game::Game(Qt3DCore::QEntity * root, Qt3DRender::QCamera * camera)
    : Qt3DCore::QEntity(root)
    , rootEntity_(root)
    , camera_    (camera)
    , scene_     (std::make_unique<Scene>(root))
{
    assert(root);
    assert(camera);

    gotoMainMenu();
}


void Game::gotoMainMenu()
{
    assert(camera_);
    camera_->setPosition({20, 8, 0});
    camera_->setViewCenter({0, 4, 0});
    camera_->setUpVector({0, 1, 0});

    assert(!camFly_);
    camFly_ = std::make_unique<CamFlyingAround>(camera_, 20);

    delRackets();
    delBall();
}


void Game::singlePlayer()
{
    qDebug() << "Singleplayer";
    setScore({0, 0});

    delCamFly();
    camPlayPos();

    assert(!racket1_ && !racket2_);
    assert(!ball_);

    racket1_ = new Racket(rootEntity_);
    racket1_->setPos({5.0, 5.0, 0.0});
    racket2_ = new Racket(rootEntity_);
    racket2_->setPos({-5.0, 5.0, 0.0});
    racket1_->runAnimation2({4.0, 4.6, 2.0}, 500ms);

    ball_ = new Ball(rootEntity_);
    ball_->setPos({5.0, 5.85f, 0.0});
    //ball_->setGravity(true);
    //ball_->setV({0, Table::h + 0.2f, 0}, 1000ms);
//    ball_->setBorderCrossNotifier({{-3, 3}});

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

    new Collisions(ball_, scene_.get());
}


void Game::keyEvent(int key)
{
    Q_UNUSED(key)
    qDebug() << "Key handled in C++!";
}


void Game::camPlayPos()
{
    camera_->setPosition({20, 8, 0});
    camera_->setViewCenter({0, 3, 0});
    camera_->setUpVector({0, 1, 0});
}


void Game::delCamFly()
{
    if (camFly_) {
        delete camFly_.release();
    }
}


void Game::delRackets()
{
    if (racket1_) {
        delete racket1_;
        racket1_ = nullptr;
    }
    if (racket2_) {
        delete racket2_;
        racket2_ = nullptr;
    }
}


void Game::delBall()
{
    if (ball_) {
        delete ball_;
        ball_ = nullptr;
    }
}


void Game::addScore(Score val)
{
    score_.first  += val.first;
    score_.second += val.second;
    emit scoreChanged(score_);
}


void Game::setScore(Score val)
{
    score_ = val;
    emit scoreChanged(score_);
}


Game::Score Game::score() const
{
    return score_;
}


int Game::score1() const
{
    return score_.first;
}


int Game::score2() const
{
    return score_.second;
}















