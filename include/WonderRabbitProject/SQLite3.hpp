#pragma once

#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

#include "SQLite3/detail.hpp"

#ifndef WRP_GLOG_ENABLED
  #define L(a,b)
#endif

namespace WonderRabbitProject
{
  namespace SQLite3
  {
    struct sqlite3_t;
    
    struct prepare_t final
    {
      friend class sqlite3_t;
      
      ~prepare_t()
      {
        L(INFO, "prepare_t dtor in");
        auto r = RESULT_CODE( C::sqlite3_finalize(ps) );
        validate(r);
        L(INFO, "prepare_t dtor out");
      }
      
      template<size_t N, class T>
      T data_element() const
      { return detail::column<N,T>::get(ps); }
      
      // TS where types of columns
      template<class ... TS>
      std::tuple<TS ...> data_row() const
      {
        using t = std::tuple<TS ...>;
        t row;
        detail::row<t>::set(ps, row);
        return row;
      }
      
      template<class ... TS>
      std::vector<std::tuple<TS ...>> data() const
      {
        std::vector<std::tuple<TS ...>> data;
        auto i = std::back_inserter(data);
        
        return data;
      }
      
      RESULT_CODE step() const
      {
        auto r = step_no_validate();
        validate(r);
        return r;
      }
      
      const prepare_t & bind
      ( const std::vector<uint8_t> & blob
      , const int index = 1
      ) const
      {
        auto r = RESULT_CODE
        ( C::sqlite3_bind_blob
          ( ps
          , index
          , blob.data()
          , blob.size()
          , nullptr
          )
        );
        validate(r);
        return *this;
      }

      const prepare_t & bind( const double v, const int index = 1 ) const
      {
        auto r = RESULT_CODE( C::sqlite3_bind_double(ps, index, v) );
        validate(r);
        return *this;
      }

      const prepare_t & bind( const int32_t v, const int index = 1 ) const
      {
        auto r = RESULT_CODE( C::sqlite3_bind_int(ps, index, v) );
        validate(r);
        return *this;
      }

      const prepare_t & bind( const int64_t v, const int index = 1 ) const
      {
        auto r = RESULT_CODE( C::sqlite3_bind_int64(ps, index, v) );
        validate(r);
        return *this;
      }

      const prepare_t & bind( decltype(nullptr), const int index = 1 ) const
      {
        auto r = RESULT_CODE( C::sqlite3_bind_null(ps, index) );
        validate(r);
        return *this;
      }

      const prepare_t & bind( const std::string & text, const int index = 1 ) const
      {
        auto r = RESULT_CODE
        ( C::sqlite3_bind_text
          ( ps
          , index
          , text.data()
          , text.size()
          , nullptr
          )
        );
        validate(r);
        return *this;
      }

      const prepare_t & bind( const std::u16string & text, const int index = 1 ) const
      {
        auto r = RESULT_CODE
        ( C::sqlite3_bind_text16
          ( ps
          , index
          , text.data()
          , text.size()
          , nullptr
          )
        );
        validate(r);
        return *this;
      }

      const prepare_t & bind( const C::sqlite3_value & v, const int index = 1 ) const
      {
        auto r = RESULT_CODE( C::sqlite3_bind_value(ps, index, &v) );
        validate(r);
        return *this;
      }

      const prepare_t bind( zeroblob_size_t v, const int index = 1 ) const
      {
        assert( v.size() > std::numeric_limits<int>::max() );
        auto r = RESULT_CODE
        ( C::sqlite3_bind_zeroblob
          ( ps
          , index
          , int(v.size())
          )
        );
        validate(r);
        return *this;
      }

      const prepare_t & reset() const
      {
        auto r = RESULT_CODE( C::sqlite3_reset(ps) );
        validate(r);
        return *this;
      }
      
    private:
      
      prepare_t(C::sqlite3_stmt * ps_)
        : ps(ps_)
      { }
      
      RESULT_CODE step_no_validate() const
      { return RESULT_CODE( C::sqlite3_step(ps) ); }
      
      C::sqlite3_stmt * ps;
    };
  
    struct sqlite3_t final
    {
      static constexpr OPEN_FLAGS default_open_flags
        = OPEN_FLAGS::READWRITE
        | OPEN_FLAGS::CREATE
        ;
      
      sqlite3_t
      ( const std::string & filename = u8":memory:"
      , OPEN_FLAGS flags = default_open_flags
      )
      { open(filename, flags); }
      
      ~sqlite3_t()
      { close(); }
      
      prepare_t prepare(const std::string & sql) const
      {
        L(INFO, "prepare(u8) in");
        C::sqlite3_stmt* ps;
        auto r = RESULT_CODE
        ( C::sqlite3_prepare_v2
          ( pd
          , sql.data()
          , -1
          , &ps
          , nullptr
          )
        );
        validate(r);
        L(INFO, "prepare(u8) out");
        return prepare_t(ps);
      }
      
      prepare_t prepare(const std::u16string & sql) const
      {
        L(INFO, "prepare(u16) in");
        C::sqlite3_stmt* ps;
        auto r = RESULT_CODE
        ( C::sqlite3_prepare16_v2
          ( pd
          , sql.data()
          , -1
          , &ps
          , nullptr
          )
        );
        validate(r);
        L(INFO, "prepare(u16) out");
        return prepare_t(ps);
      }
      
      template<class T>
      void execute(const T & sql) const
      {
        L(INFO, "execute in");
        auto p = prepare(sql);
        L(INFO, "execute prepared");
        p.step();
        L(INFO, "execute out");
      }
      
    private:
      
      inline void open(const std::string & filename, OPEN_FLAGS flags)
      {
        auto r = RESULT_CODE
        ( C::sqlite3_open_v2
          ( filename.data()
          , &pd
          , int(flags)
          , nullptr
          )
        );
        validate(r);
        L(INFO, "opened");
      }
      
      inline void close()
      {
        auto r = RESULT_CODE( C::sqlite3_close_v2(pd) );
        validate(r);
        L(INFO, "closed");
      }
      
      C::sqlite3 * pd = nullptr;
    };
    
  }
}

