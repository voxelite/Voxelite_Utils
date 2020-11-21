#pragma once

#include <cstdint>
#include <string>
#include <sstream>
#include <regex>

namespace Voxelite::Util
{
    [[nodiscard]] inline constexpr uint32_t MakeVersion(uint32_t major, uint32_t minor, uint32_t patch = 0) noexcept
    {
        // Same as VK_MAKE_VERSION
        // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VK_MAKE_VERSION.html
        return ((major << 22u) | (minor << 12u) | patch);
    }
    inline constexpr void BreakVersion(uint32_t version, uint32_t& major, uint32_t& minor, uint32_t& patch) noexcept
    {
        // 4'096 values
        // 0b00000000'00000000'00001111'11111111 == ((1u << 12u) - 1u) == 4'096u
        patch = version & 0x0000'0FFFu;

        // 1'024 values
        // 0b00000000'00111111'11110000'00000000 == (1u << 22u) - (1u << 12u) == 4'190'208u
        minor = (version & 0x003F'F000u) >> 12u;

        // 1'024 values
        // 0b11111111'11000000'00000000'00000000 == (1u << 32u) - (1u << 22u) == 4'290'772'992u
        major = (version & 0xFFC0'0000u) >> 22u;
    }

    inline std::string MakeVersionString(uint32_t major, uint32_t minor, uint32_t patch = 0)
    {
        std::stringstream ss;

        ss << major << '.' << minor;
        if(patch != 0)
            ss << '_' << patch;

        return ss.str();
    }
    inline std::string MakeVersionString(uint32_t version)
    {
        uint32_t major, minor, patch;
        BreakVersion(version, major, minor, patch);

        return MakeVersionString(major, minor, patch);
    }

    /// Utility function to wrap around strtoul
    [[nodiscard]] static uint32_t str2u32(const std::string& value)
    {
        const char* endPtr = value.c_str() + value.length();
        return strtoul(value.c_str(), const_cast<char**>(&endPtr), 10);
    }
    static const std::regex reg = std::regex("^([0-9]+)\\.([0-9]+)((_|.)([0-9]+))?$");
    inline bool BreakVersionString(const std::string& version, uint32_t& major, uint32_t& minor, uint32_t& patch) noexcept
    {
        try
        {
            std::smatch regResult;
            if (std::regex_match(version, regResult, reg))
            {
                major = str2u32(regResult[1].str());
                minor = str2u32(regResult[2].str());

                if (regResult.size() > 5)
                    patch = str2u32(regResult[5].str());
                else
                    patch = 0;

                return true;
            }
        }
        catch (std::exception& ex)
        {
        }

        major = 0;
        minor = 0;
        patch = 0;

        return false;
    }
    [[nodiscard]] inline uint32_t BreakVersionString(const std::string& version) noexcept
    {
        uint32_t major, minor, patch;
        BreakVersionString(version, major, minor, patch);

        return MakeVersion(major, minor, patch);
    }
}
