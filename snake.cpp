/**
 * @file snake.cpp
 * @brief ����ʵ���ļ�
 * @details ʵ�����ߵĳ�ʼ�����ƶ�����ײ��⡢������ƵȺ�����Ϸ�߼�
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
 * @brief ��ʼ����������
 * @details ��������㼯�ϣ��ڿ���̨����������������ɫԲ�Σ�
 */
void Snake::InitSnake() {
  // ������������е㣬�������
  for (auto &point : snake) {
    point.PrintCircular(); // ����Բ���ַ�"��"��ʾ����
  }
}

/**
 * @brief ���������Ե�ʳ�����ã�
 * @details
 * ���ݵ�ǰ�ƶ��������ߵ�β����deque��back�����һ���µĵ㣬ʹ��������
 *          ����ӵĵ����ݷ�������ͷ�����һ��Ԫ�أ��Ļ������ƶ�һ��
 */
void Snake::Move() {
  switch (direction) // ���ݵ�ǰ�ƶ���������µ�
  {
  case Direction::UP: // �����ƶ�
    // ����ͷ�Ϸ�����µ㣨Y�����1��
    snake.emplace_back(Point(snake.back().GetX(), snake.back().GetY() - 1));
    break;
  case Direction::DOWN: // �����ƶ�
    // ����ͷ�·�����µ㣨Y�����1��
    snake.emplace_back(Point(snake.back().GetX(), snake.back().GetY() + 1));
    break;
  case Direction::LEFT: // �����ƶ�
    // ����ͷ�������µ㣨X�����1��
    snake.emplace_back(Point(snake.back().GetX() - 1, snake.back().GetY()));
    break;
  case Direction::RIGHT: // �����ƶ�
    // ����ͷ�Ҳ�����µ㣨X�����1��
    snake.emplace_back(Point(snake.back().GetX() + 1, snake.back().GetY()));
    break;
  default:
    break;
  }

  // ��������ӵ���ͷ���֣���ɫ��
  SetColor(14);                 // ������ɫΪ��ɫ
  snake.back().PrintCircular(); // �����ߵ���ͷ��
}

/**
 * @brief �������ƶ���δ�Ե�ʳ��ʱ���ã�
 * @details ��ͷ�����һ���µ㣨���ݷ��򣩣�ͬʱ�����ɾ��β����ʵ���ƶ�Ч��
 *          �����ߵĻ����ƶ���ʽ�������ߵĳ��Ȳ���
 */
void Snake::NormalMove() {
  Move();                // ��ͷ������µ㣨���ƶ�����������
  snake.front().Clear(); // ���β����ʾ
  snake.pop_front();     // ɾ��β���㣬�����ߵĳ��Ȳ���
}

/**
 * @brief ������Ƿ񳬳��߽磨ײǽ��
 * @return bool true��ʾδ�����߽磨��ȫ����false��ʾ�����߽磨��Ϸ������
 * @details �����ͷ��snake.back()���������Ƿ��ڵ�ͼ�߽��ڣ�2-29֮�䣩
 */
bool Snake::OverEdge() const {
  // �����ͷ�����Ƿ�����Ч��Χ�ڣ�2 <= x < 30, 2 <= y < 30��
  // ע�⣺�߽�������1-30������Ч��Ϸ������2-29
  return snake.back().GetX() < 30 && snake.back().GetY() < 30 &&
         snake.back().GetX() > 1 && snake.back().GetY() > 1;
}

/**
 * @brief ������Ƿ�ײ������
 * @return bool true��ʾδײ��������ȫ����false��ʾײ��������Ϸ������
 * @details ͨ���������������ͷ�Ƿ����������岿���ص�
 *          �����ͷλ���������г��ֵĴ�������1�Σ������������岿���ص�������ײ������
 */
bool Snake::HitItself() const {
  const int headX = snake.back().GetX();
  const int headY = snake.back().GetY();
  // ��ͷ��β������������һ����ͷ��ͬ��λ�ü���Ϊײ������
  std::deque<Point>::size_type cnt = 1; // ����������ʼΪ1����ͷ����
  for (const auto &point : snake) {
    if (!(point.GetX() == headX && point.GetY() == headY))
      ++cnt;
    else
      break;
  }
  return cnt == snake.size();
}

/**
 * @brief ����������벢�ı��ߵ��ƶ�����
 * @return bool true��ʾ������Ϸ��false��ʾ��ESC��ͣ���˳���Ϸѭ����
 * @details ��ⷽ������벢�����ߵ��ƶ����򣬽�ֹ���෴�����ƶ�
 *          ��ESC��ʱ����false��������ͣ�˵�
 */
bool Snake::ChangeDirection() {
  char ch;

  if (kbhit()) // ����Ƿ��м������루��������
  {
    ch = getch(); // ��ȡ�����ַ�

    switch (ch) {
    case -32:       // �������ǰ׺�루-32��ʾ���µ��Ƿ������
      ch = getch(); // �ٴλ�ȡ���õ�ʵ�ʵķ����ֵ
      switch (ch) {
      case KEY_UP: // �Ϸ������UP��
        // �����ǰ���������£������������ƶ�����ֹ180��ת��
        if (direction != Direction::DOWN)
          direction = Direction::UP;
        break;
      case KEY_DOWN: // �·������DOWN��
        if (direction != Direction::UP)
          direction = Direction::DOWN;
        break;
      case KEY_LEFT: // �������LEFT��
        if (direction != Direction::RIGHT)
          direction = Direction::LEFT;
        break;
      case KEY_RIGHT: // �ҷ������RIGHT��
        if (direction != Direction::LEFT)
          direction = Direction::RIGHT;
        break;
      default:
        break;
      }
      return true; // ����ı�ɹ���������Ϸ

    case KEY_ESC:        // ESC��
      return false; // ����false��������ͣ�˵�

    default:       // ��������
      return true; // ��������������������Ϸ
    }
  }
  return true; // �ް������룬������Ϸ
}

/**
 * @brief ������Ƿ�Ե���ͨʳ��
 * @param cfood ʳ�����ĳ�����
 * @return bool true��ʾ�Ե�ʳ�false��ʾδ�Ե�
 * @details �����ͷ�����Ƿ�����ͨʳ��������ͬ
 */
bool Snake::GetFood(const Food &cfood) const {
  // �Ƚ���ͷ������ʳ������
  if (snake.back().GetX() == cfood.x && snake.back().GetY() == cfood.y)
    return true; // �Ե�ʳ��
  else
    return false; // δ�Ե�ʳ��
}

/**
 * @brief ������Ƿ�Ե���ʱʳ��
 * @param cfood ʳ���������ã���Ҫ�޸�ʳ��״̬��
 * @return bool true��ʾ�Ե���ʱʳ�false��ʾδ�Ե�
 * @details �����ͷ�����Ƿ�����ʱʳ��������ͬ���Ե��������ʱʳ�ﲢ��ս�����
 */
bool Snake::GetBigFood(Food &cfood) {
  // �Ƚ���ͷ��������ʱʳ������
  if (snake.back().GetX() == cfood.big_x &&
      snake.back().GetY() == cfood.big_y) {
    // �Ե���ʱʳ������ʱʳ��״̬
    cfood.big_flag = false; // �����ʱʳ����ڱ�־
    cfood.big_x = 0;        // ��������
    cfood.big_y = 0;

    // �����������ʾ
    SetCursorPosition(1, 0);
    std::cout
        << "                                                            "; // �ÿո񸲸ǽ�����

    return true; // �Ե���ʱʳ��
  } else
    return false; // δ�Ե���ʱʳ��
}
