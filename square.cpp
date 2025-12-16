#include "square.hpp"

top::Square::Square(int x, int y, int len):
IDraw(), start{x, y}, length(len)
{
  if (len <= 0)
  {
    throw std::logic_error("Invalid len");
  }
}

top::p_t top::Square::begin() const
{
  return start;
}  
    
top::p_t top::Square::next(p_t p) const
{
  if (p.y == start.y && p.x < start.x + length)
  {
    return p_t{p.x + 1, p.y};
  }
  else if (p.x == start.x + length && p.y < start.y + length)
  {
    return p_t{p.x, p.y + 1};
  }
  else if (p.y == start.y + length && p.x > start.x)
  {
    return p_t{p.x - 1, p.y};
  }
  else if (p.x == start.x && p.y > start.y)
  {  
    return p_t{p.x, p.y - 1};
  }
  return start;
}
