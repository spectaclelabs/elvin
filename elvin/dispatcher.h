#ifndef ELVIN_DISPATCHER_H
#define ELVIN_DISPATCHER_H

#include <functional>
#include "indices.h"

namespace elvin {

// Dispatcher for unpacking vectors into functions.
// Modified from http://stackoverflow.com/a/14663637

template<typename IterableType, typename ReturnType, typename... Args>
struct Dispatcher {

    template<typename FunctionType>
    Dispatcher(FunctionType function) : function(function) {}

    // The call operator which performs the dispatch
    ReturnType operator () (const IterableType& iterable) {
        if (iterable.size() != sizeof...(Args)) {
            // Wrong number of arguments provided!
            return;
        }

        // Delegates to internal function call: needed for deducing
        // a sequence of integers to be used for unpacking.
        return call(iterable, BuildIndices<sizeof...(Args)>{});
    }

private:

    // The heart of the dispatching mechanism
    template<size_t... Indices>
    ReturnType call(const IterableType& iterable, indices<Indices...>) {
        return function(iterable[Indices]...);
    }

    // Wrapper that holds the function to be invoked.
    std::function<ReturnType(Args...)> function;
};

// Helper function
template<typename IterableType, typename ReturnType, typename... Args>
std::function<ReturnType (const IterableType&)> make_dispatcher(ReturnType (*function)(Args...)) {
    Dispatcher<IterableType, ReturnType, Args...> dispatcher(function);
    return dispatcher;
}

}

#endif
