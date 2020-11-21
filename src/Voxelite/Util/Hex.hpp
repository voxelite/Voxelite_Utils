#pragma once

#include <cstdint>
#include <string>
#include <cassert>
#include <stdexcept>

// Dec2Hex
namespace Voxelite::Util
{
    [[nodiscard]] inline char Dec2Hex_Half(uint8_t half) noexcept
    {
        assert(half <= 0x0F);
        static constexpr const char* decToHex = "0123456789ABCDEF";
        return decToHex[half];
    }

    inline void Dec2Hex(uint8_t decValue, char& upperChar, char& lowerChar) noexcept
    {
        lowerChar = Dec2Hex_Half(decValue & 0x0Fu);
        upperChar = Dec2Hex_Half(static_cast<uint8_t>(decValue >> 4u) & 0x0Fu);
    }

    [[nodiscard]] inline std::string Dec2Hex(uint8_t decValue) noexcept
    {
        char rtn[1 + sizeof(decValue) * 2] = { '\0', '\0', '\0' };

        Dec2Hex(decValue, rtn[0], rtn[1]);

        return std::string(rtn);
    }
    [[nodiscard]] inline std::string Dec2Hex(uint16_t decValue) noexcept
    {
        char rtn[1 + sizeof(decValue) * 2] = { '\0', '\0', '\0' };

        for(std::size_t i = 0; i < sizeof(decValue) * 2; i++)
            rtn[sizeof(decValue) * 2 - 1 - i] = Dec2Hex_Half(static_cast<uint8_t>(decValue >> (i * 4u)) & 0x0Fu);

        return std::string(rtn);
    }
    [[nodiscard]] inline std::string Dec2Hex(uint32_t decValue) noexcept
    {
        char rtn[1 + sizeof(decValue) * 2] = { '\0', '\0', '\0' };

        for(std::size_t i = 0; i < sizeof(decValue) * 2; i++)
            rtn[sizeof(decValue) * 2 - 1 - i] = Dec2Hex_Half(static_cast<uint8_t>(decValue >> (i * 4u)) & 0x0Fu);

        return std::string(rtn);
    }
    [[nodiscard]] inline std::string Dec2Hex(uint64_t decValue) noexcept
    {
        char rtn[1 + sizeof(decValue) * 2] = { '\0', '\0', '\0' };

        for(std::size_t i = 0; i < sizeof(decValue) * 2; i++)
            rtn[sizeof(decValue) * 2 - 1 - i] = Dec2Hex_Half(static_cast<uint8_t>(decValue >> (i * 4u)) & 0x0Fu);

        return std::string(rtn);
    }
}

// Hex2Dec
namespace Voxelite::Util
{
    [[nodiscard]] inline uint8_t Hex2Dec_Half(char hex)
    {
        switch (hex)
        {
            case '0':
                return 0x00;
            case '1':
                return 0x01;
            case '2':
                return 0x02;
            case '3':
                return 0x03;
            case '4':
                return 0x04;
            case '5':
                return 0x05;
            case '6':
                return 0x06;
            case '7':
                return 0x07;
            case '8':
                return 0x08;
            case '9':
                return 0x09;
            case 'A':
            case 'a':
                return 0x0A;
            case 'B':
            case 'b':
                return 0x0B;
            case 'C':
            case 'c':
                return 0x0C;
            case 'D':
            case 'd':
                return 0x0D;
            case 'E':
            case 'e':
                return 0x0E;
            case 'F':
            case 'f':
                return 0x0F;

            default:
                throw std::runtime_error("`hex` is not valid Hexadecimal character");
        }
    }

    [[nodiscard]] inline uint8_t Hex2Dec(char hexUpper, char hexLower)
    {
        return (Hex2Dec_Half(hexUpper) << 4u) + Hex2Dec_Half(hexLower);
    }

    inline void Hex2Dec(const char* hex, uint8_t& dec)
    {
        if(hex == nullptr || hex[0] == '\0')
            dec = 0;
        else if(hex[1] == '\0')
            dec = Hex2Dec_Half(hex[0]);
        else
            dec = Hex2Dec(hex[0], hex[1]);
    }
    inline void Hex2Dec(const char* hex, uint16_t& dec)
    {
        dec = 0;
        for(std::size_t i = 0; i < sizeof(uint16_t) * 2 && hex[i] != '\0'; i++)
            dec = (dec << 4u) + Hex2Dec_Half(hex[i]);
    }
    inline void Hex2Dec(const char* hex, uint32_t& dec)
    {
        dec = 0;
        for(std::size_t i = 0; i < sizeof(uint32_t) * 2 && hex[i] != '\0'; i++)
            dec = (dec << 4u) + Hex2Dec_Half(hex[i]);
    }
    inline void Hex2Dec(const char* hex, uint64_t& dec)
    {
        dec = 0;
        for(std::size_t i = 0; i < sizeof(uint64_t) * 2 && hex[i] != '\0'; i++)
            dec = (dec << 4u) + Hex2Dec_Half(hex[i]);
    }

    inline void Hex2Dec(const std::string& hex, uint8_t& dec) { Hex2Dec(hex.c_str(), dec); }
    inline void Hex2Dec(const std::string& hex, uint16_t& dec) { Hex2Dec(hex.c_str(), dec); }
    inline void Hex2Dec(const std::string& hex, uint32_t& dec) { Hex2Dec(hex.c_str(), dec); }
    inline void Hex2Dec(const std::string& hex, uint64_t& dec) { Hex2Dec(hex.c_str(), dec); }

    [[nodiscard]] inline uint8_t Hex2Dec_uint8(const char* hex)
    {
        uint8_t dec;
        Hex2Dec(hex, dec);
        return dec;
    }
    [[nodiscard]] inline uint16_t Hex2Dec_uint16(const char* hex)
    {
        uint16_t dec;
        Hex2Dec(hex, dec);
        return dec;
    }
    [[nodiscard]] inline uint32_t Hex2Dec_uint32(const char* hex)
    {
        uint32_t dec;
        Hex2Dec(hex, dec);
        return dec;
    }
    [[nodiscard]] inline uint64_t Hex2Dec_uint64(const char* hex)
    {
        uint64_t dec;
        Hex2Dec(hex, dec);
        return dec;
    }

    [[nodiscard]] inline uint8_t Hex2Dec_uint8(const std::string& hex) { return Hex2Dec_uint8(hex.c_str()); }
    [[nodiscard]] inline uint16_t Hex2Dec_uint16(const std::string& hex) { return Hex2Dec_uint16(hex.c_str()); }
    [[nodiscard]] inline uint32_t Hex2Dec_uint32(const std::string& hex) { return Hex2Dec_uint32(hex.c_str()); }
    [[nodiscard]] inline uint64_t Hex2Dec_uint64(const std::string& hex) { return Hex2Dec_uint64(hex.c_str()); }
}
