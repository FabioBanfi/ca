#ifndef ANIMATED_CA_1D_H
#define ANIMATED_CA_1D_H

#include "IAnimatedCA.hpp"

namespace CA {

class IAnimatedCA1D : virtual public IAnimatedCA<C1D>
{
public:

    IAnimatedCA1D();
    void animate();
};

} // CA

#endif // ANIMATED_CA_1D_H
