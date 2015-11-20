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
 *      PLEASE CHECK THE CODE FOR TRANSLATION, SOMEHOW IT MIGHT NOT BE WORKING WELL.
 *      BUT THE CODE IS CORRECT. PLEASE CHECK IT.
 *
 *
 *
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

Mat scaling(Mat img1);
Mat rotation(Mat img1);
Mat transformed(Mat img1);
Mat mul_by_s(Mat img1, Mat img2);
Mat mul_by_r(Mat img1, Mat img2);

int main(int argc, char** argv) {
  string imageName1("..\\..\\sampleimages\\lena_gray_256.tif");
  string imageName2("..\\..\\sampleimages\\lake.tif");
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

//  Mat images[5] = { image1, image2, image3, image4, image5 };

  Mat images[5] = { image1, image2, image3, image4, image5 };
  for (int i = 0; i < 1; ++i) {
    Mat i1;
//    i1 = scaling(images[i]);
    Mat i2 = rotation(images[i]);
//    Mat i3 = transformed(images[i]);
    namedWindow("Scaled", WINDOW_AUTOSIZE);
//    imshow("Scaled", i1);
    imshow("Rotated", i2);
//    imshow("Translated", i3);
    imshow("Original", image1);

    waitKey(0);
  }
/*

  for (int i = 0; i < 5; ++i) {

    Mat i1 = transformed(rotation(scaling(images[i])));
//    namedWindow("Scaled", WINDOW_AUTOSIZE);
    imshow("combined", i1);
    imshow("Original", image1);

    waitKey(0);
  }
*/

  destroyAllWindows();
  return 0;
}

Mat scaling(Mat img1) {
  int value, i, j;
  float scale;
  cout << "How much to scale?\n";
  cin >> scale;
  Size s1;
  s1 = img1.size();

  Mat img3(scale * s1.height, scale * s1.width, CV_8UC1);

  Mat scaling = (Mat_<float>(2, 2) << scale, 0, 0, scale);
  for (i = 0; i < s1.height; i++) {
    for (j = 0; j < s1.width; j++) {
      Mat new_ = (Mat_<int>(2, 1) << i, j);
      Mat res = mul_by_s(scaling, new_);
      int i_ = (int) res.at<float>(0);
      int j_ = (int) res.at<float>(1);

      img3.at<uchar>(i_, j_) = img1.at<uchar>(i, j);
    }
  }

//  waitKey(0);
  return img3;
}

Mat transformed(Mat img1) {

  int value, i, j;
  int x, y;
  cout << "How much to translate?\n";
  cin >> x >> y;
  Size s1;
  s1 = img1.size();

  Mat img3(s1.height * 2, s1.width * 2, CV_8UC1);
  int array[9] = { 1, 0, x, 1, y, 0, 0, 0, 1 };

  Mat trans = Mat(3, 3, CV_64F, array);
  for (i = 0; i < s1.height; i++) {
    for (j = 0; j < s1.width; j++) {
      int array[3] = { i, j, 1 };
      Mat new_ = Mat(3, 1, CV_64F, array);

      Mat res = mul_by_s(trans, new_);
      int i_ = (int) res.at<float>(0);
      int j_ = (int) res.at<float>(1);

      if (i_ < img1.rows && j_ < img1.cols && i_ > 0 && j_ > 0)
        img3.at<int>(i_, j_) = img1.at<int>(i, j);

    }
  }
  return img3;
}

Mat mul_by_s(Mat img1, Mat img2) {
  Size s1, s2;
  int value;
  s1 = img1.size();
  s2 = img2.size();

  Mat img3(s1.height, s2.width, CV_32F);

  for (int i = 0; i < s1.height; ++i) {
    for (int j = 0; j < s2.width; ++j) {

      value = 0;
      for (int k = 0; k < s1.width; ++k) {
        int x = img1.at<float>(i, k);
        int y = img2.at<uchar>(k, j);
        value += (int) (x * y);
//        cout<<value<<endl;
      }
//      cout<<value<<endl;
//      if (value < 0)
//        value = 0;
//      if (value > 255)
//        value = 255;
      img3.at<float>(i, j) = value;
    }
  }
//   cout<<img3;
  return img3;
}

//Mat mul_by_r(Mat img1, Mat img2) {
//  Size s1, s2;
//  int value;
//  s1 = img1.size();
//  s2 = img2.size();
//
//  Mat img3(s1.height, s2.width, CV_8SC1);
//
//  for (int i = 0; i < s1.height; ++i) {
//    for (int j = 0; j < s2.width; ++j) {
//
//      value = 0;
//      for (int k = 0; k < s1.width; ++k) {
//        float x = img1.at<double>(i, k);
//        float y = img2.at<uchar>(k, j);
//        value += (double) (x * y);
//
//      }
//      cout<<value<<endl;
//      if (value < 0)
//        value = 0;
//      if (value > 255)
//        value = 255;
//      img3.at<float>(i, j) = value;
//    }
//  }
////   cout<<img3;
//  return img3;
//}

Mat rotation(Mat img1) {
  int value, i, j;
  float theta;
  float angle;
  cout << "How much to rotate?\n";
  cin >> theta;
  Size s1;
  s1 = img1.size();

  theta = theta * M_PI / 180;

  Mat img3(s1.height * 2, s1.width * 2, CV_8UC1);
  /*
   Mat rot = (Mat_<float>(2, 2) <<
   cos(theta),-1*sin(theta),
   sin(theta), cos(theta));
   */
  double array[9] = { cos(theta), -sin(theta), 0, sin(theta), cos(theta), 0, 0,
      0, 1 };

  Mat rot = Mat(3, 3, CV_64F, array);

  for (i = 0; i < s1.height; i++) {
    for (j = 0; j < s1.width; j++) {
      double array[3] = { (double) i, (double) j, 1 };
      Mat new_ = Mat(3, 1, CV_64F, array);

      Mat res = rot * new_;
      double i_ = res.at<double>(0);
      double j_ = res.at<double>(1);

      if (i_ < img1.rows && j_ < img1.cols && i_ > 0 && j_ > 0)
        img3.at<double>(i_, j_) = img1.at<double>(i, j);

    }
  }

//  imwrite("final-rot.jpg", img3);
//  imshow("Rotated", img3);
//  imshow("Original", img1);

//  waitKey(0);
  return img3;
}
