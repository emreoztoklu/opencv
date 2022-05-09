/*
This is a test for including all libraries and path
to check is everthign alright
*/

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/////////////////  Images  //////////////////////

void main() {

    string path = "Resources/test.jpg";
    Mat img = imread(path);
    imshow("Image", img);
    waitKey(0);

}

