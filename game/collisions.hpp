#pragma once

#include "stdafx.hpp"
#include "time.hpp"


class Ball;
class Table;

class Collisions final
        : public QObject {
    Q_OBJECT

public:
    Collisions(Ball * ball, Table const * table);
    ~Collisions() override;

private slots:
    void update(Time dt);
    void harakiri();

private:
    Ball * ball_;
    Table const * table_;
};
