#pragma once

#include "c.hpp"

namespace WonderRabbitProject
{
  namespace SQLite3
  {
    
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
// MSVC++ がまともに constexpr や定数式を扱えないために必要な定義
#ifdef _MSC_VER
    , READWRITE_CREATE = 0x00000006
#endif
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
#ifndef _WIN32
    , ERROR      =  1
#else
    , ERROR_     =  1
#endif
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
  
  }
}

