/**
 * @file startinterface.cpp
 * @brief ��ʼ���涯��ʵ���ļ�
 * @details ʵ������Ϸ����ʱ�Ŀ�ʼ����Ч�����������ζ�����"SNAKE"���ֶ���
 */

#include "startinterface.h"
#include <windows.h>

/**
 * @brief ��һ�׶ζ������ߴ���߳��ֵ���ȫ��ʾ
 * @details �����ʾ�����ÿ���㣬Ӫ���ߴ�����𽥳��ֵĶ���Ч��
 */
void StartInterface::PrintFirst() {
  // ������ʼ�����е�����㼯��
  for (auto &point : startsnake) {
    point.Print(); // ���Ƶ�ǰ�㣨����"��"��
    Sleep(speed);  // �ӳ٣����ƶ����ٶ�
  }
}

/**
 * @brief �ڶ��׶ζ������ߴ��������ƶ�
 * @details �ߴ��������ƶ���ͬʱ���ֲ����ε������ƶ��켣
 *          �ƶ������в��ϸ���ͷ��λ�ò�ɾ��β����ʵ���ƶ�Ч��
 */
void StartInterface::PrintSecond() {
  // ��ͷ��Ҫ��x����10�ƶ���40
  for (int i = 10; i != 40; ++i) {
    /* ������ͷ����һ��λ�ã�������ѹ��startsnake�У����Ƴ���������βȥ��
       ʹ����ѧ��ʽʹ�ߵ��ƶ��켣���ֲ����Σ�
       j��ֵ��15-19֮�䲨�����γ����������Ч�� */
        int j = (((i-2) % 8) < 4) ? (15 + (i-2) % 8) : (21 - (i-2) % 8);

        // ����β����µ㣨ģ����ͷ�ƶ���
        startsnake.emplace_back(Point(i, j));
        startsnake.back().Print(); // ��������ӵĵ�

        // �����ɾ����β��ʵ���ƶ�Ч����
        startsnake.front().Clear();
        startsnake.pop_front();

        Sleep(speed); // �ӳ٣����ƶ����ٶ�
  }
}

/**
 * @brief �����׶ζ���������ʧͬʱ����"SNAKE"����
 * @details ������ʧ��ͬʱ������"SNAKE"����໬����Ļ
 *          ���ζ���ͬ�����У�ֱ������ȫ��ʧ�����ֵ���ָ��λ��
 */
void StartInterface::PrintThird() {
  // ���߻�û��ʧ������û�ƶ���ָ��λ��ʱ��������
  while (!startsnake.empty() || textsnake.back().GetX() < 33) {
    if (!startsnake.empty()) // ����߻�û��ʧ������ɾ����ͷ
    {
      startsnake.front().Clear();
      startsnake.pop_front();
    }

    ClearText();  // �������������ʾ
    PrintText();  // ���Ƹ���λ�ú�����֣������ƶ�һ��
    Sleep(speed); // �ӳ٣����ƶ����ٶ�
  }
}

/**
 * @brief ����"SNAKE"����
 * @details �������ֵ㼯�ϣ���������x����>=0�ĵ㣨����ʵ�ִ���໬���Ч����
 */
void StartInterface::PrintText() {
  // ��������"SNAKE"�����е�
  for (auto &point : textsnake) {
    if (point.GetX() >= 0) // ֻ�����Ѿ�������Ļ��Χ�ڵĵ㣨x >= 0��
      point.Print();       // ���Ʒ���"��"
  }
}

/**
 * @brief ������ֲ������ƶ�һ��
 * @details �����ǰ������ʾ��Ȼ���������ֵ������ƶ�һ����λ
 *          ����ʵ�����ִ���໬��Ķ���Ч��
 */
void StartInterface::ClearText() {
  // �������ֵ����е㣬����������ƶ�
  for (auto &point : textsnake) {
    if (point.GetX() >= 0) // ֻ�������Ļ��Χ�ڵĵ�
      point.Clear();       // �����ʾ

    // �����x�����1��ʵ�������ƶ���Ч��
    point.ChangePosition(point.GetX() + 1, point.GetY());
  }
}

/**
 * @brief ִ�������Ŀ�ʼ��������
 * @details ����ִ�������׶Σ��߳��֡����ƶ�������ʧ+���ֳ���
 */
void StartInterface::Action() {
  PrintFirst();  // ��һ�׶Σ��ߴ���߳���
  PrintSecond(); // �ڶ��׶Σ��ߴ��������ƶ�
  PrintThird();  // �����׶Σ�����ʧ������"SNAKE"����
}
