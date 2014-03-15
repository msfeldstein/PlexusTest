#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    dots.init(70, ofGetWidth() / 2, 20);
    cam.enableMouseInput();
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

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    light.setGlobalPosition(x, y, 0);
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
