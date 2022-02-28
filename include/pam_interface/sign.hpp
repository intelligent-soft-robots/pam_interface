#pragma once

namespace pam_interface
{
enum Sign
{
    AGONIST,
    ANTAGONIST
};
static const Sign signs[2] = {Sign::AGONIST, Sign::ANTAGONIST};

/**
 * Switch sign, i.e. returns AGONIST
 * if sign is ANTAGONIST, and vice versa
 */
Sign switch_sign(const Sign& sign);

}  // namespace pam_interface
