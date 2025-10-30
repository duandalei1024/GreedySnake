#ifndef TOOLS_H
#define TOOLS_H

// 这些函数本质上是对Windows API的封装
void SetWindowSize(int cols, int lines);
void SetCursorPosition(const int x, const int y);
void SetColor(int colorID);
void SetBackColor();
void ClearScreen();

#endif // TOOLS_H
