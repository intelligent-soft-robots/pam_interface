#pragma once

#include <cmath>

namespace pam_interface
{
/**
 * Returns addition of given to_rotate variable with
 * rotation_angle. Angles are casted between minus pi
 * and plus pi.
 *
 * Variables should be given in radian.
 */
double rotate(double to_rotate, double rotation_angle);

}  // namespace pam_interface
