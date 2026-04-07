#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP

#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <iterator>

namespace topit {

template <class T>
class Vector {
public:
    //(ДЗ)
    struct Iterator {
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit Iterator(pointer ptr) noexcept : ptr_(ptr) {}

        reference operator*() const noexcept { return *ptr_; }
        pointer operator->() const noexcept { return ptr_; }

        Iterator& operator++() noexcept {
            ++ptr_;
            return *this;
        }

        Iterator operator++(int) noexcept {
            Iterator tmp(*this);
            ++ptr_;
            return tmp;
        }

        Iterator& operator--() noexcept {
            --ptr_;
            return *this;
        }

        Iterator operator--(int) noexcept {
            Iterator tmp(*this);
            --ptr_;
            return tmp;
        }

        Iterator& operator+=(difference_type n) noexcept {
            ptr_ += n;
            return *this;
        }

        Iterator& operator-=(difference_type n) noexcept {
            ptr_ -= n;
            return *this;
        }

        Iterator operator+(difference_type n) const noexcept {
            return Iterator(ptr_ + n);
        }

        Iterator operator-(difference_type n) const noexcept {
            return Iterator(ptr_ - n);
        }

        difference_type operator-(const Iterator& rhs) const noexcept {
            return ptr_ - rhs.ptr_;
        }

        reference operator[](difference_type n) const noexcept {
            return ptr_[n];
        }

        bool operator==(const Iterator& rhs) const noexcept {
            return ptr_ == rhs.ptr_;
        }

        bool operator!=(const Iterator& rhs) const noexcept {
            return ptr_ != rhs.ptr_;
        }

        bool operator<(const Iterator& rhs) const noexcept {
            return ptr_ < rhs.ptr_;
        }

        bool operator>(const Iterator& rhs) const noexcept {
            return ptr_ > rhs.ptr_;
        }

        bool operator<=(const Iterator& rhs) const noexcept {
            return ptr_ <= rhs.ptr_;
        }

        bool operator>=(const Iterator& rhs) const noexcept {
            return ptr_ >= rhs.ptr_;
        }

    private:
        pointer ptr_;
    };

    struct ConstIterator {
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        explicit ConstIterator(pointer ptr) noexcept : ptr_(ptr) {}
        ConstIterator(const Iterator& it) noexcept : ptr_(&(*it)) {}

        reference operator*() const noexcept { return *ptr_; }
        pointer operator->() const noexcept { return ptr_; }

        ConstIterator& operator++() noexcept {
            ++ptr_;
            return *this;
        }

        ConstIterator operator++(int) noexcept {
            ConstIterator tmp(*this);
            ++ptr_;
            return tmp;
        }

        ConstIterator& operator--() noexcept {
            --ptr_;
            return *this;
        }

        ConstIterator operator--(int) noexcept {
            ConstIterator tmp(*this);
            --ptr_;
            return tmp;
        }

        ConstIterator& operator+=(difference_type n) noexcept {
            ptr_ += n;
            return *this;
        }

        ConstIterator& operator-=(difference_type n) noexcept {
            ptr_ -= n;
            return *this;
        }

        ConstIterator operator+(difference_type n) const noexcept {
            return ConstIterator(ptr_ + n);
        }

        ConstIterator operator-(difference_type n) const noexcept {
            return ConstIterator(ptr_ - n);
        }

        difference_type operator-(const ConstIterator& rhs) const noexcept {
            return ptr_ - rhs.ptr_;
        }

        reference operator[](difference_type n) const noexcept {
            return ptr_[n];
        }

        bool operator==(const ConstIterator& rhs) const noexcept {
            return ptr_ == rhs.ptr_;
        }

        bool operator!=(const ConstIterator& rhs) const noexcept {
            return ptr_ != rhs.ptr_;
        }

        bool operator<(const ConstIterator& rhs) const noexcept {
            return ptr_ < rhs.ptr_;
        }

        bool operator>(const ConstIterator& rhs) const noexcept {
            return ptr_ > rhs.ptr_;
        }

        bool operator<=(const ConstIterator& rhs) const noexcept {
            return ptr_ <= rhs.ptr_;
        }

        bool operator>=(const ConstIterator& rhs) const noexcept {
            return ptr_ >= rhs.ptr_;
        }

    private:
        pointer ptr_;
    };

    using iterator = Iterator;
    using const_iterator = ConstIterator;

    // ============== ОСНОВНЫЕ МЕТОДЫ ==============
    ~Vector();
    Vector();
    Vector(const Vector& rhs);
    Vector(Vector&& rhs) noexcept;
    explicit Vector(size_t size);
    Vector(size_t size, const T& init);
    Vector(std::initializer_list<T> il);  // КЛАССНАЯ РАБОТА

    Vector& operator=(const Vector& rhs);
    Vector& operator=(Vector&& rhs) noexcept;

    void swap(Vector& rhs) noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    // КЛАССНАЯ РАБОТА
    void reserve(size_t required);
    void shrinkToFit();

   
    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;

   
    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

   
    void pushBack(const T& v);
    void pushBackCount(size_t k, const T& v);  // КЛАССНАЯ РАБОТА
    template <class IT>
    void pushBackRange(IT b, size_t c);        // КЛАССНАЯ РАБОТА
    void popBack();

    void insert(size_t i, const T& v);         // КЛАССНАЯ РАБОТА
    void erase(size_t i);                      // КЛАССНАЯ РАБОТА

    //  МЕТОДЫ РАБОТЫ С ДИАПАЗОНАМИ (КЛАССНАЯ РАБОТА) 
    void insert(size_t i, const Vector& rhs, size_t start, size_t end);
    void erase(size_t start, size_t end);

    //  ИТЕРАТОРНЫЙ INSERT (ДЗ) 
    template <class FwdIterator>
    void insert(iterator pos, FwdIterator first, FwdIterator last);

private:
    T* data_;
    size_t size_;
    size_t capacity_;

    void rangeCheck(size_t id) const;
    void reallocate(size_t newCap);
    void unsafePushBack(const T& v);
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

// КЛАССНАЯ РАБОТА
template <class T>
topit::Vector<T>::Vector(std::initializer_list<T> il)
    : Vector(il.size())
{
    size_t i = 0;
    for (const T& val : il) {
        data_[i++] = val;
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

// КЛАССНАЯ РАБОТА
template <class T>
void topit::Vector<T>::reserve(size_t required)
{
    if (required > capacity_) {
        reallocate(required);
    }
}

// КЛАССНАЯ РАБОТА
template <class T>
void topit::Vector<T>::shrinkToFit()
{
    if (size_ < capacity_) {
        reallocate(size_);
    }
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

// ВСПОМОГАТЕЛЬНЫЙ МЕТОД
template <class T>
void topit::Vector<T>::reallocate(size_t newCap)
{
    T* newData = new T[newCap];
    size_t i = 0;
    try {
        for (; i < size_; ++i) {
            newData[i] = std::move(data_[i]);
        }
    } catch (...) {
        for (size_t j = 0; j < i; ++j) {
            newData[j].~T();
        }
        delete[] newData;
        throw;
    }
    delete[] data_;
    data_ = newData;
    capacity_ = newCap;
}

// ВСПОМОГАТЕЛЬНЫЙ МЕТОД
template <class T>
void topit::Vector<T>::unsafePushBack(const T& v)
{
    data_[size_] = v;
    ++size_;
}

template <class T>
void topit::Vector<T>::pushBack(const T& v)
{
    if (size_ == capacity_) {
        size_t newCap = (capacity_ == 0) ? 1 : capacity_ * 2;
        reserve(newCap);
    }
    unsafePushBack(v);
}

// КЛАССНАЯ РАБОТА
template <class T>
void topit::Vector<T>::pushBackCount(size_t k, const T& v)
{
    if (k == 0) return;
    
    size_t newSize = size_ + k;
    if (newSize > capacity_) {
        size_t newCap = capacity_ == 0 ? 1 : capacity_;
        while (newCap < newSize) {
            newCap *= 2;
        }
        reserve(newCap);
    }
    
    for (size_t i = 0; i < k; ++i) {
        unsafePushBack(v);
    }
}

// КЛАССНАЯ РАБОТА
template <class T>
template <class IT>
void topit::Vector<T>::pushBackRange(IT b, size_t c)
{
    if (c == 0) return;
    
    size_t newSize = size_ + c;
    if (newSize > capacity_) {
        size_t newCap = capacity_ == 0 ? 1 : capacity_;
        while (newCap < newSize) {
            newCap *= 2;
        }
        reserve(newCap);
    }
    
    for (size_t i = 0; i < c; ++i) {
        unsafePushBack(*(b + i));
    }
}

template <class T>
void topit::Vector<T>::popBack()
{
    if (size_ > 0) {
        --size_;
    }
}

// КЛАССНАЯ РАБОТА
template <class T>
void topit::Vector<T>::insert(size_t i, const T& v)
{
    if (i > size_) {
        throw std::out_of_range("Vector::insert: index out of range");
    }
    if (size_ == capacity_) {
        size_t newCap = (capacity_ == 0) ? 1 : capacity_ * 2;
        reserve(newCap);
    }
    for (size_t k = size_; k > i; --k) {
        data_[k] = std::move(data_[k - 1]);
    }
    data_[i] = v;
    ++size_;
}

// КЛАССНАЯ РАБОТА
template <class T>
void topit::Vector<T>::erase(size_t i)
{
    rangeCheck(i);
    for (size_t k = i; k < size_ - 1; ++k) {
        data_[k] = std::move(data_[k + 1]);
    }
    --size_;
}

// ДЗ
template <class T>
typename topit::Vector<T>::iterator topit::Vector<T>::begin() noexcept
{
    return iterator(data_);
}

// ДЗ
template <class T>
typename topit::Vector<T>::iterator topit::Vector<T>::end() noexcept
{
    return iterator(data_ + size_);
}

// ДЗ
template <class T>
typename topit::Vector<T>::const_iterator topit::Vector<T>::begin() const noexcept
{
    return const_iterator(data_);
}

// ДЗ
template <class T>
typename topit::Vector<T>::const_iterator topit::Vector<T>::end() const noexcept
{
    return const_iterator(data_ + size_);
}

// ДЗ
template <class T>
typename topit::Vector<T>::const_iterator topit::Vector<T>::cbegin() const noexcept
{
    return const_iterator(data_);
}

// ДЗ
template <class T>
typename topit::Vector<T>::const_iterator topit::Vector<T>::cend() const noexcept
{
    return const_iterator(data_ + size_);
}

// КЛАССНАЯ РАБОТА
template <class T>
void topit::Vector<T>::insert(size_t i, const Vector& rhs, size_t start, size_t end)
{
    if (i > size_) {
        throw std::out_of_range("Vector::insert range: position out of range");
    }
    if (start > end || end > rhs.size_) {
        throw std::out_of_range("Vector::insert range: bad source range");
    }
    size_t count = end - start;
    if (count == 0) {
        return;
    }

    Vector tmp(size_ + count);
    for (size_t k = 0; k < i; ++k) {
        tmp.data_[k] = std::move(data_[k]);
    }
    for (size_t k = 0; k < count; ++k) {
        tmp.data_[i + k] = rhs.data_[start + k];
    }
    for (size_t k = i; k < size_; ++k) {
        tmp.data_[k + count] = std::move(data_[k]);
    }
    swap(tmp);
}

// КЛАССНАЯ РАБОТА
template <class T>
void topit::Vector<T>::erase(size_t start, size_t end)
{
    if (start > end || end > size_) {
        throw std::out_of_range("Vector::erase range: bad range");
    }
    size_t count = end - start;
    if (count == 0) {
        return;
    }
    for (size_t k = end; k < size_; ++k) {
        data_[k - count] = std::move(data_[k]);
    }
    size_ -= count;
}

// ДЗ
template <class T>
template <class FwdIterator>
void topit::Vector<T>::insert(iterator pos, FwdIterator first, FwdIterator last)
{
    size_t index = static_cast<size_t>(pos - begin());
    if (index > size_) {
        throw std::out_of_range("Vector::insert iterator: position out of range");
    }
    size_t count = static_cast<size_t>(std::distance(first, last));
    if (count == 0) {
        return;
    }

    Vector tmp(size_ + count);
    for (size_t k = 0; k < index; ++k) {
        tmp.data_[k] = std::move(data_[k]);
    }
    size_t j = index;
    for (FwdIterator it = first; it != last; ++it, ++j) {
        tmp.data_[j] = *it;
    }
    for (size_t k = index; k < size_; ++k, ++j) {
        tmp.data_[j] = std::move(data_[k]);
    }
    swap(tmp);
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
