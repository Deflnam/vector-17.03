#include <iostream>
#include <iomanip>
#include "top-it-vector.hpp"

bool testEmptyVector()
{
  // std::cout << __func__ << "\n";
  topit::Vector< int > v;
  return v.isEmpty();
}

bool testGetSize()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.popBack();
  return v.getSize() == 2;
}

bool testGetCapacity()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  return v.getCapacity() == 4;
}

bool testElementInboudAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  try
  {
    int & val = v.at(0);
    return val == 1;
  }
  catch (...)
  {
    return false;
  }
}

bool testElementOutOfBoundAccess()
{
  topit::Vector< int > v;
  try
  {
    v.at(0);
    return false;
  }
  catch(const std::out_of_range &)
  {
    return true;
  }
  catch (...)
  {
    return false;
  }
}

bool testElementInboudConstAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  const topit::Vector< int > & rv = v;
  try
  {
    const int & val = rv.at(0);
    return val == 1;
  }
  catch (...)
  {
    return false;
  }
}

bool testElementOutOfBoundConstAccess()
{
  const topit::Vector< int > v;
  try
  {
    v.at(0);
    return false;
  }
  catch(const std::out_of_range &)
  {
    return true;
  }
  catch (...)
  {
    return false;
  }
}

bool testCopyConstructorForEmpty()
{
  topit::Vector< int > v;
  topit::Vector< int > yav(v);
  return v == yav;
}

bool testCopyConstructorForNonEmpty()
{
  topit::Vector< int > v;
  v.pushBack(1);
  topit::Vector< int > yav = v;
  return v == yav;
}

int main()
{
  using test_t = std::pair< const char *, bool(*)() >;
  test_t tests[] = {
    { "Empty vector", testEmptyVector },
    { "Size of vector", testGetSize },
    { "Capacity of vector", testGetCapacity },
    { "Inbound access", testElementInboudAccess },
    { "Out of bound access", testElementOutOfBoundAccess },
    { "Inbound const access", testElementInboudConstAccess },
    { "Out of bound const access", testElementOutOfBoundConstAccess },
    { "Copy empty vector", testCopyConstructorForEmpty },
    { "Copy non-empty vector", testCopyConstructorForNonEmpty }
  };
  const size_t count = sizeof(tests) / sizeof(test_t);
  bool pass = true;
  for (size_t i = 0; i < count; ++i)
  {
    bool res = tests[i].second();
    std::cout << tests[i].first << ": " << res << "\n";
    pass = pass && res;
  }
  std::cout << "RESULT: " << pass << "\n";
  // Подсчёт кол-ва пройденных / непройденных тестов
  // Выводить только непрошедшие тесты
}
