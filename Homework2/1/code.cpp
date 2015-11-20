/*
 * code.cpp
 *
 *  Created on: Oct 17, 2015
 *      Author: Naman
 */

#include <core/mat.hpp>
#include <core/mat.inl.hpp>
#include <highgui.hpp>
#include <imgcodecs.hpp>
#include <iostream>
#include <string>

#include "../../helpers/helpers.cpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv) {

  string imageName1("../../sampleimages/pirate.tif");
  Mat image1;
  image1 = imread(imageName1.c_str(), IMREAD_GRAYSCALE);

  string imageName2("../../sampleimages/mandril_gray.tif");
  Mat image2;
  image2 = imread(imageName2.c_str(), IMREAD_GRAYSCALE);

  string imageName3("../../sampleimages/lena_gray_256.tif");
  Mat image3;
  image3 = imread(imageName3.c_str(), IMREAD_GRAYSCALE);

  if (image1.empty() || image2.empty()) {
    cout << "404" << endl;
    return -1;
  }

  float d0 = 70;
  Mat images[3] = { image1, image2, image3 };
  for (int i = 0; i < 3; ++i) {

    Mat i1 = gauss_low(images[i], d0);
    Mat H = getGauss(images[i], d0);

//    inverse
    Mat H_ = 1 / H;
    Mat i3 = convolveWithFreq(i1, H_);

//    pseudo inverse
      Mat H__ = pseudo_inv(H, 0.1);
    Mat i4 = convolveWithFreq(i1, H__);

    imshow("Pseudo Inverse", i4);
    imshow("Inverse", i3);
    imshow("Blurrerd", i1);
    imshow("original", images[i]);
    waitKey(0);
  }

  destroyAllWindows();
  return 0;
}

