#pragma once

#include <stdexcept>
#include <string>

#ifndef WRP_GLOG_ENABLED
  #define L(a,b)
#endif

namespace WonderRabbitProject
{
  namespace SQLite3
  {
    
    namespace C
    {
      #include <sqlite3.h>
    }

    const std::string version        = SQLITE_VERSION;
    const uint32_t    version_number = SQLITE_VERSION_NUMBER;
    const std::string source_id      = SQLITE_SOURCE_ID;

    inline std::string sqlite3_version()
    { throw std::logic_error("not impl; use the other API."); }
    
    inline std::string sqlite3_libversion()
    { return C::sqlite3_libversion(); }
    
    inline std::string sqlite3_sourceid()
    { return C::sqlite3_sourceid(); }
    
    inline uint32_t libversion_number()
    { return C::sqlite3_libversion_number(); }

    #ifndef WRP_SQLITE3_NO_UNDEF    
      #undef SQLITE_VERSION
      #undef SQLITE_VERSION_NUMBER
      #undef SQLITE_SOURCE_ID
    #endif
    
    enum class OPEN_FLAGS : int
    { READONLY       = 0x00000001
    , READWRITE      = 0x00000002
    , CREATE         = 0x00000004
    , DELETEONCLOSE  = 0x00000008
    , EXCLUSIVE      = 0x00000010
    , AUTOPROXY      = 0x00000020
    , URI            = 0x00000040
    , MEMORY         = 0x00000080
    , MAIN_DB        = 0x00000100
    , TEMP_DB        = 0x00000200
    , TRANSIENT_DB   = 0x00000400
    , MAIN_JOURNAL   = 0x00000800
    , TEMP_JOURNAL   = 0x00001000
    , SUBJOURNAL     = 0x00002000
    , MASTER_JOURNAL = 0x00004000
    , NOMUTEX        = 0x00008000
    , FULLMUTEX      = 0x00010000
    , SHAREDCACHE    = 0x00020000
    , PRIVATECACHE   = 0x00040000
    , WAL            = 0x00080000
    };
    
    #ifndef WRP_SQLITE3_NO_UNDEF    
      #undef SQLITE_OPEN_READONLY
      #undef SQLITE_OPEN_READWRITE
      #undef SQLITE_OPEN_CREATE
      #undef SQLITE_OPEN_DELETEONCLOSE
      #undef SQLITE_OPEN_EXCLUSIVE
      #undef SQLITE_OPEN_AUTOPROXY
      #undef SQLITE_OPEN_URI
      #undef SQLITE_OPEN_MEMORY
      #undef SQLITE_OPEN_MAIN_DB
      #undef SQLITE_OPEN_TEMP_DB
      #undef SQLITE_OPEN_TRANSIENT_DB
      #undef SQLITE_OPEN_MAIN_JOURNAL
      #undef SQLITE_OPEN_TEMP_JOURNAL
      #undef SQLITE_OPEN_SUBJOURNAL
      #undef SQLITE_OPEN_MASTER_JOURNAL
      #undef SQLITE_OPEN_NOMUTEX
      #undef SQLITE_OPEN_FULLMUTEX
      #undef SQLITE_OPEN_SHAREDCACHE
      #undef SQLITE_OPEN_PRIVATECACHE
      #undef SQLITE_OPEN_WAL
    #endif
    
    constexpr OPEN_FLAGS operator|(const OPEN_FLAGS a, const OPEN_FLAGS b)
    { return OPEN_FLAGS( int(a) | int(b) ); }

    enum class RESULT_CODE : int
    { OK         =  0
    , ERROR      =  1
    , INTERNAL   =  2
    , PERM       =  3
    , ABORT      =  4
    , BUSY       =  5
    , LOCKED     =  6
    , NOMEM      =  7
    , READONLY   =  8
    , INTERRUPT  =  9
    , IOERR      = 10
    , CORRUPT    = 11
    , NOTFOUND   = 12
    , FULL       = 13
    , CANTOPEN   = 14
    , PROTOCOL   = 15
    , EMPTY      = 16
    , SCHEMA     = 17
    , TOOBIG     = 18
    , CONSTRAINT = 19
    , MISMATCH   = 20
    , MISUSE     = 21
    , NOLFS      = 22
    , AUTH       = 23
    , FORMAT     = 24
    , RANGE      = 25
    , NOTADB     = 26
    , ROW        = 100
    , DONE       = 101
    };

    #ifndef WRP_SQLITE3_NO_UNDEF    
      #undef SQLITE_OK
      #undef SQLITE_ERROR
      #undef SQLITE_INTERNAL
      #undef SQLITE_PERM
      #undef SQLITE_ABORT
      #undef SQLITE_BUSY
      #undef SQLITE_LOCKED
      #undef SQLITE_NOMEM
      #undef SQLITE_READONLY
      #undef SQLITE_INTERRUPT
      #undef SQLITE_IOERR
      #undef SQLITE_CORRUPT
      #undef SQLITE_NOTFOUND
      #undef SQLITE_FULL
      #undef SQLITE_CANTOPEN
      #undef SQLITE_PROTOCOL
      #undef SQLITE_EMPTY
      #undef SQLITE_SCHEMA
      #undef SQLITE_TOOBIG
      #undef SQLITE_CONSTRAINT
      #undef SQLITE_MISMATCH
      #undef SQLITE_MISUSE
      #undef SQLITE_NOLFS
      #undef SQLITE_AUTH
      #undef SQLITE_FORMAT
      #undef SQLITE_RANGE
      #undef SQLITE_NOTADB
      #undef SQLITE_ROW
      #undef SQLITE_DONE
    #endif
    
    inline void validate(RESULT_CODE r)
    {
      if( r != RESULT_CODE::OK )
        throw std::runtime_error
          ( u8"FAIL; RESULT_CODE is " + std::to_string(int(r)) );
            // ToDo: to_string(RESULT_CODE)
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
    
    struct sqlite3_t;
    
    struct prepare_t final
    {
      friend class sqlite3_t;
      
      ~prepare_t()
      {
        auto r = RESULT_CODE( C::sqlite3_finalize(ps) );
        validate(r);
      }
      
      void step() const
      {
        auto r = RESULT_CODE( C::sqlite3_step(ps) );
        validate(r);
      }
      
      void bind
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
      }

      void bind( const double v, const int index = 1 ) const
      {
        auto r = RESULT_CODE( C::sqlite3_bind_double(ps, index, v) );
        validate(r);
      }

      void bind( const int32_t v, const int index = 1 ) const
      {
        auto r = RESULT_CODE( C::sqlite3_bind_int(ps, index, v) );
        validate(r);
      }

      void bind( const int64_t v, const int index = 1 ) const
      {
        auto r = RESULT_CODE( C::sqlite3_bind_int64(ps, index, v) );
        validate(r);
      }

      void bind( decltype(nullptr), const int index = 1 ) const
      {
        auto r = RESULT_CODE( C::sqlite3_bind_null(ps, index) );
        validate(r);
      }

      void bind( const std::string & text, const int index = 1 ) const
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
      }

      void bind( const std::u16string & text, const int index = 1 ) const
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
      }

      void bind( const C::sqlite3_value & v, const int index = 1 ) const
      {
        auto r = RESULT_CODE( C::sqlite3_bind_value(ps, index, &v) );
        validate(r);
      }

      void bind( zeroblob_size_t v, const int index = 1 ) const
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
      }

      void reset() const
      {
        auto r = RESULT_CODE( C::sqlite3_reset(ps) );
        validate(r);
      }
      
    private:
      
      prepare_t(C::sqlite3_stmt * ps_)
        : ps(ps_)
      { }
      
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
        return prepare_t(ps);
      }
      
      prepare_t prepare(const std::u16string & sql) const
      {
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
        return prepare_t(ps);
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
      }
      
      inline void close()
      {
        auto r = RESULT_CODE( C::sqlite3_close_v2(pd) );
        validate(r);
      }
      
      C::sqlite3 * pd = nullptr;
    };
    
  }
}

