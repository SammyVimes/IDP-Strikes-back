#include "exception.h"

Exception::Exception():exception()
{
    text = "";
    line = 0;
    function = "";
    timestamp = "";
}

Exception::Exception(std::string text, int line, std::string function, std::string timestamp):
  exception(),
  text(text),
  line(line),
  function(function),
  timestamp(timestamp)
{
  std::ostringstream oss;
  oss  << "Exception \""
       << text
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