/*
 * code.cpp
 *
 *  Created on: Oct 17, 2015
 *      Author: Naman
 */

#include <core/cvdef.h>
#include <core/mat.hpp>
#include <core/mat.inl.hpp>
#include <core/types.hpp>
#include <highgui.hpp>
#include <imgcodecs.hpp>
#include <imgproc.hpp>
#include <iostream>
#include <string>

#include "../../helpers/helpers.cpp"

using namespace cv;
using namespace std;

Mat ideal_high(Mat img, float d0);
Mat ideal_low(Mat img, float d0);
void MyFilledCircle(Mat img, float d0, float color);

int main(int argc, char** argv) {

  string imageName1("../../sampleimages/lena_gray_256.tif");
  Mat image1;
  image1 = imread(imageName1.c_str(), IMREAD_GRAYSCALE);

  string imageName2("../../sampleimages/lake.tif");
  Mat image2;
  image2 = imread(imageName2.c_str(), IMREAD_GRAYSCALE);

  string imageName3("../../sampleimages/jetplane.tif");
  Mat image3;
  image3 = imread(imageName3.c_str(), IMREAD_GRAYSCALE);

  if (image1.empty() || image2.empty()) {
    cout << "404" << endl;
    return -1;
  }

  float d0;
  cout << "Enter D0" << endl;
  cin >> d0;

  Mat images[3] = { image1, image2, image3 };
  for (int i = 0; i < 3; ++i) {
        Mat i1 = gauss_high(image1,d0);
          Mat i2 = butter_high(image1,d0,2);
          Mat i3 = ideal_high(image1,d0);

      Mat i4 = gauss_low(image1,d0);
      Mat i5 = butter_low(image1,d0,2);
      Mat i6 = ideal_low(image1,d0);

        imshow("Gauss High", i1);
        imshow("Butter High", i2);
        imshow("Ideal High", i3);
        imshow("Gaussian Blurred Fourier", i4);
        imshow("Butterworth Blurred Fourier", i5);
        imshow("Ideal Blurred Fourier", i6);

    waitKey(0);
  }

  destroyAllWindows();
  return 0;
}

Mat ideal_high(Mat img, float d0) {
  Size s1 = img.size();
  Mat H(s1.height, s1.width, CV_32F, Scalar(255, 255, 255));
  MyFilledCircle(H, d0, 0);
  Mat i = convolveWithFreq(img,H);
//  normalize(i, i, 1, 0, NORM_INF);
  return i;
}

Mat ideal_low(Mat img, float d0) {
  Size s1 = img.size();
  Mat H(s1.height, s1.width, CV_32F, Scalar(0,0,0));
  MyFilledCircle(H, d0, 255);

  return convolveWithFreq(img,H);
}

void MyFilledCircle(Mat img, float d0, float color) {
  int thickness = -1;
  int lineType = 8;
  Size s1 = img.size();
  Point center = Point(s1.height / 2, s1.width / 2);
  circle(img, center, d0, Scalar(color, color, color), thickness, lineType);
}
