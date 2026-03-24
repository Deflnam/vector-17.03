#ifndef TOPIT_VECTOR_HPP
#define TOPIT_VECTOR_HPP

#include <cstddef>
#include <stdexcept>
#include <algorithm>

namespace topit {

  template< class T >
  struct Vector {

    struct VectorIterator {
      using iterator_category = std::random_access_iterator_tag;
      using value_type = T;
      using difference_type = std::ptrdiff_t;
      using pointer = T *;
      using reference = T &;

      explicit VectorIterator(T * ptr):
        ptr_(ptr)
      {}

      reference operator*() const noexcept
      {
        return *ptr_;
      }

      pointer operator->() const noexcept
      {
        return ptr_;
      }

      VectorIterator & operator++() noexcept
      {
        ++ptr_;
        return *this;
      }

      VectorIterator operator++(int) noexcept
      {
        VectorIterator tmp(*this);
        ++ptr_;
        return tmp;
      }

      VectorIterator & operator--() noexcept
      {
        --ptr_;
        return *this;
      }

      VectorIterator operator--(int) noexcept
      {
        VectorIterator tmp(*this);
        --ptr_;
        return tmp;
      }

      VectorIterator & operator+=(difference_type n) noexcept
      {
        ptr_ += n;
        return *this;
      }

      VectorIterator & operator-=(difference_type n) noexcept
      {
        ptr_ -= n;
        return *this;
      }

      VectorIterator operator+(difference_type n) const noexcept
      {
        return VectorIterator(ptr_ + n);
      }

      VectorIterator operator-(difference_type n) const noexcept
      {
        return VectorIterator(ptr_ - n);
      }

      difference_type operator-(const VectorIterator & rhs) const noexcept
      {
        return ptr_ - rhs.ptr_;
      }

      reference operator[](difference_type n) const noexcept
      {
        return ptr_[n];
      }

      bool operator==(const VectorIterator & rhs) const noexcept
      {
        return ptr_ == rhs.ptr_;
      }

      bool operator!=(const VectorIterator & rhs) const noexcept
      {
        return ptr_ != rhs.ptr_;
      }

      bool operator<(const VectorIterator & rhs) const noexcept
      {
        return ptr_ < rhs.ptr_;
      }

      bool operator>(const VectorIterator & rhs) const noexcept
      {
        return ptr_ > rhs.ptr_;
      }

      bool operator<=(const VectorIterator & rhs) const noexcept
      {
        return ptr_ <= rhs.ptr_;
      }

      bool operator>=(const VectorIterator & rhs) const noexcept
      {
        return ptr_ >= rhs.ptr_;
      }

    private:
      T * ptr_;
    };

    struct VectorConstIterator {
      using iterator_category = std::random_access_iterator_tag;
      using value_type = T;
      using difference_type = std::ptrdiff_t;
      using pointer = const T *;
      using reference = const T &;

      explicit VectorConstIterator(const T * ptr):
        ptr_(ptr)
      {}

      VectorConstIterator(VectorIterator it):
        ptr_(&(*it))
      {}

      reference operator*() const noexcept
      {
        return *ptr_;
      }

      pointer operator->() const noexcept
      {
        return ptr_;
      }

      VectorConstIterator & operator++() noexcept
      {
        ++ptr_;
        return *this;
      }

      VectorConstIterator operator++(int) noexcept
      {
        VectorConstIterator tmp(*this);
        ++ptr_;
        return tmp;
      }

      VectorConstIterator & operator--() noexcept
      {
        --ptr_;
        return *this;
      }

      VectorConstIterator operator--(int) noexcept
      {
        VectorConstIterator tmp(*this);
        --ptr_;
        return tmp;
      }

      VectorConstIterator & operator+=(difference_type n) noexcept
      {
        ptr_ += n;
        return *this;
      }

      VectorConstIterator & operator-=(difference_type n) noexcept
      {
        ptr_ -= n;
        return *this;
      }

      VectorConstIterator operator+(difference_type n) const noexcept
      {
        return VectorConstIterator(ptr_ + n);
      }

      VectorConstIterator operator-(difference_type n) const noexcept
      {
        return VectorConstIterator(ptr_ - n);
      }

      difference_type operator-(const VectorConstIterator & rhs) const noexcept
      {
        return ptr_ - rhs.ptr_;
      }

      reference operator[](difference_type n) const noexcept
      {
        return ptr_[n];
      }

      bool operator==(const VectorConstIterator & rhs) const noexcept
      {
        return ptr_ == rhs.ptr_;
      }

      bool operator!=(const VectorConstIterator & rhs) const noexcept
      {
        return ptr_ != rhs.ptr_;
      }

      bool operator<(const VectorConstIterator & rhs) const noexcept
      {
        return ptr_ < rhs.ptr_;
      }

      bool operator>(const VectorConstIterator & rhs) const noexcept
      {
        return ptr_ > rhs.ptr_;
      }

      bool operator<=(const VectorConstIterator & rhs) const noexcept
      {
        return ptr_ <= rhs.ptr_;
      }

      bool operator>=(const VectorConstIterator & rhs) const noexcept
      {
        return ptr_ >= rhs.ptr_;
      }

    private:
      const T * ptr_;
    };

    ~Vector();
    Vector();
    Vector(const Vector< T > & rhs);
    Vector(Vector< T > && rhs) noexcept;
    Vector(size_t size, const T & init);

    Vector< T > & operator=(const Vector< T > & rhs);
    Vector< T > & operator=(Vector< T > && rhs) noexcept;

    void swap(Vector< T > & rhs) noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    T & operator[](size_t id) noexcept;
    const T & operator[](size_t id) const noexcept;
    T & at(size_t id);
    const T & at(size_t id) const;

    VectorIterator begin() noexcept
    {
      return VectorIterator(data_);
    }

    VectorIterator end() noexcept
    {
      return VectorIterator(data_ + size_);
    }

    VectorConstIterator begin() const noexcept
    {
      return VectorConstIterator(data_);
    }

    VectorConstIterator end() const noexcept
    {
      return VectorConstIterator(data_ + size_);
    }

    VectorConstIterator cbegin() const noexcept
    {
      return VectorConstIterator(data_);
    }

    VectorConstIterator cend() const noexcept
    {
      return VectorConstIterator(data_ + size_);
    }

    void pushBack(const T & v);
    void popBack();

    void insert(size_t i, const T & v);
    void erase(size_t i);

    void insert(size_t i, const Vector< T > & rhs, size_t start, size_t end);
    void erase(size_t start, size_t end);

    template< class FwdIterator >
    void insert(VectorIterator pos, FwdIterator first, FwdIterator last);

  private:
    T * data_;
    size_t size_;
    size_t capacity_;

    explicit Vector(size_t size);
    void reallocate(size_t newCap);
  };

  template< class T >
  bool operator==(const Vector< T > & lhs, const Vector< T > & rhs);

}

template< class T >
topit::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

template< class T >
topit::Vector< T >::Vector(size_t size):
  data_(size ? new T[size] : nullptr),
  size_(size),
  capacity_(size)
{}

template< class T >
topit::Vector< T >::Vector(const Vector< T > & rhs):
  Vector(rhs.getSize())
{
  for (size_t i = 0; i < rhs.getSize(); ++i) {
    data_[i] = rhs[i];
  }
}

template< class T >
topit::Vector< T >::Vector(Vector< T > && rhs) noexcept:
  data_(rhs.data_),
  size_(rhs.size_),
  capacity_(rhs.capacity_)
{
  rhs.data_ = nullptr;
  rhs.size_ = 0;
  rhs.capacity_ = 0;
}

template< class T >
topit::Vector< T >::Vector(size_t size, const T & init):
  Vector(size)
{
  for (size_t i = 0; i < size; ++i) {
    data_[i] = init;
  }
}

template< class T >
topit::Vector< T >::~Vector()
{
  delete[] data_;
}

template< class T >
topit::Vector< T > & topit::Vector< T >::operator=(const Vector< T > & rhs)
{
  if (this != std::addressof(rhs)) {
    Vector< T > cpy(rhs);
    swap(cpy);
  }
  return *this;
}

template< class T >
topit::Vector< T > & topit::Vector< T >::operator=(Vector< T > && rhs) noexcept
{
  if (this != std::addressof(rhs)) {
    Vector< T > cpy(std::move(rhs));
    swap(cpy);
  }
  return *this;
}

template< class T >
void topit::Vector< T >::swap(Vector< T > & rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
}

template< class T >
bool topit::Vector< T >::isEmpty() const noexcept
{
  return size_ == 0;
}

template< class T >
size_t topit::Vector< T >::getSize() const noexcept
{
  return size_;
}

template< class T >
size_t topit::Vector< T >::getCapacity() const noexcept
{
  return capacity_;
}

template< class T >
T & topit::Vector< T >::operator[](size_t id) noexcept
{
  return const_cast< T & >(static_cast< const Vector< T > & >(*this)[id]);
}

template< class T >
const T & topit::Vector< T >::operator[](size_t id) const noexcept
{
  return data_[id];
}

template< class T >
T & topit::Vector< T >::at(size_t id)
{
  return const_cast< T & >(static_cast< const Vector< T > & >(*this).at(id));
}

template< class T >
const T & topit::Vector< T >::at(size_t id) const
{
  if (id >= size_) {
    throw std::out_of_range("bad id");
  }
  return data_[id];
}

template< class T >
void topit::Vector< T >::reallocate(size_t newCap)
{
  T * newData = new T[newCap];
  for (size_t i = 0; i < size_; ++i) {
    newData[i] = data_[i];
  }
  delete[] data_;
  data_ = newData;
  capacity_ = newCap;
}

template< class T >
void topit::Vector< T >::pushBack(const T & v)
{
  if (size_ == capacity_) {
    const size_t newCap = (capacity_ == 0) ? 1 : capacity_ * 2;
    reallocate(newCap);
  }
  data_[size_] = v;
  ++size_;
}

template< class T >
void topit::Vector< T >::popBack()
{
  if (size_) {
    --size_;
  }
}

template< class T >
void topit::Vector< T >::insert(size_t i, const T & v)
{
  if (i > size_) {
    throw std::out_of_range("insert: index out of range");
  }
  Vector< T > tmp(size_ + 1);
  for (size_t k = 0; k < i; ++k) {
    tmp.data_[k] = data_[k];
  }
  tmp.data_[i] = v;
  for (size_t k = i; k < size_; ++k) {
    tmp.data_[k + 1] = data_[k];
  }
  swap(tmp);
}

template< class T >
void topit::Vector< T >::erase(size_t i)
{
  if (i >= size_) {
    throw std::out_of_range("erase: index out of range");
  }
  Vector< T > tmp(size_ - 1);
  for (size_t k = 0; k < i; ++k) {
    tmp.data_[k] = data_[k];
  }
  for (size_t k = i + 1; k < size_; ++k) {
    tmp.data_[k - 1] = data_[k];
  }
  swap(tmp);
}

template< class T >
void topit::Vector< T >::insert(
  size_t i,
  const Vector< T > & rhs,
  size_t start,
  size_t end)
{
  if (i > size_) {
    throw std::out_of_range("insert range: position out of range");
  }
  if (start > end || end > rhs.getSize()) {
    throw std::out_of_range("insert range: bad source range");
  }
  const size_t count = end - start;
  if (count == 0) {
    return;
  }
  Vector< T > tmp(size_ + count);
  for (size_t k = 0; k < i; ++k) {
    tmp.data_[k] = data_[k];
  }
  for (size_t k = 0; k < count; ++k) {
    tmp.data_[i + k] = rhs[start + k];
  }
  for (size_t k = i; k < size_; ++k) {
    tmp.data_[k + count] = data_[k];
  }
  swap(tmp);
}

template< class T >
void topit::Vector< T >::erase(size_t start, size_t end)
{
  if (start > end || end > size_) {
    throw std::out_of_range("erase range: bad range");
  }
  const size_t count = end - start;
  if (count == 0) {
    return;
  }
  Vector< T > tmp(size_ - count);
  for (size_t k = 0; k < start; ++k) {
    tmp.data_[k] = data_[k];
  }
  for (size_t k = end; k < size_; ++k) {
    tmp.data_[k - count] = data_[k];
  }
  swap(tmp);
}

template< class T >
template< class FwdIterator >
void topit::Vector< T >::insert(VectorIterator pos, FwdIterator first, FwdIterator last)
{
  const size_t i = static_cast< size_t >(pos - begin());
  if (i > size_) {
    throw std::out_of_range("insert iterator: position out of range");
  }
  size_t count = 0;
  for (FwdIterator it = first; it != last; ++it) {
    ++count;
  }
  if (count == 0) {
    return;
  }
  Vector< T > tmp(size_ + count);
  for (size_t k = 0; k < i; ++k) {
    tmp.data_[k] = data_[k];
  }
  size_t j = 0;
  for (FwdIterator it = first; it != last; ++it, ++j) {
    tmp.data_[i + j] = *it;
  }
  for (size_t k = i; k < size_; ++k) {
    tmp.data_[k + count] = data_[k];
  }
  swap(tmp);
}

template< class T >
bool topit::operator==(const Vector< T > & lhs, const Vector< T > & rhs)
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
