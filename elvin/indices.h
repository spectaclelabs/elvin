#ifndef INDICES_H
#define INDICES_H

namespace elvin {

// Here be dragons
// Variadic template magic thanks to Martinho Fernandes
// Taken from http://stackoverflow.com/q/10929202#10930078
template <std::size_t... Indices>
struct indices {
    using next = indices<Indices..., sizeof...(Indices)>;
};

template <std::size_t N>
struct build_indices {
    using type = typename build_indices<N-1>::type::next;
};

template <>
struct build_indices<0> {
    using type = indices<>;
};

template <std::size_t N>
using BuildIndices = typename build_indices<N>::type;

}

#endif
