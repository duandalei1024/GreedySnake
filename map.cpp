/**
 * @file map.cpp
 * @brief 地图类实现文件
 * @details 实现了游戏地图的绘制功能，用于显示游戏区域的边界
 */

#include "map.h"
#include <chrono>
#include <thread>

/**
 * @brief 绘制游戏地图边界
 * @details
 * 遍历地图边界点集合，逐个绘制边界方块，并通过Sleep函数营造逐帧显示的动画效果
 *          地图边界在Map构造函数中已初始化（x: 1-30, y: 1-30的矩形框）
 */
void Map::PrintInitmap() {
  // 遍历地图边界点集合，逐个绘制边界
  for (auto &point : initmap) {
    point.Print(); // 在当前点位置绘制方块"■"
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}
