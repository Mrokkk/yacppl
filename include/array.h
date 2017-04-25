#pragma once

#include <cstddef>
#include "iterator.h"
#include "initializer_list.h"

namespace yacppl {

template<typename Type, size_t _size = 0>
class array {

    template <bool is_const>
    using detail_iterator = pointer_iterator<Type, is_const>;

    Type array_[_size];

public:

    using iterator = detail_iterator<false>;
    using const_iterator = detail_iterator<true>;

    array() = default;

    array(const std::initializer_list<Type> &list) {
        unsigned i = 0;
        for (const auto &v : list) {
            array_[i++] = v;
        }
    }

    template <typename Container>
    array(const Container &container) {
        unsigned i = 0;
        for (const auto &v : container) {
            array_[i++] = v;
        }
    }

    size_t size() const {
        return _size;
    }

    Type &operator[](int index) {
        return array_[index];
    }

    iterator begin() {
        return iterator(array_);
    }

    const_iterator begin() const {
        return const_iterator(array_);
    }

    const_iterator end() const {
        return const_iterator(array_ + _size);
    }

    const_iterator cbegin() const {
        return const_iterator(array_);
    }

    iterator end() {
        return iterator(array_ + _size);
    }

    const_iterator cend() const {
        return const_iterator(array_ + _size);
    }

    Type *data() {
        return array_;
    }

};

} // namespace yacppl

