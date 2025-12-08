#include <iostream>
#include <cstddef>

namespace top
{
  struct p_t
  {
    int x, y;
  };

  struct IDraw
  {
    virtual p_t begin() const = 0;
    virtual p_t next(p_t p) const = 0;
    virtual ~IDraw() = default;
  };

  bool operator==(p_t a, p_t b)
  {
    return a.x == b.x && a.y == b.y;
  }

  bool operator!=(p_t a, p_t b)
  {
    return !(a == b);
  }

  struct Dot: IDraw
  {
    virtual p_t begin() const override;
    virtual p_t next(p_t p) const override;
    p_t o;
    explicit Dot(int x, int y);
    ~Dot() override = default;
  };

  struct frame_t
  {
    p_t left_bot;
    p_t right_top;
  };

  void extend(p_t ** pts, size_t s, p_t p);

  void get_points(IDraw * b, p_t ** ps, size_t & s);

  size_t rows(frame_t f);

  size_t cols(frame_t f);

  frame_t build_frame(const p_t * ps, size_t s);

  char * build_canvas(frame_t f, char fill);

  void paint_canvas(char * cnv, frame_t fr, const p_t * ps, size_t k, char f);

  void print_canvas(const char * cnv, frame_t fr);

  struct VLine : IDraw
  {
    VLine(int x, int y, int len);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int length;
  };

  struct HLine : IDraw
  {
    HLine(int x, int y, int len);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int length;
  };

  struct Square : IDraw
  {
    Square(int x, int y, int len);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int length;
  };
}

int main()
{
  using namespace top;
  IDraw * f[3] = {};
  size_t s = 0;
  char * cnv = nullptr;
  p_t * p = nullptr;
  int err = 0;
  try
  {
    f[0] = new Dot(0, 0);
    f[1] = new Dot(2, 3);
    f[2] = new Dot(-5, -2);
    for (size_t i = 0; i < 3; ++i)
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
  delete[] p;
  delete[] cnv;
  return err;
}

top::Dot::Dot(int x, int y):
IDraw(), o{x, y}
{}

top::p_t top::Dot::begin() const
{
  return o;
}

top::p_t top::Dot::next(p_t) const
{
  return begin();
}

top::VLine::VLine(int x, int y, int len) : IDraw(), start{x,y}, length(len)
{}

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

top::HLine::HLine(int x, int y, int len) : IDraw(), start{x, y}, length(len)
{}

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
  return p_t{p.x + 1, start.y };
}

top::Square::Square(int x, int y, int len) : IDraw(), start{x, y}, length(len)
{}

top::p_t top::Square::begin() const
{
  return start;
}

top::p_t top::Square::next(p_t p) const
{
  if (p.y == start.y && p.x < start.x + length)
  {
    return p_t{p.x + 1, p.y};
  } else if (p.x == start.x + length && p.y < start.y + length)
  {
    return p_t{p.x, p.y + 1};
  } else if (p.y == start.y + length && p.x > start.x)
  {
    return p_t{p.x - 1, p.y};
  } else if (p.x == start.x && p.y > start.y)
  {
    return p_t{p.x, p.y - 1};
  }
  return start;
}

void top::extend(p_t ** pts, size_t s, p_t p)
{
  p_t * res = new p_t[s + 1];
  for (size_t i = 0; i < s; ++i)
  {
    res[i] = (*pts)[i];
  }
  res[s] = p;
  delete[] *pts;
  *pts = res;
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

char * top::build_canvas(frame_t f, char fill)
{
  char * cnv = new char[rows(f) * cols(f)];
  for (size_t i = 0; i < rows(f) * cols(f); ++i)
  {
    cnv[i] = fill;
  }
  return cnv;
}

void top::paint_canvas(char * cnv, frame_t fr, const p_t * ps, size_t k, char f)
{
  for (size_t i = 0; i < k; ++i)
  {
    int dx = ps[i].x - fr.left_bot.x;
    int dy = fr.right_top.y - ps[i].y;
    cnv[dy * cols(fr) + dx] = f;
  }
}

void top::print_canvas(const char * cnv, frame_t fr)
{
  for (size_t i = 0; i < rows(fr); ++i)
  {
    for (size_t j = 0; j < cols(fr); ++j)
    {
      std::cout << cnv[i * cols(fr) + j];
    }
    std::cout << "\n";
  }
}
