#include <stdexcept>
#include <cstdint>
#include <string>
#include <iostream>
#include <fstream>
#include <WonderRabbitProject/SQLite3.hpp>

int main()
try
{
  using WonderRabbitProject::SQLite3::sqlite3_t;
  
  sqlite3_t d;
  for(auto n = 3; n; --n)
    d.execute
      ( std::string("create table t")
      + std::to_string(n)
      + "(a,b,c)"
      );

  // execute_data is mixed feature of
  // `sqlite3_t::execute` and `prepare_t::data`
  auto data = d.execute_data<std::string, std::string>
    ( "select name, sql"
      " from sqlite_master"
      " where type = 'table'"
    );

  for(const auto & row : data)
    std::cout
      << std::get<0>(row)
      << " : "
      << std::get<1>(row)
      << std::endl
      ;
  
}
catch(const std::exception & e)
{
  std::cerr << "exception: " << e.what();
  return -1;
}
catch(...)
{
  std::cerr << "exception: unkown";
  return -2;
}
