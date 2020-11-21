#include <Voxelite/Util/Uuid.hpp>
#include <iostream>

static void test(const Voxelite::Util::Uuid& uuid, uint64_t upper, uint64_t lower, const std::string& str)
{
    if(uuid.GetUpperData() != upper)
    {
        std::cerr << std::right << std::hex << uuid.GetUpperData() << std::endl;
        std::cerr << std::right << std::hex << upper << std::endl;
        std::cerr << std::endl;
        throw std::runtime_error("Upper Data does not match");
    }
    if(uuid.GetLowerData() != lower)
    {
        std::cerr << std::right << std::hex << uuid.GetLowerData() << std::endl;
        std::cerr << std::right << std::hex << lower << std::endl;
        std::cerr << std::endl;
        throw std::runtime_error("Lower Data does not match");
    }

    if(uuid.AsString() != str)
    {
        std::cerr << uuid.AsString() << std::endl;
        std::cerr << str << std::endl;
        std::cerr << std::endl;
        throw std::runtime_error("UUID String does not match");
    }
}
static void test(const Voxelite::Util::Uuid& uuid, const std::string& str)
{
    if(uuid.AsString() != str)
    {
        std::cerr << uuid.AsString() << std::endl;
        std::cerr << str << std::endl;
        std::cerr << std::endl;
        throw std::runtime_error("UUID String does not match");
    }
}

int main(int argc, const char** argv)
{
    using namespace Voxelite::Util;

    test(Uuid(), 0, 0, "00000000-0000-0000-0000-000000000000");

    test(Uuid(0x00, 0x01), 0x00, 0x01, "00000000-0000-0000-0000-000000000001");
    test(Uuid(0x00, 0x10), 0x00, 0x10, "00000000-0000-0000-0000-000000000010");

    test(Uuid(0x01, 0x00), 0x01, 0x00, "00000000-0000-0001-0000-000000000000");
    test(Uuid(0x10, 0x00), 0x10, 0x00, "00000000-0000-0010-0000-000000000000");

    test(Uuid(0x01, 0x01), 0x01, 0x01, "00000000-0000-0001-0000-000000000001");

    test(Uuid("0123456789ABCDEFFEDCBA9876543210"), "01234567-89AB-CDEF-FEDC-BA9876543210");
    test(Uuid("01234567-89AB-CDEF-FEDC-BA9876543210"), "01234567-89AB-CDEF-FEDC-BA9876543210");
    test(Uuid("{01234567-89AB-CDEF-FEDC-BA9876543210}"), "01234567-89AB-CDEF-FEDC-BA9876543210");

    {
        Uuid uuid = Uuid("123e4567-e89b-12d3-a456-426614174000");
        if(uuid.GetVersion() != 1)
        {
            std::cerr << "Expected version 1 but got " << static_cast<uint32_t>(uuid.GetVersion()) << std::endl;
            std::cerr << uuid.AsString() << std::endl;
            throw std::runtime_error("Wrong version");
        }
        if(uuid.GetVariant() != 1)
        {
            std::cerr << "Expected variant 1 but got " << static_cast<uint32_t>(uuid.GetVariant()) << std::endl;
            std::cerr << uuid.AsString() << std::endl;
            throw std::runtime_error("Wrong variant");
        }
        //TODO Time
        if(uuid.GetClockSequence() != 9302)
        {
            std::cerr << "Expected clock 9302 but got " << static_cast<uint32_t>(uuid.GetClockSequence()) << std::endl;
            std::cerr << uuid.AsString() << std::endl;
            throw std::runtime_error("Wrong clock");
        }
        //TODO Node
    }
    {
        Uuid uuid4 = Uuid::CreateVersion4();
        if(uuid4.GetVersion() != 4)
        {
            std::cerr << "Expected version 4 but got " << static_cast<uint32_t>(uuid4.GetVersion()) << std::endl;
            std::cerr << uuid4.AsString() << std::endl;
            throw std::runtime_error("Wrong version");
        }
    }
    {
        Uuid uuid3 = Uuid::CreateVersion3(Uuid::Nil, "test");
        if(uuid3.GetVersion() != 3)
        {
            std::cerr << "Expected version 3 but got " << static_cast<uint32_t>(uuid3.GetVersion()) << std::endl;
            std::cerr << uuid3.AsString() << std::endl;
            throw std::runtime_error("Wrong version");
        }
        std::string uuidString = "96E17D7A-AC89-38CF-95E1-BF5098DA34E1";
        if(uuid3.AsString() != uuidString)
        {
            std::cerr << "Got:      " << uuid3 << std::endl;
            std::cerr << "Expected: " << uuidString << std::endl;
            throw std::runtime_error("Wrong UUID3");
        }
    }
    {
        Uuid uuid5 = Uuid::CreateVersion5(Uuid::Nil, "test");
        if(uuid5.GetVersion() != 5)
        {
            std::cerr << "Expected version 5 but got " << static_cast<uint32_t>(uuid5.GetVersion()) << std::endl;
            std::cerr << uuid5.AsString() << std::endl;
            throw std::runtime_error("Wrong version");
        }
        std::string uuidString = "E8B764DA-5FE5-51ED-8AF8-C5C6ECA28D7A";
        if(uuid5.AsString() != uuidString)
        {
            std::cerr << "Got:      " << uuid5 << std::endl;
            std::cerr << "Expected: " << uuidString << std::endl;
            throw std::runtime_error("Wrong UUID5");
        }
    }
    {
        Uuid uuid = Uuid("96c9c974-2bf8-11eb-9c66-4f3f95abfd8a");
        if(uuid.GetVersion() != 1)
        {
            std::cerr << "Expected version 1 but got " << static_cast<uint32_t>(uuid.GetVersion()) << std::endl;
            std::cerr << uuid.AsString() << std::endl;
            throw std::runtime_error("Wrong version");
        }
        if(uuid.GetVariant() != 1)
        {
            std::cerr << "Expected variant 1 but got " << static_cast<uint32_t>(uuid.GetVariant()) << std::endl;
            std::cerr << uuid.AsString() << std::endl;
            throw std::runtime_error("Wrong variant");
        }
    }
}
