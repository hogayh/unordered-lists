/**
 * @file ArrayADTList.h
 * @brief Array-based ADT list with Rule-of-Three and iterators.
 */
#ifndef ARRAY_ADT_LIST_H
#define ARRAY_ADT_LIST_H

#include <cstddef>
#include <stdexcept>
#include <algorithm> // std::copy

template <typename T>
class ArrayADTList {
private:
    T*          items_;
    std::size_t length_;
    std::size_t capacity_;

public:
    // ---------- Iterator -----------
    class Iterator {
        T* cur_;
        T* end_;
    public:
        Iterator(T* cur, T* end) : cur_(cur), end_(end) {}
        T& operator*() const {
            if (cur_ >= end_) throw std::out_of_range("Iterator at end");
            return *cur_;
        }
        Iterator& operator++() { if (cur_ < end_) ++cur_; return *this; }
        bool operator==(const Iterator& rhs) const { return cur_ == rhs.cur_; }
        bool operator!=(const Iterator& rhs) const { return !(*this == rhs); }
    };

    // ---------- Ctors / dtor / assignment (Rule of 3) ----------
    ArrayADTList() : items_(new T[1000]), length_(0), capacity_(1000) {}
    explicit ArrayADTList(std::size_t cap)
        : items_(new T[cap]), length_(0), capacity_(cap) {}

    ArrayADTList(const ArrayADTList& other)
        : items_(new T[other.capacity_]),
          length_(other.length_),
          capacity_(other.capacity_) {
        std::copy(other.items_, other.items_ + length_, items_);
    }

    ArrayADTList& operator=(const ArrayADTList& other) {
        if (this != &other) {
            T* newItems = new T[other.capacity_];
            std::copy(other.items_, other.items_ + other.length_, newItems);
            delete[] items_;
            items_   = newItems;
            length_  = other.length_;
            capacity_= other.capacity_;
        }
        return *this;
    }

    ~ArrayADTList() { delete[] items_; }

    // ---------- Basic ops ----------
    void makeEmpty() { length_ = 0; }

    bool isFull() const { return length_ >= capacity_; }

    int getLength() const { return static_cast<int>(length_); }

    void putItem(const T& item) {
        if (isFull()) throw std::overflow_error("ArrayADTList is full");
        items_[length_++] = item;
    }

    // Remove first occurrence of key, keep order (shift-left)
    bool deleteItem(const T& key) {
        for (std::size_t i = 0; i < length_; ++i) {
            if (items_[i] == key) {
                for (std::size_t j = i + 1; j < length_; ++j)
                    items_[j - 1] = items_[j];
                --length_;
                return true;
            }
        }
        return false;
    }

    // Lookup by key; if found, write value to found_item and return true
    bool getItem(const T& key, T& found_item) const {
        for (std::size_t i = 0; i < length_; ++i) {
            if (items_[i] == key) { found_item = items_[i]; return true; }
        }
        return false;
    }

    // ---------- Iteration ----------
    Iterator begin() { return Iterator(items_, items_ + length_); }
    Iterator end()   { return Iterator(items_ + length_, items_ + length_); }
    Iterator begin() const { return Iterator(items_, items_ + length_); }
    Iterator end()   const { return Iterator(items_ + length_, items_ + length_); }
};

#endif // ARRAY_ADT_LIST_H
