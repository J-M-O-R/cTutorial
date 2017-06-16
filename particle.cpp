#include <math.h>
#include "particle.h"

namespace cTutorial {

Particle::Particle(): m_x{0}, m_y{0} {
    init();
}

Particle::~Particle() {

}

void Particle::init() {
    m_x = 0;
    m_y = 0;
    /* double(rand())/RAND_MAX <- gives random numbers from 0.0 to 1.0
     * the numerator is cast to double because both variables are int, hence
     * it would be a division of ints which in this case would be either 0
     * or 1 always. Forcing one variable to double forces a double division.
     */
    // We want the direction in a polar coordinates sytem.
    // Radians in this case, i.e. from 0 to 2*Pi
    m_direction = (2 * M_PI * rand())/RAND_MAX;
    m_speed = (MAX_SPEED * rand())/RAND_MAX;
    /* The speed is uniform distributed between 0 and MAX_SPEED. For increasing
     * the differences in speed among particles we square the speeds. This
     * gives a less uniform motion.
     */
    m_speed *= m_speed;
}

void Particle::update(int interval) {
    // Adding a side motion to the particles so they don't move in a straight path.
    m_direction += interval * 0.0003;

    m_xDelta = m_speed * cos(m_direction);
    m_yDelta = m_speed * sin(m_direction);

    m_x += m_xDelta * interval;
    m_y += m_yDelta * interval;
    // The particles that go outside of the particle box get reinitialized to the center.
    if(m_x <= -1 || m_x > 1 ||
       m_y <= -1 || m_y > 1) {
        init();
    }
    // Let reinitialize some random particles with every update
    if(rand() < RAND_MAX/100) { // <- 1 in 100 chance.
        init();
    }
}

}
