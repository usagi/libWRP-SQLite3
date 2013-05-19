#pragma once

#include <vector>
#include <string>

#include "c.hpp"
#include "global.hpp"
#include "misc.hpp"

namespace WonderRabbitProject
{
  namespace SQLite3
  {

    namespace detail
    {
      template<size_t N, class T>
      struct column
      {
        static inline T get(C::sqlite3_stmt * ps)
        { throw std::logic_error("not impl"); }
      };
      
      template<size_t N>
      struct column<N, std::vector<uint8_t>>
      {
        static inline std::vector<uint8_t> get(C::sqlite3_stmt * ps)
        {
          auto size = static_cast<size_t>(C::sqlite3_column_bytes(ps, N));
          auto data = static_cast<const uint8_t *>(C::sqlite3_column_blob(ps, N));
          return std::vector<uint8_t>(data, data + size);
        }
      };
      
      template<size_t N>
      struct column<N, std::vector<int8_t>>
      {
        static inline std::vector<int8_t> get(C::sqlite3_stmt * ps)
        {
          auto size = static_cast<size_t>(C::sqlite3_column_bytes(ps, N));
          auto data = static_cast<const int8_t *>(C::sqlite3_column_blob(ps, N));
          return std::vector<int8_t>(data, data + size);
        }
      };
      
      template<size_t N>
      struct column<N, std::vector<char>>
      {
        static inline std::vector<char> get(C::sqlite3_stmt * ps)
        {
          auto size = static_cast<char>(C::sqlite3_column_bytes(ps, N));
          auto data = static_cast<const char *>(C::sqlite3_column_blob(ps, N));
          return std::vector<char>(data, data + size);
        }
      };
      
      template<size_t N>
      struct column<N, double>
      {
        static inline double get(C::sqlite3_stmt * ps)
        { return C::sqlite3_column_double(ps, N); }
      };
      
      template<size_t N>
      struct column<N, int32_t>
      {
        static inline int32_t get(C::sqlite3_stmt * ps)
        { return C::sqlite3_column_int(ps, N); }
      };
      
      template<size_t N>
      struct column<N, int64_t>
      {
        static inline int64_t get(C::sqlite3_stmt * ps)
        { return C::sqlite3_column_int64(ps, N); }
      };
      
      template<size_t N>
      struct column<N, std::string>
      {
        static inline std::string get(C::sqlite3_stmt * ps)
        {
          auto size = static_cast<size_t>(C::sqlite3_column_bytes(ps, N));
          auto data = C::sqlite3_column_text(ps, N);
          return std::string
            ( reinterpret_cast<const char *>(data)
            , size
            );
        }
      };
      
      template<size_t N>
      struct column<N, std::u16string>
      {
        static inline std::u16string get(C::sqlite3_stmt * ps)
        {
          auto size = static_cast<size_t>(C::sqlite3_column_bytes16(ps, N));
          auto data = C::sqlite3_column_text16(ps, N);
          return std::u16string
            ( reinterpret_cast<const char16_t *>(data)
            , size
            );
        }
      };
      

      template<size_t N, class T>
      struct row_
      {
        static inline void set(C::sqlite3_stmt * ps, T & tuple)
        {
          using element_type = typename std::tuple_element<N, T>::type;
          std::get<N>(tuple) = detail::column<N, element_type>::get(ps);
          row_<N - 1, T>::set(ps, tuple);
        }
      };
      
      template<class T>
      struct row_<0, T>
      {
        static inline void set(C::sqlite3_stmt * ps, T & tuple)
        {
          using element_type = typename std::tuple_element<0, T>::type;
          std::get<0>(tuple) = detail::column<0, element_type>::get(ps);
        }
      };
      
      template<class T>
      struct row
      {
        static inline void set(C::sqlite3_stmt * ps, T & tuple)
        { row_<std::tuple_size<T>::value - 1, T>::set(ps, tuple); }
      };
      

    }
    
  }
}
