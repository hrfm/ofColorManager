#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    private:
    
        ofxOscSender _sender;
        
        ofImage _img;
        
        ofPoint _p;
        ofColor _b4color;
        ofColor _color;
        
        int _displayText;
        
        double _speed;
        double _radian;
        double _radius;
        
        int _lock;
        int _aKey;
        int _autoMode;
        
};
