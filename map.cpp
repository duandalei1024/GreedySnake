/**
 * @file map.cpp
 * @brief ��ͼ��ʵ���ļ�
 * @details ʵ������Ϸ��ͼ�Ļ��ƹ��ܣ�������ʾ��Ϸ����ı߽�
 */

#include "map.h"
#include <windows.h>

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
    Sleep(10);     // �ӳ�10���룬Ӫ��߽���֡��ʾ�Ķ���Ч��
  }
}
