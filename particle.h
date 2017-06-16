#ifndef PARTICLE_H
#define PARTICLE_H

#include <stdlib.h>

namespace cTutorial {

struct Particle
{
// public:   <- By default in a 'struct'. In 'class' the default is 'private'. Only difference between class and struct.
    double m_x, m_y;

    Particle();
    virtual ~Particle();

    void update(int interval);
private:
    constexpr static double MAX_SPEED{0.04};
    // Polar coordinates
    double m_speed, m_direction;
    // Displacement
    double m_xDelta, m_yDelta;

    void init();
};

}
#endif // PARTICLE_H
