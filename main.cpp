#include <iostream>
#include <iomanip>
#include <stdexcept>

#include "top-it-vector.hpp"

namespace {

  bool testEmptyVector()
  {
    const topit::Vector< int > v;
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

  bool testElementInboundAccess()
  {
    topit::Vector< int > v;
    v.pushBack(1);
    try {
      const int & val = v.at(0);
      return val == 1;
    } catch (...) {
      return false;
    }
  }

  bool testElementOutOfBoundAccess()
  {
    topit::Vector< int > v;
    try {
      v.at(0);
      return false;
    } catch (const std::out_of_range &) {
      return true;
    } catch (...) {
      return false;
    }
  }

  bool testElementInboundConstAccess()
  {
    topit::Vector< int > v;
    v.pushBack(1);
    const topit::Vector< int > & rv = v;
    try {
      const int & val = rv.at(0);
      return val == 1;
    } catch (...) {
      return false;
    }
  }

  bool testElementOutOfBoundConstAccess()
  {
    const topit::Vector< int > v;
    try {
      v.at(0);
      return false;
    } catch (const std::out_of_range &) {
      return true;
    } catch (...) {
      return false;
    }
  }

  bool testCopyConstructorForEmpty()
  {
    const topit::Vector< int > v;
    const topit::Vector< int > copy(v);
    return v == copy;
  }

  bool testCopyConstructorForNonEmpty()
  {
    topit::Vector< int > v;
    v.pushBack(1);
    const topit::Vector< int > copy = v;
    try {
      return copy.getSize() == v.getSize()
          && copy.at(0) == v.at(0);
    } catch (...) {
      return false;
    }
  }
}
