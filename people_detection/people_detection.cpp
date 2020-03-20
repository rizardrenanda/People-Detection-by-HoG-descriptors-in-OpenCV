#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{	
	// Read the image file
	Mat image;
	image = imread(argv[1], CV_LOAD_IMAGE_COLOR);  
	// Create a window for display.	
	namedWindow("Display window", WINDOW_AUTOSIZE);
	// Check for invalid input
	if (!image.data)                              
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	// Call SVMDetector and set its coeff
	HOGDescriptor hog;
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
	// Call detectMultiScale to find the bounding boxes
	vector<Rect> found, found_filtered, rects;
	hog.detectMultiScale(image, found, 0, Size(8, 8), Size(32, 32), 1.05, 2);
	

	//compute sizes of bounding boxes
	size_t i, j;
	for (i = 0; i<found.size(); i++)
	{
		Rect r = found[i];
		for (j = 0; j<found.size(); j++)
		if (j != i && (r & found[j]) == r)
			break;
		if (j == found.size())
			found_filtered.push_back(r);
	}
	//create bounding boxes and put it on the image
	for (i = 0; i < found_filtered.size(); i++)
	{
		Rect r = found_filtered[i];
		r.x += cvRound(r.width*0.1);
		r.width = cvRound(r.width*0.8);
		r.y += cvRound(r.height*0.06);
		r.height = cvRound(r.height*0.9);
		rectangle(image, r.tl(), r.br(), cv::Scalar(0, 255, 0), 2);
	}
	
	//Show image with its bounding boxes
	imshow("Display window", image);   
	waitKey(2);
	//Write the resulting image
	std::string str;
	std::string str2 = argv[1];
	std::string str3 = "_BB.png";
	str.append(str2);
	str.append(str3);
	imwrite(str, image);
	return 0;
}

