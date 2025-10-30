#ifndef POINT_H
#define POINT_H

class Point {
public:
  Point() {}
  Point(const int x, const int y) : x(x), y(y) {}
  void Print() const;
  void PrintCircular() const;
  void Clear() const;
  void ChangePosition(const int x, const int y);
  bool operator==(const Point &point) const {
    return (point.x == this->x) && (point.y == this->y);
  }
  int GetX() const { return this->x; }
  int GetY() const { return this->y; }

private:
  int x, y;
};
#endif // POINT_H
