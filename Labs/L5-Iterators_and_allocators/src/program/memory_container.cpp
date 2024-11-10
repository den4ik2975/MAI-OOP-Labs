#include "memory_container.h"

fixed_memory_resource::fixed_memory_resource(size_t size)
    : buffer_size_(size) {
    buffer_ = new char[size];
    blocks_.push_back({buffer_, size, true});
}

fixed_memory_resource::~fixed_memory_resource() {
    delete[] buffer_;
}

void* fixed_memory_resource::do_allocate(size_t bytes, size_t alignment) {
    for (auto& block : blocks_) {
        if (block.is_free && block.size >= bytes) {
            block.is_free = false;
            if (block.size > bytes) {
                blocks_.insert(std::next(blocks_.begin()),
                    {static_cast<char*>(block.ptr) + bytes,
                     block.size - bytes,
                     true});
                block.size = bytes;
            }
            return block.ptr;
        }
    }
    throw std::bad_alloc();
}

void fixed_memory_resource::do_deallocate(void* p, size_t bytes, size_t alignment) {
    for (auto it = blocks_.begin(); it != blocks_.end(); ++it) {
        if (it->ptr == p) {
            it->is_free = true;
            // Merge with next block if free
            auto next = std::next(it);
            if (next != blocks_.end() && next->is_free) {
                it->size += next->size;
                blocks_.erase(next);
            }
            // Merge with previous block if free
            if (it != blocks_.begin()) {
                auto prev = std::prev(it);
                if (prev->is_free) {
                    prev->size += it->size;
                    blocks_.erase(it);
                }
            }
            return;
        }
    }
}

bool fixed_memory_resource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}
