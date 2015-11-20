/*
 * code.cpp
 *
 *  Created on: Aug 19, 2015
 *      Author: Naman Gupta
 */

#include <core/cvdef.h>
#include <core/mat.hpp>
#include <core/mat.inl.hpp>
#include <core/types.hpp>
#include <highgui.hpp>
#include <imgcodecs.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

Mat avg_filter(Mat img1, int n);
Mat apply_filter_l(Mat img1, Mat filter);
Mat apply_filter_a(Mat img1, Mat filter);
Mat apply_filter5(Mat img1, Mat filter);
Mat laplacian_filter(Mat img1, Mat filter);
Mat subtract_img(Mat img1, Mat img3);

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
  cout << "What filter size do you want 3 or 5?" << endl;
  cin >> inp;

  for (int i = 0; i < 5; ++i) {
    Mat filter_b = (Mat_<float>(3, 3) << 0, 1, 0, 1, -4, 1, 0, 1, 0);
    Mat filter_c = (Mat_<float>(3, 3) << 1, 1, 1, 1, -8, 1, 1, 1, 1);

    Mat img3;
    img3 = laplacian_filter(avg_filter(images[i], inp), filter_b);

    Mat img4;
    img4 = laplacian_filter(avg_filter(images[i], inp), filter_c);

    imshow("Original", images[i]);
    imshow("Image3 after 3x3 filter", img3);
    imshow("Image4 after 3x3 filter", img4);

    waitKey(0);
    destroyAllWindows();
  }

  return 0;
}

Mat avg_filter(Mat img1, int n) {

  Mat filter(n, n, CV_8UC1);

  for (int i = 0; i < filter.size().height; ++i) {
    for (int j = 0; j < filter.size().width; ++j) {
      filter.at<uchar>(i, j) = 1;
    }
  }

  Mat img3;
  if (n == 3) {
    img3 = apply_filter_a(img1, filter);
  } else {
    img3 = apply_filter5(img1, filter);
  }
  return img3;
}

Mat laplacian_filter(Mat img1, Mat filter) {
//cout<<"1111";
//  for (int i = 0; i < filter.size().height; ++i) {
//    for (int j = 0; j < filter.size().width; ++j) {
//      if (i == 0 && j == 1) {
//        filter.at<uchar>(i, j) = 1;
//      } else if (i == 1 && (j == 0 || j == 2)) {
//        filter.at<uchar>(i, j) = 1;
//      } else if (i == 2 && j == 1) {
//        filter.at<uchar>(i, j) = 1;
//      } else if (i == 1 && j == 1) {
//        filter.at<uchar>(i, j) = Scalar(-5;
//      } else {
//        filter.at<uchar>(i, j) = 0;
//      }
//    }
//  }

  Mat img3;
//  if (n == 3)
  img3 = apply_filter_l(img1, filter);

  img3 = subtract_img(img1, img3);
  //  else
//    img3 = apply_filter5(img1, filter);

//  img3 = subtract_img(img1, img3);
//  imwrite("final-lapl-filter.jpg", img3);
//  namedWindow("Laplacian", WINDOW_AUTOSIZE);
//  imshow("Laplacian", img3);
//
//  waitKey(0);

  return img3;
}

Mat apply_filter_l(Mat img1, Mat filter) {
  Size s1;
  int value;
  s1 = img1.size();
//  int pad;
//  if (filter.size().height == 3)
//  pad = 1;
//  else
//    pad = 3;

//  Mat copy_img1;
//  copy_img1.create(img1.rows + 2 * pad, img1.cols + 2 * pad, img1.type());
//  copy_img1.setTo(Scalar::all(0));
//  img1.copyTo(copy_img1(Rect(pad, pad, img1.rows, img1.cols)));
//  int new_height = copy_img1.size().height;
//  int new_width = copy_img1.size().width;

  /*
   cout<<copy_img1<<endl;
   Mat copy_img1(s1.height + filter.size().height - 1 , s1.width + filter.size().width - 1, CV_8UC1);
   cout<<new_height<<" "<<new_width<<endl;

   //0 padding
   for (int i = 0; i < new_height; ++i) {
   for (int j = 0; j < new_width; ++j) {
   if(i == 0 || i == 1 || i==new_height || i==new_height -1 ){
   copy_img1.at<uchar>(i, j) = 0;
   }
   if(j == 0 || j == 1 || j==new_width || j==new_width -1 ){
   copy_img1.at<uchar>(i, j) = 0;
   }
   else{
   copy_img1.at<uchar>(i, j) = 0;
   }
   }
   }
   */
  Mat img3(s1.height, s1.width, CV_8UC1);
  for (int i = 0; i < s1.height; ++i) {
    for (int j = 0; j < s1.width; ++j) {
      /*
       if (i == 0 || i == new_height) {
       value = copy_img1.at<uchar>(i, j - 1) * filter.at<uchar>(1, 0)
       + copy_img1.at<uchar>(i, j) * filter.at<uchar>(1, 1)
       + copy_img1.at<uchar>(i, j + 1) * filter.at<uchar>(1, 2)
       + copy_img1.at<uchar>(i + 1, j - 1) * filter.at<uchar>(2, 0)
       + copy_img1.at<uchar>(i + 1, j) * filter.at<uchar>(2, 1)
       + copy_img1.at<uchar>(i + 1, j + 1) * filter.at<uchar>(2, 2);
       } else if (j == 0 || j == new_width) {

       value = copy_img1.at<uchar>(i - 1, j - 1) * filter.at<uchar>(0, 0)
       + copy_img1.at<uchar>(i - 1, j) * filter.at<uchar>(0, 1)
       + copy_img1.at<uchar>(i - 1, j + 1) * filter.at<uchar>(0, 2)
       + copy_img1.at<uchar>(i, j - 1) * filter.at<uchar>(1, 0)
       + copy_img1.at<uchar>(i, j) * filter.at<uchar>(1, 1)
       + copy_img1.at<uchar>(i, j + 1) * filter.at<uchar>(1, 2);
       */
//      } else {
//      cout<<filter;
      value = img1.at<uchar>(i - 1, j - 1) * filter.at<float>(0, 0)
          + img1.at<uchar>(i - 1, j) * filter.at<float>(0, 1)
          + img1.at<uchar>(i - 1, j + 1) * filter.at<float>(0, 2)
          + img1.at<uchar>(i, j - 1) * filter.at<float>(1, 0)
          + img1.at<uchar>(i, j) * filter.at<float>(1, 1)
          + img1.at<uchar>(i, j + 1) * filter.at<float>(1, 2)
          + img1.at<uchar>(i + 1, j - 1) * filter.at<float>(2, 0)
          + img1.at<uchar>(i + 1, j) * filter.at<float>(2, 1)
          + img1.at<uchar>(i + 1, j + 1) * filter.at<float>(2, 2);
//      }
//cout<<value<<endl;
//      value /= filter.size().height * filter.size().width;
      if (value < 0)
        value = 0;
      if (value > 255)
        value = 255;
      img3.at<uchar>(i, j) = value;
    }
  }
  return img3;
}

Mat apply_filter_a(Mat img1, Mat filter) {
  Size s1;
  int value;
  s1 = img1.size();
//  int pad;
//  if (filter.size().height == 3)
//  pad = 1;
//  else
//    pad = 3;

//  Mat copy_img1;
//  copy_img1.create(img1.rows + 2 * pad, img1.cols + 2 * pad, img1.type());
//  copy_img1.setTo(Scalar::all(0));
//  img1.copyTo(copy_img1(Rect(pad, pad, img1.rows, img1.cols)));
//  int new_height = copy_img1.size().height;
//  int new_width = copy_img1.size().width;

  /*
   cout<<copy_img1<<endl;
   Mat copy_img1(s1.height + filter.size().height - 1 , s1.width + filter.size().width - 1, CV_8UC1);
   cout<<new_height<<" "<<new_width<<endl;

   //0 padding
   for (int i = 0; i < new_height; ++i) {
   for (int j = 0; j < new_width; ++j) {
   if(i == 0 || i == 1 || i==new_height || i==new_height -1 ){
   copy_img1.at<uchar>(i, j) = 0;
   }
   if(j == 0 || j == 1 || j==new_width || j==new_width -1 ){
   copy_img1.at<uchar>(i, j) = 0;
   }
   else{
   copy_img1.at<uchar>(i, j) = 0;
   }
   }
   }
   */
  Mat img3(s1.height, s1.width, CV_8UC1);
  for (int i = 0; i < s1.height; ++i) {
    for (int j = 0; j < s1.width; ++j) {
      /*
       if (i == 0 || i == new_height) {
       value = copy_img1.at<uchar>(i, j - 1) * filter.at<uchar>(1, 0)
       + copy_img1.at<uchar>(i, j) * filter.at<uchar>(1, 1)
       + copy_img1.at<uchar>(i, j + 1) * filter.at<uchar>(1, 2)
       + copy_img1.at<uchar>(i + 1, j - 1) * filter.at<uchar>(2, 0)
       + copy_img1.at<uchar>(i + 1, j) * filter.at<uchar>(2, 1)
       + copy_img1.at<uchar>(i + 1, j + 1) * filter.at<uchar>(2, 2);
       } else if (j == 0 || j == new_width) {

       value = copy_img1.at<uchar>(i - 1, j - 1) * filter.at<uchar>(0, 0)
       + copy_img1.at<uchar>(i - 1, j) * filter.at<uchar>(0, 1)
       + copy_img1.at<uchar>(i - 1, j + 1) * filter.at<uchar>(0, 2)
       + copy_img1.at<uchar>(i, j - 1) * filter.at<uchar>(1, 0)
       + copy_img1.at<uchar>(i, j) * filter.at<uchar>(1, 1)
       + copy_img1.at<uchar>(i, j + 1) * filter.at<uchar>(1, 2);
       */
//      } else {
//      cout<<filter;
      value = img1.at<uchar>(i - 1, j - 1) * filter.at<uchar>(0, 0)
          + img1.at<uchar>(i - 1, j) * filter.at<uchar>(0, 1)
          + img1.at<uchar>(i - 1, j + 1) * filter.at<uchar>(0, 2)
          + img1.at<uchar>(i, j - 1) * filter.at<uchar>(1, 0)
          + img1.at<uchar>(i, j) * filter.at<uchar>(1, 1)
          + img1.at<uchar>(i, j + 1) * filter.at<uchar>(1, 2)
          + img1.at<uchar>(i + 1, j - 1) * filter.at<uchar>(2, 0)
          + img1.at<uchar>(i + 1, j) * filter.at<uchar>(2, 1)
          + img1.at<uchar>(i + 1, j + 1) * filter.at<uchar>(2, 2);
//      }
//cout<<value<<endl;
      value /= filter.size().height * filter.size().width;
      if (value < 0)
        value = 0;
      if (value > 255)
        value = 255;
      img3.at<uchar>(i, j) = value;
    }
  }
  return img3;
}

Mat apply_filter5(Mat img1, Mat filter) {
  Size s1;
  int value;
  s1 = img1.size();
  int pad;
//  if (filter.size().height == 3)
  pad = 3;
//  else
//    pad = 3;

  Mat copy_img1;
  copy_img1.create(img1.rows + 2 * pad, img1.cols + 2 * pad, img1.type());
  copy_img1.setTo(Scalar::all(0));
  img1.copyTo(copy_img1(Rect(pad, pad, img1.rows, img1.cols)));
  int new_height = copy_img1.size().height;
  int new_width = copy_img1.size().width;

  /*
   cout<<copy_img1<<endl;
   Mat copy_img1(s1.height + filter.size().height - 1 , s1.width + filter.size().width - 1, CV_8UC1);
   cout<<new_height<<" "<<new_width<<endl;

   //0 padding
   for (int i = 0; i < new_height; ++i) {
   for (int j = 0; j < new_width; ++j) {
   if(i == 0 || i == 1 || i==new_height || i==new_height -1 ){
   copy_img1.at<uchar>(i, j) = 0;
   }
   if(j == 0 || j == 1 || j==new_width || j==new_width -1 ){
   copy_img1.at<uchar>(i, j) = 0;
   }
   else{
   copy_img1.at<uchar>(i, j) = 0;
   }
   }
   }
   */

  Mat img3(s1.height, s1.width, CV_8UC1);
  for (int i = 0; i < s1.height; ++i) {
    for (int j = 0; j < s1.width; ++j) {
      value = copy_img1.at<uchar>(i - 2, j - 2) * filter.at<uchar>(0, 0)
          + copy_img1.at<uchar>(i - 2, j - 1) * filter.at<uchar>(0, 1)
          + copy_img1.at<uchar>(i - 2, j) * filter.at<uchar>(0, 2)
          + copy_img1.at<uchar>(i - 2, j + 1) * filter.at<uchar>(0, 3)
          + copy_img1.at<uchar>(i - 2, j + 2) * filter.at<uchar>(0, 4)
          + copy_img1.at<uchar>(i - 1, j - 2) * filter.at<uchar>(1, 0)
          + copy_img1.at<uchar>(i - 1, j - 1) * filter.at<uchar>(1, 1)
          + copy_img1.at<uchar>(i - 1, j) * filter.at<uchar>(1, 2)
          + copy_img1.at<uchar>(i - 1, j + 1) * filter.at<uchar>(1, 3)
          + copy_img1.at<uchar>(i - 1, j + 2) * filter.at<uchar>(1, 4)
          + copy_img1.at<uchar>(i, j - 2) * filter.at<uchar>(2, 0)
          + copy_img1.at<uchar>(i, j - 1) * filter.at<uchar>(2, 1)
          + copy_img1.at<uchar>(i, j) * filter.at<uchar>(2, 2)
          + copy_img1.at<uchar>(i, j + 1) * filter.at<uchar>(2, 3)
          + copy_img1.at<uchar>(i, j + 2) * filter.at<uchar>(2, 4)
          + copy_img1.at<uchar>(i + 1, j - 2) * filter.at<uchar>(3, 0)
          + copy_img1.at<uchar>(i + 1, j - 1) * filter.at<uchar>(3, 1)
          + copy_img1.at<uchar>(i + 1, j) * filter.at<uchar>(3, 2)
          + copy_img1.at<uchar>(i + 1, j + 1) * filter.at<uchar>(3, 3)
          + copy_img1.at<uchar>(i + 1, j + 2) * filter.at<uchar>(3, 4)
          + copy_img1.at<uchar>(i + 2, j - 2) * filter.at<uchar>(4, 0)
          + copy_img1.at<uchar>(i + 2, j - 1) * filter.at<uchar>(4, 1)
          + copy_img1.at<uchar>(i + 2, j) * filter.at<uchar>(4, 2)
          + copy_img1.at<uchar>(i + 2, j + 1) * filter.at<uchar>(4, 3)
          + copy_img1.at<uchar>(i + 2, j + 2) * filter.at<uchar>(4, 4);

      value /= filter.size().height * filter.size().width;
      if (value < 0)
        value = 0;
      if (value > 255)
        value = 255;
      img3.at<uchar>(i, j) = value;
    }
  }
  return img3;
}

Mat subtract_img(Mat img1, Mat img3) {
  Size s1;
  int value;
  s1 = img1.size();

  for (int i = 0; i < s1.height; ++i) {
    for (int j = 0; j < s1.width; ++j) {
      value = img1.at<uchar>(i, j) - img3.at<uchar>(i, j);
      if (value < 0)
        value = 0;
      img3.at<uchar>(i, j) = value;
    }
  }
  return img3;
}
