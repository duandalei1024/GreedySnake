/**
 * @file point.cpp
 * @brief 坐标点类实现文件
 * @details 实现了Point类的所有方法，用于在控制台指定位置绘制图形或清除内容
 */

#include "point.h"
#include "tools.h"
#include <iostream>

/**
 * @brief 在当前位置绘制方块图形
 * @details 使用图形字符"■"在控制台指定坐标位置绘制方块，用于地图边界等静态元素
 */
void Point::Print() const {
  SetCursorPosition(x, y); // 设置光标到指定坐标位置
  std::cout << "■";        // 输出方块字符（占2个字符宽度）
}

/**
 * @brief 在当前位置绘制圆形图形
 * @details 使用图形字符"●"在控制台指定坐标位置绘制圆形，主要用于蛇身的绘制
 */
void Point::PrintCircular() const {
  SetCursorPosition(x, y); // 设置光标到指定坐标位置
  std::cout << "●";        // 输出圆形字符（占2个字符宽度）
}

/**
 * @brief 清除当前位置的输出内容
 * @details 通过输出两个空格来清除指定位置的显示内容，用于蛇移动时的尾部清除
 */
void Point::Clear() const {
  SetCursorPosition(x, y); // 设置光标到指定坐标位置
  std::cout << "  ";       // 输出两个空格清除显示（因为图形字符占2个字符宽度）
}

/**
 * @brief 更改坐标点的位置
 * @param x 新的x坐标值
 * @param y 新的y坐标值
 * @details 更新当前点的坐标值，用于动画效果中的位置移动
 */
void Point::ChangePosition(const int x, const int y) {
  this->x = x; // 更新x坐标
  this->y = y; // 更新y坐标
}
