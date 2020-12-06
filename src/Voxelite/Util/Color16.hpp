#pragma once

#include <cstdint>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <ostream>
#include <sstream>

namespace Voxelite::Util
{
    class Color
    {
    public:
#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"
        constexpr Color(uint16_t color) noexcept : m_Color(color)
        {
        }

        inline constexpr Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) noexcept
         : Color(
                 (static_cast<uint16_t>(alpha / 17u) << 12u) +
                 (static_cast<uint16_t>(blue / 17u) << 8u) +
                 (static_cast<uint16_t>(green / 17u) << 4u) +
                 (static_cast<uint16_t>(red / 17u) << 0u)
                )
        {
        }

        inline constexpr Color(uint8_t red, uint8_t green, uint8_t blue) noexcept
         : Color(red, green, blue, 0u)
        {
        }

        inline constexpr Color(glm::ivec4 vec) noexcept
         : Color(
                 static_cast<uint8_t>(vec.r),
                 static_cast<uint8_t>(vec.g),
                 static_cast<uint8_t>(vec.b),
                 static_cast<uint8_t>(vec.a)
                )
        {
        }

        inline constexpr Color(glm::ivec3 vec) noexcept
         : Color(
                 static_cast<uint8_t>(vec.r),
                 static_cast<uint8_t>(vec.g),
                 static_cast<uint8_t>(vec.b)
                )
        {
        }

        inline constexpr Color(float red, float green, float blue, float alpha) noexcept
         : Color(
                 static_cast<uint8_t>(red * 255),
                 static_cast<uint8_t>(green * 255),
                 static_cast<uint8_t>(blue * 255),
                 static_cast<uint8_t>(alpha * 255)
                )
        {
        }

        inline constexpr Color(float red, float green, float blue) noexcept
         : Color(red, green, blue, 0.0f)
        {
        }

        inline constexpr Color(glm::vec4 vec) noexcept
         : Color(
                 vec.r,
                 vec.g,
                 vec.b,
                 vec.a
                )
        {
        }

        inline constexpr Color(glm::vec3 vec) noexcept
         : Color(
                 vec.r,
                 vec.g,
                 vec.b
                )
        {
        }
#pragma clang diagnostic pop

    private:
        const uint16_t m_Color;

    // Bytes
    public:
        [[nodiscard]] inline uint8_t Red() const noexcept
        {
            return (static_cast<uint8_t>(m_Color >> 0u) & 0x000Fu) * 17;
        }

        [[nodiscard]] inline uint8_t Green() const noexcept
        {
            return (static_cast<uint8_t>(m_Color >> 4u) & 0x000Fu) * 17;
        }

        [[nodiscard]] inline uint8_t Blue() const noexcept
        {
            return (static_cast<uint8_t>(m_Color >> 8u) & 0x000Fu) * 17;
        }

        [[nodiscard]] inline uint8_t Alpha() const noexcept
        {
            return (static_cast<uint8_t>(m_Color >> 12u) & 0x000Fu) * 17;
        }

    // Vectors
    public:
        [[nodiscard]] inline glm::vec3 AsVector3() const noexcept
        {
            return glm::vec3(
                    static_cast<float>(Red()) / 255.0f,
                    static_cast<float>(Green()) / 255.0f,
                    static_cast<float>(Blue()) / 255.0f
                    );
        }
        [[nodiscard]] inline glm::vec4 AsVector4() const noexcept
        {
            return glm::vec4(
                    static_cast<float>(Red()) / 255.0f,
                    static_cast<float>(Green()) / 255.0f,
                    static_cast<float>(Blue()) / 255.0f,
                    static_cast<float>(Alpha()) / 255.0f
                    );
        }
        [[nodiscard]] inline glm::ivec3 AsIntVector3() const noexcept
        {
            return glm::ivec3(
                    Red(),
                    Green(),
                    Blue()
                    );
        }
        [[nodiscard]] inline glm::ivec4 AsIntVector4() const noexcept
        {
            return glm::ivec4(
                    Red(),
                    Green(),
                    Blue(),
                    Alpha()
                    );
        }

    public:
        [[nodiscard]] inline std::string AsConsoleCode() const
        {
            std::stringstream ss;
            ss << "\E[38;2;" << Red() << ';' << Green() << ';' << Blue() << 'm';
            return ss.str();
        }

    private:
        static constexpr const char* decToHex = "0123456789ABCDEF";
    public:
        [[nodiscard]] inline std::string AsHexRGB() const noexcept
        {
            char hexArray[8] = {
                    '#',
                    'R', 'R',
                    'G', 'G',
                    'B', 'B',
                    '\0'
            };

            uint8_t red = Red();
            hexArray[1] = decToHex[static_cast<uint8_t>(red >> 0u) & 0x0Fu];
            hexArray[2] = decToHex[static_cast<uint8_t>(red >> 4u) & 0x0Fu];

            uint8_t green = Green();
            hexArray[3] = decToHex[static_cast<uint8_t>(green >> 0u) & 0x0Fu];
            hexArray[4] = decToHex[static_cast<uint8_t>(green >> 4u) & 0x0Fu];

            uint8_t blue = Blue();
            hexArray[5] = decToHex[static_cast<uint8_t>(blue >> 0u) & 0x0Fu];
            hexArray[6] = decToHex[static_cast<uint8_t>(blue >> 4u) & 0x0Fu];

            return std::string(hexArray);
        }
        [[nodiscard]] inline std::string AsHexRGBA() const noexcept
        {
            char hexArray[10] = {
                    '#',
                    'R', 'R',
                    'G', 'G',
                    'B', 'B',
                    'A', 'A',
                    '\0'
            };

            uint8_t red = Red();
            hexArray[2] = decToHex[static_cast<uint8_t>(red >> 0u) & 0x0Fu];
            hexArray[1] = decToHex[static_cast<uint8_t>(red >> 4u) & 0x0Fu];

            uint8_t green = Green();
            hexArray[4] = decToHex[static_cast<uint8_t>(green >> 0u) & 0x0Fu];
            hexArray[3] = decToHex[static_cast<uint8_t>(green >> 4u) & 0x0Fu];

            uint8_t blue = Blue();
            hexArray[6] = decToHex[static_cast<uint8_t>(blue >> 0u) & 0x0Fu];
            hexArray[5] = decToHex[static_cast<uint8_t>(blue >> 4u) & 0x0Fu];

            uint8_t alpha = Alpha();
            hexArray[8] = decToHex[static_cast<uint8_t>(alpha >> 0u) & 0x0Fu];
            hexArray[7] = decToHex[static_cast<uint8_t>(alpha >> 4u) & 0x0Fu];

            return std::string(hexArray);
        }
    };
}
