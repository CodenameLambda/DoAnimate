template <typename I>
struct iterator_range {
    const I begin_iterator;
    const I end_iterator;

    iterator_range(const I begin_it, const I end_it)
    : begin_iterator(begin_it), end_iterator(end_it) {
    }

    template <typename J>
    iterator_range(const iterator_range<J> other)
    : begin_iterator(other.begin_iterator), end_iterator(end_iterator) {
    }

    I begin() const {
        return begin_iterator;
    }

    I end() const {
        return end_iterator;
    }
};


template <typename T>
struct numeric_range {
    const T start = 0;
    const T stop;
    const T step = 1;

    numeric_range(const T stop) : stop(stop) {
    }

    numeric_range(const T start, const T stop) : start(start), stop(stop) {
    }

    numeric_range(const T start, const T stop, const T step) : start(start), stop(stop), step(step) {
    }

    // TODO begin, end, rbegin, rend
};