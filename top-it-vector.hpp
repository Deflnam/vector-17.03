#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP

#include <cstddef>
#include <stdexcept>
#include <algorithm>

namespace topit {

template <class T>
class Vector {
public:
    ~Vector();
    Vector();
    Vector(const Vector& rhs);
    Vector(Vector&& rhs) noexcept;
    explicit Vector(size_t size);
    Vector(size_t size, const T& init);

    Vector& operator=(const Vector& rhs);
    Vector& operator=(Vector&& rhs) noexcept;

    void swap(Vector& rhs) noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;

    void pushBack(const T& v);
    void popBack();
    void insert(size_t i, const T& v);
    void erase(size_t i);

private:
    T* data_;
    size_t size_;
    size_t capacity_;

    void rangeCheck(size_t id) const;
    void reallocate(size_t newCap);
};

template <class T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs);

}  

template <class T>
topit::Vector<T>::Vector()
    : data_(nullptr)
    , size_(0)
    , capacity_(0)
{}

template <class T>
topit::Vector<T>::Vector(size_t size)
    : data_(size ? new T[size] : nullptr)
    , size_(size)
    , capacity_(size)
{}

template <class T>
topit::Vector<T>::Vector(size_t size, const T& init)
    : Vector(size)
{
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = init;
    }
}

template <class T>
topit::Vector<T>::Vector(const Vector& rhs)
    : Vector(rhs.size_)
{
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = rhs.data_[i];
    }
}

template <class T>
topit::Vector<T>::Vector(Vector&& rhs) noexcept
    : data_(rhs.data_)
    , size_(rhs.size_)
    , capacity_(rhs.capacity_)
{
    rhs.data_ = nullptr;
    rhs.size_ = 0;
    rhs.capacity_ = 0;
}

template <class T>
topit::Vector<T>::~Vector()
{
    delete[] data_;
}

template <class T>
topit::Vector<T>& topit::Vector<T>::operator=(const Vector& rhs)
{
    if (this != std::addressof(rhs)) {
        Vector copy(rhs);
        swap(copy);
    }
    return *this;
}

template <class T>
topit::Vector<T>& topit::Vector<T>::operator=(Vector&& rhs) noexcept
{
    if (this != std::addressof(rhs)) {
        Vector moved(std::move(rhs));
        swap(moved);
    }
    return *this;
}

template <class T>
void topit::Vector<T>::swap(Vector& rhs) noexcept
{
    std::swap(data_, rhs.data_);
    std::swap(size_, rhs.size_);
    std::swap(capacity_, rhs.capacity_);
}

template <class T>
bool topit::Vector<T>::isEmpty() const noexcept
{
    return size_ == 0;
}

template <class T>
size_t topit::Vector<T>::getSize() const noexcept
{
    return size_;
}

template <class T>
size_t topit::Vector<T>::getCapacity() const noexcept
{
    return capacity_;
}

template <class T>
T& topit::Vector<T>::operator[](size_t id) noexcept
{
    return data_[id];
}

template <class T>
const T& topit::Vector<T>::operator[](size_t id) const noexcept
{
    return data_[id];
}

template <class T>
void topit::Vector<T>::rangeCheck(size_t id) const
{
    if (id >= size_) {
        throw std::out_of_range("Vector::at: index out of range");
    }
}

template <class T>
T& topit::Vector<T>::at(size_t id)
{
    rangeCheck(id);
    return data_[id];
}

template <class T>
const T& topit::Vector<T>::at(size_t id) const
{
    rangeCheck(id);
    return data_[id];
}

template <class T>
void topit::Vector<T>::reallocate(size_t newCap)
{
    T* newData = new T[newCap];
    for (size_t i = 0; i < size_; ++i) {
        newData[i] = std::move(data_[i]);
    }
    delete[] data_;
    data_ = newData;
    capacity_ = newCap;
}

template <class T>
void topit::Vector<T>::pushBack(const T& v)
{
    if (size_ == capacity_) {
        size_t newCap = (capacity_ == 0) ? 1 : capacity_ * 2;
        reallocate(newCap);
    }
    data_[size_] = v;
    ++size_;
}

template <class T>
void topit::Vector<T>::popBack()
{
    if (size_ > 0) {
        --size_;
    }
}

template <class T>
void topit::Vector<T>::insert(size_t i, const T& v)
{
    if (i > size_) {
        throw std::out_of_range("Vector::insert: index out of range");
    }
    if (size_ == capacity_) {
        size_t newCap = (capacity_ == 0) ? 1 : capacity_ * 2;
        reallocate(newCap);
    }
    for (size_t k = size_; k > i; --k) {
        data_[k] = std::move(data_[k - 1]);
    }
    data_[i] = v;
    ++size_;
}

template <class T>
void topit::Vector<T>::erase(size_t i)
{
    rangeCheck(i);
    for (size_t k = i; k < size_ - 1; ++k) {
        data_[k] = std::move(data_[k + 1]);
    }
    --size_;
}

template <class T>
bool topit::operator==(const Vector<T>& lhs, const Vector<T>& rhs)
{
    if (lhs.getSize() != rhs.getSize()) {
        return false;
    }
    for (size_t i = 0; i < lhs.getSize(); ++i) {
        if (!(lhs[i] == rhs[i])) {
            return false;
        }
    }
    return true;
}

#endif  
