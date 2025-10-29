/**
 * @file main.cpp
 * @brief 贪吃蛇游戏程序入口文件
 * @details 本文件包含程序的main函数，负责启动游戏控制器并进入游戏主循环
 */

#include "controller.h"

/**
 * @brief 程序主入口函数
 * @details 创建游戏控制器对象并启动游戏主循环
 * @return int 程序退出状态码，0表示正常退出
 */
int main() {
  Controller c; // 创建游戏控制器对象，负责整个游戏的流程控制
  c.Game();     // 启动游戏主循环，包括开始界面、难度选择、游戏运行等
  return 0;     // 程序正常退出
}
