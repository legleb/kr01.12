#ifndef DOT_HPP
#define DOT_HPP
#include "idraw.hpp"
namespace top
{
  struct Dot: IDraw
  {
    virtual p_t begin() const override;
    virtual p_t next(p_t p) const override;
    explicit Dot(int x, int y);
    ~Dot() override = default;
  private:
    p_t o;
  };
}
#endif
