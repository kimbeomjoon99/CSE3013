/*

	ofxWinMenu basic example - ofApp.cpp

	Example of using ofxWinMenu addon to create a menu for a Microsoft Windows application.
	
	Copyright (C) 2016-2017 Lynn Jarvis.

	https://github.com/leadedge

	http://www.spout.zeal.co

    =========================================================================
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    =========================================================================

	03.11.16 - minor comment cleanup
	21.02.17 - rebuild for OF 0.9.8

*/
#include "ofApp.h"
#include <iostream>
using namespace std;
//--------------------------------------------------------------
void ofApp::setup() {

	ofSetWindowTitle("Maze Example"); // Set the app name on the title bar
	ofSetFrameRate(15);
	ofBackground(255, 255, 255);
	// Get the window size for image loading
	windowWidth = ofGetWidth();
	windowHeight = ofGetHeight();
	isdfs = false;
	isbfs = 0;
	isOpen = 0;

	// final project
	// 새롭게 정의된 변수 초기화
	isdarkmaze = 0;
	user_x = 0;
	user_y = 0;
	gameclear = 0;
	hint1 = 0;
	hint2 = 0;
	hint3 = 0;


	// Centre on the screen
	ofSetWindowPosition((ofGetScreenWidth()-windowWidth)/2, (ofGetScreenHeight()-windowHeight)/2);

	// Load a font rather than the default
	myFont.loadFont("verdana.ttf", 12, true, true);

	// Load an image for the example
	//myImage.loadImage("lighthouse.jpg");

	// Window handle used for topmost function
	hWnd = WindowFromDC(wglGetCurrentDC());

	// Disable escape key exit so we can exit fullscreen with Escape (see keyPressed)
	ofSetEscapeQuitsApp(false);

	//
	// Create a menu using ofxWinMenu
	//

	// A new menu object with a pointer to this class
	menu = new ofxWinMenu(this, hWnd);

	// Register an ofApp function that is called when a menu item is selected.
	// The function can be called anything but must exist. 
	// See the example "appMenuFunction".
	menu->CreateMenuFunction(&ofApp::appMenuFunction);

	// Create a window menu
	HMENU hMenu = menu->CreateWindowMenu();

	//
	// Create a "File" popup menu
	//
	HMENU hPopup = menu->AddPopupMenu(hMenu, "File");

	//
	// Add popup items to the File menu
	//

	// Open an maze file
	menu->AddPopupItem(hPopup, "Open", false, false); // Not checked and not auto-checked
	
	// Final File popup menu item is "Exit" - add a separator before it
	menu->AddPopupSeparator(hPopup);
	menu->AddPopupItem(hPopup, "Exit", false, false);

	//
	// View popup menu
	//
	hPopup = menu->AddPopupMenu(hMenu, "View");

	bShowInfo = true;  // screen info display on
	menu->AddPopupItem(hPopup, "Show DFS",false,false); // Checked
	bTopmost = false; // app is topmost
	menu->AddPopupItem(hPopup, "Show BFS"); // Not checked (default)
	bFullscreen = false; // not fullscreen yet
	menu->AddPopupItem(hPopup, "Full screen", false, false); // Not checked and not auto-check

	//
	// Help popup menu
	//
	hPopup = menu->AddPopupMenu(hMenu, "Help");
	menu->AddPopupItem(hPopup, "About", false, false); // No auto check

	// Set the menu to the window
	menu->SetWindowMenu();

	menu->AddPopupItem(hMenu, "DFS", false, false);	
	menu->AddPopupItem(hMenu, "BFS", false, false);

	// final project
	// Darkmaze Gameplay 탭 생성 후 start gameplay, hint level 1, hint level 2, hint level 3 버튼 생성
	hPopup = menu->AddPopupMenu(hMenu, "Darkmaze Gameplay");
	menu->AddPopupItem(hPopup, "start gameplay");
	menu->AddPopupItem(hPopup, "hint level 1");
	menu->AddPopupItem(hPopup, "hint level 2");
	menu->AddPopupItem(hPopup, "hint level 3");
} // end Setup


//
// Menu function
//
// This function is called by ofxWinMenu when an item is selected.
// The the title and state can be checked for required action.
// 
void ofApp::appMenuFunction(string title, bool bChecked) {

	ofFileDialogResult result;
	string filePath;
	size_t pos;

	//
	// File menu
	//
	if(title == "Open") {
		isdarkmaze = 0;
		gameclear = 0;
		hint1 = 0;
		hint2 = 0;
		hint3 = 0;
		if (isOpen) {
			freeMemory();
		}
		readFile();
	}
	if(title == "Exit") {
		if (isOpen) {
			freeMemory();
		}
		ofExit(); // Quit the application
	}

	//
	// Window menu
	//
	if(title == "Show DFS") {
		//bShowInfo = bChecked;  // Flag is used elsewhere in Draw()
		if (isOpen)
		{
			DFS();
			bShowInfo = bChecked;
		}
		else
			cout << "you must open file first" << endl;
		
	}

	if(title == "Show BFS") {
		doTopmost(bChecked); // Use the checked value directly
		if (isOpen)
		{
			BFS();
			bShowInfo = bChecked;
		}
		else
			cout << "you must open file first" << endl;
	}

	if(title == "Full screen") {
		bFullscreen = !bFullscreen; // Not auto-checked and also used in the keyPressed function
		doFullScreen(bFullscreen); // But als take action immediately
	}

	//
	// Help menu
	//
	if(title == "About") {
		ofSystemAlertDialog("ofxWinMenu\nbasic example\n\nhttp://spout.zeal.co");
	}

	if (title == "DFS") {
		//bShowInfo = bChecked;  // Flag is used elsewhere in Draw()
		if (isOpen)
		{
			DFS();
			bShowInfo = bChecked;
		}
		else
			cout << "you must open file first" << endl;

	}

	if (title == "BFS") {
		doTopmost(bChecked); // Use the checked value directly
		if (isOpen)
		{
			BFS();
			bShowInfo = bChecked;
		}
		else
			cout << "you must open file first" << endl;
	}

	// final project
	// 게임이 시작되면 힌트 플래그 변수 및 gameclear 변수 초기화한 후 darkmaze함수 호출
	if (title == "start gameplay"){
		hint1 = 0;
		hint2 = 0;
		hint3 = 0;
		gameclear = 0;
		darkmaze();
		
	}

	// hint1 변수에 true값 할당 -> 힌트 레벨 1에 해당하는 경로 출력
	if (title == "hint level 1" && isdarkmaze) {
		hint1++;
	}

	// hint2 변수에 true값 할당 -> 힌트 레벨 2에 해당하는 경로 출력
	if (title == "hint level 2" && isdarkmaze) {
		hint2++;
	}

	// hint3 변수에 true값 할당 -> 힌트 레벨 3에 해당하는 경로 출력
	if (title == "hint level 3" && isdarkmaze) {
		hint3++;
	}
} // end appMenuFunction


//--------------------------------------------------------------
void ofApp::update() {

}


//--------------------------------------------------------------
void ofApp::draw() {
	if (gameclear) {
		findexit();
	}
	else {

		ofBackground(255);

		char str[256];
		//ofBackground(0, 0, 0, 0);
		ofSetColor(100);
		ofSetLineWidth(5);
		int i, j;

		// TO DO : DRAW MAZE; 
		// 저장된 자료구조를 이용해 미로를 그린다.
		// add code here
		ofSetRectMode(OF_RECTMODE_CENTER);
		for (i = 0; i < HEIGHT; i++) {
			for (j = 0; j < WIDTH; j++) {
				ofDrawRectangle(20 + (j * 30), 20 + (i * 30), 5, 5);
				ofDrawRectangle(20 + ((j + 1) * 30), 20 + (i * 30), 5, 5);
				ofDrawRectangle(20 + (j * 30), 20 + ((i + 1) * 30), 5, 5);
				ofDrawRectangle(20 + ((j + 1) * 30), 20 + ((i + 1) * 30), 5, 5);
				if (mst[i][j]->upside == NULL) {
					ofDrawLine(20 + (j * 30), 20 + (i * 30), 20 + ((j + 1) * 30), 20 + (i * 30));
				}
				if (mst[i][j]->downside == NULL) {
					ofDrawLine(20 + (j * 30), 20 + ((i + 1) * 30), 20 + ((j + 1) * 30), 20 + ((i + 1) * 30));
				}
				if (mst[i][j]->leftside == NULL) {
					ofDrawLine(20 + (j * 30), 20 + (i * 30), 20 + (j * 30), 20 + ((i + 1) * 30));
				}
				if (mst[i][j]->rightside == NULL) {
					ofDrawLine(20 + ((j + 1) * 30), 20 + (i * 30), 20 + ((j + 1) * 30), 20 + ((i + 1) * 30));
				}
			}
		}


		if (isdfs)
		{
			ofSetColor(200);
			ofSetLineWidth(5);
			if (isOpen)
				dfsdraw();
			else
				cout << "You must open file first" << endl;
		}
		else if (isbfs) {
			ofSetColor(200);
			ofSetLineWidth(5);
			if (isOpen)
				bfsdraw();
			else
				cout << "You must open file first" << endl;
		}

		if (bShowInfo) {
			// Show keyboard duplicates of menu functions
			sprintf(str, " comsil project");
			myFont.drawString(str, 15, ofGetHeight() - 20);
		}

		if (isdarkmaze) {
			if (isOpen) {
				darkmazedraw();
			}
			
		}

	}
} // end Draw


void ofApp::doFullScreen(bool bFull)
{
	// Enter full screen
	if(bFull) {
		// Remove the menu but don't destroy it
		menu->RemoveWindowMenu();
		// hide the cursor
		ofHideCursor();
		// Set full screen
		ofSetFullscreen(true);
	}
	else { 
		// return from full screen
		ofSetFullscreen(false);
		// Restore the menu
		menu->SetWindowMenu();
		// Restore the window size allowing for the menu
		ofSetWindowShape(windowWidth, windowHeight + GetSystemMetrics(SM_CYMENU)); 
		// Centre on the screen
		ofSetWindowPosition((ofGetScreenWidth()-ofGetWidth())/2, (ofGetScreenHeight()-ofGetHeight())/2);
		// Show the cursor again
		ofShowCursor();
		// Restore topmost state
		if(bTopmost) doTopmost(true);
	}

} // end doFullScreen


void ofApp::doTopmost(bool bTop)
{
	if(bTop) {
		// get the current top window for return
		hWndForeground = GetForegroundWindow();
		// Set this window topmost
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 
		ShowWindow(hWnd, SW_SHOW);
	}
	else {
		SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		ShowWindow(hWnd, SW_SHOW);
		// Reset the window that was topmost before
		if(GetWindowLong(hWndForeground, GWL_EXSTYLE) & WS_EX_TOPMOST)
			SetWindowPos(hWndForeground, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 
		else
			SetWindowPos(hWndForeground, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 
	}
} // end doTopmost


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
	// Escape key exit has been disabled but it can be checked here
	if(key == VK_ESCAPE) {
		// Disable fullscreen set, otherwise quit the application as usual
		if(bFullscreen) {
			bFullscreen = false;
			doFullScreen(false);
		}
		else {
			if (isOpen) {
				freeMemory();
			}
			ofExit();
		}
	}

	// Remove or show screen info
	if(key == ' ') {
		bShowInfo = !bShowInfo;
		// Update the menu check mark because the item state has been changed here
		menu->SetPopupItem("Show DFS", bShowInfo);
	}

	if(key == 'f') {
		bFullscreen = !bFullscreen;	
		doFullScreen(bFullscreen);
		// Do not check this menu item
		// If there is no menu when you call the SetPopupItem function it will crash
	}

} // end keyPressed

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (isdarkmaze) { // 암전 미로 탈출 게임이 진행될 경우
		// 왼쪽 키가 입력되고 왼쪽으로 이동 가능하면 user_x--
		if (key == OF_KEY_LEFT && mst[user_y][user_x]->leftside != NULL) {
			user_x--;
		}
		// 오른쪽 키가 입력되고 오른쪽으로 이동 가능하면 user_x++
		else if (key == OF_KEY_RIGHT && mst[user_y][user_x]->rightside != NULL) {
			user_x++;
		}
		// 위쪽 키가 입력되고 위쪽으로 이동 가능하면 user_y--
		else if (key == OF_KEY_UP && mst[user_y][user_x]->upside != NULL) {
			user_y--;
		}
		// 아래쪽 키가 입력되고 아래쪽으로 이동 가능하면 user_y++
		else if (key == OF_KEY_DOWN && mst[user_y][user_x]->downside != NULL) {
			user_y++;
		}

		// 출구에 다다르면 gameclear에 true 할당
		if (user_y == HEIGHT - 1 && user_x == WIDTH - 1) {
			gameclear++;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
bool ofApp::readFile()
{
	ofFileDialogResult openFileResult = ofSystemLoadDialog("Select .maz file");
	string filePath;
	size_t pos;
	// Check whether the user opened a file
	if (openFileResult.bSuccess) {
		ofLogVerbose("User selected a file");

		//We have a file, check it and process it
		string fileName = openFileResult.getName();
		//string fileName = "maze0.maz";
		printf("file name is %s\n", fileName.c_str());
		filePath = openFileResult.getPath();
		printf("Open\n");
		pos = filePath.find_last_of(".");
		if (pos != string::npos && pos != 0 && filePath.substr(pos + 1) == "maz") {

			ofFile file(fileName);

			if (!file.exists()) {
				cout << "Target file does not exists." << endl;
				return false;
			}
			else {
				
				cout << "We found the target file." << endl;
				isOpen = 1;
			}

			ofBuffer buffer(file);

			// Input_flag is a variable for indication the type of input.
			// If input_flag is zero, then work of line input is progress.
			// If input_flag is one, then work of dot input is progress.
			int input_flag = 0;

			// Idx is a variable for index of array.
			int idx = 0;

			// Read file line by line
			int cnt = 0;
			
			
			// TO DO
			// .maz 파일을 input으로 받아서 적절히 자료구조에 넣는다

			lines.clear();

			for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
				string line = *it;
				lines.push_back(line);
				cnt++;
			}

			HEIGHT = cnt / 2;
			WIDTH = lines[0].length() / 2;

			input = (char**)malloc(sizeof(char*) * cnt);
			for (int i = 0; i < cnt; i++) {
				input[i] = (char*)malloc(sizeof(char) * (lines[i].length() + 1));
				strcpy(input[i], lines[i].c_str());
			}

			/*debug input array
			for (int i = 0; i < cnt; i++) {
				printf("%s\n", input[i]);
			}*/

			mst = (vertex***)malloc(sizeof(vertex**) * HEIGHT);
			for (int i = 0; i < HEIGHT; i++) {
				mst[i] = (vertex**)malloc(sizeof(vertex*) * WIDTH);
				for (int j = 0; j < WIDTH; j++) {
					mst[i][j] = (vertex*)malloc(sizeof(vertex));
				}
			}

			int i, j;
			for (i = 0; i < HEIGHT; i++) {
				for (j = 0; j < WIDTH; j++) {
					if (input[i * 2][(j * 2) + 1] == ' ') {
						mst[i][j]->upside = mst[i - 1][j];
						if (i) {
							mst[i - 1][j]->downside = mst[i][j];
						}
					}
					else {
						mst[i][j]->upside = NULL;
						if (i) {
							mst[i - 1][j]->downside = NULL;
						}
					}
					if (input[(i + 1) * 2][(j * 2) + 1] == ' ') {
						mst[i][j]->downside = mst[i + 1][j];
						if (i != HEIGHT - 1) {
							mst[i + 1][j]->upside = mst[i][j];
						}
					}
					else {
						mst[i][j]->downside = NULL;
						if (i != HEIGHT - 1) {
							mst[i + 1][j]->upside = NULL;
						}
					}
					if (input[(i * 2) + 1][(j * 2)] == ' ') {
						mst[i][j]->leftside = mst[i][j - 1];
						if (j) {
							mst[i][j - 1]->rightside = mst[i][j];
						}
					}
					else {
						mst[i][j]->leftside = NULL;
						if (j) {
							mst[i][j - 1]->rightside = NULL;
						}
					}
					if (input[(i * 2) + 1][(j + 1) * 2] == ' ') {
						mst[i][j]->rightside = mst[i][j + 1];
						if (j != WIDTH - 1) {
							mst[i][j + 1]->leftside = mst[i][j];
						}
					}
					else {
						mst[i][j]->rightside = NULL;
						if (j != WIDTH - 1) {
							mst[i][j + 1]->leftside = NULL;
						}
					}

					mst[i][j]->visit = false;
					mst[i][j]->revisit = false;
				}

			}

			root = mst[0][0];
		}
		else {
			printf("  Needs a '.maz' extension\n");
			return false;
		}
	}
}
void ofApp::freeMemory() {

	//TO DO
	// malloc한 memory를 free해주는 함수
	int i;
	for (i = 0; i < (HEIGHT * 2) + 1; i++) {
		free(input[i]);
	}
	free(input);
	for (i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			free(mst[i][j]);
		}
		free(mst[i]);
	}
	free(mst);
}

bool ofApp::DFS()//DFS탐색을 하는 함수
{
	//TO DO
	//DFS탐색을 하는 함수 ( 3주차)
	isbfs = 0;
	isBFS = 0;

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			mst[i][j]->visit = false;
			mst[i][j]->revisit = false;
		}
	}

	vertex* maze_exit = mst[HEIGHT - 1][WIDTH - 1];
	vertex* curr = root;
	vertex* prev = root;
	stack<vertex*> path;
	int first_flag = 0;
	int ccc = 0;
	while (1) {
		curr->visit = true;

		if (!first_flag) {
			if (curr->downside != NULL)
				curr = curr->downside;
			else if (curr->rightside != NULL)
				curr = curr->rightside;
			path.push(prev);
			first_flag++;
			continue;
		}

		if (curr->rightside != NULL && !curr->rightside->visit) {
			path.push(curr);
			prev = curr;
			curr = curr->rightside;
			//continue;
		}
		else if (curr->downside != NULL && !curr->downside->visit) {
			path.push(curr);
			prev = curr;
			curr = curr->downside;
			//continue;
		}
		else if (curr->leftside != NULL && !curr->leftside->visit) {
			path.push(curr);
			prev = curr;
			curr = curr->leftside;
			//continue;
		}
		else if (curr->upside != NULL && !curr->upside->visit) {
			path.push(curr);
			prev = curr;
			curr = curr->upside;
			//continue;
		}
		else {
			curr->revisit = true;
			curr = prev;
			path.pop();
			prev = path.top();
			//path.pop();
		}
		
		if (curr == maze_exit) {
			curr->visit = true;
			break;
		}
	}

	isDFS = 1;
	isdfs = 1;

	return true;
}
void ofApp::dfsdraw()
{
	//TO DO 
	//DFS를 수행한 결과를 그린다. (3주차 내용)
	int i, j;
	
	ofSetColor(255, 0, 0);
	
	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			if (mst[i][j]->visit) {
				if (mst[i][j]->leftside != NULL && mst[i][j]->visit && mst[i][j]->leftside->visit) {
					ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + ((j - 1) * 30), 35 + (i * 30));
				}
				if (mst[i][j]->downside != NULL && mst[i][j]->visit && mst[i][j]->downside->visit) {
					ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + (j * 30), 35 + ((i + 1) * 30));
				}
				if (mst[i][j]->rightside != NULL && mst[i][j]->visit && mst[i][j]->rightside->visit) {
					ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + ((j + 1) * 30), 35 + (i * 30));
				}
				if (mst[i][j]->upside != NULL && mst[i][j]->visit && mst[i][j]->upside->visit) {
					ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + (j * 30), 35 + ((i - 1) * 30));
				}
			}
		}
	}

	ofSetColor(0, 255, 0);
	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			if (mst[i][j]->visit) {
				if (mst[i][j]->leftside != NULL && mst[i][j]->visit && mst[i][j]->leftside->revisit) {
					ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + ((j - 1) * 30), 35 + (i * 30));
				}
				if (mst[i][j]->downside != NULL && mst[i][j]->visit && mst[i][j]->downside->revisit) {
					ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + (j * 30), 35 + ((i + 1) * 30));
				}
				if (mst[i][j]->rightside != NULL && mst[i][j]->visit && mst[i][j]->rightside->revisit) {
					ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + ((j + 1) * 30), 35 + (i * 30));
				}
				if (mst[i][j]->upside != NULL && mst[i][j]->visit && mst[i][j]->upside->revisit) {
					ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + (j * 30), 35 + ((i - 1) * 30));
				}
			}
		}
	}
	
}


bool ofApp::BFS()
{
	isdfs = 0;
	isDFS = 0;

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			mst[i][j]->visit = false;
			mst[i][j]->revisit = false;
		}
	}

	vertex* maze_exit = mst[HEIGHT - 1][WIDTH - 1];
	queue<vertex*> path;
	vertex* curr = root;
	path.push(curr);
	curr->visit = true;
	curr->revisit = true;
	
	while (1) {
		if (curr->rightside != NULL && !curr->rightside->visit) {
			path.push(curr->rightside);
			curr->rightside->parent = curr;
			curr->rightside->visit = true;
			if (curr->rightside == maze_exit) {
				curr->rightside->revisit = true;
				while (1) {
					curr->revisit = true;
					curr = curr->parent;
					if (curr == root) {
						break;
					}
				}
				break;
			}
		}
		if (curr->downside != NULL && !curr->downside->visit) {
			path.push(curr->downside);
			curr->downside->parent = curr;
			curr->downside->visit = true;
			if (curr->downside == maze_exit) {
				curr->downside->revisit = true;
				while (1) {
					curr->revisit = true;
					curr = curr->parent;
					if (curr == root) {
						break;
					}
				}
				break;
			}
		}
		if (curr->leftside != NULL && !curr->leftside->visit) {
			path.push(curr->leftside);
			curr->leftside->parent = curr;
			curr->leftside->visit = true;
			if (curr->leftside == maze_exit) {
				curr->leftside->revisit = true;
				while (1) {
					curr->revisit = true;
					curr = curr->parent;
					if (curr == root) {
						break;
					}
				}
				break;
			}
		}
		if (curr->upside != NULL && !curr->upside->visit) {
			path.push(curr->upside);
			curr->upside->parent = curr;
			curr->upside->visit = true;
			if (curr->upside == maze_exit) {
				curr->upside->revisit = true;
				while (1) {
					curr->revisit = true;
					curr = curr->parent;
					if (curr == root) {
						break;
					}
				}
				break;
			}
		}

		curr = path.front();
		path.pop();

	}

	isBFS = 1;
	isbfs = 1;

	return true;
}
void ofApp::bfsdraw()
{
	int i, j;

	ofSetColor(0, 255, 0);
	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			if (mst[i][j]->visit) {
				if (mst[i][j]->leftside != NULL && mst[i][j]->visit && mst[i][j]->leftside->visit) {
					ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + ((j - 1) * 30), 35 + (i * 30));
				}
				if (mst[i][j]->downside != NULL && mst[i][j]->visit && mst[i][j]->downside->visit) {
					ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + (j * 30), 35 + ((i + 1) * 30));
				}
				if (mst[i][j]->rightside != NULL && mst[i][j]->visit && mst[i][j]->rightside->visit) {
					ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + ((j + 1) * 30), 35 + (i * 30));
				}
				if (mst[i][j]->upside != NULL && mst[i][j]->visit && mst[i][j]->upside->visit) {
					ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + (j * 30), 35 + ((i - 1) * 30));
				}
			}
		}
	}

	ofSetColor(255, 0, 0);
	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			if (mst[i][j]->visit) {
				if (mst[i][j]->leftside != NULL && mst[i][j]->revisit && mst[i][j]->leftside->revisit) {
					ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + ((j - 1) * 30), 35 + (i * 30));
				}
				if (mst[i][j]->downside != NULL && mst[i][j]->revisit && mst[i][j]->downside->revisit) {
					ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + (j * 30), 35 + ((i + 1) * 30));
				}
				if (mst[i][j]->rightside != NULL && mst[i][j]->revisit && mst[i][j]->rightside->revisit) {
					ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + ((j + 1) * 30), 35 + (i * 30));
				}
				if (mst[i][j]->upside != NULL && mst[i][j]->revisit && mst[i][j]->upside->revisit) {
					ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + (j * 30), 35 + ((i - 1) * 30));
				}
			}
		}
	}

	ofSetColor(200);
}

void ofApp::darkmaze() {
	// 다른 플래그 변수를 0으로 초기화
	isdfs = 0;
	isDFS = 0;
	isbfs = 0;
	isBFS = 0;

	//파일이 열렸으면 메모리 해제
	if (isOpen)
		freeMemory();
	//파일을 읽어들임
	readFile();
	if (!isOpen)
		return;

	//힌트 시스템을 위한 BFS함수 호출
	BFS();
	// BFS메뉴 클릭 시 아무런 일도 일어나지 않게 변수 다시 0으로 초기화
	isbfs = 0;
	isBFS = 0;

	// 암전 미로 탈출 게임 시작
	isdarkmaze = 1;
}

void ofApp::darkmazedraw() {
	// 배경을 검은색으로 바꿔줌(암전)
	ofBackground(0);

	//사용자의 시야를 흰색 원으로 표현
	ofSetColor(255);
	ofDrawCircle((user_x * 30) + 35, (user_y * 30) + 35, 75);

	// 색상을 검은색으로 설정, 미로를 화면에 그림
	// 사용자의 시야에만 미로가 그려짐
	ofSetColor(0);
	int i, j;
	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			ofDrawRectangle(20 + (j * 30), 20 + (i * 30), 5, 5);
			ofDrawRectangle(20 + ((j + 1) * 30), 20 + (i * 30), 5, 5);
			ofDrawRectangle(20 + (j * 30), 20 + ((i + 1) * 30), 5, 5);
			ofDrawRectangle(20 + ((j + 1) * 30), 20 + ((i + 1) * 30), 5, 5);
			if (mst[i][j]->upside == NULL) {
				ofDrawLine(20 + (j * 30), 20 + (i * 30), 20 + ((j + 1) * 30), 20 + (i * 30));
			}
			if (mst[i][j]->downside == NULL) {
				ofDrawLine(20 + (j * 30), 20 + ((i + 1) * 30), 20 + ((j + 1) * 30), 20 + ((i + 1) * 30));
			}
			if (mst[i][j]->leftside == NULL) {
				ofDrawLine(20 + (j * 30), 20 + (i * 30), 20 + (j * 30), 20 + ((i + 1) * 30));
			}
			if (mst[i][j]->rightside == NULL) {
				ofDrawLine(20 + ((j + 1) * 30), 20 + (i * 30), 20 + ((j + 1) * 30), 20 + ((i + 1) * 30));
			}
		}
	}

	// 힌트 레벨 3이 실행되었을 경우 모든 미로에 힌트 경로를 그려줌
	if (hint3) {
		// 힌트 경로를 유저의 시야 안에만 그려준다(탈출 경로가 아닌 경로를 초록색으로 그림)
		ofSetColor(0, 255, 0);
		for (i = 0; i < HEIGHT; i++) {
			for (j = 0; j < WIDTH; j++) {
				if (mst[i][j]->visit) {
					if (mst[i][j]->leftside != NULL && mst[i][j]->visit && mst[i][j]->leftside->visit) {
						if (i < user_y + 2 && i > user_y - 2 && j < user_x + 2 && j > user_x - 2)
							ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + ((j - 1) * 30), 35 + (i * 30));
					}
					if (mst[i][j]->downside != NULL && mst[i][j]->visit && mst[i][j]->downside->visit) {
						if (i < user_y + 2 && i > user_y - 2 && j < user_x + 2 && j > user_x - 2)
							ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + (j * 30), 35 + ((i + 1) * 30));
					}
					if (mst[i][j]->rightside != NULL && mst[i][j]->visit && mst[i][j]->rightside->visit) {
						if (i < user_y + 2 && i > user_y - 2 && j < user_x + 2 && j > user_x - 2)
							ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + ((j + 1) * 30), 35 + (i * 30));
					}
					if (mst[i][j]->upside != NULL && mst[i][j]->visit && mst[i][j]->upside->visit) {
						if (i < user_y + 2 && i > user_y - 2 && j < user_x + 2 && j > user_x - 2)
							ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + (j * 30), 35 + ((i - 1) * 30));
					}
				}
			}
		}

		// 힌트 경로를 유저의 시야 안에만 그려준다(탈출 경로를 보라색으로 그림)
		ofSetColor(178, 102, 200);
		for (i = 0; i < HEIGHT; i++) {
			for (j = 0; j < WIDTH; j++) {
				if (mst[i][j]->visit) {
					if (mst[i][j]->leftside != NULL && mst[i][j]->revisit && mst[i][j]->leftside->revisit) {
						if (i < user_y + 2 && i > user_y - 2 && j < user_x + 2 && j > user_x - 2)
							ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + ((j - 1) * 30), 35 + (i * 30));
					}
					if (mst[i][j]->downside != NULL && mst[i][j]->revisit && mst[i][j]->downside->revisit) {
						if (i < user_y + 2 && i > user_y - 2 && j < user_x + 2 && j > user_x - 2)
							ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + (j * 30), 35 + ((i + 1) * 30));
					}
					if (mst[i][j]->rightside != NULL && mst[i][j]->revisit && mst[i][j]->rightside->revisit) {
						if (i < user_y + 2 && i > user_y - 2 && j < user_x + 2 && j > user_x - 2)
							ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + ((j + 1) * 30), 35 + (i * 30));
					}
					if (mst[i][j]->upside != NULL && mst[i][j]->revisit && mst[i][j]->upside->revisit) {
						if (i < user_y + 2 && i > user_y - 2 && j < user_x + 2 && j > user_x - 2)
							ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + (j * 30), 35 + ((i - 1) * 30));
					}
				}
			}
		}
	}
	// 힌트 레벨 2가 실행되었을 경우 출발점을 기준으로 높이의 2/3, 너비의 2/3 만큼 힌트 경로를 그려줌
	else if (hint2) {
		// 힌트 경로를 유저의 시야 안에만 그려준다(탈출 경로가 아닌 경로를 초록색으로 그림)
		ofSetColor(0, 255, 0);
		for (i = 0; i < (WIDTH * 2) / 3; i++) {
			for (j = 0; j < (WIDTH * 2) / 3; j++) {
				if (mst[i][j]->visit) {
					if (mst[i][j]->leftside != NULL && mst[i][j]->visit && mst[i][j]->leftside->visit) {
						if (i < user_y + 2 && i > user_y - 2 && j < user_x + 2 && j > user_x - 2)
							ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + ((j - 1) * 30), 35 + (i * 30));
					}
					if (mst[i][j]->downside != NULL && mst[i][j]->visit && mst[i][j]->downside->visit) {
						if (i < user_y + 2 && i > user_y - 2 && j < user_x + 2 && j > user_x - 2)
							ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + (j * 30), 35 + ((i + 1) * 30));
					}
					if (mst[i][j]->rightside != NULL && mst[i][j]->visit && mst[i][j]->rightside->visit) {
						if (i < user_y + 2 && i > user_y - 2 && j < user_x + 2 && j > user_x - 2)
							ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + ((j + 1) * 30), 35 + (i * 30));
					}
					if (mst[i][j]->upside != NULL && mst[i][j]->visit && mst[i][j]->upside->visit) {
						if (i < user_y + 2 && i > user_y - 2 && j < user_x + 2 && j > user_x - 2)
							ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + (j * 30), 35 + ((i - 1) * 30));
					}
				}
			}
		}

		// 힌트 경로를 유저의 시야 안에만 그려준다(탈출 경로를 보라색으로 그림)
		ofSetColor(178, 102, 200);
		for (i = 0; i < (WIDTH * 2) / 3; i++) {
			for (j = 0; j < (WIDTH * 2) / 3; j++) {
				if (mst[i][j]->visit) {
					if (mst[i][j]->leftside != NULL && mst[i][j]->revisit && mst[i][j]->leftside->revisit) {
						if (i < user_y + 2 && i > user_y - 2 && j < user_x + 2 && j > user_x - 2)
							ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + ((j - 1) * 30), 35 + (i * 30));
					}
					if (mst[i][j]->downside != NULL && mst[i][j]->revisit && mst[i][j]->downside->revisit) {
						if (i < user_y + 2 && i > user_y - 2 && j < user_x + 2 && j > user_x - 2)
							ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + (j * 30), 35 + ((i + 1) * 30));
					}
					if (mst[i][j]->rightside != NULL && mst[i][j]->revisit && mst[i][j]->rightside->revisit) {
						if (i < user_y + 2 && i > user_y - 2 && j < user_x + 2 && j > user_x - 2)
							ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + ((j + 1) * 30), 35 + (i * 30));
					}
					if (mst[i][j]->upside != NULL && mst[i][j]->revisit && mst[i][j]->upside->revisit) {
						if (i < user_y + 2 && i > user_y - 2 && j < user_x + 2 && j > user_x - 2)
							ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + (j * 30), 35 + ((i - 1) * 30));
					}
				}
			}
		}
	}
	// 힌트 레벨 1이 실행되었을 경우 출발점을 기준으로 높이의 1/3, 너비의 1/3 만큼 힌트 경로를 그려줌
	else if (hint1) {
		// 힌트 경로를 유저의 시야 안에만 그려준다(탈출 경로가 아닌 경로를 초록색으로 그림)
		ofSetColor(0, 255, 0);
		for (i = 0; i < HEIGHT / 3; i++) {
			for (j = 0; j < WIDTH / 3; j++) {
				if (mst[i][j]->visit) {
					if (mst[i][j]->leftside != NULL && mst[i][j]->visit && mst[i][j]->leftside->visit) {
						if (i < user_y + 2 && i > user_y - 2 && j < user_x + 2 && j > user_x - 2)
							ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + ((j - 1) * 30), 35 + (i * 30));
					}
					if (mst[i][j]->downside != NULL && mst[i][j]->visit && mst[i][j]->downside->visit) {
						if (i < user_y + 2 && i > user_y - 2 && j < user_x + 2 && j > user_x - 2)
							ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + (j * 30), 35 + ((i + 1) * 30));
					}
					if (mst[i][j]->rightside != NULL && mst[i][j]->visit && mst[i][j]->rightside->visit) {
						if (i < user_y + 2 && i > user_y - 2 && j < user_x + 2 && j > user_x - 2)
							ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + ((j + 1) * 30), 35 + (i * 30));
					}
					if (mst[i][j]->upside != NULL && mst[i][j]->visit && mst[i][j]->upside->visit) {
						if (i < user_y + 2 && i > user_y - 2 && j < user_x + 2 && j > user_x - 2)
							ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + (j * 30), 35 + ((i - 1) * 30));
					}
				}
			}
		}

		// 힌트 경로를 유저의 시야 안에만 그려준다(탈출 경로를 보라색으로 그림)
		ofSetColor(178, 102, 200);
		for (i = 0; i < HEIGHT / 3; i++) {
			for (j = 0; j < WIDTH / 3; j++) {
				if (mst[i][j]->visit) {
					if (mst[i][j]->leftside != NULL && mst[i][j]->revisit && mst[i][j]->leftside->revisit) {
						if (i < user_y + 2 && i > user_y - 2 && j < user_x + 2 && j > user_x - 2)
							ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + ((j - 1) * 30), 35 + (i * 30));
					}
					if (mst[i][j]->downside != NULL && mst[i][j]->revisit && mst[i][j]->downside->revisit) {
						if (i < user_y + 2 && i > user_y - 2 && j < user_x + 2 && j > user_x - 2)
							ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + (j * 30), 35 + ((i + 1) * 30));
					}
					if (mst[i][j]->rightside != NULL && mst[i][j]->revisit && mst[i][j]->rightside->revisit) {
						if (i < user_y + 2 && i > user_y - 2 && j < user_x + 2 && j > user_x - 2)
							ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + ((j + 1) * 30), 35 + (i * 30));
					}
					if (mst[i][j]->upside != NULL && mst[i][j]->revisit && mst[i][j]->upside->revisit) {
						if (i < user_y + 2 && i > user_y - 2 && j < user_x + 2 && j > user_x - 2)
							ofDrawLine(35 + (j * 30), 35 + (i * 30), 35 + (j * 30), 35 + ((i - 1) * 30));
					}
				}
			}
		}
	}
	
	// 유저의 시야 안에 출구가 들어오면 출구를 보라색 정사각형으로 표시
	if (user_y >= HEIGHT - 3 && user_x >= WIDTH - 3) {
		if (!(user_y == HEIGHT - 3 && user_x == WIDTH - 3)) {
			ofSetColor(178, 102, 200);
			ofDrawRectangle(((WIDTH - 1) * 30) + 35, ((HEIGHT - 1) * 30) + 35, 20, 20);
		}
	}
	
	//유저의 게임말을 빨간색 정사각형으로 표시
	ofRectMode(OF_RECTMODE_CENTER);
	ofSetColor(255, 0, 0);
	ofDrawRectangle((user_x * 30) + 35, (user_y * 30) + 35, 10, 10);
}

void ofApp::findexit() {
	// 배경을 흰 색으로 바꿔줌
	ofBackground(255);

	// 미로를 다시 그려줌
	ofSetColor(100);
	int i, j;
	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			ofDrawRectangle(20 + (j * 30), 20 + (i * 30), 5, 5);
			ofDrawRectangle(20 + ((j + 1) * 30), 20 + (i * 30), 5, 5);
			ofDrawRectangle(20 + (j * 30), 20 + ((i + 1) * 30), 5, 5);
			ofDrawRectangle(20 + ((j + 1) * 30), 20 + ((i + 1) * 30), 5, 5);
			if (mst[i][j]->upside == NULL) {
				ofDrawLine(20 + (j * 30), 20 + (i * 30), 20 + ((j + 1) * 30), 20 + (i * 30));
			}
			if (mst[i][j]->downside == NULL) {
				ofDrawLine(20 + (j * 30), 20 + ((i + 1) * 30), 20 + ((j + 1) * 30), 20 + ((i + 1) * 30));
			}
			if (mst[i][j]->leftside == NULL) {
				ofDrawLine(20 + (j * 30), 20 + (i * 30), 20 + (j * 30), 20 + ((i + 1) * 30));
			}
			if (mst[i][j]->rightside == NULL) {
				ofDrawLine(20 + ((j + 1) * 30), 20 + (i * 30), 20 + ((j + 1) * 30), 20 + ((i + 1) * 30));
			}
		}
	}

	//미로의 출구를 보라색 정사각형으로 표현
	ofSetColor(178, 102, 200);
	ofDrawRectangle(((WIDTH - 1) * 30) + 35, ((HEIGHT - 1) * 30) + 35, 20, 20);
	//미로의 출구에 유저가 다다른 것을 빨간색 정사각형으로 표현
	ofSetColor(255, 0, 0);
	ofDrawRectangle(((WIDTH - 1) * 30) + 35, ((HEIGHT - 1) * 30) + 35, 10, 10);

	// 초록색 글상자 삽입
	ofSetColor(0, 255, 0);
	ofDrawRectangle(600, 450, 440, 100);

	// Congratulations! 메시지 출력
	ofSetColor(255, 0, 0);
	ofTrueTypeFont verdana;
	verdana.loadFont("verdana.ttf", 32);
	verdana.drawString("Congratulations!", 400, 450);

	// Open new .maz file or start new darkmaze game. 메시지 출력
	ofSetColor(0);
	verdana.loadFont("verdana.ttf", 12);
	verdana.drawString("Open new .maz file or start new darkmaze game.", 405, 485);

	// 변수 초기화
	user_y = 0;
	user_x = 0; 
	hint1 = 0;
	hint2 = 0;
	hint3 = 0;
}
