#ifndef SQUARE_HPP
#define SQUARE_HPP
#include "idraw.hpp"
#include <stdexcept>

namespace top
{
  struct Square: IDraw
  {
    Square(int x, int y, int len);
    p_t begin() const override;
    p_t next(p_t p) const override;
  private:
    p_t start;
    int length;
  };
}
#endif
