#include "pam_interface/sign.hpp"

namespace pam_interface
{
Sign switch_sign(const Sign& sign)
{
    if (sign == Sign::AGONIST) return Sign::ANTAGONIST;
    return Sign::AGONIST;
}

}  // namespace pam_interface
