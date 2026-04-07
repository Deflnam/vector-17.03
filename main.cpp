#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include "top-it-vector.hpp"

bool testEmptyVector()
{
    topit::Vector<int> v;
    return v.isEmpty();
}

bool testGetSize()
{
    topit::Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    v.popBack();
    return v.getSize() == 2;
}

bool testGetCapacity()
{
    topit::Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    return v.getCapacity() == 4;
}

bool testElementInboundAccess()
{
    topit::Vector<int> v;
    v.pushBack(1);
    try {
        return v.at(0) == 1;
    } catch (...) {
        return false;
    }
}

bool testElementOutOfBoundAccess()
{
    topit::Vector<int> v;
    try {
        v.at(0);
        return false;
    } catch (const std::out_of_range&) {
        return true;
    } catch (...) {
        return false;
    }
}

bool testElementInboundConstAccess()
{
    topit::Vector<int> v;
    v.pushBack(1);
    const topit::Vector<int>& rv = v;
    try {
        return rv.at(0) == 1;
    } catch (...) {
        return false;
    }
}

bool testElementOutOfBoundConstAccess()
{
    const topit::Vector<int> v;
    try {
        v.at(0);
        return false;
    } catch (const std::out_of_range&) {
        return true;
    } catch (...) {
        return false;
    }
}

bool testCopyConstructorForEmpty()
{
    topit::Vector<int> v;
    topit::Vector<int> copy(v);
    return v == copy;
}

bool testCopyConstructorForNonEmpty()
{
    topit::Vector<int> v;
    v.pushBack(1);
    topit::Vector<int> copy = v;
    try {
        return copy.getSize() == v.getSize() && copy.at(0) == v.at(0);
    } catch (...) {
        return false;
    }
}

bool testMoveConstructor()
{
    topit::Vector<int> v;
    v.pushBack(10);
    v.pushBack(20);
    topit::Vector<int> moved(std::move(v));
    return moved.getSize() == 2
        && moved[0] == 10
        && moved[1] == 20
        && v.isEmpty();
}

bool testMoveAssignment()
{
    topit::Vector<int> v;
    v.pushBack(5);
    v.pushBack(6);
    topit::Vector<int> target;
    target = std::move(v);
    return target.getSize() == 2
        && target[0] == 5
        && target[1] == 6
        && v.isEmpty();
}

bool testInsertAtBegin()
{
    topit::Vector<int> v;
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
    topit::Vector<int> v;
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
    topit::Vector<int> v;
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
    topit::Vector<int> v;
    v.pushBack(1);
    try {
        v.insert(5, 99);
        return false;
    } catch (const std::out_of_range&) {
        return true;
    } catch (...) {
        return false;
    }
}

bool testEraseFirst()
{
    topit::Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    v.erase(0);
    return v.getSize() == 2 && v[0] == 2 && v[1] == 3;
}

bool testEraseMiddle()
{
    topit::Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    v.erase(1);
    return v.getSize() == 2 && v[0] == 1 && v[1] == 3;
}

bool testEraseLast()
{
    topit::Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    v.erase(2);
    return v.getSize() == 2 && v[0] == 1 && v[1] == 2;
}

bool testEraseOutOfRange()
{
    topit::Vector<int> v;
    v.pushBack(1);
    try {
        v.erase(5);
        return false;
    } catch (const std::out_of_range&) {
        return true;
    } catch (...) {
        return false;
    }
}

bool testInsertRangeAtBegin()
{
    topit::Vector<int> v;
    v.pushBack(4);
    v.pushBack(5);
    topit::Vector<int> src;
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
    topit::Vector<int> v;
    v.pushBack(1);
    v.pushBack(5);
    topit::Vector<int> src;
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
    topit::Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    topit::Vector<int> src;
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
    topit::Vector<int> v;
    v.pushBack(1);
    v.pushBack(5);
    topit::Vector<int> src;
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
    topit::Vector<int> v;
    v.pushBack(1);
    topit::Vector<int> src;
    src.pushBack(10);
    try {
        v.insert(0, src, 1, 0);
        return false;
    } catch (const std::out_of_range&) {
        return true;
    } catch (...) {
        return false;
    }
}

bool testEraseRangeAll()
{
    topit::Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    v.erase(0, 3);
    return v.isEmpty();
}

bool testEraseRangeMiddle()
{
    topit::Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    v.pushBack(4);
    v.pushBack(5);
    v.erase(1, 4);
    return v.getSize() == 2 && v[0] == 1 && v[1] == 5;
}

bool testEraseRangeEmpty()
{
    topit::Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.erase(1, 1);
    return v.getSize() == 2;
}

bool testEraseRangeBadRange()
{
    topit::Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    try {
        v.erase(2, 1);
        return false;
    } catch (const std::out_of_range&) {
        return true;
    } catch (...) {
        return false;
    }
}

bool testIteratorInsertAtBegin()
{
    topit::Vector<int> v;
    v.pushBack(2);
    v.pushBack(3);
    std::vector<int> src = {1};
    v.insert(v.begin(), src.begin(), src.end());
    return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testIteratorInsertAtMiddle()
{
    topit::Vector<int> v;
    v.pushBack(1);
    v.pushBack(3);
    std::vector<int> src = {2};
    v.insert(v.begin() + 1, src.begin(), src.end());
    return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testIteratorInsertAtEnd()
{
    topit::Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    std::vector<int> src = {3};
    v.insert(v.end(), src.begin(), src.end());
    return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testIteratorInsertMultiple()
{
    topit::Vector<int> v;
    v.pushBack(1);
    v.pushBack(5);
    std::vector<int> src = {2, 3, 4};
    v.insert(v.begin() + 1, src.begin(), src.end());
    return v.getSize() == 5
        && v[0] == 1 && v[1] == 2 && v[2] == 3
        && v[3] == 4 && v[4] == 5;
}

bool testIteratorInsertEmptyRange()
{
    topit::Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    std::vector<int> src;
    v.insert(v.begin() + 1, src.begin(), src.end());
    return v.getSize() == 2 && v[0] == 1 && v[1] == 2;
}

bool testIteratorInsertFromVector()
{
    topit::Vector<int> v;
    v.pushBack(1);
    v.pushBack(5);
    topit::Vector<int> src;
    src.pushBack(2);
    src.pushBack(3);
    src.pushBack(4);
    v.insert(v.begin() + 1, src.begin(), src.end());
    return v.getSize() == 5
        && v[0] == 1 && v[1] == 2 && v[2] == 3
        && v[3] == 4 && v[4] == 5;
}

bool testIteratorBeginEnd()
{
    topit::Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    int sum = 0;
    for (auto it = v.begin(); it != v.end(); ++it) {
        sum += *it;
    }
    return sum == 6;
}

bool testConstIterator()
{
    topit::Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    const topit::Vector<int>& cv = v;
    int sum = 0;
    for (auto it = cv.cbegin(); it != cv.cend(); ++it) {
        sum += *it;
    }
    return sum == 6;
}

bool testReverseIteration()
{
    topit::Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    int expected = 3;
    for (auto it = v.end() - 1; it >= v.begin(); --it) {
        if (*it != expected) {
            return false;
        }
        --expected;
    }
    return true;
}

struct ThrowAfter {
    static int countdown;
    int value;

    ThrowAfter() : value(0) {}
    explicit ThrowAfter(int v) : value(v) {}

    ThrowAfter(const ThrowAfter& rhs) {
        if (countdown > 0 && --countdown == 0) {
            throw std::runtime_error("ThrowAfter copy");
        }
        value = rhs.value;
    }

    ThrowAfter& operator=(const ThrowAfter& rhs) {
        if (countdown > 0 && --countdown == 0) {
            throw std::runtime_error("ThrowAfter assign");
        }
        value = rhs.value;
        return *this;
    }

    bool operator==(const ThrowAfter& rhs) const {
        return value == rhs.value;
    }
};

int ThrowAfter::countdown = 0;

bool testInsertRangeStrongGuarantee()
{
    topit::Vector<ThrowAfter> v;
    v.pushBack(ThrowAfter(1));
    v.pushBack(ThrowAfter(2));
    v.pushBack(ThrowAfter(3));
    topit::Vector<ThrowAfter> src;
    src.pushBack(ThrowAfter(10));
    src.pushBack(ThrowAfter(11));
    src.pushBack(ThrowAfter(12));
    ThrowAfter::countdown = 5;
    bool caught = false;
    try {
        v.insert(1, src, 0, 3);
    } catch (const std::runtime_error&) {
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

bool testIteratorInsertStrongGuarantee()
{
    topit::Vector<ThrowAfter> v;
    v.pushBack(ThrowAfter(1));
    v.pushBack(ThrowAfter(2));
    v.pushBack(ThrowAfter(3));
    std::vector<ThrowAfter> src;
    src.push_back(ThrowAfter(10));
    src.push_back(ThrowAfter(11));
    src.push_back(ThrowAfter(12));
    ThrowAfter::countdown = 5;
    bool caught = false;
    try {
        v.insert(v.begin() + 1, src.begin(), src.end());
    } catch (const std::runtime_error&) {
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

int main()
{
    using test_t = std::pair<const char*, bool(*)()>;
    test_t tests[] = {
        {"Empty vector", testEmptyVector},
        {"Size of vector", testGetSize},
        {"Capacity of vector", testGetCapacity},
        {"Inbound access", testElementInboundAccess},
        {"Out of bound access", testElementOutOfBoundAccess},
        {"Inbound const access", testElementInboundConstAccess},
        {"Out of bound const access", testElementOutOfBoundConstAccess},
        {"Copy empty vector", testCopyConstructorForEmpty},
        {"Copy non-empty vector", testCopyConstructorForNonEmpty},
        {"Move constructor", testMoveConstructor},
        {"Move assignment", testMoveAssignment},
        {"Insert at begin", testInsertAtBegin},
        {"Insert at middle", testInsertAtMiddle},
        {"Insert at end", testInsertAtEnd},
        {"Insert out of range", testInsertOutOfRange},
        {"Erase first", testEraseFirst},
        {"Erase middle", testEraseMiddle},
        {"Erase last", testEraseLast},
        {"Erase out of range", testEraseOutOfRange},
        {"Insert range at begin", testInsertRangeAtBegin},
        {"Insert range in middle", testInsertRangeInMiddle},
        {"Insert range at end", testInsertRangeAtEnd},
        {"Insert range partial", testInsertRangePartial},
        {"Insert range bad range", testInsertRangeBadRange},
        {"Erase range all", testEraseRangeAll},
        {"Erase range middle", testEraseRangeMiddle},
        {"Erase range empty", testEraseRangeEmpty},
        {"Erase range bad range", testEraseRangeBadRange},
        {"Insert range strong guarantee", testInsertRangeStrongGuarantee},
        {"Iterator insert at begin", testIteratorInsertAtBegin},
        {"Iterator insert at middle", testIteratorInsertAtMiddle},
        {"Iterator insert at end", testIteratorInsertAtEnd},
        {"Iterator insert multiple", testIteratorInsertMultiple},
        {"Iterator insert empty range", testIteratorInsertEmptyRange},
        {"Iterator insert from Vector", testIteratorInsertFromVector},
        {"Iterator begin/end", testIteratorBeginEnd},
        {"Const iterator", testConstIterator},
        {"Reverse iteration", testReverseIteration},
        {"Iterator insert strong guarantee", testIteratorInsertStrongGuarantee}
    };

    const size_t count = sizeof(tests) / sizeof(test_t);
    size_t passed = 0;
    size_t failed = 0;

    for (size_t i = 0; i < count; ++i) {
        bool res = tests[i].second();
        if (res) {
            ++passed;
        } else {
            ++failed;
            std::cout << "FAILED: " << tests[i].first << "\n";
        }
    }

    std::cout << "Passed: " << passed << "\n";
    std::cout << "Failed: " << failed << "\n";
    std::cout << "Total:  " << count << "\n";
    std::cout << "RESULT: " << (failed == 0 ? "ALL TESTS PASSED" : "SOME TESTS FAILED") << "\n";

    return (failed == 0) ? 0 : 1;
}
