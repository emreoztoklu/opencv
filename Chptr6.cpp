#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


//********************** COLOR DETECTÝON **********************

Mat imgHSV;
Mat mask;

int hmin = 0, smin = 110, vmin = 153;
int hmax = 19,smax = 240, vmax = 255;

//int hmin = 0,	  smin = 0,   vmin = 0;
//int hmax = 179, smax = 255, vmax = 255;

void main(void) {

	string path = "Resources/shapes.png";
	Mat img = imread(path);
	imshow("image", img);

	cvtColor(img, imgHSV, COLOR_BGR2HSV);
	imshow("image_HSV", imgHSV);

	/////////////////////////////////////////////

	namedWindow("TrackBars", (640,200));
	createTrackbar("Hue_Min", "TrackBars", &hmin, 179);
	createTrackbar("Hue_Max", "TrackBars", &hmax, 179);
	createTrackbar("Sat_Min", "TrackBars", &smin, 255);
	createTrackbar("Sat_Max", "TrackBars", &smax, 255);
	createTrackbar("Val_Min", "TrackBars", &vmin, 255);
	createTrackbar("Val_Max", "TrackBars", &vmax, 255);

	while (true) {
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);

		inRange(imgHSV, lower, upper, mask);
		imshow("Image_mask", mask);
		waitKey(1);
	}

	////////////////////////////////////////////
}
