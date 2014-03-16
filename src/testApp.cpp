#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    dots.init(100, ofGetWidth() / 2, 20);
    cam.enableMouseInput();
    light.setPosition(ofGetWidth(), 100, 400);
    midiIn.listPorts(); // via instance
	//ofxMidiIn::listPorts(); // via static as well
    
	// open port by number (you may need to change this)
	midiIn.openPort(1);
    midiIn.ignoreTypes(false, false, false);
    midiIn.addListener(this);
    midiIn.setVerbose(true);
}

//--------------------------------------------------------------
void testApp::update(){
    dots.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackgroundGradient(ofColor(0,0,0), ofColor(90,90,90));
    cam.begin();
    ofEnableLighting();
    ofEnableDepthTest();
    light.enable();
    
    dots.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == 'r') {
        dots.init(70, ofGetWidth() / 2, 20);
    }
}

void testApp::newMidiMessage(ofxMidiMessage& msg) {
    std::cout << "id:"<<msg.control <<" val:"<<msg.value<<"\n";
    if (msg.control == 14) {
        dots.attraction = msg.value / 227.0;
    } else if (msg.control == 15) {
        
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
