#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(360 - 60);

	float R = 200;
	float r = 50;
	float u_span = 5;

	ofMesh face, line;
	line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	for (int r = 50; r > 0; r -= 2) {

		int v_start = ofMap(ofNoise(r * 0.06 + ofGetFrameNum() * 0.01), 0, 1, -720, 720);
		int v_end = v_start + 12;
		int v_span = 1;

		for (int v = v_start; v <= v_end; v += v_span) {

			for (int u = 0; u < 180; u += u_span) {

				face.addVertex(this->make_point(R, r, u - u_span * 0.5, v - v_span * 0.5));
				face.addVertex(this->make_point(R, r, u + u_span * 0.5, v - v_span * 0.5));
				face.addVertex(this->make_point(R, r, u + u_span * 0.5, v + v_span * 0.5));
				face.addVertex(this->make_point(R, r, u - u_span * 0.5, v + v_span * 0.5));

				line.addVertex(this->make_point(R, r, u - u_span * 0.51, v - v_span * 0.51));
				line.addVertex(this->make_point(R, r, u + u_span * 0.51, v - v_span * 0.51));
				line.addVertex(this->make_point(R, r, u + u_span * 0.51, v + v_span * 0.51));
				line.addVertex(this->make_point(R, r, u - u_span * 0.51, v + v_span * 0.51));

				for (int i = 0; i < 4; i++) {

					face.addColor(ofColor(0));
					line.addColor(ofColor(255));
				}

				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 3);
				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 3); face.addIndex(face.getNumVertices() - 4);


				if (v == v_start) {

					line.addIndex(line.getNumVertices() - 3); line.addIndex(line.getNumVertices() - 4);
				}

				if (v == v_end) {

					line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 2);
				}
			}
		}
	}

	face.draw();
	line.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// ���w�f�b�T������ �`���Ċy���ސ��w�����@P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}