//
//  Dots.cpp
//  plexusTest
//
//  Created by Michael Feldstein on 3/14/14.
//
//

#include "Dots.h"

int plexusDistance = 100;

void Dots::init(int nParticles, float positionDispersion, float velocityDispersion) {
    particles.empty();
    ofSeedRandom();
	//
	ofVec3f position, velocity;
	ofColor color;
	for(int i = 0; i < nParticles; i++){
		position.x = (ofRandom(1.0f) - 0.5f)  * positionDispersion;
		position.y = (ofRandom(1.0f) - 0.5f)  * positionDispersion;
		position.z = (ofRandom(1.0f) - 0.5f)  * positionDispersion / 2.0;
        
		velocity.x = (ofRandom(1.0f) - 0.5f)  * velocityDispersion;
		velocity.y = (ofRandom(1.0f) - 0.5f)  * velocityDispersion;
		velocity.z = (ofRandom(1.0f) - 0.5f)  * velocityDispersion;
        
		Particle newParticle;
		newParticle.position = position;
		newParticle.velocity = velocity;
        
		// add our new particle to the vector
		particles.push_back(newParticle);
	}
}

struct Pair {
    Dots::Particle p1;
    Dots::Particle p2;
    float distance;
};

void Dots::update() {
    for(unsigned int i = 0; i < particles.size(); i++){
        float dt = ofGetLastFrameTime();
        particles[i].position += particles[i].velocity * dt;
    }
}

float roff() {
    float randomness = 5.0f;
    return ofRandom(randomness) - randomness / 2.0f;
}

void Dots::draw() {
    ofSetColor(255,255,255);
    ofPushMatrix();
    ofTranslate(getPosition().x, getPosition().y);
    
    vector<Pair> lines;
    
    for(unsigned int i = 0; i < particles.size(); i++){
        Particle p = particles.at(i);
        ofDrawSphere(p.position, 10);
        for (unsigned int j = i + 1; j < particles.size(); j++) {
            Particle p2 = particles.at(j);
            float dist = p.position.distance(p2.position);
            if (dist < plexusDistance) {
                Pair l;
                l.p1 = p;
                l.p2 = p2;
                l.distance = dist;
                lines.push_back(l);
            }
        }
    }
    for (unsigned int i = 0; i < lines.size(); ++i) {
        Pair p = lines.at(i);
        ofVec3f p1 = p.p1.position;
        ofVec3f p2 = p.p2.position;
        ofSetColor(255, 255, 255, 255 * (plexusDistance - fabs(p.distance)));
        ofLine(p1, p2);
        
    }
    ofPopMatrix();
}