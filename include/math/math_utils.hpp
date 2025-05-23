#pragma once
#include "vec3.hpp"

// TODO: Implement utility functions for each data type 

// scalar
template<typename T>
constexpr T min(T a, T b) noexcept { return a < b ? a : b; }

template<typename T>
constexpr T max(T a, T b) noexcept { return a > b ? a : b; }

template<typename T>
constexpr T clamp(T v, T lo, T hi) noexcept 
{ return min(max(v, lo), hi); }


// vec3
template<typename T>
constexpr Vec3<T> min(const Vec3<T>& a, const Vec3<T>& b) noexcept
{ return { min(a.x, b.x), min(a.y, b.y), min(a.z, b.z)}; }

template<typename T>
constexpr Vec3<T> max(const Vec3<T>& a, const Vec3<T>& b) noexcept
{ return { max(a.x, b.x), max(a.y, b.y), max(a.z, b.z)}; }

template<typename T>
constexpr Vec3<T> clamp(const Vec3<T>& v, T lo, T hi) noexcept
{ return { clamp(v.x, lo, hi), 
           clamp(v.y, lo, hi), 
           clamp(v.z, lo, hi)}; }


// reflect ?

// refract ?

// transpose

// inverse

// ...

