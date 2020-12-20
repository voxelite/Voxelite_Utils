#include "ICodename.hpp"

namespace Voxelite::Util
{
    static const int Codename_MinLength = 4;
    static const int Codename_MaxLength = 32;
    static const std::regex Codename_Regex = std::regex("^[a-z][a-z0-9_]+[a-z0-9]$");

    void ICodename::AssertCodename(const std::string& codename)
    {
        if(codename.size() < Codename_MinLength)
            throw std::runtime_error("Codename is too short");
        if(codename.size() > Codename_MaxLength)
            throw std::runtime_error("Codename is too long");
        if(!std::regex_match(codename, Codename_Regex))
            throw std::runtime_error("Codename does not match regex");
    }

    bool ICodename::CheckCodename(const std::string& codename) noexcept
    {
        if(codename.size() < Codename_MinLength)
            return false;
        if(codename.size() > Codename_MaxLength)
            return false;
        if(!std::regex_match(codename, Codename_Regex))
            return false;
        return true;
    }
}
