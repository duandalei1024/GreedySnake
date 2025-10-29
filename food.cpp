/**
 * @file food.cpp
 * @brief ʳ����ʵ���ļ�
 * @details ʵ������Ϸ�е���ͨʳ�����ʱʳ������ɡ����ơ���˸�ȹ���
 */

#include "food.h"
#include "tools.h"
#include <cstdlib>
#include <iostream>

/**
 * @brief ������ͨʳ��
 * @param csnake �߶�������ã����ڼ��ʳ���Ƿ��������ص�
 * @details
 * �������ʳ�����꣬ȷ��ʳ��λ���ڵ�ͼ�ڣ�2-29���������������ʱʳ���ص�
 *          ÿ��5����ͨʳ���ᴥ����ʱʳ�������
 */
void Food::DrawFood(Snake &csnake) {
  /* ����rand����������꣬�����䷶Χ������2-29�ڣ����ڵ�ͼ�ڣ�
     �����õ������������ص��������»�ȡ��
     ͬʱÿ5��ʳ��ͳ���һ����ʱʳ�� */
  while (true) {
    // ����������꣨0-29��
    int tmp_x = rand() % 30;
    int tmp_y = rand() % 30;

    // ȷ����������Ϊ2����ͼ�ڱ߽磩
    if (tmp_x < 2)
      tmp_x += 2;
    if (tmp_y < 2)
      tmp_y += 2;

    bool flag = false; // ����Ƿ����������ʱʳ���ص�

    // ������ɵ������Ƿ��������ص���������ʱʳ��λ���ص�
    for (auto &point : csnake.snake) {
      if ((point.GetX() == tmp_x && point.GetY() == tmp_y) ||
          (tmp_x == big_x && tmp_y == big_y)) {
        flag = true; // �����ص������Ϊ��Чλ��
        break;
      }
    }

    if (flag)
      continue; // ����ص���������������

    // �ҵ���Чλ�ã�����ʳ������
    x = tmp_x;
    y = tmp_y;

    // ��ָ��λ�û���ʳ���ɫ����ǣ�
    SetCursorPosition(x, y);
    SetColor(13);     // ������ɫΪ��ɫ
    std::cout << "��"; // ���������ַ�

    // ʳ�������������ÿ5����ͨʳ�����1����ʱʳ��
    ++cnt;
    cnt %= 5;     // ȡģ���㣬ʹcnt��0-4֮��ѭ��
    if (cnt == 0) // �����ﵽ5ʱ������ʱʳ��
    {
      DrawBigFood(csnake);
    }
    break; // �ɹ����ɲ�����ʳ��˳�ѭ��
  }
}

/**
 * @brief ������ʱʳ���ʳ�
 * @param csnake �߶�������ã����ڼ��ʳ���Ƿ��������ص�
 * @details ������ʱʳ���λ�ã����ƽ���������ȷ�������������ͨʳ���ص�
 *          ��ʱʳ���е���ʱ���ܣ����ڻ��Զ���ʧ
 */
void Food::DrawBigFood(Snake &csnake) {
  // ���ƽ���������ʾ��ʱʳ���ʣ��ʱ�䣩
  SetCursorPosition(5, 0);
  SetColor(11); // ������ɫΪ����ɫ
  std::cout
      << "------------------------------------------"; // ���42��"-"��Ϊ������
  progress_bar = 42; // ��ʼ������������Ϊ42����Ӧ42��"-"�ַ���

  // ѭ��������ʱʳ���λ�ã�ȷ�������������ͨʳ���ص�
  while (true) {
    // �����������
    int tmp_x = rand() % 30;
    int tmp_y = rand() % 30;

    // ȷ����������Ϊ2����ͼ�ڱ߽磩
    if (tmp_x < 2)
      tmp_x += 2;
    if (tmp_y < 2)
      tmp_y += 2;

    bool flag = false; // ����Ƿ����������ͨʳ���ص�

    // ����Ƿ����������ͨʳ��λ���ص�
    for (auto &point : csnake.snake) {
      if ((point.GetX() == tmp_x && point.GetY() == tmp_y) ||
          (tmp_x == x && tmp_y == y)) {
        flag = true; // �����ص�
        break;
      }
    }

    if (flag)
      continue; // ����ص���������������

    // �ҵ���Чλ�ã�������ʱʳ������
    big_x = tmp_x;
    big_y = tmp_y;

    // ��ָ��λ�û�����ʱʳ���ɫ���飩
    SetCursorPosition(big_x, big_y);
    SetColor(18);     // ������ɫ����ɫ������
    std::cout << "��"; // ��������ַ�

    big_flag = true;   // ������ʱʳ����ڱ�־
    flash_flag = true; // ������˸��־����ʼΪ��ʾ״̬��
    break;             // �ɹ����ɲ����ƣ��˳�ѭ��
  }
}

/**
 * @brief ��ȡʳ�������ֵ
 * @return int ��ǰ��������ֵ��0-4֮�䣩
 * @details �����ⲿ��ѯ��ǰ�����ɵ���ͨʳ���������������һ����ʱʳ��ļ�����
 */
int Food::GetCnt() { return cnt; }

/**
 * @brief ��˸��ʱʳ�ﲢ���½�����
 * @details ͨ��������ʾ��������ʱʳ��ʵ����˸Ч����ͬʱ���½�������ʾʣ��ʱ��
 *          ������������ʱ����ʱʳ���Զ���ʧ
 */
void Food::FlashBigFood() {
  // ��˸��ʱʳ�������ʾ������
  SetCursorPosition(big_x, big_y);
  SetColor(18);
  if (flash_flag) // �����ǰ����ʾ״̬
  {
    std::cout << "  ";  // �����ʾ����������ո�
    flash_flag = false; // �л�Ϊ����״̬
  } else                // �����ǰ������״̬
  {
    std::cout << "��";  // ��ʾʳ��
    flash_flag = true; // �л�Ϊ��ʾ״̬
  }

  // ���½��������ӵ�ǰλ������ɾ��һ��"-"�ַ�
  SetCursorPosition(26, 0);
  SetColor(11);
  // �ӽ�����ĩ�˵���ǰλ�ã����ɾ��"-"�ַ�
  for (int i = 42; i >= progress_bar; --i)
    std::cout << "\b \b"; // "\b"�˸�" "�ո�"\b"���˸�ʵ��ɾ��Ч��

  --progress_bar; // ���������ȼ�1

  // ������������㣬��ʱʳ����ʧ
  if (progress_bar == 0) {
    SetCursorPosition(big_x, big_y);
    std::cout << "  "; // �����ʱʳ����ʾ
    big_flag = false;  // �����ʱʳ����ڱ�־
    big_x = 0;         // ��������
    big_y = 0;
  }
}

/**
 * @brief ��ȡ��ʱʳ���Ƿ���ڱ�־
 * @return bool true��ʾ��ʱʳ����ڣ�false��ʾ������
 * @details �����ⲿ��ѯ��ǰ�Ƿ�����ʱʳ�����
 */
bool Food::GetBigFlag() { return big_flag; }

/**
 * @brief ��ȡ��ʱʳ���������ǰֵ
 * @return int ��������ǰ����ֵ��0-42��
 * @details �����ⲿ��ѯ��ʱʳ���ʣ��ʱ�䣬�����ڼ���÷ֵ�
 */
int Food::GetProgressBar() { return progress_bar; }
