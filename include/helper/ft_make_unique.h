#ifndef  __FT_MAKE_UNIQUE__
# define __FT_MAKE_UNIQUE__

# include <cstddef>     // For std::size_t
# include <utility>     // For std::forward
# include <type_traits> // For std::remove_extent_t
# include <memory>      // For std::is_array_v, std::is_unbounded_array_v
# include <concepts>    // For concepts

# include "ft_unique_ptr.h" // For ft::unique_ptr

namespace ft {

    // ============================
    // Concepts
    // ============================
    template <typename T>
    concept NonArray = !std::is_array_v<T>;

    template <typename T>
    concept UnboundedArray = std::is_unbounded_array_v<T>;

    // ============================
    // Single object version
    // ============================
    template <NonArray T, typename... Args>
    constexpr unique_ptr<T> make_unique(Args&&... args) {
        return unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

    // ============================
    // Dynamic array version (T[])
    // ============================
    template <UnboundedArray T>
    constexpr unique_ptr<T> make_unique(std::size_t n) {
        using U = std::remove_extent_t<T>;
        return unique_ptr<T>(new U[n]());
    }

} // namespace ft

#endif// __FT_MAKE_UNIQUE__