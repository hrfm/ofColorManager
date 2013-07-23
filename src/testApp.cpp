#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetFrameRate(30);
    ofSetVerticalSync(true);
    ofSetBackgroundAuto(true);
    ofBackground(28, 28, 28);
	
    
    _sender.setup("127.0.0.1", 10000);
    
    _img.loadImage("ColorChartHex.png");
    
    _color.r = 255;
    _color.g = 255;
    _color.b = 255;
    
    _p.x = ofGetWidth() / 2;
    _p.y = ofGetHeight() / 2;
    
    _displayText = 0;
    
    _radius   = 0;
    _speed    = 0.1;
    
    _aKey     = 0;
    _lock     = 0;
    _autoMode = 0;
    
}

//--------------------------------------------------------------
void testApp::update(){
   if( _b4color != _color ){
       ofxOscMessage m;
       m.setAddress("/color");
       m.addIntArg( _color.r );
       m.addIntArg( _color.g );
       m.addIntArg( _color.b );
       _sender.sendMessage(m);
       _b4color = _color;
   };
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetColor(255);
    _img.draw(0,0);
    
    float w = ofGetWidth()/2;
    float h = ofGetHeight()/2;
    if(_autoMode == 1 ){
        _p.x = floor( w + _radius * cos( _radian ) );
        _p.y = floor( h + _radius * sin( _radian ) );
        ofNoFill();
        ofCircle(w, h, _radius);
        _radian += _speed;
    }
    
    if( 0 <= _p.x && _p.x < _img.width && 0 <= _p.y && _p.y < _img.height ){
        _color = _img.getColor(_p.x,_p.y);
    }else{
        _color = 0;
    }
    
    ofFill();
    ofSetColor(_color);
    ofCircle(_p.x,_p.y,6);
    ofNoFill();
    ofSetColor(255);
    ofCircle(_p.x,_p.y,6);
    
    if( _displayText == 1 ){
        
        if( _lock == 1 ){
            ofSetColor(230);
        }else{
            ofSetColor(128);
        }
        ofDrawBitmapString("[L]lock", 5, 13 );
        
        if( _autoMode == 1 ){
            ofSetColor(230);
        }else{
            ofSetColor(128);
        }
        ofDrawBitmapString("[A]auto speed:" + ofToString(_speed), 70, 13 );
        
    }
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if( key == 32 ){
        if( _displayText == 0 ){
            _displayText = 1;
        }else{
            _displayText = 0;
        }
    }else if( key == 357 ){
        _speed += 0.01;
    }else if( key == 359 ){
        _speed -= 0.01;
    }else{
        if( _lock == 1 ) return;
        if( key == 97 ){
            _aKey     = 1;
            _autoMode = 1;
        }
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    if( key == 97 ){
        _aKey = 0;
    }
    if( key == 108 ){
        if( _lock == 0 ){
            _lock = 1;
        }else{
            _lock = 0;
        }
    }
    if( _lock == 1 ) return;
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    if( _lock == 1 ) return;
    if( _aKey == 0 ) _autoMode = 0;
    _p.x = x;
    _p.y = y;
    double dx = x - ofGetWidth() / 2;
    double dy = y - ofGetHeight() / 2;
    _radius = sqrt( pow( dx, 2.0 ) + pow( dy, 2.0 ) );
    if( _autoMode == 0 ) _radian = atan2( dy, dx );
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    if( _lock == 1 ) return;
    if( _aKey == 0 ) _autoMode = 0;
    _p.x = x;
    _p.y = y;
    double dx = x - ofGetWidth() / 2;
    double dy = y - ofGetHeight() / 2;
    _radius = sqrt( pow( dx, 2.0 ) + pow( dy, 2.0 ) );
    if( _autoMode == 0 ) _radian = atan2( dy, dx );
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){}

