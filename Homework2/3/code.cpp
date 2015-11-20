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
#include <iostream>
#include <string>


#include "../../helpers/helpers.cpp"

using namespace cv;
using namespace std;

Mat ideal_low(Mat img, float d0);
void MyFilledCircle(Mat img, float d0, float color);


int main(int argc, char** argv) {

  string imageName1("../../sampleimages/wrinkles.jpg");
  Mat image1;
  image1 = imread(imageName1.c_str(), IMREAD_GRAYSCALE);
  Mat filter =
        (Mat_<float>(5, 5) << 1, 4, 7, 4, 1, 4, 16, 26, 16, 4, 7, 26, 41, 26, 7, 4, 16, 26, 16, 4, 1, 4, 7, 4, 1);

    filter /= 273;

  Mat i1 = apply_filter5(image1,filter);

  filter =
          (Mat_<float>(5, 5) << 1, 1, 1, 1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
  filter /= 25;

  Mat i2 = apply_filter5(image1,filter);

  float d0;
  cout << "Enter D0" << endl;
  cin >> d0;

  Mat i3 = gauss_low(image1,d0);
  Mat i4 = butter_low(image1,d0,2);
  Mat i5 = ideal_low(image1,d0);

    imshow("Gauss Blurred Spatial", i1);
    imshow("Avg Blurred Spatial", i2);
    imshow("Gauss Blurred Fourier", i3);
    imshow("Butterworth Blurred Fourier", i4);
    imshow("Ideal Blurred Fourier", i5);

    waitKey(0);


  destroyAllWindows();
  return 0;
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
