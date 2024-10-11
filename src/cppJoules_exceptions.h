#ifndef RAPL_EXCEPTION
#define RAPL_EXCEPTION
#include <exception>
#include <string>
class CPPJoulesException : public std::exception
{
private:
  std::string message;

public:
  explicit CPPJoulesException(std::string msg) : message(std::move(msg)) {}
  const char *what() const noexcept override
  {
    return message.c_str();
  }
};
#endif