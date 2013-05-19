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
  d.execute("create table bin(filename primary key, blob)");
  d.execute
  ( "insert into bin values('nico.png',x'"
    "89504e470d0a1a0a0000000d49484452"
    "000000080000000808020000004b6d29"
    "dc0000003f4944415408d77d8b410ac0"
    "301002cd2cf9ff83836b2fa58590563c"
    "88a3234127dd6d95b6709eff8101b277"
    "5cd59f0fd902253c06d91a09dd3de77b"
    "5dab810be8c319189c120a0400000000"
    "49454e44ae426082"
    "')"
  );
  
  auto s = d.prepare("select * from bin");
  
  using WonderRabbitProject::SQLite3::RESULT_CODE;
  
  // low level access: step
  while ( s.step() == RESULT_CODE::ROW )
  {
    // low level access: data_element
    auto filename = s.data_element<0, std::string>();
    auto blob     = s.data_element<1, std::vector<char>>();
    
    std::ofstream o( filename
                   , std::ofstream::binary
                   | std::ofstream::trunc
                   );
    
    o.write( blob.data(), blob.size());

    std::cout
      << "write \""
      << filename
      << "\" , "
      << blob.size()
      << " [bytes]"
      << std::endl
      ;
  }
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
