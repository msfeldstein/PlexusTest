//
//  Dots.cpp
//  plexusTest
//
//  Created by Michael Feldstein on 3/14/14.
//
//

#include "Dots.h"

int plexusDistance = 100;

Dots::Dots() {
    drawDots = true;
    drawLines = true;
    drawTriangles = true;
}

void Dots::init(int nParticles, float positionDispersion, float velocityDispersion) {
    particles.clear();
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
    attraction = 0.1;
}



void Dots::update() {
    for(unsigned int i = 0; i < particles.size(); i++){
        particles[i].neighbors.clear();
    }
    for(unsigned int i = 0; i < particles.size(); i++){
        float dt = ofGetLastFrameTime();
        particles[i].position += particles[i].velocity * dt;
        
        for (unsigned int j = i + 1; j < particles.size(); j++) {
            float dist = particles[i].position.distance(particles[j].position);
            if (dist < plexusDistance) {
                particles[i].neighbors.push_back(&particles[j]);
                attract(particles[i], particles[j]);
            }
        }
        
        if (abs(getPosition().distance(particles[i].position)) > 500) {
            particles[i].velocity -= particles[i].position.normalized() * 10;
        }
    }
}

float roff() {
    float randomness = 5.0f;
    return ofRandom(randomness) - randomness / 2.0f;
}

void Dots::attract(Dots::Particle& p1, Dots::Particle& p2) {
    ofVec3f direction = p1.position - p2.position;
    p1.velocity -= direction.normalized() * attraction;
    p2.velocity += direction.normalized() * attraction;
}

void Dots::draw() {
    ofSetColor(255,255,255);
    ofPushMatrix();
    ofDisableDepthTest();
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofTranslate(getPosition().x, getPosition().y);
    
    if (drawLines) {
        // Draw the lines
        for(unsigned int i = 0; i < particles.size(); i++){
            for (unsigned int j = 0; j < particles[i].neighbors.size(); ++j) {
                ofVec3f p1 = particles[i].position;
                ofVec3f p2 = particles[i].neighbors.at(j)->position;
                float distance = p1.distance(p2);
                ofSetColor(255, 255, 255, 200 - fabs(distance) * 2);
                ofLine(p1, p2);

            }
        }
    }
    
    if (drawTriangles) {
        // Draw the triangles
        for(unsigned int i = 0; i < particles.size(); i++){
            for (unsigned int j = 0; j < particles[i].neighbors.size(); ++j) {
                Particle* firstNeighbor = particles[i].neighbors.at(j);
                for (unsigned int k = 0; k < j; ++k) {
                    Particle* secondNeighbor = particles[i].neighbors.at(k);
                    for (unsigned int l = 0; l < secondNeighbor->neighbors.size(); l++) {
                        if (secondNeighbor->neighbors.at(l) == firstNeighbor) {
                            // Match!
                            float d1 = particles[i].position.distance(firstNeighbor->position);
                            float d2 = particles[i].position.distance(secondNeighbor->position);
                            float d3 = firstNeighbor->position.distance(secondNeighbor->position);
                            float largestDistance = max(d1, max(d2,d3));
                            ofSetColor(255, 255, 255, 100 - largestDistance);
                            ofTriangle(particles[i].position, firstNeighbor->position, secondNeighbor->position);
                        }
                    }
                }
            }
        }
    }
    
    if (drawDots) {
        // Draw the spheres
        ofSetColor(255,255,255);
        for(unsigned int i = 0; i < particles.size(); i++){
            Particle p = particles.at(i);
            ofDrawSphere(p.position, 2);
        }
    }

    ofPopMatrix();
}