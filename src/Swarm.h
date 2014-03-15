#pragma once
#include "ofMain.h"

#define SPRING_CONSTANT 0.1f
#define MAX_VELOCITY 30.0f

// This 'swarm' object demonstrates a simple particle system
//  with 'simple harmonic motion'
class Swarm : public ofNode {
	struct particle {
		ofVec3f position;
		ofVec3f velocity;
		ofColor color;
	};

	public:
		Swarm();
		void init(int nParticles, float positionDispersion, float velocityDispersion);
		void customDraw();
		ofLight light;
        void update();

	protected:
		vector<particle>particles;
};