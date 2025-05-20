#pragma once
#include <cmath>

template <typename T>
struct Vec3
{
    T x, y, z;
    constexpr Vec3() noexcept : x(0), y(0), z(0) {}
    constexpr Vec3(T x, T y, T z) noexcept : x(x), y(y), z(z) {}

    T&       operator[](int i) noexcept { return (&x)[i]; }
    T const& operator[](int i) const noexcept { return (&x)[i]; }
    T*       data() noexcept { return &x; }
    T const* data() noexcept { return &x; }
};

using vec3 = Vec3<float>;
using dvec3 = Vec3<double>;

template <typename T>
constexpr Vec3<T>& operator+=(Vec3<T> &a, Vec3<T> const& b) noexcept
{ a.x += b.x; a.y += b.y; a.z += b.z; return a; }

template <typename T>
constexpr Vec3<T>& operator-=(Vec3<T> &a, Vec3<T> const& b) noexcept
{ a.x -= b.x; a.y -= b.y; a.z -= b.z; return a; }

template <typename T>
constexpr Vec3<T>& operator*=(Vec3<T> &a, T s) noexcept
{ a.x *= s; a.y *= s; a.z *= s; return a; }

template <typename T>
constexpr Vec3<T>& operator/=(Vec3<T> &a, T s) noexcept 
{ a.x *= s; a.y *= s; a.z *= s; return a; }

template <typename T>
constexpr Vec3<T> operator+(Vec3<T> a, Vec3<T> const& s) noexcept { return a += s; }

template <typename T>
constexpr Vec3<T> operator-(Vec3<T> const& a) noexcept { return {-a.x, -a.y, -a.z}; }

template <typename T>
constexpr Vec3<T> operator-(Vec3<T> a, Vec3<T> const& b) noexcept { return a -=b; }

template <typename T>
constexpr Vec3<T> operator*(Vec3<T> a, T s) noexcept { return a *= s; }

template <typename T>
constexpr Vec3<T> operator*(T s, Vec3<T> a) noexcept { return a *= s; }

template <typename T>
constexpr Vec3<T> operator/(Vec3<T> const& a, T s) noexcept { return a /= s; }

template<typename T>
constexpr T dot(Vec3<T> const& a, Vec3<T> const& b) noexcept 
{ return a.x * b.x + a.y * b.y + a.z * b.z; }

template<typename T>
constexpr Vec3<T> cross(Vec3<T> const& a, Vec3<T> const& b) noexcept 
{ return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x}; }

template<typename T>
T length(Vec3<T> const & a) noexcept { return std::sqrt(dot(a, a)); }

template<typename T>
Vec3<T> normalize(Vec3<T> const& a) noexcept { return a / length(a); }

template<typename T>
constexpr bool operator==(Vec3<T> const& a, Vec3<T> const& b) noexcept 
{ return a.x == b.x && a.y == b.y && a.z == b.z; }

template<typename T>
constexpr bool operator!=(Vec3<T> const& a, Vec3<T> const& b) noexcept 
{ return !(a==b); }