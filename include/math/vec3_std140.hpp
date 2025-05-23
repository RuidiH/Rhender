#pragma once
#include "vec3.hpp"

struct alignas(16) Vec3Std140
{
    float x, y, z;
    float _pad; // Padding to ensure 16-byte alignment
    constexpr Vec3Std140(vec3 v) noexcept
        : x(v.x), y(v.y), z(v.z), _pad(0) {}
    float       *data() noexcept { return &x; }
    float const *data() const noexcept { return &x; }
};

static_assert(sizeof(Vec3Std140) == 16, 
    "Vec3Std140 must be 16 bytes for std140 alignment.");
static_assert(alignof(Vec3Std140) == 16, 
"Vec3Std140 must be 16-byte aligned for std140 compliance.");