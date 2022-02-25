#include "pam_interface/state/robot.hpp"

namespace pam_interface
{
namespace internal
{
int next_id()
{
    static int id = 0;
    id++;
    return id;
}
}  // namespace internal
}  // namespace pam_interface
