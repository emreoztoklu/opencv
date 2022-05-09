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
	rectangle(img, Point(130, 226), Point(382, 286), Scalar(WHITE), FILLED);
	line(img, Point(130, 296), Point(382, 296), Scalar(WHITE), 2);



	putText(img, "This is a test text", Point(137, 262), FONT_HERSHEY_DUPLEX, 0.8, Scalar(ORANGE), 2);

	imshow("Image", img);
	waitKey(0);
}
