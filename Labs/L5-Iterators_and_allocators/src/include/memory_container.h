#ifndef MEMORY_CONTAINER_H
#define MEMORY_CONTAINER_H

#include <memory_resource>
#include <list>
#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <iterator>

struct MemoryBlock {
    void* ptr;
    size_t size;
    bool is_free;
};

class fixed_memory_resource : public std::pmr::memory_resource {
    char* buffer_;
    size_t buffer_size_;
    std::list<MemoryBlock> blocks_;

public:
    explicit fixed_memory_resource(size_t size);
    ~fixed_memory_resource();

private:
    void* do_allocate(size_t bytes, size_t alignment) override;
    void do_deallocate(void* p, size_t bytes, size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;
};

template<typename T>
class dynamic_array {
public:
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator(pointer ptr) : ptr_(ptr) {}

        reference operator*() { return *ptr_; }
        pointer operator->() { return ptr_; }

        iterator& operator++() {
            ++ptr_;
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++ptr_;
            return tmp;
        }

        bool operator==(const iterator& other) const {
            return ptr_ == other.ptr_;
        }

        bool operator!=(const iterator& other) const {
            return ptr_ != other.ptr_;
        }

    private:
        pointer ptr_;
    };

    using allocator_type = std::pmr::polymorphic_allocator<T>;

    explicit dynamic_array(std::pmr::memory_resource* resource = nullptr)
        : size_(0), capacity_(0), data_(nullptr), alloc_(resource) {}

    ~dynamic_array() {
        clear();
        alloc_.deallocate(data_, capacity_);
    }

    void push_back(const T& value) {
        if (size_ == capacity_) {
            size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
            T* new_data = alloc_.allocate(new_capacity);

            for (size_t i = 0; i < size_; ++i) {
                std::allocator_traits<allocator_type>::construct(alloc_, &new_data[i], data_[i]);
                std::allocator_traits<allocator_type>::destroy(alloc_, &data_[i]);
            }

            if (data_) {
                alloc_.deallocate(data_, capacity_);
            }

            data_ = new_data;
            capacity_ = new_capacity;
        }

        std::allocator_traits<allocator_type>::construct(alloc_, &data_[size_], value);
        ++size_;
    }

    void pop_back() {
        if (size_ > 0) {
            std::allocator_traits<allocator_type>::destroy(alloc_, &data_[--size_]);
        }
    }

    void clear() {
        for (size_t i = 0; i < size_; ++i) {
            std::allocator_traits<allocator_type>::destroy(alloc_, &data_[i]);
        }
        size_ = 0;
    }

    size_t size() const { return size_; }
    iterator begin() { return iterator(data_); }
    iterator end() { return iterator(data_ + size_); }

private:
    T* data_;
    size_t size_;
    size_t capacity_;
    allocator_type alloc_;
};

#endif // MEMORY_CONTAINER_H
