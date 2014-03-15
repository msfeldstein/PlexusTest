//
//  Dots.cpp
//  plexusTest
//
//  Created by Michael Feldstein on 3/14/14.
//
//

#include "Dots.h"

void Dots::init(int nParticles, float positionDispersion, float velocityDispersion) {
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
};

void Dots::update() {
    for(unsigned int i = 0; i < particles.size(); i++){
        Particle p = particles.at(i);
        p.position += p.velocity;
    }
}

void Dots::draw() {
    ofPushMatrix();
    ofTranslate(getPosition().x, getPosition().y);
    
    vector<Pair> lines;
    
    for(unsigned int i = 0; i < particles.size(); i++){
        Particle p = particles.at(i);
        ofDrawSphere(p.position, 10);
        for (unsigned int j = i + 1; j < particles.size(); j++) {
            Particle p2 = particles.at(j);
            if (ofDist(p.position.x, p.position.y, p2.position.x, p2.position.y) < 100) {
                Pair l;
                l.p1 = p;
                l.p2 = p2;
                lines.push_back(l);
            }
        }
    }
    for (unsigned int i = 0; i < lines.size(); ++i) {
        Pair p = lines.at(i);
        ofVec3f p1 = p.p1.position;
        ofVec3f p2 = p.p2.position;
        
        ofLine(p1, p2);
        
    }
    ofPopMatrix();
}