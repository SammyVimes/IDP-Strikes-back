#include "exception.h"

Exception::Exception():exception()
{
    line = 0;
    function = "";
    timestamp = "";
}

Exception::Exception(int line, std::string function, std::string timestamp):
  exception(),
  line(line),
  function(function),
  timestamp(timestamp)
{
  std::ostringstream oss;
  oss  << "Exception \""
       << "\" in function \""
       << function
       << "\" in line: "
       << line
       << ". Time: "
       << timestamp;
  fullString = oss.str();
}

const char *Exception::what() const throw()
{
  return fullString.c_str();
}
