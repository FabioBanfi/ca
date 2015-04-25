#ifndef ANIMATED_CA_2D_H
#define ANIMATED_CA_2D_H

#include "IAnimatedCA.hpp"

namespace CA {

class IAnimatedCA2D : virtual public IAnimatedCA<C2D>
{
public:

    IAnimatedCA2D();
    void animate();
};

} // CA

#endif // ANIMATED_CA_2D_H
