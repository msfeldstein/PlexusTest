//
//  Dots.h
//  plexusTest
//
//  Created by Michael Feldstein on 3/14/14.
//
//

#ifndef __plexusTest__Dots__
#define __plexusTest__Dots__

#include <iostream>
#pragma once
#include "ofMain.h"



class Dots : public ofNode {
public:
    struct Particle {
		ofVec3f position;
		ofVec3f velocity;
        vector<Particle*> neighbors;
	};

    void init(int nParticles, float positionDispersion, float velocityDispersion);
    void draw();
    void update();
    vector<Particle> particles;
    void attract(Particle& p, Particle& p2);
    float attraction;
    
};

#endif /* defined(__plexusTest__Dots__) */

