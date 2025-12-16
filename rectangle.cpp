#include "rectangle.hpp"

top::Rectangle::Rectangle(int x, int y, int height, int width):
IDraw(), start{x, y}, hei(height), wid(width)
{
  if (height <= 0 || width <= 0)
  {
    throw std::logic_error("Invalid len");
  }
}

top::p_t top::Rectangle::begin() const
{
  return start;
}

top::p_t top::Rectangle::next(p_t p) const
{
  if (p.y == start.y && p.x < start.x + wid)
  {
    return p_t{p.x + 1, p.y};
  }
  else if (p.x == start.x + wid && p.y < start.y + hei)
  {
    return p_t{p.x, p.y + 1};
  }
  else if (p.y == start.y + hei && p.x > start.x)
  {
    return p_t{p.x - 1, p.y};
  }
  else if (p.x == start.x && p.y > start.y)
  {
    return p_t{p.x, p.y - 1};
  }
  return start;
}
