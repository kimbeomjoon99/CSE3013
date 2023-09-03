#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(15); // Limit the speed of our program to 15 frames per second
    
    // We still want to draw on a black background, so we need to draw
    // the background before we do anything with the brush
    ofBackground(255,255,255);
    ofSetLineWidth(4);
    
    draw_flag = 0;
    load_flag = 0;
    dot_diameter = 20.0f;
    dot_location = 0;

    water_flag = 0;
    sel_dot_change = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(127,23,31);  // Set the drawing color to brown
    
    // Draw shapes for ceiling and floor
    ofDrawRectangle(0, 0, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofDrawRectangle(0, 728, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofSetLineWidth(5);
    
    
    ofSetLineWidth(5);
    if( draw_flag){
        
        
        /* COMSIL1-TODO 3 : Draw the line segment and dot in which water starts to flow in the screen.
         Note that after drawing line segment and dot, you have to make selected water start dot colored in red.
         */
        int i, j;
        ofSetColor(0, 0, 0);
        for (i = 0; i < num_of_line; i++) {
            ofDrawLine(linex1[i], liney1[i], linex2[i], liney2[i]);
        }
        for (i = 0; i < num_of_dot; i++) {
            if (i == dot_location) {
                ofSetColor(255, 0, 0);
                ofDrawCircle(dotx1[i], doty1[i], 10);
                ofSetColor(0, 0, 0);
            }
            else ofDrawCircle(dotx1[i], doty1[i], 10);
        }
        
        
        
        // 2nd week portion.
        ofSetLineWidth(2);
        ofSetColor(0, 0, 255);
        //cout << "loop\n";
        if (water_flag) {
            int index = 0;
            for (i = 0; i < (2 * num_of_line) + 3; i++) {
                
                if (draw_water_spotx[i] == -1) break;
                index++;
            }

            for (i = 0; i < index - 1; i++) {
                //cout << draw_water_spotx[i] << " " << draw_water_spoty[i] << "\n";
                ofDrawLine(draw_water_spotx[i], draw_water_spoty[i], draw_water_spotx[i + 1], draw_water_spoty[i + 1]);
            }
            //water_flag--;
        }

    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'v') {
        // HACK: only needed on windows, when using ofSetAutoBackground(false)
        glReadBuffer(GL_FRONT);
        ofSaveScreen("savedScreenshot_"+ofGetTimestampString()+".png");
    }
    if (key == 'q'){
        // Reset flags
        draw_flag = 0;
        
        // Free the dynamically allocated memory exits.
        delete[] linex1; delete[] linex2; delete[] liney1; delete[] liney2;
        delete[] dotx1; delete[] doty1; 
        delete[] linslope;
        delete[] draw_water_spotx;
        delete[] draw_water_spoty;
        
        
        cout << "Dynamically allocated memory has been freed." << endl;
        
        _Exit(0);
    }
    if (key == 'd'){
        if( !load_flag) return;
        
        /* COMSIL1-TODO 2: This is draw control part.
        You should draw only after when the key 'd' has been pressed.
        */
        draw_flag = 1;
        draw();
    }
    if (key == 's' && !sel_dot_change){
        // 2nd week portion.

        water_flag = 1;
        sel_dot_change = 1;

        
        int i;

        for (i = 0; i < (2 * num_of_line) + 3; i++) {
            draw_water_spotx[i] = -1;
            draw_water_spoty[i] = -1;
        }

        Wx = dotx1[dot_location]; Wy = doty1[dot_location];

        draw_water_spotx[0] = Wx;
        draw_water_spoty[0] = Wy;

        int spot_ind = 1;
        while (spot_ind < (2 * num_of_line) + 3) {
            int touched_line = -1;
            float distance = 10000;
            for (i = 0; i < num_of_line; i++) {
                if ((linex1[i] >= Wx || linex2[i] <= Wx) || (liney1[i] <= Wy && liney2[i] <= Wy)) {
                    
                    continue;
                }
                float tmpy = liney1[i] + (linslope[i] * (Wx - linex1[i]));
                float tmp_dist = tmpy - Wy;
                if (tmp_dist < distance) {
                    distance = tmp_dist;
                    touched_line = i;
                }
            }
            if (touched_line == -1) {
                draw_water_spotx[spot_ind] = Wx;
                draw_water_spoty[spot_ind] = 728;
                break;
            }
            else {
                draw_water_spotx[spot_ind] = Wx;
                draw_water_spoty[spot_ind] = Wy + distance - 3;
                spot_ind++;
                //ofDrawLine(Wx, Wy, Wx, Wy + distance);
                if (linslope[touched_line] > 0) {
                    draw_water_spotx[spot_ind] = linex2[touched_line];
                    draw_water_spoty[spot_ind] = liney2[touched_line] - 3;
                    spot_ind++;
                    //ofDrawLine(Wx, Wy + distance, linex2[touched_line], liney2[touched_line]);
                    Wx = linex2[touched_line];
                    Wy = liney2[touched_line] - 3;
                    
                }
                else if (linslope[touched_line] < 0) {
                    draw_water_spotx[spot_ind] = linex1[touched_line];
                    draw_water_spoty[spot_ind] = liney1[touched_line] - 3;
                    spot_ind++;
                    //ofDrawLine(Wx, Wy + distance, linex1[touched_line], liney1[touched_line]);
                    Wx = linex1[touched_line];
                    Wy = liney1[touched_line] - 3;
                }
            }
        }

        draw();
    }
    if (key == 'e'){
        // 2nd week portion.

        water_flag = 0;
        sel_dot_change = 0;
        Wx = dotx1[dot_location]; Wy = doty1[dot_location];

        draw();
        
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if( key == 'l'){
        // Open the Open File Dialog
        ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a only txt for Waterfall");
        
        // Check whether the user opened a file
        if( openFileResult.bSuccess){
            ofLogVerbose("User selected a file");
            
            // We have a file, so let's check it and process it
            processOpenFileSelection(openFileResult);
            load_flag = 1;
        }
    }
    
    /* COMSIL1-TODO 4: This is selection dot control part.
     You can select dot in which water starts to flow by left, right direction key (<- , ->).
     */
    
    
    if (key == OF_KEY_RIGHT && !sel_dot_change){

        if (dot_location == num_of_dot - 1) {
            dot_location = 0;
        }
        else dot_location++;

        

        cout << "Selcted Dot Coordinate is (" << dotx1[dot_location] << ", " << doty1[dot_location] << ")" << endl;
    }
    if (key == OF_KEY_LEFT && !sel_dot_change){
        
        if (!dot_location) {
            dot_location = num_of_dot - 1;
        }
        else dot_location--;

        //Wx = dotx1[dot_location]; Wy = doty1[dot_location];

        cout << "Selcted Dot Coordinate is (" << dotx1[dot_location] << ", " << doty1[dot_location] << ")" << endl;
    }
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

void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult) { 
    //Path to the comma delimited file
    //string fileName = "input.txt";
    
    string fileName = openFileResult.getName();
    ofFile file(fileName);
    
    if( !file.exists()) cout << "Target file does not exists." << endl;
    else cout << "We found the target file." << endl;
    
    ofBuffer buffer(file);
    
    /* This variable is for indicating which type of input is being received.
     IF input_type == 0, then work of getting line input is in progress.
     IF input_type == 1, then work of getting dot input is in progress.
     */
    int input_type = 0;
    
    
    /* COMSIL1-TODO 1 : Below code is for getting the number of line and dot, getting coordinates.
     You must maintain those information. But, currently below code is not complete.
     Also, note that all of coordinate should not be out of screen size.
     However, all of coordinate do not always turn out to be the case.
     So, You have to develop some error handling code that can detect whether coordinate is out of screen size.
    */
    
    
    // Read file line by line
    int line_flag_count = 0;
    int line_index = 0; int dot_index = 0;
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;
        
        // Split line into strings
        vector<string> words = ofSplitString(line, " ");

        if( words.size() == 1){
            
            if( input_type == 0){ // Input for the number of lines.
                num_of_line = atoi(words[0].c_str());
                cout << "The number of line is: " << num_of_line << endl;
                linex1 = new int[num_of_line];
                linex2 = new int[num_of_line];
                liney1 = new int[num_of_line];
                liney2 = new int[num_of_line];
            }
            else{ // Input for the number of dots.
                num_of_dot = atoi(words[0].c_str());
                cout << "The number of dot is: " << num_of_dot << endl;
                dotx1 = new int[num_of_dot];
                doty1 = new int[num_of_dot];
            }
        }
        else if (words.size() >= 2){
            int x1,y1,x2,y2;
            if( input_type == 0){ // Input for actual information of lines
                x1 = atoi(words[0].c_str());
                y1 = atoi(words[1].c_str());
                x2 = atoi(words[2].c_str());
                y2 = atoi(words[3].c_str());
                if (x1 < 0 || x2 < 0 || x1 > 1024 || x2 > 1024 || y1 < 40 || y1 >= 728 || y2 < 40 || y2 >= 728) {
                    delete[] linex1; delete[] linex2; delete[] liney1; delete[] liney2;
                    _Exit(0);
                }
                line_flag_count++;
                if (line_flag_count == num_of_line) input_type++;
                linex1[line_index] = x1; linex2[line_index] = x2;
                liney1[line_index] = y1; liney2[line_index] = y2;
                line_index++;
            }
            else{ // Input for actual information of dots.
                x1 = atoi(words[0].c_str());
                y1 = atoi(words[1].c_str());
                if (x1 < 0 || x1 > 1024 || y1 < 40 || y1 >= 728) {
                    delete[] linex1; delete[] linex2; delete[] liney1; delete[] liney2;
                    delete[] dotx1; delete[] doty1;
                    _Exit(0);
                }
                dotx1[dot_index] = x1;
                doty1[dot_index] = y1;
                dot_index++;
            }
        } // End of else if.
    } // End of for-loop (Read file line by line).
    
    linslope = new float[num_of_line];
    for (int i = 0; i < num_of_line; i++) {
        float slope = (float)(liney2[i] - liney1[i]) / (float)(linex2[i] - linex1[i]);
        linslope[i] = slope;
    }
    Wx = dotx1[0]; Wy = doty1[0];

    draw_water_spotx = new float[(2 * num_of_line) + 3];
    draw_water_spoty = new float[(2 * num_of_line) + 3];

    load_flag = 1;

    //initializeWaterLines();
}

void ofApp::initializeWaterLines() {
    ;
}


