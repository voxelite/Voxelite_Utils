#include <Voxelite/Util/Hex.hpp>
#include <iostream>

template<typename T>
static void test(T decValue, T testValue)
{
    if(decValue != testValue)
    {
        std::cerr << static_cast<uint64_t>(decValue) << std::endl;
        std::cerr << static_cast<uint64_t>(testValue) << std::endl;
        std::cerr << std::endl;
        throw std::runtime_error("Dec value does not match test value");
    }
}

int main(int argc, const char** argv)
{
    using namespace Voxelite::Util;

    // uint8_t
    {
        test(Hex2Dec('0', '0'), static_cast<uint8_t>(0x00));

        test(Hex2Dec('0', '1'), static_cast<uint8_t>(0x01));
        test(Hex2Dec('1', '0'), static_cast<uint8_t>(0x10));

        test(Hex2Dec('0', 'F'), static_cast<uint8_t>(0x0F));
        test(Hex2Dec('F', '0'), static_cast<uint8_t>(0xF0));

        test(Hex2Dec('1', '1'), static_cast<uint8_t>(0x11));
        test(Hex2Dec('3', '3'), static_cast<uint8_t>(0x33));
        test(Hex2Dec('F', 'F'), static_cast<uint8_t>(0xFF));
        test(Hex2Dec('A', 'E'), static_cast<uint8_t>(0xAE));
    }

    // uint8_t
    {
        test(Hex2Dec_uint8("00"), static_cast<uint8_t>(0x00));

        test(Hex2Dec_uint8("01"), static_cast<uint8_t>(0x01));
        test(Hex2Dec_uint8("10"), static_cast<uint8_t>(0x10));

        test(Hex2Dec_uint8("0F"), static_cast<uint8_t>(0x0F));
        test(Hex2Dec_uint8("F0"), static_cast<uint8_t>(0xF0));

        test(Hex2Dec_uint8("11"), static_cast<uint8_t>(0x11));
        test(Hex2Dec_uint8("33"), static_cast<uint8_t>(0x33));
        test(Hex2Dec_uint8("FF"), static_cast<uint8_t>(0xFF));
        test(Hex2Dec_uint8("AE"), static_cast<uint8_t>(0xAE));

        test(Hex2Dec_uint8("1"), static_cast<uint8_t>(0x01));
        test(Hex2Dec_uint8("F"), static_cast<uint8_t>(0x0F));
    }

    // uint16_t
    {
        test(Hex2Dec_uint16("0000"), static_cast<uint16_t>(0x00'00));

        test(Hex2Dec_uint16("0001"), static_cast<uint16_t>(0x00'01));
        test(Hex2Dec_uint16("0010"), static_cast<uint16_t>(0x00'10));
        test(Hex2Dec_uint16("0100"), static_cast<uint16_t>(0x01'00));
        test(Hex2Dec_uint16("1000"), static_cast<uint16_t>(0x10'00));

        test(Hex2Dec_uint16("1111"), static_cast<uint16_t>(0x11'11));
        test(Hex2Dec_uint16("ABCD"), static_cast<uint16_t>(0xAB'CD));
        test(Hex2Dec_uint16("FFFF"), static_cast<uint16_t>(0xFF'FF));

        test(Hex2Dec_uint16("11"), static_cast<uint16_t>(0x00'11));
        test(Hex2Dec_uint16("CD"), static_cast<uint16_t>(0x00'CD));
        test(Hex2Dec_uint16("FF"), static_cast<uint16_t>(0x00'FF));
    }

    // uint32_t
    {
        test(Hex2Dec_uint32("00000000"), static_cast<uint32_t>(0x00'00'00'00));

        test(Hex2Dec_uint32("00000001"), static_cast<uint32_t>(0x00'00'00'01));
        test(Hex2Dec_uint32("00000010"), static_cast<uint32_t>(0x00'00'00'10));
        test(Hex2Dec_uint32("00000100"), static_cast<uint32_t>(0x00'00'01'00));
        test(Hex2Dec_uint32("00001000"), static_cast<uint32_t>(0x00'00'10'00));
        test(Hex2Dec_uint32("00010000"), static_cast<uint32_t>(0x00'01'00'00));
        test(Hex2Dec_uint32("00100000"), static_cast<uint32_t>(0x00'10'00'00));
        test(Hex2Dec_uint32("01000000"), static_cast<uint32_t>(0x01'00'00'00));
        test(Hex2Dec_uint32("10000000"), static_cast<uint32_t>(0x10'00'00'00));

        test(Hex2Dec_uint32("11111111"), static_cast<uint32_t>(0x11'11'11'11));
        test(Hex2Dec_uint32("01234567"), static_cast<uint32_t>(0x01'23'45'67));
        test(Hex2Dec_uint32("FFFFFFFF"), static_cast<uint32_t>(0xFF'FF'FF'FF));

        test(Hex2Dec_uint32("1111"), static_cast<uint32_t>(0x00'00'11'11));
        test(Hex2Dec_uint32("4567"), static_cast<uint32_t>(0x00'00'45'67));
        test(Hex2Dec_uint32("FFFF"), static_cast<uint32_t>(0x00'00'FF'FF));
    }

    // uint64_t
    {
        test(Hex2Dec_uint64("0000000000000000"), static_cast<uint64_t>(0x00'00'00'00'00'00'00'00));

        test(Hex2Dec_uint64("0000000000000001"), static_cast<uint64_t>(0x00'00'00'00'00'00'00'01));
        test(Hex2Dec_uint64("0000000000000010"), static_cast<uint64_t>(0x00'00'00'00'00'00'00'10));
        test(Hex2Dec_uint64("0000000000000100"), static_cast<uint64_t>(0x00'00'00'00'00'00'01'00));
        test(Hex2Dec_uint64("0000000000001000"), static_cast<uint64_t>(0x00'00'00'00'00'00'10'00));
        test(Hex2Dec_uint64("0000000000010000"), static_cast<uint64_t>(0x00'00'00'00'00'01'00'00));
        test(Hex2Dec_uint64("0000000000100000"), static_cast<uint64_t>(0x00'00'00'00'00'10'00'00));
        test(Hex2Dec_uint64("0000000001000000"), static_cast<uint64_t>(0x00'00'00'00'01'00'00'00));
        test(Hex2Dec_uint64("0000000010000000"), static_cast<uint64_t>(0x00'00'00'00'10'00'00'00));
        test(Hex2Dec_uint64("0000000100000000"), static_cast<uint64_t>(0x00'00'00'01'00'00'00'00));
        test(Hex2Dec_uint64("0000001000000000"), static_cast<uint64_t>(0x00'00'00'10'00'00'00'00));
        test(Hex2Dec_uint64("0000010000000000"), static_cast<uint64_t>(0x00'00'01'00'00'00'00'00));
        test(Hex2Dec_uint64("0000100000000000"), static_cast<uint64_t>(0x00'00'10'00'00'00'00'00));
        test(Hex2Dec_uint64("0001000000000000"), static_cast<uint64_t>(0x00'01'00'00'00'00'00'00));
        test(Hex2Dec_uint64("0010000000000000"), static_cast<uint64_t>(0x00'10'00'00'00'00'00'00));
        test(Hex2Dec_uint64("0100000000000000"), static_cast<uint64_t>(0x01'00'00'00'00'00'00'00));
        test(Hex2Dec_uint64("1000000000000000"), static_cast<uint64_t>(0x10'00'00'00'00'00'00'00));

        test(Hex2Dec_uint64("1111111111111111"), static_cast<uint64_t>(0x11'11'11'11'11'11'11'11));
        test(Hex2Dec_uint64("0123456789ABCDEF"), static_cast<uint64_t>(0x01'23'45'67'89'AB'CD'EF));
        test(Hex2Dec_uint64("FFFFFFFFFFFFFFFF"), static_cast<uint64_t>(0xFF'FF'FF'FF'FF'FF'FF'FF));

        test(Hex2Dec_uint64("11111111"), static_cast<uint64_t>(0x00'00'00'00'11'11'11'11));
        test(Hex2Dec_uint64("89ABCDEF"), static_cast<uint64_t>(0x00'00'00'00'89'AB'CD'EF));
        test(Hex2Dec_uint64("FFFFFFFF"), static_cast<uint64_t>(0x00'00'00'00'FF'FF'FF'FF));
    }
}
