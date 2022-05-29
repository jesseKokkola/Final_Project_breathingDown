#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	#ifdef _USE_LIVE_VIDEO
        vidGrabber.setVerbose(true);
        vidGrabber.setup(320,240);
	#else
        vidPlayer.load("fingers.mov");
        vidPlayer.play();
        vidPlayer.setLoopState(OF_LOOP_NORMAL);
	#endif
       ofBackground(0);
      kuva.load("Takauma.jpg");
        kuva.resize(1280,720);
        pikselit = kuva.getPixels();
        koko=3;
        counter=0;
        keski = {koko * NUM/2,koko * NUM2/2};
       for (int x=0;x<NUM;x++){
        for(int y=0;y<NUM2;y++){
            posV[x][y]={x*koko,y*koko};
    }
        }

    colorImg.allocate(320,240);
	grayImage.allocate(320,240);
	grayBg.allocate(320,240);
	grayDiff.allocate(320,240);

	bLearnBakground = true;
    threshold = 80;
}

//--------------------------------------------------------------
void ofApp::update(){
	
    float lis = 2;
    bool bNewFrame = false;
  
    
	#ifdef _USE_LIVE_VIDEO
       vidGrabber.update();
	   bNewFrame = vidGrabber.isFrameNew();
    #else
        vidPlayer.update();
        bNewFrame = vidPlayer.isFrameNew();
	#endif

	if (bNewFrame){

		#ifdef _USE_LIVE_VIDEO
            colorImg.setFromPixels(vidGrabber.getPixels());
	    #else
            colorImg.setFromPixels(vidPlayer.getPixels());
        #endif

        grayImage = colorImg;
		if (bLearnBakground == true){
			grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
			bLearnBakground = false;
		}

		// take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);

		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(grayDiff, 20, (340*240)/3, 10, true);	// find holes
        if (contourFinder.nBlobs>0){
           counter-=counter;
        } else {
            counter+=lis;
        }    }
    if (counter<-1){
        counter=0;
    }
    if (counter>1500){
        counter=1500;
    }
  
}

//--------------------------------------------------------------
void ofApp::draw(){
    std::cout <<"counter:" << counter << endl;
	// draw the incoming, the grayscale, the bg and the thresholded difference
	//ofSetHexColor(0xffffff);
	//colorImg.draw(20,20);
	//grayImage.draw(360,20);
	//grayBg.draw(20,280);
	//grayDiff.draw(360,280);

	// then draw the contours:

	//ofFill();
	//ofSetHexColor(0x333333);
	//ofDrawRectangle(360,540,320,240);
	//ofSetHexColor(0xffffff);

	// we could draw the whole contour finder
	//contourFinder.draw(360,540);

	// or, instead we can draw each blob individually from the blobs vector,
	// this is how to get access to them:
   // for (int i = 0; i < contourFinder.nBlobs; i++){
       // contourFinder.blobs[i].draw(360,540);
		
		// draw over the centroid if the blob is a hole
		//ofSetColor(255);
		//if(contourFinder.blobs[i].hole){
			//ofDrawBitmapString("hole",
				//contourFinder.blobs[i].boundingRect.getCenter().x + 360,
				//contourFinder.blobs[i].boundingRect.getCenter().y + 540);
		//}
   // }
    float blobSize=0;
    
        for (int x=0;x<NUM;x+=koko){
                  for(int y=0;y<NUM2;y+=koko){
                      float etaisyys = glm::distance(posV[x][y], keski);
                      etaisyys-=counter;
                      if (contourFinder.nBlobs<0){
                                              etaisyys+=counter;
                                          }
                      float scaledEtaisyys = etaisyys*50;
                      
                      float vari = ofMap(scaledEtaisyys, 0,koko*NUM/2,255,0);
                      ofSetColor(pikselit.getColor(x,y),vari);
                      ofDrawRectangle(x,y,koko/3,koko/3);
                         
                  
              }
        }
    
	// finally, a report:
	//ofSetHexColor(0xffffff);
	//stringstream reportStr;
	//reportStr << "bg subtraction and blob detection" << endl
			//  << "press ' ' to capture bg" << endl
			 // << "threshold " << threshold << " (press: +/-)" << endl
             // << "num blobs found " << contourFinder.nBlobs << ", fps: " << endl
           // << "size blob[0] found " << blobSize << endl
//  <<  ", fps: " << ofGetFrameRate();
	//ofDrawBitmapString(reportStr.str(), 20, 600);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	//switch (key){
		//case ' ':
			//bLearnBakground = true;
			//break;
		//case '+':
			//threshold ++;
			//if (threshold > 255) threshold = 255;
			//break;
		//case '-':
			//threshold --;
			//if (threshold < 0) threshold = 0;
			//break;
	//}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
