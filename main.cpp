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
    bool testMoveConstructor()
  {
    topit::Vector< int > v;
    v.pushBack(10);
    v.pushBack(20);
    const topit::Vector< int > moved(std::move(v));
    return moved.getSize() == 2
        && moved[0] == 10
        && moved[1] == 20
        && v.isEmpty();
  }

  bool testMoveAssignment()
  {
    topit::Vector< int > v;
    v.pushBack(5);
    v.pushBack(6);
    topit::Vector< int > target;
    target = std::move(v);
    return target.getSize() == 2
        && target[0] == 5
        && target[1] == 6
        && v.isEmpty();
  }
    bool testInsertAtBegin()
  {
    topit::Vector< int > v;
    v.pushBack(2);
    v.pushBack(3);
    v.insert(0, 1);
    return v.getSize() == 3
        && v[0] == 1
        && v[1] == 2
        && v[2] == 3;
  }

  bool testInsertAtMiddle()
  {
    topit::Vector< int > v;
    v.pushBack(1);
    v.pushBack(3);
    v.insert(1, 2);
    return v.getSize() == 3
        && v[0] == 1
        && v[1] == 2
        && v[2] == 3;
  }

  bool testInsertAtEnd()
  {
    topit::Vector< int > v;
    v.pushBack(1);
    v.pushBack(2);
    v.insert(2, 3);
    return v.getSize() == 3
        && v[0] == 1
        && v[1] == 2
        && v[2] == 3;
  }

  bool testInsertOutOfRange()
  {
    topit::Vector< int > v;
    v.pushBack(1);
    try {
      v.insert(5, 99);
      return false;
    } catch (const std::out_of_range &) {
      return true;
    } catch (...) {
      return false;
    }
  }

  bool testEraseFirst()
  {
    topit::Vector< int > v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    v.erase(0);
    return v.getSize() == 2
        && v[0] == 2
        && v[1] == 3;
  }

  bool testEraseMiddle()
  {
    topit::Vector< int > v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    v.erase(1);
    return v.getSize() == 2
        && v[0] == 1
        && v[1] == 3;
  }

  bool testEraseLast()
  {
    topit::Vector< int > v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    v.erase(2);
    return v.getSize() == 2
        && v[0] == 1
        && v[1] == 2;
  }

  bool testEraseOutOfRange()
  {
    topit::Vector< int > v;
    v.pushBack(1);
    try {
      v.erase(5);
      return false;
    } catch (const std::out_of_range &) {
      return true;
    } catch (...) {
      return false;
    }
  }


}
