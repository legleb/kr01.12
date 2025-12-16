#ifndef DIAGLINE_HPP
#define DIAGLINE_HPP
#include "idraw.hpp"
#include <stdexcept>

namespace top
{
  struct DiagLine: IDraw
  {
    DiagLine(int x, int y, int len);
    p_t begin() const override;
    p_t next(p_t p) const override;
  private:
    p_t start;
    int length;
  };
}
#endif
