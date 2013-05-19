# libWRP-SQLite3

C++ SQLite3 wrapper library

## Features

- simple for use
    - open with ctor
    - database and statement close automatically with dtor by RAII
    - support `execute`
    - support `prepare`, `bind` and `reset`
        - `bind` and `reset` are chainable :)
    - support low-level controls; eg. `step`, `data_element`, `data_row`
- compile-time optimization friendly
    - but, not support indeterminately in compile-time
- header only
    - :)
- C++11 standard conformable and seal C API
    - rewrite to `enum class` from CPP `#define`s
    - std::tuple for use to data row
    - C API was sealed into the namespace `WonderRabbitProject::SQLite3::C`

## Library

The library is in the "./include" directory.

### Usage and Sample

    #include <WonderRabbitProject/SQLite3.hpp>

    using WonderRabbitProject::SQLite3::sqlite3_t;
    
    sqlite3_t database;
    database.execute("create table t(a,b,c)");
    database.execute("insert into t values(123, 4.5e+6, 'Hello')");
    database.execute("insert into t values(987, 6.5e-4, 'World')");
    auto statement = database.prepare("select * from t");
    auto data = statement.data<int32_t, double, std::string>();
    for ( const auto & row : data )
      std::cout << std::get<0>(row) << "\n"
                << std::get<1>(row) << "\n"
                << std::get<2>(row) << endl
                ;

And more examples available in:

1. [example\_01](example/example_01.cxx) // basic example
2. [example\_02](example/example_02.cxx) // blob example

## Requirement

* C++11
* [libqlite3](http://www.sqlite.org/) &gt;= 3.7

### Optional

* [google-glog](https://code.google.com/p/google-glog/)
* [Ninja](http://martine.github.com/ninja/)

## API Reference documentations

- [libWRP-SQLite3 API Reference](documents/html/index.html)

## License

* [GNU GENERAL PUBLIC LICENSE Version 3](http://www.gnu.org/licenses/gpl.html)

## Author

(C)2013 Usagi Ito<usagi@WonderRabbitProject.net> / [Wonder Rabbit Project](http://www.WonderRabbitProject.net/).

