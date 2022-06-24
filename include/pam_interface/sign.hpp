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
 * Switches agonist or antagonist state of passed Sign object.
 *
 * i.e. if sign is AGONIST, returns ANTAGONIST and vice versa.
 *
 * @param sign Sign object
 * @return Sign object with switched agonist/antagonist state
 */
Sign switch_sign(const Sign& sign);

}  // namespace pam_interface
