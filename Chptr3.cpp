#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//********************** BASIC FUNCTIONS **********************
int main(void) {

	string path = "Resources/test.jpg";
	Mat img = imread(path);

///////////////////////////////////////////////////////////
	Mat imgResize;

	//cout << img.size().width << "\n";
	//cout << img.size().height << "\n";
	cout << img.size()<< "\n";

	/*1
	resize(img, imgResize,Size(320,240));
	cout << imgResize.size() << "\n";
	imshow("Image_Resize 320x240", imgResize);
	*/

	resize(img, imgResize, Size(), 0.5,0.5);	// Scaled 1/2
	cout << imgResize.size() << "\n";
	imshow("Image_Resize", imgResize);

//////////////////////CROP IMAGE///////////////////////////
	/*
	You are getting a piece from your picture as you sized  0, 0, 300 , 250 position
	from image
	*/

	Mat imgCrop;
	Rect roi(170, 0, 270, 300);		

	imgCrop = img(roi);
	imshow("Image_Crop", imgCrop);


///////////////////////////////////////////////////////////
	imshow("BGR_Image", img);
	waitKey(0);
}

