#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>		// import this file
#include <iostream>

using namespace std;
using namespace cv;

//BGR Blue Green Red
#define BLUE	255,0,0
#define GREEN	0,255,0
#define RED		0,0,255
#define PINK	255,0,255
#define WHITE	255,255,255
#define BLACK	0,0,0
#define ORANGE  0,69,255


/********************** FACE DETECT **********************/


int main(void) {

	string path = "Resources/test.jpg";
	Mat img = imread(path);

	////////////////////////////////////////
	CascadeClassifier faceCascade;
	if (!faceCascade.load("Resources/haarcascade_frontalface_default.xml"))
		cout << "XML file not loaded!" << endl;
	//if (faceCascade.empty()) { cout << "XML file not loaded!" << endl;}

	vector<Rect>faces;
	faceCascade.detectMultiScale(img, faces, 1.3, 20);

	for (int i = 0; i < faces.size(); i++) {
		rectangle(img, faces[i].tl(), faces[i].br(), Scalar(PINK), 3);
	}


	imshow("image", img);
	waitKey(0);
}