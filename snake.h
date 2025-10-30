#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include "point.h"

class Food;
class Snake
{
public:
    enum class Direction {UP, DOWN, LEFT, RIGHT};

    Snake() {
        snake.emplace_back(14, 8);
        snake.emplace_back(15, 8);
        snake.emplace_back(16, 8);
        direction = Direction::DOWN;
    }
    void InitSnake();
    void Move();
    void NormalMove();
    bool OverEdge() const;
    bool HitItself() const;
    bool ChangeDirection();
    bool GetFood(const Food&) const;
    bool GetBigFood(Food&);
private:
    std::deque<Point> snake;
    Direction direction;
    friend class Food;//��Food����Ϊ��Ԫ���Ա������˽��Ԫ��
};
#endif // SNAKE_H
