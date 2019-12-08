#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	for (int i = 0; i < 10; i++) {

		this->deg_start_list.push_back(0);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int i = 0; i < this->deg_start_list.size(); i++) {

		auto seed = glm::vec2(ofRandom(1000), ofRandom(1000));
		auto location = glm::vec2(ofMap(ofNoise(seed.x, ofGetFrameNum() * 0.005), 0, 1, 50, ofGetWidth() - 50), ofMap(ofNoise(seed.y, ofGetFrameNum() * 0.005), 0, 1, 50, ofGetHeight() - 50));
		auto next_location = glm::vec2(ofMap(ofNoise(seed.x, (ofGetFrameNum() + 1) * 0.005), 0, 1, 50, ofGetWidth() - 50), ofMap(ofNoise(seed.y, (ofGetFrameNum() + 1) * 0.005), 0, 1, 50, ofGetHeight() - 50));
		auto distance = next_location - location;
		auto len = glm::length(distance);
		auto radius = ofMap(len, 0, 5, 20, 45);
		this->deg_start_list[i] += distance.x + distance.y > 0 ? ofMap(len, 0, 5, 0, 8) : ofMap(len, 0, 5, 0, -8);

		ofFill();
		ofSetColor(239);
		ofDrawCircle(location, 20);

		ofNoFill();
		ofSetColor(39);
		ofDrawCircle(location, 20);

		for (int deg_start = this->deg_start_list[i]; deg_start < this->deg_start_list[i] + 360; deg_start += 60) {

			vector<glm::vec2> vertices, sub_vertices;
			for (int deg = deg_start; deg <= deg_start + 40; deg++) {

				vertices.push_back(location + glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
				sub_vertices.push_back(location + glm::vec2((radius + 5) * cos(deg * DEG_TO_RAD), (radius + 5) * sin(deg * DEG_TO_RAD)));
			}

			reverse(sub_vertices.begin(), sub_vertices.end());

			ofFill();
			ofSetColor(239);
			ofBeginShape();
			ofVertices(vertices);
			ofVertices(sub_vertices);
			ofEndShape();

			ofNoFill();
			ofSetColor(39);
			ofBeginShape();
			ofVertices(vertices);
			ofVertices(sub_vertices);
			ofEndShape(true);
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}