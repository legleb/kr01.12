#include "idraw.hpp"

namespace
{
  void extend(top::p_t ** pts, size_t s, top::p_t p)
  {
    top::p_t * res = new top::p_t[s + 1];
    for (size_t i = 0; i < s; ++i)
    {
      res[i] = (*pts)[i];
    }
    res[s] = p;
    delete[] *pts;
    *pts = res;
  }
}
   
void top::get_points(IDraw * d, p_t ** ps, size_t & s)
{
  p_t p = d->begin();
  extend(ps, s, p);
  size_t delta = 1;
  while (d->next(p) != d->begin())
  {
    p = d->next(p);
    extend(ps, s + delta, p);
    ++delta;
  }
  s += delta;
}
