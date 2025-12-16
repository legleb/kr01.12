#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "idraw.hpp"
#include <stdexcept>

namespace top
{
  struct Rectangle: IDraw
  {
    Rectangle(int x, int y, int height, int width);
    p_t begin() const override;
    p_t next(p_t p) const override;
  private:
    p_t start;   
    int hei, wid;
  };
}
#endif
