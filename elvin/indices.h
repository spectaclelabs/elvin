#ifndef ELVIN_INDICES_H
#define ELVIN_INDICES_H

namespace elvin {

template <std::size_t... Is>
struct Indices {
    using next = Indices<Is..., sizeof...(Is)>;
};

template <std::size_t N>
struct IndexBuilder {
    using type = typename IndexBuilder<N-1>::type::next;
};

template <>
struct IndexBuilder<0> {
    using type = Indices<>;
};

}

#endif
