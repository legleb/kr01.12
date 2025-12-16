#include "vline.hpp"

top::VLine::VLine(int x, int y, int len):
IDraw(), start{x,y}, length(len)
{
  if (len <= 0)
  {
    throw std::logic_error("Invalid len");
  }
}

top::p_t top::VLine::begin() const
{
  return start;
}

top::p_t top::VLine::next(p_t p) const
{
  if (p.y == start.y + length)
  {
    return start;
  }
  return p_t{start.x, p.y + 1};
}
