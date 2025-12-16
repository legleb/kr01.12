#ifndef GEOM_HPP
#define GEOM_HPP
#include <cstddef>
#include <algorithm>
namespace top
{
  struct p_t
  {
    int x, y;
  };

  bool operator==(p_t a, p_t b);

  bool operator!=(p_t a, p_t b);

  struct frame_t
  {
    p_t left_bot, right_top;
  };

  frame_t build_frame(const p_t * ps, size_t s);

  size_t rows(frame_t f);
  
  size_t cols(frame_t f);
}
#endif
