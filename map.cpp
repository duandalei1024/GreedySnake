/**
 * @file map.cpp
 * @brief ��ͼ��ʵ���ļ�
 * @details ʵ������Ϸ��ͼ�Ļ��ƹ��ܣ�������ʾ��Ϸ����ı߽�
 */

#include "map.h"
#include <chrono>
#include <thread>

/**
 * @brief ������Ϸ��ͼ�߽�
 * @details
 * ������ͼ�߽�㼯�ϣ�������Ʊ߽緽�飬��ͨ��Sleep����Ӫ����֡��ʾ�Ķ���Ч��
 *          ��ͼ�߽���Map���캯�����ѳ�ʼ����x: 1-30, y: 1-30�ľ��ο�
 */
void Map::PrintInitmap() {
  // ������ͼ�߽�㼯�ϣ�������Ʊ߽�
  for (auto &point : initmap) {
    point.Print(); // �ڵ�ǰ��λ�û��Ʒ���"��"
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}
