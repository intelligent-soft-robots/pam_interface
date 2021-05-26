#pragma once

#include <iostream>

namespace pam_interface
{
class JointState

{
public:
    template <class Archive>
    void serialize(Archive &archive)
    {
        archive(desired_agonist,
                desired_antagonist,
                agonist,
                antagonist,
                encoder,
                position,
                velocity,
                reference_found);
    }

    int desired_agonist;
    int desired_antagonist;
    int agonist;
    int antagonist;
    int encoder;
    double position;
    double velocity;
    bool reference_found;
};

}  // namespace pam_interface
