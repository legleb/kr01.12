#include "diagline.hpp"

top::DiagLine::DiagLine(int x, int y, int len):
IDraw(), start{x, y}, length(len)
{
  if (len <= 0)
  {
    throw std::logic_error("Invalid len");
  }
}

top::p_t top::DiagLine::begin() const
{
  return start;
}

top::p_t top::DiagLine::next(p_t p) const
{
  if (p.x == start.x + length && p.y == start.y + length)
  {
    return start;
  }
  return p_t{p.x + 1, p.y + 1};
}
