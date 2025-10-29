/**
 * @file food.cpp
 * @brief 食物类实现文件
 * @details 实现了游戏中的普通食物和限时食物的生成、绘制、闪烁等功能
 */

#include "food.h"
#include "tools.h"
#include <cstdlib>
#include <iostream>

/**
 * @brief 绘制普通食物
 * @param csnake 蛇对象的引用，用于检查食物是否与蛇身重叠
 * @details
 * 随机生成食物坐标，确保食物位置在地图内（2-29），不与蛇身和限时食物重叠
 *          每吃5颗普通食物后会触发限时食物的生成
 */
void Food::DrawFood(Snake &csnake) {
  /* 利用rand函数获得坐标，并将其范围限制在2-29内，即在地图内，
     如果获得的坐标与蛇身重叠，则重新获取。
     同时每5颗食物就出现一颗限时食物 */
  while (true) {
    // 生成随机坐标（0-29）
    int tmp_x = rand() % 30;
    int tmp_y = rand() % 30;

    // 确保坐标至少为2（地图内边界）
    if (tmp_x < 2)
      tmp_x += 2;
    if (tmp_y < 2)
      tmp_y += 2;

    bool flag = false; // 标记是否与蛇身或限时食物重叠

    // 检查生成的坐标是否与蛇身重叠，或与限时食物位置重叠
    for (auto &point : csnake.snake) {
      if ((point.GetX() == tmp_x && point.GetY() == tmp_y) ||
          (tmp_x == big_x && tmp_y == big_y)) {
        flag = true; // 发现重叠，标记为无效位置
        break;
      }
    }

    if (flag)
      continue; // 如果重叠，重新生成坐标

    // 找到有效位置，设置食物坐标
    x = tmp_x;
    y = tmp_y;

    // 在指定位置绘制食物（紫色五角星）
    SetCursorPosition(x, y);
    SetColor(13);     // 设置颜色为紫色
    std::cout << "★"; // 输出五角星字符

    // 食物计数器自增，每5个普通食物出现1个限时食物
    ++cnt;
    cnt %= 5;     // 取模运算，使cnt在0-4之间循环
    if (cnt == 0) // 计数达到5时触发限时食物
    {
      DrawBigFood(csnake);
    }
    break; // 成功生成并绘制食物，退出循环
  }
}

/**
 * @brief 绘制限时食物（大食物）
 * @param csnake 蛇对象的引用，用于检查食物是否与蛇身重叠
 * @details 生成限时食物的位置，绘制进度条，并确保不与蛇身和普通食物重叠
 *          限时食物有倒计时功能，过期会自动消失
 */
void Food::DrawBigFood(Snake &csnake) {
  // 绘制进度条（显示限时食物的剩余时间）
  SetCursorPosition(5, 0);
  SetColor(11); // 设置颜色为青蓝色
  std::cout
      << "------------------------------------------"; // 输出42个"-"作为进度条
  progress_bar = 42; // 初始化进度条长度为42（对应42个"-"字符）

  // 循环生成限时食物的位置，确保不与蛇身和普通食物重叠
  while (true) {
    // 生成随机坐标
    int tmp_x = rand() % 30;
    int tmp_y = rand() % 30;

    // 确保坐标至少为2（地图内边界）
    if (tmp_x < 2)
      tmp_x += 2;
    if (tmp_y < 2)
      tmp_y += 2;

    bool flag = false; // 标记是否与蛇身或普通食物重叠

    // 检查是否与蛇身或普通食物位置重叠
    for (auto &point : csnake.snake) {
      if ((point.GetX() == tmp_x && point.GetY() == tmp_y) ||
          (tmp_x == x && tmp_y == y)) {
        flag = true; // 发现重叠
        break;
      }
    }

    if (flag)
      continue; // 如果重叠，重新生成坐标

    // 找到有效位置，设置限时食物坐标
    big_x = tmp_x;
    big_y = tmp_y;

    // 在指定位置绘制限时食物（蓝色方块）
    SetCursorPosition(big_x, big_y);
    SetColor(18);     // 设置颜色（蓝色高亮）
    std::cout << "■"; // 输出方块字符

    big_flag = true;   // 设置限时食物存在标志
    flash_flag = true; // 设置闪烁标志（初始为显示状态）
    break;             // 成功生成并绘制，退出循环
  }
}

/**
 * @brief 获取食物计数器值
 * @return int 当前计数器的值（0-4之间）
 * @details 用于外部查询当前已生成的普通食物数量（相对于下一个限时食物的计数）
 */
int Food::GetCnt() { return cnt; }

/**
 * @brief 闪烁限时食物并更新进度条
 * @details 通过交替显示和隐藏限时食物实现闪烁效果，同时更新进度条显示剩余时间
 *          当进度条归零时，限时食物自动消失
 */
void Food::FlashBigFood() {
  // 闪烁限时食物：交替显示和隐藏
  SetCursorPosition(big_x, big_y);
  SetColor(18);
  if (flash_flag) // 如果当前是显示状态
  {
    std::cout << "  ";  // 清除显示（输出两个空格）
    flash_flag = false; // 切换为隐藏状态
  } else                // 如果当前是隐藏状态
  {
    std::cout << "■";  // 显示食物
    flash_flag = true; // 切换为显示状态
  }

  // 更新进度条：从当前位置向左删除一个"-"字符
  SetCursorPosition(26, 0);
  SetColor(11);
  // 从进度条末端到当前位置，逐个删除"-"字符
  for (int i = 42; i >= progress_bar; --i)
    std::cout << "\b \b"; // "\b"退格，" "空格，"\b"再退格，实现删除效果

  --progress_bar; // 进度条长度减1

  // 如果进度条归零，限时食物消失
  if (progress_bar == 0) {
    SetCursorPosition(big_x, big_y);
    std::cout << "  "; // 清除限时食物显示
    big_flag = false;  // 清除限时食物存在标志
    big_x = 0;         // 重置坐标
    big_y = 0;
  }
}

/**
 * @brief 获取限时食物是否存在标志
 * @return bool true表示限时食物存在，false表示不存在
 * @details 用于外部查询当前是否有限时食物存在
 */
bool Food::GetBigFlag() { return big_flag; }

/**
 * @brief 获取限时食物进度条当前值
 * @return int 进度条当前长度值（0-42）
 * @details 用于外部查询限时食物的剩余时间，可用于计算得分等
 */
int Food::GetProgressBar() { return progress_bar; }
