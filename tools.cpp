/**
 * @file tools.cpp
 * @brief Windows����̨���ߺ���ʵ���ļ�
 * @details ��װ��Windows
 * API�г��õĿ���̨�����������������ڴ�С���á���궨λ����ɫ���Ƶ�
 */

#include "tools.h"
#include <stdio.h>
#include <windows.h>


/**
 * @brief ���ÿ���̨���ڴ�С�ͱ���
 * @param cols �����������߼���λ��һ��ͼ���ַ�ռ2�������ַ���ȣ�
 * @param lines ��������
 * @details ͨ��system�������Windows��mode���������ÿ���̨���ڴ�С
 *          ע�⣺����ͼ���ַ�"��"��"��"��ռ2���ַ���ȣ�����ʵ��������Ҫ����2
 */
void SetWindowSize(int cols, int lines) {
  system("title ̰����"); // ���ÿ���̨���ڱ���Ϊ"̰����"

  char cmd[30]; // ���ڴ洢ϵͳ������ַ�����
  // ����mode�����ַ��������ô�������������
  // ע�⣺cols��Ҫ����2����Ϊÿ��ͼ���ַ�ռ2���ַ����
  sprintf(cmd, "mode con cols=%d lines=%d", cols * 2, lines);
  system(cmd); // ִ���������ô��ڴ�С
}

/**
 * @brief ���ÿ���̨���λ��
 * @param x Ŀ��λ�õ�x���꣨�߼����꣩
 * @param y Ŀ��λ�õ�y���꣨�߼����꣩
 * @details ʹ��Windows
 * API���ÿ���̨���λ�ã�����ͼ���ַ�ռ2���ַ���ȣ�x������Ҫ����2
 */
void SetCursorPosition(const int x, const int y) {
  COORD position;     // Windows API�е�����ṹ��
  position.X = x * 2; // ����x���꣨����2��Ϊͼ���ַ�ռ2���ַ���ȣ�
  position.Y = y;     // ����y���꣨�кŲ���Ҫ������

  // ����Windows API���ÿ���̨���λ��
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

/**
 * @brief ���ÿ���̨�ı���ɫ
 * @param colorID ��ɫIDֵ��Windows����̨��ɫ�룩
 * @details ʹ��Windows API���ú���������ı���ɫ
 *          ������ɫֵ��0-�ڣ�1-����2-�̣�3-�࣬4-�죬5-�ϣ�6-�ƣ�7-�׵�
 */
void SetColor(int colorID) {
  // ����Windows API���ÿ���̨�ı����ԣ���ɫ��
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
}

/**
 * @brief �����ı�����������ɫ
 * @details
 * �����ı�Ϊ��ɫǰ������ɫ������RGBȫΪ1�����γɸ���Ч�������ڲ˵�ѡ��ѡ��״̬
 */
void SetBackColor() {
  // ���ÿ���̨�ı����ԣ�
  // FOREGROUND_BLUE - ��ɫǰ��
  // BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED - ��ɫ������RGBȫΪ1��
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                          FOREGROUND_BLUE |      // ��ɫǰ��
                              BACKGROUND_BLUE |  // ��ɫ��������
                              BACKGROUND_GREEN | // ��ɫ��������
                              BACKGROUND_RED); // ��ɫ������������ϳɰ�ɫ������
}
