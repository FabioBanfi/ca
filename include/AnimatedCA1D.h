#ifndef ANIMATED_CA_1D_H
#define ANIMATED_CA_1D_H

#include "AnimatedCA.hpp"

namespace CA {

class AnimatedCA1D : virtual public AnimatedCA<C1D>
{
protected:

    AnimatedCA1D();

public:

    void animate();
};

} // CA

#endif // ANIMATED_CA_1D_H
