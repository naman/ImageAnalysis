/*
 * code.cpp
 *
 *  Created on: Aug 30, 2015
 *      Author: Naman Gupta
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
 *      PLEASE CHECK THE CODE FOR POWER LAW TRANSFORMATION ON YOUR PC, SOMEHOW IT IS NOT WORKING ON MY PC.
 *      pow() function is not working on laptop :/
 *ERROR: _ZSt3powIhdEN9__gnu_cxx11__promote_2IT_T0_NS0_9__promoteIS2_Xsr3std12__is_integerIS2_EE7__valueEE6__typeENS4_IS3_Xsr3std12__is_integerIS3_EE7__valueEE6__typeEE6__typeES2_S3_()
 *
 *      BUT THE CODE IS CORRECT. PLEASE CHECK IT.
 *
 *
 *ANSWER: No the transformations wont be same, not reversible.
 *
 *
 *
 *
 *
 */
#include <core/cvdef.h>
#include <core/mat.hpp>
#include <core/mat.inl.hpp>
#include <core/types.hpp>
#include <highgui.hpp>
#include <imgcodecs.hpp>
#include <cmath>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

Mat power_law(Mat img1, double gamma);
Mat con(Mat img1);
int contrastr(int value, int r1, int s1, int r2, int s2);
int complement(Mat img1);

int main(int argc, char** argv) {
  string imageName1("..\\..\\sampleimages\\lena_color_256.tif");
  string imageName2("..\\..\\sampleimages\\house.tif");
  string imageName3("..\\..\\sampleimages\\jetplane.tif");
  string imageName4("..\\..\\sampleimages\\house.tif");
  string imageName5("..\\..\\sampleimages\\house.tif");

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

  Mat images[5] = { image1, image2, image3, image4, image5 };
  int inp;
  cout << "What gamma?" << endl;
  cin >> inp;

  for (int i = 0; i < 5; ++i) {

    Mat img3;
    img3 = power_law(images[i], inp);

//    Mat img4;/*
//    img4 = con(images[i]);
//*/    complement(images[i]);

    imshow("Original", images[i]);
    imshow("Power", img3);
//    imshow("Contrastretched", img4);

    waitKey(0);
    destroyAllWindows();
  }

  return 0;
}

Mat con(Mat img1) {
  int value;
  Size s;
  s = img1.size();
  Mat img3(s.height, s.width, CV_8UC1);
  int r1, s1, r2, s2;
  cout << "r1 s1 r2 s2?" << endl;
  cin >> r1 >> s1 >> r2 >> s2;

  for (int i = 0; i < s.height; i++) {
    for (int j = 0; j < s.width; j++) {
      value = contrastr(img1.at<uchar>(i, j), r1, s1, r2, s2);
      if (value > 255)
        value = 255;
      else if (value < 0)
        value = 0;

      img3.at<uchar>(i, j) = value;
    }
  }

  return img3;
}

int contrastr(int value, int r1, int s1, int r2, int s2) {
  float mah;
  if (r1 >= value && 0 <= value)
    mah = (s1 / r1) * value;
  else if (value <= r2 && value > r1)
    mah = ((s2 - s1) / (r2 - r1)) * (value - r1) + s1;
  else if (value <= 255 && value > r2)
    mah = ((255 - s2) / (255 - r2)) * (value - r2) + s2;
  mah = (int) mah;
  return mah;
}

int complement(Mat img1) {
  Size s1;
  int value;
  s1 = img1.size();

  Mat img3(s1.height, s1.width, CV_8UC1);

  for (int i = 0; i < s1.height; ++i) {
    for (int j = 0; j < s1.width; ++j) {
      value = 255 - img1.at<uchar>(i, j);
      if (value < 0)
        value = 0;
//      if (value > 255) value = 255;
      img3.at<uchar>(i, j) = value;
    }
  }

//  imwrite("final-compl.jpg",img3);
  namedWindow("Screen", WINDOW_AUTOSIZE);
  imshow("Screen", img3);

  waitKey(0);
  return 0;
}

Mat power_law(Mat img1, double gamma) {
  Size s1;
  int value;
  s1 = img1.size();
  gamma = 1.0 / gamma;
  int c = 1;
  Mat img3(s1.height, s1.width, CV_8UC1);

  for (int i = 0; i < s1.height; ++i) {
    for (int j = 0; j < s1.width; ++j) {
      value = c * pow(img1.at<uchar>(i, j), gamma);
//      value = c * (img1.at<uchar>(i, j)** gamma));

      if (value < 0)
        value = 0;
//      if (value > 255) value = 255;
      img3.at<uchar>(i, j) = value;
    }
  }

  waitKey(0);
  return img3;
}

