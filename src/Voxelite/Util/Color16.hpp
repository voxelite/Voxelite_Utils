#pragma once

#include <cstdint>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Voxelite::Util
{
    typedef uint16_t color16_t;

    [[nodiscard]] inline constexpr glm::vec3 AsColorRGB(color16_t value) noexcept
    {
        return glm::vec3(
                static_cast<float>(static_cast<uint8_t>(value >> 0u) & 0x0Fu) / 15.0f,
                static_cast<float>(static_cast<uint8_t>(value >> 4u) & 0x0Fu) / 15.0f,
                static_cast<float>(static_cast<uint8_t>(value >> 8u) & 0x0Fu) / 15.0f
                        );
    }
    [[nodiscard]] inline constexpr glm::vec4 AsColorRGBA(color16_t value) noexcept
    {
        return glm::vec4(
                static_cast<float>(static_cast<uint8_t>(value >>  0u) & 0x0Fu) / 15.0f,
                static_cast<float>(static_cast<uint8_t>(value >>  4u) & 0x0Fu) / 15.0f,
                static_cast<float>(static_cast<uint8_t>(value >>  8u) & 0x0Fu) / 15.0f,
                static_cast<float>(static_cast<uint8_t>(value >> 12u) & 0x0Fu) / 15.0f
                        );
    }
    [[nodiscard]] inline constexpr color16_t FromColor(float r, float g, float b) noexcept
    {
        assert(r >= 0.0f);
        assert(r <= 1.0f);

        assert(g >= 0.0f);
        assert(g <= 1.0f);

        assert(b >= 0.0f);
        assert(b <= 1.0f);

        return (static_cast<uint16_t>(r * 15.0f) << 0u) +
               (static_cast<uint16_t>(g * 15.0f) << 4u) +
               (static_cast<uint16_t>(b * 15.0f) << 8u);
    }
    [[nodiscard]] inline color16_t FromColor(const glm::vec3& rgb) noexcept
    {
        return FromColor(rgb.r, rgb.g, rgb.b);
    }

    [[nodiscard]] inline constexpr color16_t FromColor(float r, float g, float b, float a) noexcept
    {
        assert(r >= 0.0f);
        assert(r <= 1.0f);

        assert(g >= 0.0f);
        assert(g <= 1.0f);

        assert(b >= 0.0f);
        assert(b <= 1.0f);

        assert(a >= 0.0f);
        assert(a <= 1.0f);

        return (static_cast<uint16_t>(r * 15.0f) << 0u) +
               (static_cast<uint16_t>(g * 15.0f) << 4u) +
               (static_cast<uint16_t>(b * 15.0f) << 8u) +
               (static_cast<uint16_t>(a * 15.0f) << 12u);
    }
    [[nodiscard]] inline color16_t FromColor(const glm::vec4& rgba) noexcept
    {
        return FromColor(rgba.r, rgba.g, rgba.b, rgba.a);
    }

    class Color16
    {
    public:
        Color16() = delete; // Static class

        // Example colors:

        // Transparent
    public:
        static const color16_t Transparent_White = FromColor(1.0f, 1.0f, 1.0f, 1.0f);
        static const color16_t Transparent_Black = FromColor(0.0f, 0.0f, 0.0f, 1.0f);
        // Grayscale
    public:
        static const color16_t White = FromColor(1.0f, 1.0f, 1.0f);
        static const color16_t Gray  = FromColor(0.5f, 0.5f, 0.5f);
        static const color16_t Black = FromColor(0.0f, 0.0f, 0.0f);

        // RGB components
    public:
        static const color16_t Red   = FromColor(1.0f, 0.0f, 0.0f);
        static const color16_t Green = FromColor(0.0f, 1.0f, 0.0f);
        static const color16_t Blue  = FromColor(0.0f, 0.0f, 1.0f);

        // RGB 2-components
    public:
        static const color16_t Yellow = FromColor(1.0f, 1.0f, 0.0f);
        static const color16_t Aqua   = FromColor(0.0f, 1.0f, 1.0f);
        static const color16_t Purple = FromColor(1.0f, 0.0f, 1.0f);
    };
}
