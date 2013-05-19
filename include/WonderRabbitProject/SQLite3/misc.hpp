#pragma once

#include "c.hpp"
#include "global.hpp"

namespace WonderRabbitProject
{
  namespace SQLite3
  {
    
    inline void validate(RESULT_CODE r)
    {
      switch(r)
      {
        case RESULT_CODE::OK:
        case RESULT_CODE::ROW:
        case RESULT_CODE::DONE:
          return;
        default:
          // ToDo: to_string(RESULT_CODE)
          auto m = u8"FAIL; RESULT_CODE is " + std::to_string(int(r));
          L(ERROR, m);
          throw std::runtime_error(m);
      }
    }
    
    struct zeroblob_size_t final
    {
      explicit zeroblob_size_t(size_t size__) noexcept
        : size_(size__)
      { }
      size_t size() const
      { return size_; }
    private:
      const size_t size_;
    };
  }
}

