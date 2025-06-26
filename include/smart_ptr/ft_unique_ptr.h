#ifndef  __FT_UNIQUE_PTR__
# define __FT_UNIQUE_PTR__

# include <utility> // For std::move, std::exchange
# include <cstddef> // For std::nullptr_t
# include <ostream> // For std::ostream, std::ostream& operator<<

namespace ft {
    // Default Deleter for unique_ptr
    template <typename T>
    struct DefaultDeleter {
        constexpr void operator()(T* ptr) const noexcept{
            delete ptr;
        }
    };
    // Specialization for arrays
    template <typename T>
    struct DefaultDeleter<T[]> {
        constexpr void operator()(T* ptr) const noexcept{
            delete[] ptr;
        }
    };

    // Base class for unique_ptr
    template <typename T, typename Deleter = DefaultDeleter<T>>
    class base_unique_ptr {
        public:
        // Type definitions
            using pointer      = T*;
            using element_type = T ;
            using deleter_type = Deleter;
        
        public:
            // Default constructor
            constexpr base_unique_ptr() noexcept : _ptr { nullptr }, _deleter() { }
            // Constructor with pointer
            constexpr explicit base_unique_ptr(pointer ptr) noexcept
                : _ptr { ptr }, _deleter() { }
            // Constructor with pointer and custom deleter
            constexpr base_unique_ptr(pointer ptr, const deleter_type& deleter) noexcept
                : _ptr { ptr }, _deleter { std::move(deleter) } { }
            // Move constructor
            constexpr base_unique_ptr(base_unique_ptr&& other) noexcept
                : _ptr { other._ptr }, _deleter { std::move(other._deleter) }
            { other._ptr = nullptr; }
            // Move assignment operator
            constexpr base_unique_ptr& operator=(base_unique_ptr&& other) noexcept {
                if ( this == &other ) {
                    return *this;
                }

                if ( _ptr ) {
                    _deleter(_ptr);
                }
                _ptr = other._ptr;
                _deleter = std::move(other._deleter);
                other._ptr = nullptr;
                return *this;
            }
            // Destructor
            constexpr ~base_unique_ptr() noexcept {
                if ( _ptr ) {
                    _deleter(_ptr);
                }
            }

            // Delete copy constructor and assignment operator
            base_unique_ptr(const base_unique_ptr&) = delete;
            base_unique_ptr& operator=(const base_unique_ptr&) = delete;

            // Assignment operator for nullptr
            constexpr base_unique_ptr& operator=(std::nullptr_t) noexcept {
                if ( _ptr ) {
                    _deleter(_ptr);
                }
                _ptr = nullptr;
                return *this;
            }

        public:
            // Check if the pointer is not null
            constexpr explicit operator bool() const noexcept {
                return _ptr != nullptr;
            }

            // Swap function
            constexpr void swap(base_unique_ptr& other) noexcept {
                using std::swap;
                swap(_ptr, other._ptr);
                swap(_deleter, other._deleter);
            }

            // Release the ownership of the pointer
            constexpr pointer release() noexcept {
                return std::exchange(_ptr, nullptr);
            }

            // Reset the pointer and delete the managed object
            constexpr void reset(pointer ptr = nullptr) noexcept {
                if ( _ptr ) {
                    __deleter(_ptr);
                }
                _ptr = ptr;
            }
        public:
            // Get the raw pointer
            constexpr pointer get() const noexcept {
                return _ptr;
            }

            // Get the deleter
            constexpr deleter_type& get_deleter() noexcept {
                return _deleter;
            }

            // Get the deleter (const version)
            constexpr const deleter_type& get_deleter() const noexcept {
                return _deleter;
            }


        protected:
            // Pointer to the managed object
            pointer      _ptr;
            // Deleter for the managed object
            deleter_type _deleter;

    };

    // Unique pointer class
    template <typename T, typename Deleter = DefaultDeleter<T>>
    // unique_ptr class derived from base_unique_ptr
    class unique_ptr : public base_unique_ptr<T, Deleter> {
        public:
            // Type definitions
            using pointer      = typename base_unique_ptr<T, Deleter>::pointer;
            using element_type = typename base_unique_ptr<T, Deleter>::element_type;
            using deleter_type = typename base_unique_ptr<T, Deleter>::deleter_type;
        
        public:
            // Inherit constructors and assignment operators from base_unique_ptr
            using base_unique_ptr<T, Deleter>::base_unique_ptr;
            using base_unique_ptr<T, Deleter>::operator=;

        public:
            // Template specialization

            // Overload operator-> to provide access to the managed object
            pointer operator->() const noexcept {
                return this->_ptr;
            }

            // Overload operator* to dereference the managed object
            element_type& operator*() const noexcept {
                return *(this->_ptr);
            }
    };

    template <typename T, typename Deleter>
    class unique_ptr<T[], Deleter> : public base_unique_ptr<T, Deleter> {
        public:
            // Type definitions
            using pointer      = typename base_unique_ptr<T, Deleter>::pointer;
            using element_type = typename base_unique_ptr<T, Deleter>::element_type;
            using deleter_type = typename base_unique_ptr<T, Deleter>::deleter_type;

        public:
            // Inherit constructors and assignment operators from base_unique_ptr
            using base_unique_ptr<T, Deleter>::base_unique_ptr;
            using base_unique_ptr<T, Deleter>::operator=;

        public:
            // Overload operator[] to access elements of the array
            element_type& operator[](std::size_t index) const noexcept {
                return this->_ptr[index];
            }
    };

} // namespace ft

// Swap function for unique_ptr
template <typename T, typename Deleter>
constexpr void swap(ft::unique_ptr<T, Deleter>& lhs, ft::unique_ptr<T, Deleter>& rhs) noexcept {
    lhs.swap(rhs);
}

// Boolean operator for unique_ptr
template <typename T1, typename D1, typename T2, typename D2>
constexpr bool operator==(const ft::unique_ptr<T1, D1>& lhs,
                          const ft::unique_ptr<T2, D2>& rhs) noexcept {
    return lhs.get() == rhs.get();
}
template <typename T1, typename D1, typename T2, typename D2>
constexpr bool operator!=(const ft::unique_ptr<T1, D1>& lhs,
                          const ft::unique_ptr<T2, D2>& rhs) noexcept {
    return !(lhs == rhs);
}
template <typename T1, typename D1, typename T2, typename D2>
constexpr bool operator<(const ft::unique_ptr<T1, D1>& lhs,
                         const ft::unique_ptr<T2, D2>& rhs) noexcept {
    return lhs.get() < rhs.get();
}
template <typename T1, typename D1, typename T2, typename D2>
constexpr bool operator<=(const ft::unique_ptr<T1, D1>& lhs,
                          const ft::unique_ptr<T2, D2>& rhs) noexcept {
    return !(rhs < lhs);
}
template <typename T1, typename D1, typename T2, typename D2>
constexpr bool operator>(const ft::unique_ptr<T1, D1>& lhs,
                         const ft::unique_ptr<T2, D2>& rhs) noexcept {
    return rhs < lhs;
}
template <typename T1, typename D1, typename T2, typename D2>
constexpr bool operator>=(const ft::unique_ptr<T1, D1>& lhs,
                          const ft::unique_ptr<T2, D2>& rhs) noexcept {
    return !(lhs < rhs);
}

// Output stream operator for unique_ptr
template <typename T, typename Deleter>
std::ostream& operator<<(std::ostream& os, const ft::unique_ptr<T, Deleter>& ptr) {
    if ( ptr ) {
        os << ptr->get();
    }
}

#endif// __FT_UNIQUE_PTR__