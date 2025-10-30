/**
 * @file snake.cpp
 * @brief 蛇类实现文件
 * @details 实现了蛇的初始化、移动、碰撞检测、方向控制等核心游戏逻辑
 */

#include "snake.h"
#include "food.h"
#include "tools.h"
#include <conio.h>
#include <iostream>

namespace {
constexpr int KEY_UP = 72;
constexpr int KEY_DOWN = 80;
constexpr int KEY_LEFT = 75;
constexpr int KEY_RIGHT = 77;
constexpr int KEY_ESC = 27;
}


/**
 * @brief 初始化并绘制蛇
 * @details 遍历蛇身点集合，在控制台绘制完整的蛇身（黄色圆形）
 */
void Snake::InitSnake() {
  // 遍历蛇身的所有点，逐个绘制
  for (auto &point : snake) {
    point.PrintCircular(); // 绘制圆形字符"●"表示蛇身
  }
}

/**
 * @brief 蛇增长（吃到食物后调用）
 * @details
 * 根据当前移动方向，在蛇的尾部（deque的back）添加一个新的点，使蛇身增长
 *          新添加的点会根据方向在蛇头（最后一个元素）的基础上移动一步
 */
void Snake::Move() {
  switch (direction) // 根据当前移动方向添加新点
  {
  case Direction::UP: // 向上移动
    // 在蛇头上方添加新点（Y坐标减1）
    snake.emplace_back(Point(snake.back().GetX(), snake.back().GetY() - 1));
    break;
  case Direction::DOWN: // 向下移动
    // 在蛇头下方添加新点（Y坐标加1）
    snake.emplace_back(Point(snake.back().GetX(), snake.back().GetY() + 1));
    break;
  case Direction::LEFT: // 向左移动
    // 在蛇头左侧添加新点（X坐标减1）
    snake.emplace_back(Point(snake.back().GetX() - 1, snake.back().GetY()));
    break;
  case Direction::RIGHT: // 向右移动
    // 在蛇头右侧添加新点（X坐标加1）
    snake.emplace_back(Point(snake.back().GetX() + 1, snake.back().GetY()));
    break;
  default:
    break;
  }

  // 绘制新添加的蛇头部分（黄色）
  SetColor(14);                 // 设置颜色为黄色
  snake.back().PrintCircular(); // 绘制蛇的新头部
}

/**
 * @brief 蛇正常移动（未吃到食物时调用）
 * @details 在头部添加一个新点（根据方向），同时清除并删除尾部，实现移动效果
 *          这是蛇的基本移动方式，保持蛇的长度不变
 */
void Snake::NormalMove() {
  Move();                // 在头部添加新点（向移动方向增长）
  snake.front().Clear(); // 清除尾部显示
  snake.pop_front();     // 删除尾部点，保持蛇的长度不变
}

/**
 * @brief 检测蛇是否超出边界（撞墙）
 * @return bool true表示未超出边界（安全），false表示超出边界（游戏结束）
 * @details 检查蛇头（snake.back()）的坐标是否在地图边界内（2-29之间）
 */
bool Snake::OverEdge() const {
  // 检查蛇头坐标是否在有效范围内（2 <= x < 30, 2 <= y < 30）
  // 注意：边界坐标是1-30，但有效游戏区域是2-29
  return snake.back().GetX() < 30 && snake.back().GetY() < 30 &&
         snake.back().GetX() > 1 && snake.back().GetY() > 1;
}

/**
 * @brief 检测蛇是否撞到自身
 * @return bool true表示未撞到自身（安全），false表示撞到自身（游戏结束）
 * @details 通过遍历蛇身，检查蛇头是否与其他身体部分重叠
 *          如果蛇头位置在蛇身中出现的次数超过1次（即与其他身体部分重叠），则撞到自身
 */
bool Snake::HitItself() const {
  const int headX = snake.back().GetX();
  const int headY = snake.back().GetY();
  // 从头到尾遍历，遇到第一个与头相同的位置即认为撞到自身
  std::deque<Point>::size_type cnt = 1; // 计数器，初始为1（蛇头本身）
  for (const auto &point : snake) {
    if (!(point.GetX() == headX && point.GetY() == headY))
      ++cnt;
    else
      break;
  }
  return cnt == snake.size();
}

/**
 * @brief 处理键盘输入并改变蛇的移动方向
 * @return bool true表示继续游戏，false表示按ESC暂停（退出游戏循环）
 * @details 检测方向键输入并更新蛇的移动方向，禁止向相反方向移动
 *          按ESC键时返回false，触发暂停菜单
 */
bool Snake::ChangeDirection() {
  char ch;

  if (kbhit()) // 检测是否有键盘输入（非阻塞）
  {
    ch = getch(); // 获取按键字符

    switch (ch) {
    case -32:       // 方向键的前缀码（-32表示按下的是方向键）
      ch = getch(); // 再次获取，得到实际的方向键值
      switch (ch) {
      case KEY_UP: // 上方向键（UP）
        // 如果当前方向不是向下，则允许向上移动（禁止180度转向）
        if (direction != Direction::DOWN)
          direction = Direction::UP;
        break;
      case KEY_DOWN: // 下方向键（DOWN）
        if (direction != Direction::UP)
          direction = Direction::DOWN;
        break;
      case KEY_LEFT: // 左方向键（LEFT）
        if (direction != Direction::RIGHT)
          direction = Direction::LEFT;
        break;
      case KEY_RIGHT: // 右方向键（RIGHT）
        if (direction != Direction::LEFT)
          direction = Direction::RIGHT;
        break;
      default:
        break;
      }
      return true; // 方向改变成功，继续游戏

    case KEY_ESC:        // ESC键
      return false; // 返回false，触发暂停菜单

    default:       // 其他按键
      return true; // 忽略其他按键，继续游戏
    }
  }
  return true; // 无按键输入，继续游戏
}

/**
 * @brief 检测蛇是否吃到普通食物
 * @param cfood 食物对象的常引用
 * @return bool true表示吃到食物，false表示未吃到
 * @details 检查蛇头坐标是否与普通食物坐标相同
 */
bool Snake::GetFood(const Food &cfood) const {
  // 比较蛇头坐标与食物坐标
  if (snake.back().GetX() == cfood.x && snake.back().GetY() == cfood.y)
    return true; // 吃到食物
  else
    return false; // 未吃到食物
}

/**
 * @brief 检测蛇是否吃到限时食物
 * @param cfood 食物对象的引用（需要修改食物状态）
 * @return bool true表示吃到限时食物，false表示未吃到
 * @details 检查蛇头坐标是否与限时食物坐标相同，吃到后清除限时食物并清空进度条
 */
bool Snake::GetBigFood(Food &cfood) {
  // 比较蛇头坐标与限时食物坐标
  if (snake.back().GetX() == cfood.big_x &&
      snake.back().GetY() == cfood.big_y) {
    // 吃到限时食物，清除限时食物状态
    cfood.big_flag = false; // 清除限时食物存在标志
    cfood.big_x = 0;        // 重置坐标
    cfood.big_y = 0;

    // 清除进度条显示
    SetCursorPosition(1, 0);
    std::cout
        << "                                                            "; // 用空格覆盖进度条

    return true; // 吃到限时食物
  } else
    return false; // 未吃到限时食物
}
