#include "geom.hpp"

bool top::operator==(top::p_t a, top::p_t b) {
  return a.x == b.x && a.y == b.y;
}

bool top::operator!=(top::p_t a, top::p_t b) {
  return !(a == b);
}

top::frame_t top::build_frame(const p_t * ps, size_t s)
{
  if (!s)
  {
    throw std::logic_error("bad size");
  }
  int minx = ps[0].x, maxx = ps[0].x;
  int miny = ps[0].y, maxy = ps[0].y;
  for (size_t i = 1; i < s; ++i)
  {
    minx = std::min(minx, ps[i].x);
    miny = std::min(miny, ps[i].y);
    maxx = std::max(maxx, ps[i].x);  
    maxy = std::max(maxy, ps[i].y);   
  }
  p_t aa{minx, miny};
  p_t bb{maxx, maxy};
  return {aa, bb};
}
 
size_t top::rows(frame_t f)
{  
  return (f.right_top.y - f.left_bot.y + 1);
}
      
size_t top::cols(frame_t f)
{
  return (f.right_top.x - f.left_bot.x + 1);
}
