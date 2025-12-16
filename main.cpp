#include <iostream>
#include <cstddef>
#include "ascii_draw.hpp"

int main()
{
  using namespace top;
  IDraw * f[8] = {};
  size_t s = 0;
  char * cnv = nullptr;
  p_t * p = nullptr;
  int err = 0;
  try
  {
    f[0] = new Dot(0, 0);
    f[1] = new Dot(2, 3);
    f[2] = new Dot(-5, -2);
    f[3] = new VLine(1, 1, 8);
    f[4] = new HLine(-4, 6, 7);
    f[5] = new DiagLine(-8, 2, 5);
    f[6] = new Square(3, -3, 5);
    f[7] = new Rectangle(3, -12, 5, 10);
    for (size_t i = 0; i < 8; ++i)
    {
      get_points(f[i], &p, s);
    }
    frame_t fr = build_frame(p, s);
    cnv = build_canvas(fr, '.');
    paint_canvas(cnv, fr, p, s, '#');
    print_canvas(cnv, fr);
  }
  catch (...)
  {
    std::cerr << "Error\n";
    err = 1;
  }
  delete f[0];
  delete f[1];
  delete f[2];
  delete f[3];
  delete f[4];
  delete f[5];
  delete f[6];
  delete[] p;
  delete[] cnv;
  return err;
}
