#include "pam_interface/interface.hpp"

namespace pam_interface
{
int clip(int min, int max, int v)
{
    if (v < min)
    {
        return min;
    }

    if (v > max)
    {
        return max;
    }

    return v;
}

}  // namespace pam_interface
