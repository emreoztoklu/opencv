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


///////////////  Project 3 - License Plate Detector //////////////////////
VideoCapture cap(0);

int main(void) {

	VideoCapture cap(1);
	Mat img;

	////////////////////////////////////////
	CascadeClassifier plateCascade;
	if (!plateCascade.load("Resources/haarcascade_russian_plate_number.xml"))
		cout << "XML file not loaded!" << endl;
	//if (plateCascade.empty()) { cout << "XML file not loaded!" << endl;}

	vector<Rect>plates;

	while (true) {
		cap.read(img);

		plateCascade.detectMultiScale(img, plates, 1.1, 20);


		for (int i = 0; i < plates.size(); i++) {
			
			Mat imgCrop = img(plates[i]);
			//imshow(to_string(i), imgCrop);
			imwrite("Resources/Plates/" + to_string(i) + ".png", imgCrop);
			
			rectangle(img, plates[i].tl(), plates[i].br(), Scalar(PINK), 3);
		}

		imshow("image", img);
		waitKey(1);
	}
}