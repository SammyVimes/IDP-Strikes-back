#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <sstream>
#include <exception>

class Exception : public std::exception
{
public:
  Exception();
  Exception(int line, std::string function, std::string timestamp);

  virtual const char* what() const throw();


private:
  int line;
  std::string function;
  std::string timestamp;
  std::string fullString;
};

#endif // EXCEPTION_H
