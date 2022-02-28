#include "pam_interface/rotation.hpp"

namespace pam_interface
{
double rotate(double to_rotate, double rotation_angle)
{
    // [x,y] : vector orientated at angle "to rotate"
    double x = std::cos(to_rotate);
    double y = std::sin(to_rotate);
    // sin and cos of rotation angle
    double c = std::cos(rotation_angle);
    double s = std::sin(rotation_angle);
    // performing rotation of [x,y] and
    // returning the orientation of the transformed
    // vector
    double r = atan2(x * s + y * c, x * c - y * s);
    return r;
}

}  // namespace pam_interface
