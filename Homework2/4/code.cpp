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

  Mat images[3] = { image1, image2, image3 };
  for (int i = 0; i < 3; ++i) {
     Mat i1 = ScharrOperator(images[i]);
    imshow("original", images[i]);
    imshow("Result", i1);
    waitKey(0);
  }

  destroyAllWindows();
  return 0;
}

