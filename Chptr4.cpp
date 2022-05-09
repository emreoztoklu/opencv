#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define BLUE	255,0,0
#define PINK	255,0,255
#define WHITE	255,255,255
#define BLACK	0,0,0
#define ORANGE  0,69,255

//********************** DRAW SHAPES AND TEXT **********************
int main(void) {

	//Blank Image

	Mat img(512, 512, CV_8UC3, Scalar(WHITE));


	circle(img, Point(256, 256), 155, Scalar(ORANGE),FILLED);



	imshow("Image", img);
	waitKey(0);
}
