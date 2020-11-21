#include <Voxelite/Util/Hex.hpp>
#include <iostream>

void test(const std::string& hexValue, const std::string& testValue)
{
    if(hexValue != testValue)
    {
        std::cerr << hexValue << std::endl;
        std::cerr << testValue << std::endl;
        std::cerr << std::endl;
        throw std::runtime_error("Hex value does not match test value");
    }
}

int main(int argc, const char** argv)
{
    using namespace Voxelite::Util;

    // uint8_t
    {
        test(Dec2Hex(static_cast<uint8_t>(0x00)), "00");

        test(Dec2Hex(static_cast<uint8_t>(0x01)), "01");
        test(Dec2Hex(static_cast<uint8_t>(0x10)), "10");

        test(Dec2Hex(static_cast<uint8_t>(0x0F)), "0F");
        test(Dec2Hex(static_cast<uint8_t>(0xF0)), "F0");

        test(Dec2Hex(static_cast<uint8_t>(0x11)), "11");
        test(Dec2Hex(static_cast<uint8_t>(0x33)), "33");
        test(Dec2Hex(static_cast<uint8_t>(0xFF)), "FF");
        test(Dec2Hex(static_cast<uint8_t>(0xAE)), "AE");
    }

    // uint16_t
    {
        test(Dec2Hex(static_cast<uint16_t>(0x00'00)), "0000");

        test(Dec2Hex(static_cast<uint16_t>(0x00'01)), "0001");
        test(Dec2Hex(static_cast<uint16_t>(0x00'10)), "0010");
        test(Dec2Hex(static_cast<uint16_t>(0x01'00)), "0100");
        test(Dec2Hex(static_cast<uint16_t>(0x10'00)), "1000");

        test(Dec2Hex(static_cast<uint16_t>(0x11'11)), "1111");
        test(Dec2Hex(static_cast<uint16_t>(0x01'23)), "0123");
        test(Dec2Hex(static_cast<uint16_t>(0xFF'FF)), "FFFF");
    }

    // uint32_t
    {
        test(Dec2Hex(static_cast<uint32_t>(0x00'00'00'00)), "00000000");

        test(Dec2Hex(static_cast<uint32_t>(0x00'00'00'01)), "00000001");
        test(Dec2Hex(static_cast<uint32_t>(0x00'00'00'10)), "00000010");
        test(Dec2Hex(static_cast<uint32_t>(0x00'00'01'00)), "00000100");
        test(Dec2Hex(static_cast<uint32_t>(0x00'00'10'00)), "00001000");
        test(Dec2Hex(static_cast<uint32_t>(0x00'01'00'00)), "00010000");
        test(Dec2Hex(static_cast<uint32_t>(0x00'10'00'00)), "00100000");
        test(Dec2Hex(static_cast<uint32_t>(0x01'00'00'00)), "01000000");
        test(Dec2Hex(static_cast<uint32_t>(0x10'00'00'00)), "10000000");

        test(Dec2Hex(static_cast<uint32_t>(0x11'11'11'11)), "11111111");
        test(Dec2Hex(static_cast<uint32_t>(0x01'23'45'67)), "01234567");
        test(Dec2Hex(static_cast<uint32_t>(0xFF'FF'FF'FF)), "FFFFFFFF");
    }

    // uint64_t
    {
        test(Dec2Hex(static_cast<uint64_t>(0x00'00'00'00'00'00'00'00)), "0000000000000000");

        test(Dec2Hex(static_cast<uint64_t>(0x00'00'00'00'00'00'00'01)), "0000000000000001");
        test(Dec2Hex(static_cast<uint64_t>(0x00'00'00'00'00'00'00'10)), "0000000000000010");
        test(Dec2Hex(static_cast<uint64_t>(0x00'00'00'00'00'00'01'00)), "0000000000000100");
        test(Dec2Hex(static_cast<uint64_t>(0x00'00'00'00'00'00'10'00)), "0000000000001000");
        test(Dec2Hex(static_cast<uint64_t>(0x00'00'00'00'00'01'00'00)), "0000000000010000");
        test(Dec2Hex(static_cast<uint64_t>(0x00'00'00'00'00'10'00'00)), "0000000000100000");
        test(Dec2Hex(static_cast<uint64_t>(0x00'00'00'00'01'00'00'00)), "0000000001000000");
        test(Dec2Hex(static_cast<uint64_t>(0x00'00'00'00'10'00'00'00)), "0000000010000000");
        test(Dec2Hex(static_cast<uint64_t>(0x00'00'00'01'00'00'00'00)), "0000000100000000");
        test(Dec2Hex(static_cast<uint64_t>(0x00'00'00'10'00'00'00'00)), "0000001000000000");
        test(Dec2Hex(static_cast<uint64_t>(0x00'00'01'00'00'00'00'00)), "0000010000000000");
        test(Dec2Hex(static_cast<uint64_t>(0x00'00'10'00'00'00'00'00)), "0000100000000000");
        test(Dec2Hex(static_cast<uint64_t>(0x00'01'00'00'00'00'00'00)), "0001000000000000");
        test(Dec2Hex(static_cast<uint64_t>(0x00'10'00'00'00'00'00'00)), "0010000000000000");
        test(Dec2Hex(static_cast<uint64_t>(0x01'00'00'00'00'00'00'00)), "0100000000000000");
        test(Dec2Hex(static_cast<uint64_t>(0x10'00'00'00'00'00'00'00)), "1000000000000000");

        test(Dec2Hex(static_cast<uint64_t>(0x11'11'11'11'11'11'11'11)), "1111111111111111");
        test(Dec2Hex(static_cast<uint64_t>(0x01'23'45'67'89'AB'CD'EF)), "0123456789ABCDEF");
        test(Dec2Hex(static_cast<uint64_t>(0xFF'FF'FF'FF'FF'FF'FF'FF)), "FFFFFFFFFFFFFFFF");
    }
}
