#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


/*
********************** IMAGES **********************
//How to include a image and read it.
   //function names:
   //imread 
   //imshow

int main(void) {

	string path = "Resources/cards.jpg";

	Mat img = imread(path);
	imshow("image", img);
	waitKey(0);
}
*/

/*
********************** VÝDEO **********************
// How to include a video and read it.

int main(void) {

	string video_path = "Resources/test_video.mp4";
	VideoCapture cap(video_path);
	Mat img;

	while (true) {

		cap.read(img);
		imshow("image", img);
		waitKey(20);
	}
}
*/

/*
********************** CAMERA **********************
// How to include a CAMERA and read it.
	instead of path you need a gide a ID number
		0 is frst camera ID	(laptop first camera is 0)
		1 is scnd camera ID 

int main(void) {

	VideoCapture cap(0);
	Mat img;

	while (true) {
		cap.read(img);
		imshow("Camera View", img);
		waitKey(1);
	}
}
*/

int main(void) {

	VideoCapture cap(0);
	Mat img;

	while (true) {
		
		cap.read(img);
		imshow("Camera View", img);
		waitKey(1);
	}
}
