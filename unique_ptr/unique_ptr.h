#ifndef  __UNIQUE_PTR__
# define __UNIQUE_PTR__

#include <type_traits>

namespace cxx {
    /// Primary template of default_delete, used by unique_ptr for single objects
    template <typename _Tp>
        struct default_delete
        {
            /// Default constructor
            constexpr default_delete() noexcept = default;

            /// Allows conversion from a deleter for object of another type,
            /// Only if '_Up*' is convertible to '_Tp*'
            template <
                typename _Up,
                typename = std::enable_if_t< std::is_convertible_v<_Up*, _Tp*> >
                    >
                    constexpr
                    default_delete(const default_delete<_Up>&) noexcept {   }

            /// Calls 'delete __ptr'
            constexpr void
            operator()(_Tp* __ptr)
            {
                delete __ptr;
                __ptr = nullptr;
            }
        };

    /// unique_ptr for single objects
    /// A move-only smart pointer that manages unique ownership of a resource
    template < typename _Tp, typename _Dp = default_delete<_Tp> >
        class unique_ptr
        {
        };
} // end namespace

#endif // end __UNIQUE_PTR__
