#pragma once

#include <string>
#include <string_view>

namespace sdbusplus
{

namespace message
{

namespace details
{

/** Simple wrapper class for std::string to allow conversion to and from an
 *  alternative typename. */
struct string_wrapper
{
    std::string str;

    string_wrapper() = default;
    string_wrapper(const string_wrapper&) = default;
    string_wrapper& operator=(const string_wrapper&) = default;
    string_wrapper(string_wrapper&&) = default;
    string_wrapper& operator=(string_wrapper&&) = default;
    ~string_wrapper() = default;

    string_wrapper(const std::string& str) : str(str)
    {}
    string_wrapper(std::string&& str) : str(std::move(str))
    {}

    operator const std::string&() const volatile&
    {
        return const_cast<const string_wrapper*>(this)->str;
    }
    operator std::string&&() &&
    {
        return std::move(str);
    }

    bool operator==(const string_wrapper& r) const
    {
        return str == r.str;
    }
    bool operator!=(const string_wrapper& r) const
    {
        return str != r.str;
    }
    bool operator<(const string_wrapper& r) const
    {
        return str < r.str;
    }
    bool operator==(const std::string& r) const
    {
        return str == r;
    }
    bool operator!=(const std::string& r) const
    {
        return str != r;
    }
    bool operator<(const std::string& r) const
    {
        return str < r;
    }

    friend bool operator==(const std::string& l, const string_wrapper& r)
    {
        return l == r.str;
    }
    friend bool operator!=(const std::string& l, const string_wrapper& r)
    {
        return l != r.str;
    }
    friend bool operator<(const std::string& l, const string_wrapper& r)
    {
        return l < r.str;
    }
};

/** Simple wrapper class for std::string to allow conversion to and from an
 *  alternative typename. */
struct string_path_wrapper
{
    std::string str;

    string_path_wrapper() = default;
    string_path_wrapper(const string_path_wrapper&) = default;
    string_path_wrapper& operator=(const string_path_wrapper&) = default;
    string_path_wrapper(string_path_wrapper&&) = default;
    string_path_wrapper& operator=(string_path_wrapper&&) = default;
    ~string_path_wrapper() = default;

    string_path_wrapper(const std::string& str) : str(str)
    {}
    string_path_wrapper(std::string&& str) : str(std::move(str))
    {}

    operator const std::string&() const volatile&
    {
        return const_cast<const string_path_wrapper*>(this)->str;
    }
    operator std::string&&() &&
    {
        return std::move(str);
    }

    bool operator==(const string_path_wrapper& r) const
    {
        return str == r.str;
    }
    bool operator!=(const string_path_wrapper& r) const
    {
        return str != r.str;
    }
    bool operator<(const string_path_wrapper& r) const
    {
        return str < r.str;
    }
    bool operator==(const std::string& r) const
    {
        return str == r;
    }
    bool operator!=(const std::string& r) const
    {
        return str != r;
    }
    bool operator<(const std::string& r) const
    {
        return str < r;
    }

    friend bool operator==(const std::string& l, const string_path_wrapper& r)
    {
        return l == r.str;
    }
    friend bool operator!=(const std::string& l, const string_path_wrapper& r)
    {
        return l != r.str;
    }
    friend bool operator<(const std::string& l, const string_path_wrapper& r)
    {
        return l < r.str;
    }

    std::string filename() const;
    string_path_wrapper parent_path() const;
    string_path_wrapper operator/(std::string_view) const;
    string_path_wrapper& operator/=(std::string_view);
};

/** Typename for sdbus SIGNATURE types. */
struct signature_type
{};
/** Typename for sdbus UNIX_FD types. */
struct unix_fd_type
{
    int fd;

    unix_fd_type() = default;
    unix_fd_type(int f) : fd(f)
    {}

    operator int() const
    {
        return fd;
    }
};

} // namespace details

/** std::string wrapper for OBJECT_PATH. */
using object_path = details::string_path_wrapper;
/** std::string wrapper for SIGNATURE. */
using signature = details::string_wrapper;
using unix_fd = details::unix_fd_type;

namespace details
{

template <typename T>
struct convert_from_string
{
    static auto op(const std::string&) noexcept = delete;
};

template <typename T>
struct convert_to_string
{
    static std::string op(T) = delete;
};

} // namespace details

/** @brief Convert from a string to a native type.
 *
 *  Some C++ types cannot be represented directly on dbus, so we encode
 *  them as strings.  Enums are the primary example of this.  This is a
 *  template function prototype for the conversion from string functions.
 *
 *  @return A std::optional<T> containing the value if conversion is possible.
 */
template <typename T>
auto convert_from_string(const std::string& str) noexcept
{
    return details::convert_from_string<T>::op(str);
};

/** @brief Convert from a native type to a string.
 *
 *  Some C++ types cannot be represented directly on dbus, so we encode
 *  them as strings.  Enums are the primary example of this.  This is a
 *  template function prototype for the conversion to string functions.
 *
 *  @return A std::string containing an encoding of the value, if conversion is
 *          possible.
 */
template <typename T>
std::string convert_to_string(T t)
{
    return details::convert_to_string<T>::op(t);
}

} // namespace message
} // namespace sdbusplus

namespace std
{

/** Overload of std::hash for details::string_wrappers */
template <>
struct hash<sdbusplus::message::details::string_wrapper>
{
    using argument_type = sdbusplus::message::details::string_wrapper;
    using result_type = std::size_t;

    result_type operator()(argument_type const& s) const
    {
        return hash<std::string>()(s.str);
    }
};

/** Overload of std::hash for details::string_wrappers */
template <>
struct hash<sdbusplus::message::details::string_path_wrapper>
{
    using argument_type = sdbusplus::message::details::string_path_wrapper;
    using result_type = std::size_t;

    result_type operator()(argument_type const& s) const
    {
        return hash<std::string>()(s.str);
    }
};

} // namespace std
