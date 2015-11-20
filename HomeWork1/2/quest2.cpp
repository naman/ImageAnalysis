/*
 * quest2.cpp
 *
 *  Created on: Aug 30, 2015
 *
 *
 *      Author: Naman Gupta
 */

/*
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * Light image:Histogram will have more peaks towards 255.
 * Dark Image: Histogram will have more peaks towards 255.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * */

#include <core/cvdef.h>
#include <core/mat.hpp>
#include <core/mat.inl.hpp>
#include <core/types.hpp>
#include <highgui.hpp>
#include <imgcodecs.hpp>
#include <imgproc.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace cv;
using namespace std;

void hist(Mat img);
void cdf(Mat img);

int main(int argc, char** argv) {
  string imageName1("..\\..\\sampleimages\\jetplane.tif");
  string imageName2("..\\..\\sampleimages\\livingroom.tif");
  string imageName3("..\\..\\sampleimages\\jetplane.tif");
  string imageName4("..\\..\\sampleimages\\livingroom.tif");
  string imageName5("..\\..\\sampleimages\\pirate.tif");

  Mat image1;
  image1 = imread(imageName1.c_str(), IMREAD_GRAYSCALE);

  Mat image2;
  image2 = imread(imageName2.c_str(), IMREAD_GRAYSCALE);

  Mat image3;
  image3 = imread(imageName3.c_str(), IMREAD_GRAYSCALE);

  Mat image4;
  image4 = imread(imageName4.c_str(), IMREAD_GRAYSCALE);
  Mat image5;
  image5 = imread(imageName5.c_str(), IMREAD_GRAYSCALE);

  if (image1.empty() || image2.empty()) {
    cout << "404" << endl;
    return -1;
  }
  Mat images[5] = { image1, image2, image3, image4, image5 };
  for (int i = 0; i < 5; ++i) {
    hist(images[i]);
    cdf(images[i]);

    waitKey(0);
  }

  destroyAllWindows();
  return 0;
}

void hist(Mat img) {
  /*  numbers with freq*/
  vector<Mat> numbers(1);
  vector<Mat> resultant(1);
  int mxm = 0;

  /*init to zeros with index as pixel value, and numbers[index] = frequency*/
  numbers[0] = Mat::zeros(1, 256, CV_32SC1);
  uchar value;
  for (int i = 0; i < img.rows; ++i) {
    for (int j = 0; j < img.cols; ++j) {
      value = img.at<uchar>(i, j);
      numbers[0].at<int>(value) += 1;
    }
  }

  for (int p = 0; p < 256; p++) {
    if (numbers[0].at<int>(p) > mxm)
      mxm = numbers[0].at<int>(p);
  }

  int mean;
  for (int i = 0; i < 256; i++) {
    mean += numbers[0].at<int>(i);
  }
  mean /= 256;

  double sd;
  for (int i = 0; i < 256; i++)
    sd += (numbers[0].at<int>(i) - mean) * (numbers[0].at<int>(i) - mean);
  sd = sqrt(sd / 256);

  if (mean / sd > 0.2)
    cout << "High contrast";
  else
    cout << "Low Contrast";

  resultant[0] = Mat::ones(125, 256, CV_8UC1);
  for (int x = 0; x < 256 - 1; ++x) {
    int rows = resultant[0].rows;
    line(resultant[0], Point(x, rows),
        Point(x, rows - (numbers[0].at<int>(x) * rows / mxm)),
        Scalar(222, 222, 222));
    imshow("Histogram", resultant[0]);
//    imwrite("histogram.jpg", resultant[0]);
//    waitKey(0);
  }
}

void cdf(Mat img) {
  /*  numbers with freq*/
  vector<Mat> numbers(1);
  vector<Mat> resultant(1);
  int mxm = 0;

  /*init to zeros with index as pixel value, and numbers[index] = frequency*/
  numbers[0] = Mat::zeros(1, 256, CV_32SC1);
  uchar value;
  for (int i = 0; i < img.rows; ++i) {
    for (int j = 0; j < img.cols; ++j) {
      value = img.at<uchar>(i, j);
      numbers[0].at<int>(value) += 1;
    }
  }

  for (int p = 0; p < 256; p++) {
    if (numbers[0].at<int>(p) > mxm)
      mxm = numbers[0].at<int>(p);
  }

  for (int i = 1; i < 256; i++) {
    numbers[0].at<int>(i) += numbers[0].at<int>(i - 1);
  }

  resultant[0] = Mat::ones(125, 256, CV_8UC1);
  for (int x = 0; x < 256 - 1; ++x) {
    int rows = resultant[0].rows;
    line(resultant[0], Point(x, rows),
        Point(x, rows - (numbers[0].at<int>(x) * rows / mxm)),
        Scalar(222, 222, 222));
    imshow("CDF", resultant[0]);
    //    imwrite("histogram.jpg", resultant[0]);
//    waitKey(0);

  }
}
