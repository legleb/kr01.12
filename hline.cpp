#include "hline.hpp"

top::HLine::HLine(int x, int y, int len):
IDraw(), start{x, y}, length(len)  
{
  if (len <= 0)
  {
    throw std::logic_error("Invalid len");
  }
}
    
top::p_t top::HLine::begin() const
{
  return start;
}  
    
top::p_t top::HLine::next(p_t p) const
{
  if (p.x == start.x + length)
  {
    return start;
  }
  return p_t{p.x + 1, start.y};
}
