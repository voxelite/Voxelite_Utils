#include "Uuid.hpp"

#include <sstream>
#include <ctime>
#include <random>
#include <openssl/sha.h>
#include <openssl/md5.h>

#include "Hex.hpp"

namespace Voxelite::Util
{
    const Uuid Uuid::Nil  = Uuid(0, 0);
    const Uuid Uuid::Namespace_DNS  = Uuid("6ba7b810-9dad-11d1-80b4-00c04fd430c8");
    const Uuid Uuid::Namespace_URL  = Uuid("6ba7b811-9dad-11d1-80b4-00c04fd430c8");
    const Uuid Uuid::Namespace_OID  = Uuid("6ba7b812-9dad-11d1-80b4-00c04fd430c8");
    const Uuid Uuid::Namespace_X500 = Uuid("6ba7b814-9dad-11d1-80b4-00c04fd430c8");

    inline static void WriteHex(std::ostream& stream, const uint8_t& byte)
    {
        char upperChar, lowerChar;
        Dec2Hex(byte, upperChar, lowerChar);
        stream << upperChar << lowerChar;
    }

    void Uuid::Write(std::ostream& stream, char separator, bool bracelets) const
    {
        if(bracelets)
            stream << '{';

        for(int i = RawDataLength - 1; i >= 0; i--)
        {
            const uint8_t& byte = m_Data[i];

            WriteHex(stream, byte);

            if(separator != '\0')
            {
                switch(i)
                {
                    case 6: // 8
                    case 8: // 4
                    case 10: // 4
                    case 12: // 4
                        stream << separator;
                        break;
                    default:
                        break;
                }
            }
        }

        if(bracelets)
            stream << '}';
    }

    std::string Uuid::AsString(char separator, bool bracelets) const
    {
        std::stringstream ss;
        Write(ss, separator, bracelets);
        return ss.str();
    }
}

namespace Voxelite::Util
{
    /*
    Uuid Uuid::CreateVersion1()
    {
        return CreateVersion1_Unix(std::time(nullptr));
    }

    static std::array<uint8_t, 6> GetMacAddress()
    {
        //TODO
    }

    Uuid Uuid::CreateVersion1(uint64_t uuidTime) { return CreateVersion1(uuidTime, GetMacAddress()); }
    Uuid Uuid::CreateVersion1_Unix(uint64_t unixTime) { return Uuid::CreateVersion1_Unix(unixTime, GetMacAddress()); }

    Uuid Uuid::CreateVersion1(uint64_t uuidTime, std::array<uint8_t, 6> macAddress)
    {
        //TODO
    }
     */

    std::vector<uint8_t> Uuid::NameToUUID(const Uuid& uuid_namespace, const std::string& name)
    {
        std::vector<uint8_t> bytes(RawDataLength + name.length());
        std::copy(uuid_namespace.begin(), uuid_namespace.end(), bytes.data()); // UUID
        std::copy(name.begin(), name.end(), bytes.data() + RawDataLength); // name
        return bytes;
    }

    Uuid Uuid::CreateVersion3(const Uuid& namespace_, const std::string& name)
    {
        std::vector<uint8_t> toHash = NameToUUID(namespace_, name);

        uint8_t bytes[MD5_DIGEST_LENGTH];
        MD5(toHash.data(), toHash.size(), bytes);
        std::reverse(bytes, bytes + RawDataLength);

        bytes[9] = (bytes[9] & 0b0000'1111u) + 0b0011'0000u; // Version 3
        bytes[7] = (bytes[7] & 0b0011'1111u) + 0b1000'0000u; // Variant 2

        return Uuid(bytes);
    }

    Uuid Uuid::CreateVersion5(const Uuid& namespace_, const std::string& name)
    {
        std::vector<uint8_t> toHash = NameToUUID(namespace_, name);

        uint8_t bytes[SHA_DIGEST_LENGTH];
        SHA1(toHash.data(), toHash.size(), bytes);
        std::reverse(bytes, bytes + RawDataLength);

        bytes[9] = (bytes[9] & 0b0000'1111u) + 0b0101'0000u; // Version 5
        bytes[7] = (bytes[7] & 0b0011'1111u) + 0b1000'0000u; // Variant 1

        return Uuid(bytes);
    }

    std::random_device rnd;
    std::mt19937_64 rnd_mt(rnd());
    std::uniform_int_distribution<uint64_t> rnd_dist(0, std::numeric_limits<uint64_t>::max());

    Uuid Uuid::CreateVersion4()
    {
        uint64_t upper = rnd_dist(rnd_mt);
        uint64_t lower = rnd_dist(rnd_mt);

        uint8_t bytes[RawDataLength];
        std::copy(reinterpret_cast<const uint8_t*>(&upper), reinterpret_cast<const uint8_t*>(&upper) + RawDataLength_Half, bytes);
        std::copy(reinterpret_cast<const uint8_t*>(&lower), reinterpret_cast<const uint8_t*>(&lower) + RawDataLength_Half, bytes + RawDataLength_Half);

        bytes[9] = (bytes[9] & 0b0000'1111u) + 0b0100'0000u; // Version 4
        bytes[7] = (bytes[7] & 0b0001'1111u) + 0b1100'0000u; // Variant 2

        return Uuid(bytes);
    }

    Uuid::Uuid(const std::string& data)
    {
        switch (data.length())
        {
            case 32: // 00000000000000000000000000000000
            {
                for(int i = RawDataLength - 1, si = 0; i >= 0; i--, si += 2)
                {
                    assert(si < data.length());
                    assert(si + 1 < data.length());
                    m_Data[i] = Util::Hex2Dec_uint8(data.c_str() + si);
                }

                break;
            }
            case 36: // 00000000-0000-0000-0000-000000000000
            {
                m_Data[15]  = Util::Hex2Dec_uint8(data.c_str() + 0);
                m_Data[14]  = Util::Hex2Dec_uint8(data.c_str() + 2);
                m_Data[13]  = Util::Hex2Dec_uint8(data.c_str() + 4);
                m_Data[12]  = Util::Hex2Dec_uint8(data.c_str() + 6);
                // -
                m_Data[11]  = Util::Hex2Dec_uint8(data.c_str() + 9);
                m_Data[10]  = Util::Hex2Dec_uint8(data.c_str() + 11);
                // -
                m_Data[9]  = Util::Hex2Dec_uint8(data.c_str() + 14);
                m_Data[8]  = Util::Hex2Dec_uint8(data.c_str() + 16);
                // -
                m_Data[7]  = Util::Hex2Dec_uint8(data.c_str() + 19);
                m_Data[6]  = Util::Hex2Dec_uint8(data.c_str() + 21);
                // -
                m_Data[5] = Util::Hex2Dec_uint8(data.c_str() + 24);
                m_Data[4] = Util::Hex2Dec_uint8(data.c_str() + 26);
                m_Data[3] = Util::Hex2Dec_uint8(data.c_str() + 28);
                m_Data[2] = Util::Hex2Dec_uint8(data.c_str() + 30);
                m_Data[1] = Util::Hex2Dec_uint8(data.c_str() + 32);
                m_Data[0] = Util::Hex2Dec_uint8(data.c_str() + 34);

                break;
            }
            case 38: // {00000000-0000-0000-0000-000000000000}
            {
                m_Data[15]  = Util::Hex2Dec_uint8(data.c_str() + 1);
                m_Data[14]  = Util::Hex2Dec_uint8(data.c_str() + 3);
                m_Data[13]  = Util::Hex2Dec_uint8(data.c_str() + 5);
                m_Data[12]  = Util::Hex2Dec_uint8(data.c_str() + 7);
                // -
                m_Data[11]  = Util::Hex2Dec_uint8(data.c_str() + 10);
                m_Data[10]  = Util::Hex2Dec_uint8(data.c_str() + 12);
                // -
                m_Data[9]  = Util::Hex2Dec_uint8(data.c_str() + 15);
                m_Data[8]  = Util::Hex2Dec_uint8(data.c_str() + 17);
                // -
                m_Data[7]  = Util::Hex2Dec_uint8(data.c_str() + 20);
                m_Data[6]  = Util::Hex2Dec_uint8(data.c_str() + 22);
                // -
                m_Data[5] = Util::Hex2Dec_uint8(data.c_str() + 25);
                m_Data[4] = Util::Hex2Dec_uint8(data.c_str() + 27);
                m_Data[3] = Util::Hex2Dec_uint8(data.c_str() + 29);
                m_Data[2] = Util::Hex2Dec_uint8(data.c_str() + 31);
                m_Data[1] = Util::Hex2Dec_uint8(data.c_str() + 33);
                m_Data[0] = Util::Hex2Dec_uint8(data.c_str() + 35);

                break;
            }
            default:
                throw std::runtime_error("Unsupported UUID string length");
        }
    }
}
