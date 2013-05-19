#include <stdexcept>
#include <cstdint>
#include <string>
#include <iostream>
#include <WonderRabbitProject/SQLite3.hpp>

int main()
try
{
  std::cout << "main in" << std::endl;

  using WonderRabbitProject::SQLite3::sqlite3_t;

  // example with in-memory database
  {
    // open
    sqlite3_t database; // or `sqlite3_t database("file.sqlite3")`
    std::cout << "databse opened(in-memory)" << std::endl;

    // create table
    {
      auto sql = "create table t(a,b,c)";
      database.execute(sql);
      std::cout << "database SQL executed: " << sql << std::endl;
    }

    // insert
    {
      auto sql = "insert into t values(123, 4.5e+6, \"hello\")";
      database.execute(sql);
      std::cout << "database SQL executed: " << sql << std::endl;
      
      // and more
      database.execute("insert into t values(987, 6.5e-4, \"world\")");
      database.execute("insert into t values(852, 7.4e-1, \"example\")");
      std::cout << "and more insert executed" << std::endl;
    }

    // select with prepare
    {
      auto sql = "select * from t";
      auto statement = database.prepare(sql);
      std::cout << "database SQL prepared: " << sql << std::endl;
      
      auto data = statement.data<int32_t, double, std::string>();
      std::cout << "statement data called" << std::endl;
      
      for(const auto & row : data)
      {
        std::cout
          << "data-row: "
             " ( " << std::get<0>(row)
          << " , " << std::get<1>(row)
          << " , " << std::get<2>(row)
          << " )"
          << std::endl
          ;
      }
    }
    
    // select with prepare, bind and reset
    {
      auto sql = "select * from t where a < ? and b > ?";
      auto statement = database.prepare(sql);
      std::cout << "database SQL prepared: " << sql << std::endl;

      // bind is chainable
      statement.bind(500 , 1)
               .bind(10.0, 2)
               ;
      std::cout << "statement bound" << std::endl;
      
      auto data1 = statement.data<int32_t, double, std::string>();
      std::cout << "statement data called" << std::endl;
      
      for(const auto & row : data1)
        std::cout
          << "data-row: "
             " ( " << std::get<0>(row)
          << " , " << std::get<1>(row)
          << " , " << std::get<2>(row)
          << " )"
          << std::endl
          ;

      // reset is chainable
      statement.reset()
               .bind(900, 1)
               .bind(0.0, 2)
               ;
      std::cout << "statement reset and bound" << std::endl;

      auto data2 = statement.data<int32_t, double, std::string>();
      std::cout << "statement data called" << std::endl;
      
      for(const auto & row : data2)
        std::cout
          << "data-row: "
             " ( " << std::get<0>(row)
          << " , " << std::get<1>(row)
          << " , " << std::get<2>(row)
          << " )"
          << std::endl
          ;
    }

    // close automatically with RAII dtor
  }
  
  std::cout << "main out" << std::endl;
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
