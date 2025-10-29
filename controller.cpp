/**
 * @file controller.cpp
 * @brief 游戏控制器实现文件
 * @details 实现了游戏的整体流程控制，包括开始界面、难度选择、游戏主循环、
 *          暂停菜单、分数管理、游戏结束界面等核心功能
 */

#include "controller.h"
#include "food.h"
#include "map.h"
#include "snake.h"
#include "startinterface.h"
#include "tools.h"
#include <conio.h>
#include <iostream>
#include <time.h>
#include <windows.h>


/**
 * @brief 显示游戏开始界面
 * @details 设置窗口大小，播放开始动画，然后等待玩家按键开始游戏
 */
void Controller::Start() {
  SetWindowSize(41, 32); // 设置窗口大小为41列32行（逻辑单位）
  SetColor(2);           // 设置开始动画颜色为绿色
  StartInterface *start = new StartInterface(); // 动态分配开始界面对象
  start->Action(); // 执行开始动画（蛇形动画和"SNAKE"文字）
  delete start;    // 释放内存空间

  /* 设置光标位置，并输出提示语，等待任意键输入 */
  SetCursorPosition(13, 26);
  std::cout << "Press any key to start... ";
  SetCursorPosition(13, 27);
  system("pause"); // 暂停程序，等待用户按键
}

/**
 * @brief 显示难度选择界面
 * @details 显示四个难度选项，支持上下方向键选择，回车确认
 *          根据选择的难度设置蛇的移动速度（speed值越小，速度越快）
 */
void Controller::Select() {
  /* 初始化界面选项 */
  SetColor(3); // 设置文字颜色为青色
  // 清除之前的提示文字
  SetCursorPosition(13, 26);
  std::cout << "                          ";
  SetCursorPosition(13, 27);
  std::cout << "                          ";

  // 显示难度选择提示
  SetCursorPosition(6, 21);
  std::cout << "请选择游戏难度：";
  SetCursorPosition(6, 22);
  std::cout << "(上下键选择,回车确认)";

  // 第一个选项设置背景色以表示当前选中
  SetCursorPosition(27, 22);
  SetBackColor(); // 设置高亮背景
  std::cout << "简单模式";
  SetCursorPosition(27, 24);
  SetColor(3);
  std::cout << "普通模式";
  SetCursorPosition(27, 26);
  std::cout << "困难模式";
  SetCursorPosition(27, 28);
  std::cout << "炼狱模式";
  SetCursorPosition(0, 31);
  score = 0;

  /* 上下方向键选择模块 */
  int ch;            // 记录键入值
  key = 1;           // 记录选中项，初始选择第一个（简单模式）
  bool flag = false; // 记录是否键入Enter键标记，初始置为否

  while ((ch = getch())) // 循环检测键盘输入
  {
    switch (ch) // 检测输入键
    {
    case 72:       // UP上方向键
      if (key > 1) // 当此时选中项为第一项时，UP上方向键无效
      {
        switch (key) {
        case 2:
          SetCursorPosition(27, 22); // 给待选中项设置背景色
          SetBackColor();
          std::cout << "简单模式";

          SetCursorPosition(27, 24); // 将已选中项取消我背景色
          SetColor(3);
          std::cout << "普通模式";

          --key;
          break;
        case 3:
          SetCursorPosition(27, 24);
          SetBackColor();
          std::cout << "普通模式";

          SetCursorPosition(27, 26);
          SetColor(3);
          std::cout << "困难模式";

          --key;
          break;
        case 4:
          SetCursorPosition(27, 26);
          SetBackColor();
          std::cout << "困难模式";

          SetCursorPosition(27, 28);
          SetColor(3);
          std::cout << "炼狱模式";

          --key;
          break;
        }
      }
      break;

    case 80: // DOWN下方向键
      if (key < 4) {
        switch (key) {
        case 1:
          SetCursorPosition(27, 24);
          SetBackColor();
          std::cout << "普通模式";
          SetCursorPosition(27, 22);
          SetColor(3);
          std::cout << "简单模式";

          ++key;
          break;
        case 2:
          SetCursorPosition(27, 26);
          SetBackColor();
          std::cout << "困难模式";
          SetCursorPosition(27, 24);
          SetColor(3);
          std::cout << "普通模式";

          ++key;
          break;
        case 3:
          SetCursorPosition(27, 28);
          SetBackColor();
          std::cout << "炼狱模式";
          SetCursorPosition(27, 26);
          SetColor(3);
          std::cout << "困难模式";

          ++key;
          break;
        }
      }
      break;

    case 13:       // Enter回车键
      flag = true; // 标记已按下确认键
      break;
    default: // 无效按键
      break;
    }
    if (flag)
      break; // 输入Enter回车键确认，退出检查输入循环

    SetCursorPosition(0, 31); // 将光标置于左下角，避免光标闪烁影响游戏体验
  }

  // 根据所选选项设置蛇的移动速度，speed值越小，速度越快
  switch (key) {
  case 1:
    speed = 135;
    break;
  case 2:
    speed = 100;
    break;
  case 3:
    speed = 60;
    break;
  case 4:
    speed = 30;
    break;
  default:
    break;
  }
}

/**
 * @brief 绘制游戏主界面
 * @details 清屏后绘制地图边界和侧边栏信息（游戏标题、难度、得分、操作说明）
 */
void Controller::DrawGame() {
  system("cls"); // 清屏

  /* 绘制地图 */
  SetColor(3);               // 设置颜色为青色
  Map *init_map = new Map(); // 创建地图对象
  init_map->PrintInitmap();  // 绘制地图边界（动画效果）
  delete init_map;           // 释放内存

  /* 绘制侧边栏 */
  SetColor(3); // 设置颜色为青色
  SetCursorPosition(33, 1);
  std::cout << "Greedy Snake";
  SetCursorPosition(34, 2);
  std::cout << "贪吃蛇";
  SetCursorPosition(31, 4);
  std::cout << "难度：";
  SetCursorPosition(36, 5);
  switch (key) {
  case 1:
    std::cout << "简单模式";
    break;
  case 2:
    std::cout << "普通模式";
    break;
  case 3:
    std::cout << "困难模式";
    break;
  case 4:
    std::cout << "炼狱模式";
    break;
  default:
    break;
  }
  SetCursorPosition(31, 7);
  std::cout << "得分：";
  SetCursorPosition(37, 8);
  std::cout << "     0";
  SetCursorPosition(33, 13);
  std::cout << " 方向键移动";
  SetCursorPosition(33, 15);
  std::cout << " ESC键暂停";
}

/**
 * @brief 游戏主循环（二级循环）
 * @return int 返回值：1表示重新开始，2表示退出游戏
 * @details 初始化蛇和食物，进入游戏循环，处理用户输入、碰撞检测、食物生成等
 *          当游戏结束时返回相应状态码
 */
int Controller::PlayGame() {
  /* 初始化蛇和食物 */
  Snake *csnake = new Snake(); // 创建蛇对象
  Food *cfood = new Food();    // 创建食物对象
  SetColor(6);                 // 设置颜色为黄色
  csnake->InitSnake();         // 初始化并绘制蛇
  srand(
      (unsigned)time(NULL)); // 设置随机数种子，如果没有，食物的出现位置将会固定
  cfood->DrawFood(*csnake);  // 绘制第一个食物

  /* 游戏循环 */
  // 判断是否撞墙或撞到自身，即是否还有生命（两个条件都为true时继续游戏）
  while (csnake->OverEdge() && csnake->HitItself()) {
    /* 调出选择菜单 */
    if (!csnake->ChangeDirection()) // 按Esc键时返回false
    {
      int tmp = Menu(); // 绘制菜单，并得到返回值
      switch (tmp) {
      case 1: // 继续游戏
        break;

      case 2:          // 重新开始
        delete csnake; // 释放蛇对象内存
        delete cfood;  // 释放食物对象内存
        return 1; // 将1作为PlayGame函数的返回值返回到Game函数中，表示重新开始

      case 3: // 退出游戏
        delete csnake;
        delete cfood;
        return 2; // 将2作为PlayGame函数的返回值返回到Game函数中，表示退出游戏

      default:
        break;
      }
    }

    // 检测是否吃到普通食物
    if (csnake->GetFood(*cfood)) {
      csnake->Move();           // 蛇增长（长度+1）
      UpdateScore(1);           // 更新分数，1为分数权重
      RewriteScore();           // 重新绘制分数
      cfood->DrawFood(*csnake); // 绘制新食物
    } else                      // 未吃到食物
    {
      csnake->NormalMove(); // 蛇正常移动（长度不变）
    }

    // 检测是否吃到限时食物
    if (csnake->GetBigFood(*cfood)) {
      csnake->Move();                           // 蛇增长
      UpdateScore(cfood->GetProgressBar() / 5); // 分数根据限时食物进度条确定
      RewriteScore();
    }

    // 如果此时有限时食物，闪烁它并更新进度条
    if (cfood->GetBigFlag()) {
      cfood->FlashBigFood();
    }

    Sleep(speed); // 延迟，制造蛇的移动效果（speed值越小，速度越快）
  }

  /* 蛇死亡 */
  delete csnake; // 释放分配的内存空间
  delete cfood;
  int tmp = GameOver(); // 绘制游戏结束界面，并返回所选项
  switch (tmp) {
  case 1:
    return 1; // 重新开始
  case 2:
    return 2; // 退出游戏
  default:
    return 2;
  }
}

/**
 * @brief 更新游戏分数
 * @param tmp 分数权重系数
 * @details 分数计算公式：score += key * 10 * tmp
 *          其中key是难度系数（1-4），tmp是不同食物的权重
 */
void Controller::UpdateScore(const int &tmp) {
  score += key * 10 * tmp; // 所得分数根据游戏难度及传入的参数tmp确定
}

/**
 * @brief 重新绘制分数显示
 * @details
 * 为保持分数尾部对齐，计算当前分数位数，将剩余位数用空格补全，再输出分数
 */
void Controller::RewriteScore() {
  SetCursorPosition(37, 8); // 设置光标到分数显示位置
  SetColor(11);             // 设置颜色为亮青色
  int bit = 0;              // 分数位数计数器
  int tmp = score;
  while (tmp != 0) // 计算分数的位数
  {
    ++bit;
    tmp /= 10;
  }
  // 用空格补全到6位（保持对齐）
  for (int i = 0; i < (6 - bit); ++i) {
    std::cout << " ";
  }
  std::cout << score; // 输出分数
}

/**
 * @brief 显示暂停菜单
 * @return int 返回值：1表示继续游戏，2表示重新开始，3表示退出游戏
 * @details
 * 显示三个选项（继续游戏、重新开始、退出游戏），支持上下方向键选择和回车确认
 */
int Controller::Menu() {
  /* 绘制菜单 */
  SetColor(11);
  SetCursorPosition(32, 19);
  std::cout << "菜单：";
  Sleep(100);
  SetCursorPosition(34, 21);
  SetBackColor();
  std::cout << "继续游戏";
  Sleep(100);
  SetCursorPosition(34, 23);
  SetColor(11);
  std::cout << "重新开始";
  Sleep(100);
  SetCursorPosition(34, 25);
  std::cout << "退出游戏";
  SetCursorPosition(0, 31);

  /*选择部分*/
  int ch;
  int tmp_key = 1;
  bool flag = false;
  while ((ch = getch())) {
    switch (ch) {
    case 72: // UP
      if (tmp_key > 1) {
        switch (tmp_key) {
        case 2:
          SetCursorPosition(34, 21);
          SetBackColor();
          std::cout << "继续游戏";
          SetCursorPosition(34, 23);
          SetColor(11);
          std::cout << "重新开始";

          --tmp_key;
          break;
        case 3:
          SetCursorPosition(34, 23);
          SetBackColor();
          std::cout << "重新开始";
          SetCursorPosition(34, 25);
          SetColor(11);
          std::cout << "退出游戏";

          --tmp_key;
          break;
        }
      }
      break;

    case 80: // DOWN
      if (tmp_key < 3) {
        switch (tmp_key) {
        case 1:
          SetCursorPosition(34, 23);
          SetBackColor();
          std::cout << "重新开始";
          SetCursorPosition(34, 21);
          SetColor(11);
          std::cout << "继续游戏";

          ++tmp_key;
          break;
        case 2:
          SetCursorPosition(34, 25);
          SetBackColor();
          std::cout << "退出游戏";
          SetCursorPosition(34, 23);
          SetColor(11);
          std::cout << "重新开始";

          ++tmp_key;
          break;
        }
      }
      break;

    case 13: // Enter
      flag = true;
      break;

    default:
      break;
    }

    if (flag) {
      break;
    }
    SetCursorPosition(0, 31);
  }

  if (tmp_key == 1) // 选择继续游戏，则将菜单擦除
  {
    SetCursorPosition(32, 19);
    std::cout << "      ";
    SetCursorPosition(34, 21);
    std::cout << "        ";
    SetCursorPosition(34, 23);
    std::cout << "        ";
    SetCursorPosition(34, 25);
    std::cout << "        ";
  }
  return tmp_key;
}

/**
 * @brief 游戏一级循环（主循环）
 * @details 整合整个游戏流程：开始界面 → 难度选择 → 游戏运行 → 游戏结束
 *          支持重新开始游戏和退出游戏功能
 */
void Controller::Game() {
  Start();     // 显示开始界面（动画）
  while (true) // 游戏可视为一个死循环，直到退出游戏时循环结束
  {
    Select();   // 显示难度选择界面
    DrawGame(); // 绘制游戏界面（地图、侧边栏）
    int tmp =
        PlayGame(); // 开启游戏循环，当重新开始或退出游戏时，结束循环并返回值给tmp
    if (tmp == 1)   // 返回值为1时重新开始游戏
    {
      system("cls");     // 清屏
      continue;          // 继续下一次循环（重新选择难度）
    } else if (tmp == 2) // 返回值为2时退出游戏
    {
      break; // 退出循环，结束游戏
    } else {
      break; // 其他情况也退出（容错处理）
    }
  }
}

/**
 * @brief 显示游戏结束界面
 * @return int 返回值：1表示重新开始，2表示退出游戏
 * @details 显示游戏结束信息和最终得分，提供两个选项（重新开始/退出游戏）
 *          支持左右方向键选择和回车确认
 */
int Controller::GameOver() {
  /* 绘制游戏结束界面 */
  Sleep(500); // 延迟500毫秒，让玩家看清楚蛇死亡的瞬间
  SetColor(11);
  SetCursorPosition(10, 8);
  std::cout << "━━━━━━━━━━━━━━━━━━━━━━";
  Sleep(30);
  SetCursorPosition(9, 9);
  std::cout << " ┃               Game Over !!!              ┃";
  Sleep(30);
  SetCursorPosition(9, 10);
  std::cout << " ┃                                          ┃";
  Sleep(30);
  SetCursorPosition(9, 11);
  std::cout << " ┃              很遗憾！你挂了              ┃";
  Sleep(30);
  SetCursorPosition(9, 12);
  std::cout << " ┃                                          ┃";
  Sleep(30);
  SetCursorPosition(9, 13);
  std::cout << " ┃             你的分数为：                 ┃";
  SetCursorPosition(24, 13);
  std::cout << score;
  Sleep(30);
  SetCursorPosition(9, 14);
  std::cout << " ┃                                          ┃";
  Sleep(30);
  SetCursorPosition(9, 15);
  std::cout << " ┃   是否再来一局？                         ┃";
  Sleep(30);
  SetCursorPosition(9, 16);
  std::cout << " ┃                                          ┃";
  Sleep(30);
  SetCursorPosition(9, 17);
  std::cout << " ┃                                          ┃";
  Sleep(30);
  SetCursorPosition(9, 18);
  std::cout << " ┃    嗯，好的        不了，还是学习有意思  ┃";
  Sleep(30);
  SetCursorPosition(9, 19);
  std::cout << " ┃                                          ┃";
  Sleep(30);
  SetCursorPosition(9, 20);
  std::cout << " ┃                                          ┃";
  Sleep(30);
  SetCursorPosition(10, 21);
  std::cout << "━━━━━━━━━━━━━━━━━━━━━━";

  Sleep(100);
  SetCursorPosition(12, 18);
  SetBackColor();
  std::cout << "嗯，好的";
  SetCursorPosition(0, 31);

  /* 选择部分 */
  int ch;            // 记录键盘输入
  int tmp_key = 1;   // 当前选中的选项（1或2）
  bool flag = false; // 标记是否按下确认键
  while ((ch = getch())) {
    switch (ch) {
    case 75: // LEFT左方向键
      if (tmp_key > 1) {
        SetCursorPosition(12, 18);
        SetBackColor();
        std::cout << "嗯，好的";
        SetCursorPosition(20, 18);
        SetColor(11);
        std::cout << "不了，还是学习有意思";
        --tmp_key;
      }
      break;

    case 77: // RIGHT右方向键
      if (tmp_key < 2) {
        SetCursorPosition(20, 18);
        SetBackColor();
        std::cout << "不了，还是学习有意思";
        SetCursorPosition(12, 18);
        SetColor(11);
        std::cout << "嗯，好的";
        ++tmp_key;
      }
      break;

    case 13: // Enter回车键
      flag = true;
      break;

    default:
      break;
    }

    SetCursorPosition(0, 31); // 将光标置于左下角
    if (flag) {
      break; // 按下确认键，退出选择循环
    }
  }

  SetColor(11); // 恢复颜色
  switch (tmp_key) {
  case 1:
    return 1; // 重新开始
  case 2:
    return 2; // 退出游戏
  default:
    return 1; // 默认重新开始
  }
}
