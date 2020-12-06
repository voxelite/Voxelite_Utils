#pragma once

#include <string>
#include <regex>

namespace Voxelite::Util
{
    class ICodename
    {
    public:
        explicit ICodename()
                : Codename()
        {
        }
        explicit ICodename(std::string codename)
                : Codename(std::move(codename))
        {
        }
    public:
        virtual ~ICodename() = default;

    public:
        static void AssertCodename(const std::string& codename);
        [[nodiscard]] static bool CheckCodename(const std::string& codename) noexcept;

    public:
        inline void AssertCodename() const { AssertCodename(Codename); }
        [[nodiscard]] inline bool CheckCodename() const noexcept { return CheckCodename(Codename); }

    public:
        std::string Codename;
    };
}
