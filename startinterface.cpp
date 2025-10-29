/**
 * @file startinterface.cpp
 * @brief 开始界面动画实现文件
 * @details 实现了游戏启动时的开始动画效果，包括蛇形动画和"SNAKE"文字动画
 */

#include "startinterface.h"
#include <windows.h>

/**
 * @brief 第一阶段动画：蛇从左边出现到完全显示
 * @details 逐个显示蛇身的每个点，营造蛇从左侧逐渐出现的动画效果
 */
void StartInterface::PrintFirst() {
  // 遍历开始动画中的蛇身点集合
  for (auto &point : startsnake) {
    point.Print(); // 绘制当前点（方块"■"）
    Sleep(speed);  // 延迟，控制动画速度
  }
}

/**
 * @brief 第二阶段动画：蛇从左向右移动
 * @details 蛇从左向右移动，同时保持波浪形的上下移动轨迹
 *          移动过程中不断更新头部位置并删除尾部，实现移动效果
 */
void StartInterface::PrintSecond() {
  // 蛇头需要从x坐标10移动到40
  for (int i = 10; i != 40; ++i) {
    /* 计算蛇头的下一个位置，并将其压入startsnake中，绘制出来，将蛇尾去掉
       使用数学公式使蛇的移动轨迹呈现波浪形：
       j的值在15-19之间波动，形成上下起伏的效果 */
        int j = (((i-2) % 8) < 4) ? (15 + (i-2) % 8) : (21 - (i-2) % 8);

        // 在蛇尾添加新点（模拟蛇头移动）
        startsnake.emplace_back(Point(i, j));
        startsnake.back().Print(); // 绘制新添加的点

        // 清除并删除蛇尾（实现移动效果）
        startsnake.front().Clear();
        startsnake.pop_front();

        Sleep(speed); // 延迟，控制动画速度
  }
}

/**
 * @brief 第三阶段动画：蛇消失同时文字"SNAKE"出现
 * @details 蛇逐渐消失的同时，文字"SNAKE"从左侧滑入屏幕
 *          两段动画同步进行，直到蛇完全消失且文字到达指定位置
 */
void StartInterface::PrintThird() {
  // 当蛇还没消失或文字没移动到指定位置时继续动画
  while (!startsnake.empty() || textsnake.back().GetX() < 33) {
    if (!startsnake.empty()) // 如果蛇还没消失，继续删除蛇头
    {
      startsnake.front().Clear();
      startsnake.pop_front();
    }

    ClearText();  // 清除已有文字显示
    PrintText();  // 绘制更新位置后的文字（向右移动一格）
    Sleep(speed); // 延迟，控制动画速度
  }
}

/**
 * @brief 绘制"SNAKE"文字
 * @details 遍历文字点集合，绘制所有x坐标>=0的点（用于实现从左侧滑入的效果）
 */
void StartInterface::PrintText() {
  // 遍历文字"SNAKE"的所有点
  for (auto &point : textsnake) {
    if (point.GetX() >= 0) // 只绘制已经进入屏幕范围内的点（x >= 0）
      point.Print();       // 绘制方块"■"
  }
}

/**
 * @brief 清除文字并向右移动一格
 * @details 清除当前文字显示，然后将所有文字点向右移动一个单位
 *          用于实现文字从左侧滑入的动画效果
 */
void StartInterface::ClearText() {
  // 遍历文字的所有点，清除并向右移动
  for (auto &point : textsnake) {
    if (point.GetX() >= 0) // 只清除在屏幕范围内的点
      point.Clear();       // 清除显示

    // 将点的x坐标加1，实现向右移动的效果
    point.ChangePosition(point.GetX() + 1, point.GetY());
  }
}

/**
 * @brief 执行完整的开始动画序列
 * @details 依次执行三个阶段：蛇出现、蛇移动、蛇消失+文字出现
 */
void StartInterface::Action() {
  PrintFirst();  // 第一阶段：蛇从左边出现
  PrintSecond(); // 第二阶段：蛇从左向右移动
  PrintThird();  // 第三阶段：蛇消失，文字"SNAKE"出现
}
