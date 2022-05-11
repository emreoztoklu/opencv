#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


//********************** COLOR DETECTÝON **********************

Mat imgHSV;
Mat mask;
Mat imgColor;

int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;

//int hmin = 0,	  smin = 0,   vmin = 0;
//int hmax = 179, smax = 255, vmax = 255;

VideoCapture cap(1);
Mat img;


void main(void) {
	namedWindow("TrackBars", (640, 200));
	createTrackbar("Hue_Min", "TrackBars", &hmin, 179);
	createTrackbar("Hue_Max", "TrackBars", &hmax, 179);
	createTrackbar("Sat_Min", "TrackBars", &smin, 255);
	createTrackbar("Sat_Max", "TrackBars", &smax, 255);
	createTrackbar("Val_Min", "TrackBars", &vmin, 255);
	createTrackbar("Val_Max", "TrackBars", &vmax, 255);

	while (true) {

		cap.read(img);

		cvtColor(img, imgHSV, COLOR_BGR2HSV);

		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask);

		//cout << "hmin: " << hmin << ", " << "smin: " << smin << ", " << "vmin: " << vmin << "\n" << endl;
		//cout << "hmax: " << hmax << ", " << "smax: " << smax << ", " << "vmax: " << vmax << "\n" << endl;
		
		cout << hmin << ", " << smin << ", " << vmin << "," << endl;
		cout << hmax << ", " << smax << ", " << vmax << "," << endl;

		imshow("Image", img);
		imshow("Image_mask", mask);
		waitKey(1);
	}

	////////////////////////////////////////////
}

//hmin: 51, smin : 67, vmin : 40
//hmax : 174, smax : 249, vmax : 255