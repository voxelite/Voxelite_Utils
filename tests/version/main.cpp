#include <Voxelite/Util/Version.hpp>
#include <iostream>

int main(int argc, const char** argv)
{
    using namespace Voxelite::Util;

    {
        uint32_t major, minor, patch;
        BreakVersion(MakeVersion(1,2,3), major, minor, patch);
        if(major != 1 || minor != 2 || patch != 3)
        {
            std::cerr << "Major: " << major << std::endl;
            std::cerr << "Minor: " << minor << std::endl;
            std::cerr << "Patch: " << patch << std::endl;
            throw std::runtime_error("Failed to Make&Break Version 1.2_3");
        }
    }

    if(MakeVersionString(1,2,3) != "1.2_3")
    {
        std::cerr << MakeVersionString(1,2,3) << std::endl;
        throw std::runtime_error("Invalid Version String for 1.2_3");
    }

    {
        uint32_t major, minor, patch;
        if(!BreakVersionString("1.2_3", major, minor, patch))
        {
            std::cerr << "Major: " << major << std::endl;
            std::cerr << "Minor: " << minor << std::endl;
            std::cerr << "Patch: " << patch << std::endl;
            throw std::runtime_error("Failed to Break Version String 1.2_3 into parts");
        }
    }

    if(BreakVersionString("1.2_3") != MakeVersion(1,2,3))
    {
        throw std::runtime_error("Failed to Break Version String 1.2_3");
    }
}
