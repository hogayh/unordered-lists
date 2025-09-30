#ifndef ARRAY_ADT_LIST_H
#define ARRAY_ADT_LIST_H

#include <cstddef>
#include <stdexcept>

/**
 * @brief Unordered list based on a contiguous array.
 * @tparam T element type
 */
template <typename T>
class ArrayADTList {
public:
    /**
     * @brief Forward iterator over the active portion of the array.
     */
    class Iterator {
    public:
        Iterator(T* cur, T* end) : cur_(cur), end_(end) {}
        T& operator*() const { if (cur_ >= end_) throw std::out_of_range("Iterator at end"); return *cur_; }
        Iterator& operator++() { if (cur_ < end_) ++cur_; return *this; }
        bool operator==(const Iterator& rhs) const { return cur_ == rhs.cur_; }
        bool operator!=(const Iterator& rhs) const { return !(*this == rhs); }
    private:
        T* cur_;
        T* end_;
    };

    /// Default capacity = 1000 to keep it simple for the lab.
    ArrayADTList() : items_(new T[1000]), length_(0), capacity_(1000) {}
    explicit ArrayADTList(std::size_t cap) : items_(new T[cap]), length_(0), capacity_(cap) {}
    ~ArrayADTList() { delete[] items_; }

    /// @return number of items currently stored.
    int  getLength() const { return static_cast<int>(length_); }
    /// @return true if length == capacity.
    bool isFull()   const { return length_ >= capacity_; }
    /// Makes the list logically empty (does not shrink capacity).
    void makeEmpty()      { length_ = 0; }

    /**
     * @brief Insert item at the end (unordered). Throws if full.
     */
    void putItem(const T& item) {
        if (isFull()) throw std::overflow_error("ArrayADTList is full");
        items_[length_++] = item;
    }

    /**
     * @brief Find key and copy into found_item.
     * @return true if found.
     */
    bool getItem(const T& key, T& found_item) const {
        for (std::size_t i = 0; i < length_; ++i) {
            if (items_[i] == key) { found_item = items_[i]; return true; }
        }
        return false;
    }

    /**
     * @brief Compatibility overload: (key, bool& found). Returns same as found.
     */
    bool getItem(const T& key, bool& found) const {
        for (std::size_t i = 0; i < length_; ++i) {
            if (items_[i] == key) { found = true; return true; }
        }
        found = false; return false;
    }

    /**
     * @brief Delete first occurrence by swapping with last (O(1) after find).
     * @return true if an element was removed.
     */
    bool deleteItem(const T& key) {
        for (std::size_t i = 0; i < length_; ++i) {
            if (items_[i] == key) {
                items_[i] = items_[length_ - 1];
                --length_;
                return true;
            }
        }
        return false;
    }

    /// STL-like iteration
    Iterator begin() { return Iterator(items_, items_ + length_); }
    Iterator end()   { return Iterator(items_ + length_, items_ + length_); }
    Iterator begin() const { return Iterator(items_, items_ + length_); }
    Iterator end()   const { return Iterator(items_ + length_, items_ + length_); }

private:
    T* items_;
    std::size_t length_;
    std::size_t capacity_;
};

#endif // ARRAY_ADT_LIST_H
