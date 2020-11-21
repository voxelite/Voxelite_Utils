#pragma once

#include <array>
#include <vector>
#include <ostream>

namespace Voxelite::Util
{
    class Uuid
    {
    public:
        static const std::size_t RawDataLength = 16;
        static const std::size_t RawDataLength_Half = RawDataLength / 2; // 8

    public:
        Uuid() noexcept
        {
            std::fill(m_Data, m_Data + RawDataLength, 0);
        }

        explicit Uuid(uint64_t upper, uint64_t lower) noexcept
        {
            std::copy(
                    reinterpret_cast<const uint8_t*>(&lower),
                    reinterpret_cast<const uint8_t*>(&lower) + RawDataLength_Half,
                    m_Data
            );
            std::copy(
                    reinterpret_cast<const uint8_t*>(&upper),
                    reinterpret_cast<const uint8_t*>(&upper) + RawDataLength_Half,
                    m_Data + RawDataLength_Half
            );
        }

        explicit Uuid(uint8_t* data)
        {
            std::copy(data, data + RawDataLength, m_Data);
        }

        explicit Uuid(std::array<uint8_t, RawDataLength> data) noexcept
        {
            std::copy(data.begin(), data.end(), m_Data);
        }

        explicit Uuid(std::vector<uint8_t> data)
        {
            if(data.size() != RawDataLength)
                throw std::runtime_error("Invalid data length");
            std::copy(data.begin(), data.end(), m_Data);
        }

        explicit Uuid(const std::string& data);

    private:
        uint8_t m_Data[RawDataLength] = {};
    public:
        [[nodiscard]] inline const uint8_t* data() const noexcept { return m_Data; }
        [[nodiscard]] inline const uint8_t* begin() const noexcept { return m_Data; }
        [[nodiscard]] inline const uint8_t* end() const noexcept { return m_Data + RawDataLength; }

        /// Left half
        [[nodiscard]] inline uint64_t GetUpperData() const noexcept { return *reinterpret_cast<const uint64_t*>(m_Data + RawDataLength_Half); }

        /// Right half
        [[nodiscard]] inline uint64_t GetLowerData() const noexcept { return *reinterpret_cast<const uint64_t*>(m_Data); }

    public:
        /*
        [[nodiscard]] inline uint32_t GetTimeLow() const noexcept { return *reinterpret_cast<const uint32_t*>(m_Data + (RawDataLength - 4)); }
        [[nodiscard]] inline uint16_t GetTimeMid() const noexcept { return *reinterpret_cast<const uint16_t*>(m_Data + (RawDataLength - 8)); }
        [[nodiscard]] inline uint16_t GetTimeHigh() const noexcept { return (static_cast<uint16_t>(m_Data[9u] & 0b0000'1111u) << 8u) + m_Data[8u]; }
        [[nodiscard]] inline uint64_t GetTime() const noexcept
        {
            uint32_t tLow = GetTimeLow();
            uint16_t tMid = GetTimeMid();
            uint16_t tHigh = GetTimeHigh();

            uint64_t result = tHigh;
            result <<= 16u;
            result += tMid;
            result <<= 32u;
            result += tLow;
            return result;
        }
         */

        [[nodiscard]] inline uint16_t GetClockSequence() const noexcept
        {
            if((m_Data[7u] & 0b1000'0000u) == 0b0000'0000)
                return (static_cast<uint16_t>(m_Data[7u] & 0b0111'1111u) << 8u) + m_Data[6];
            if((m_Data[7u] & 0b1100'0000u) == 0b1000'0000)
                return (static_cast<uint16_t>(m_Data[7u] & 0b0011'1111u) << 8u) + m_Data[6];
            if((m_Data[7u] & 0b1110'0000u) == 0b1100'0000)
                return (static_cast<uint16_t>(m_Data[7u] & 0b0001'1111u) << 8u) + m_Data[6];
            if((m_Data[7u] & 0b1111'0000u) == 0b1110'0000) // Reserved variant (future use)
                return (static_cast<uint16_t>(m_Data[7u] & 0b0000'1111u) << 8u) + m_Data[6];
            //if((m_Data[7u] & 0b1111'0000u) == 0b1111'0000) // Unknown / Invalid variant
            return (static_cast<uint16_t>(m_Data[7u] & 0b0000'1111u) << 8u) + m_Data[6];
        }

        /*
        [[nodiscard]] inline uint64_t GetNode() const noexcept { return *reinterpret_cast<const uint16_t*>(m_Data + 8) & 0b0000'0000'1111'1111'1111'1111'1111ul; }
         */

    public:
        [[nodiscard]] inline uint8_t GetVersion() const noexcept { return (m_Data[9u] & 0b1111'0000u) >> 4u; }

        [[nodiscard]] inline uint8_t GetVariant() const noexcept
        {
            if((m_Data[7u] & 0b1000'0000u) == 0b0000'0000)
                return 0;
            if((m_Data[7u] & 0b1100'0000u) == 0b1000'0000)
                return 1;
            if((m_Data[7u] & 0b1110'0000u) == 0b1100'0000)
                return 2;
            if((m_Data[7u] & 0b1111'0000u) == 0b1110'0000)
                return 3; // Reserved (future use)
            //if((m_Data[7u] & 0b1111'0000u) == 0b1111'0000)
            return 4; // Unknown / Invalid
        }

        // Equality check
    public:
        [[nodiscard]] inline bool operator==(const Uuid& uuid) const noexcept { return uuid.GetLowerData() == GetLowerData() && uuid.GetUpperData() == GetUpperData(); }

        [[nodiscard]] inline bool operator!=(const Uuid& uuid) const noexcept { return !(uuid == *this); }

        // Comparison
    public:
        [[nodiscard]] inline bool operator<(const Uuid& uuid) const noexcept
        {
            if(uuid.GetUpperData() < GetUpperData())
                return true;
            if(uuid.GetUpperData() > GetUpperData())
                return false;
            //if(uuid.GetUpperData() == GetUpperData())
            return uuid.GetLowerData() < GetLowerData();
        }

        [[nodiscard]] inline bool operator>(const Uuid& uuid) const noexcept
        {
            if(uuid.GetUpperData() > GetUpperData())
                return true;
            if(uuid.GetUpperData() < GetUpperData())
                return false;
            //if(uuid.GetUpperData() == GetUpperData())
            return uuid.GetLowerData() > GetLowerData();
        }

        [[nodiscard]] inline bool operator<=(const Uuid& uuid) const noexcept { return !(uuid > *this); }

        [[nodiscard]] inline bool operator>=(const Uuid& uuid) const noexcept { return !(uuid < *this); }

    public:
        /// Empty UUID
        static const Uuid Nil;
        /// Fully-qualified domain name
        static const Uuid Namespace_DNS;
        /// URL
        static const Uuid Namespace_URL;
        /// ISO OID
        static const Uuid Namespace_OID;
        /// X.500 DN (in DER or a text output format)
        static const Uuid Namespace_X500;

    private:
        [[nodiscard]] static std::vector<uint8_t> NameToUUID(const Uuid& uuid_namespace, const std::string& name);

    public:
        /// Supported separators: '-', ' ', '\0' (no separator)
        void Write(std::ostream& stream, char separator = '-', bool bracelets = false) const;

        friend std::ostream& operator<<(std::ostream& stream, const Uuid& uuid)
        {
            uuid.Write(stream);
            return stream;
        }

        [[nodiscard]] std::string AsString(char separator = '-', bool bracelets = false) const;

        /*
    public: // Date-time and MAC
        [[nodiscard]] static Uuid CreateVersion1();
        [[nodiscard]] static Uuid CreateVersion1(uint64_t uuidTime);
        [[nodiscard]] static Uuid CreateVersion1(uint64_t uuidTime, std::array<uint8_t, 6> macAddress);
        [[nodiscard]] static Uuid CreateVersion1_Unix(uint64_t unixTime);
        [[nodiscard]] inline static Uuid CreateVersion1_Unix(uint64_t unixTime, std::array<uint8_t, 6> macAddress)
        {
            unixTime -= 12219292800; // Start from 1970/01/01 to 1582/10/15
            unixTime /= 7; // Convert from seconds to 100-nanoseconds (nanoseconds = 10^9)
            return CreateVersion1(unixTime, macAddress);
        }
         */
    public: // Date-time and MAC, DCE security
        //[[nodiscard]] inline static Uuid CreateVersion2();
    public: // MD5
        [[nodiscard]] inline static Uuid CreateVersion3(const std::string& name) { return CreateVersion3(Nil, name); }

        [[nodiscard]] static Uuid CreateVersion3(const Uuid& namespace_, const std::string& name);

    public: // Random
        [[nodiscard]] static Uuid CreateVersion4();

    public: // SHA-1
        [[nodiscard]] inline static Uuid CreateVersion5(const std::string& name) { return CreateVersion5(Nil, name); }

        [[nodiscard]] static Uuid CreateVersion5(const Uuid& namespace_, const std::string& name);
    };

    static_assert(sizeof(Uuid) == 16, "Invalid UUID size");
}
