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

    bool testInsertRangeAtBegin()
  {
    topit::Vector< int > v;
    v.pushBack(4);
    v.pushBack(5);
    topit::Vector< int > src;
    src.pushBack(1);
    src.pushBack(2);
    src.pushBack(3);
    v.insert(0, src, 0, 3);
    return v.getSize() == 5
        && v[0] == 1 && v[1] == 2 && v[2] == 3
        && v[3] == 4 && v[4] == 5;
  }

  bool testInsertRangeInMiddle()
  {
    topit::Vector< int > v;
    v.pushBack(1);
    v.pushBack(5);
    topit::Vector< int > src;
    src.pushBack(2);
    src.pushBack(3);
    src.pushBack(4);
    v.insert(1, src, 0, 3);
    return v.getSize() == 5
        && v[0] == 1 && v[1] == 2 && v[2] == 3
        && v[3] == 4 && v[4] == 5;
  }

  bool testInsertRangeAtEnd()
  {
    topit::Vector< int > v;
    v.pushBack(1);
    v.pushBack(2);
    topit::Vector< int > src;
    src.pushBack(3);
    src.pushBack(4);
    src.pushBack(5);
    v.insert(2, src, 0, 3);
    return v.getSize() == 5
        && v[0] == 1 && v[1] == 2 && v[2] == 3
        && v[3] == 4 && v[4] == 5;
  }

  bool testInsertRangePartial()
  {
    topit::Vector< int > v;
    v.pushBack(1);
    v.pushBack(5);
    topit::Vector< int > src;
    src.pushBack(0);
    src.pushBack(2);
    src.pushBack(3);
    src.pushBack(4);
    src.pushBack(9);
    v.insert(1, src, 1, 4);
    return v.getSize() == 5
        && v[0] == 1 && v[1] == 2 && v[2] == 3
        && v[3] == 4 && v[4] == 5;
  }

  bool testInsertRangeBadRange()
  {
    topit::Vector< int > v;
    v.pushBack(1);
    topit::Vector< int > src;
    src.pushBack(10);
    try {
      v.insert(0, src, 1, 0);
      return false;
    } catch (const std::out_of_range &) {
      return true;
    } catch (...) {
      return false;
    }
  }

  struct ThrowAfter {
    static int countdown;
    int value;

    ThrowAfter():
      value(0)
    {}

    explicit ThrowAfter(int v):
      value(v)
    {}

    ThrowAfter(const ThrowAfter & rhs)
    {
      if (countdown > 0 && --countdown == 0) {
        throw std::runtime_error("ThrowAfter copy");
      }
      value = rhs.value;
    }

    ThrowAfter & operator=(const ThrowAfter & rhs)
    {
      if (countdown > 0 && --countdown == 0) {
        throw std::runtime_error("ThrowAfter assign");
      }
      value = rhs.value;
      return *this;
    }

    bool operator==(const ThrowAfter & rhs) const
    {
      return value == rhs.value;
    }
  };

  int ThrowAfter::countdown = 0;

  bool testInsertRangeStrongGuarantee()
  {
    topit::Vector< ThrowAfter > v;
    v.pushBack(ThrowAfter(1));
    v.pushBack(ThrowAfter(2));
    v.pushBack(ThrowAfter(3));
    topit::Vector< ThrowAfter > src;
    src.pushBack(ThrowAfter(10));
    src.pushBack(ThrowAfter(11));
    src.pushBack(ThrowAfter(12));
    ThrowAfter::countdown = 5;
    bool caught = false;
    try {
      v.insert(1, src, 0, 3);
    } catch (const std::runtime_error &) {
      caught = true;
    }
    if (!caught) {
      return false;
    }
    return v.getSize() == 3
        && v[0].value == 1
        && v[1].value == 2
        && v[2].value == 3;
  }

  bool testEraseRangeAll()
  {
    topit::Vector< int > v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    v.erase(0, 3);
    return v.isEmpty();
  }

  bool testEraseRangeMiddle()
  {
    topit::Vector< int > v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    v.pushBack(4);
    v.pushBack(5);
    v.erase(1, 4);
    return v.getSize() == 2
        && v[0] == 1
        && v[1] == 5;
  }

  bool testEraseRangeBadRange()
  {
    topit::Vector< int > v;
    v.pushBack(1);
    v.pushBack(2);
    try {
      v.erase(2, 1);
      return false;
    } catch (const std::out_of_range &) {
      return true;
    } catch (...) {
      return false;
    }
  }

  bool testEraseRangeStrongGuarantee()
  {
    topit::Vector< ThrowAfter > v;
    v.pushBack(ThrowAfter(1));
    v.pushBack(ThrowAfter(2));
    v.pushBack(ThrowAfter(3));
    v.pushBack(ThrowAfter(4));
    ThrowAfter::countdown = 1;
    bool caught = false

}
