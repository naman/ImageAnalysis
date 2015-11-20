/*
 * helpers.cpp
 *
 *  Created on: Oct 17, 2015
 *      Author: Naman
 */

#include <core/base.hpp>
#include <core/cvdef.h>
#include <core/mat.hpp>
#include <core/mat.inl.hpp>
#include <core/matx.hpp>
#include <core/types.hpp>
#include <core.hpp>
#include <objdetect.hpp>
#include <string.h>
#include <cmath>
#include <vector>

using namespace cv;
using namespace std;

/*

 Mat get_hogdescriptor_visual_image(Mat& origImg,
 vector<float>& descriptorValues, Size winSize, Size cellSize,
 int scaleFactor, double viz_factor) {
 Mat visual_image;
 resize(origImg, visual_image,
 Size(origImg.cols * scaleFactor, origImg.rows * scaleFactor));
 cvtColor(visual_image, visual_image, CV_GRAY2BGR);

 int gradientBinSize = 9;
 // dividing 180° into 9 bins, how large (in rad) is one bin?
 float radRangeForOneBin = 3.14 / (float) gradientBinSize;

 // prepare data structure: 9 orientation / gradient strenghts for each cell
 int cells_in_x_dir = winSize.width / cellSize.width;
 int cells_in_y_dir = winSize.height / cellSize.height;
 int totalnrofcells = cells_in_x_dir * cells_in_y_dir;
 float*** gradientStrengths = new float**[cells_in_y_dir];
 int** cellUpdateCounter = new int*[cells_in_y_dir];
 for (int y = 0; y < cells_in_y_dir; y++) {
 gradientStrengths[y] = new float*[cells_in_x_dir];
 cellUpdateCounter[y] = new int[cells_in_x_dir];
 for (int x = 0; x < cells_in_x_dir; x++) {
 gradientStrengths[y][x] = new float[gradientBinSize];
 cellUpdateCounter[y][x] = 0;

 for (int bin = 0; bin < gradientBinSize; bin++)
 gradientStrengths[y][x][bin] = 0.0;
 }
 }

 // nr of blocks = nr of cells - 1
 // since there is a new block on each cell (overlapping blocks!) but the last one
 int blocks_in_x_dir = cells_in_x_dir - 1;
 int blocks_in_y_dir = cells_in_y_dir - 1;

 // compute gradient strengths per cell
 int descriptorDataIdx = 0;
 int cellx = 0;
 int celly = 0;

 for (int blockx = 0; blockx < blocks_in_x_dir; blockx++) {
 for (int blocky = 0; blocky < blocks_in_y_dir; blocky++) {
 // 4 cells per block ...
 for (int cellNr = 0; cellNr < 4; cellNr++) {
 // compute corresponding cell nr
 int cellx = blockx;
 int celly = blocky;
 if (cellNr == 1)
 celly++;
 if (cellNr == 2)
 cellx++;
 if (cellNr == 3) {
 cellx++;
 celly++;
 }

 for (int bin = 0; bin < gradientBinSize; bin++) {
 float gradientStrength = descriptorValues[descriptorDataIdx];
 descriptorDataIdx++;

 gradientStrengths[celly][cellx][bin] += gradientStrength;

 } // for (all bins)

 // note: overlapping blocks lead to multiple updates of this sum!
 // we therefore keep track how often a cell was updated,
 // to compute average gradient strengths
 cellUpdateCounter[celly][cellx]++;

 } // for (all cells)

 } // for (all block x pos)
 } // for (all block y pos)

 // compute average gradient strengths
 for (int celly = 0; celly < cells_in_y_dir; celly++) {
 for (int cellx = 0; cellx < cells_in_x_dir; cellx++) {

 float NrUpdatesForThisCell = (float) cellUpdateCounter[celly][cellx];

 // compute average gradient strenghts for each gradient bin direction
 for (int bin = 0; bin < gradientBinSize; bin++) {
 gradientStrengths[celly][cellx][bin] /= NrUpdatesForThisCell;
 }
 }
 }

 cout << "descriptorDataIdx = " << descriptorDataIdx << endl;

 // draw cells
 for (int celly = 0; celly < cells_in_y_dir; celly++) {
 for (int cellx = 0; cellx < cells_in_x_dir; cellx++) {
 int drawX = cellx * cellSize.width;
 int drawY = celly * cellSize.height;

 int mx = drawX + cellSize.width / 2;
 int my = drawY + cellSize.height / 2;

 rectangle(visual_image, Point(drawX * scaleFactor, drawY * scaleFactor),
 Point((drawX + cellSize.width) * scaleFactor,
 (drawY + cellSize.height) * scaleFactor), Scalar(100, 100, 100),
 1);

 // draw in each cell all 9 gradient strengths
 for (int bin = 0; bin < gradientBinSize; bin++) {
 float currentGradStrength = gradientStrengths[celly][cellx][bin];

 // no line to draw?
 if (currentGradStrength == 0)
 continue;

 float currRad = bin * radRangeForOneBin + radRangeForOneBin / 2;

 float dirVecX = cos(currRad);
 float dirVecY = sin(currRad);
 float maxVecLen = cellSize.width / 2;
 float scale = viz_factor; // just a visual_imagealization scale,
 // to see the lines better

 // compute line coordinates
 float x1 = mx - dirVecX * currentGradStrength * maxVecLen * scale;
 float y1 = my - dirVecY * currentGradStrength * maxVecLen * scale;
 float x2 = mx + dirVecX * currentGradStrength * maxVecLen * scale;
 float y2 = my + dirVecY * currentGradStrength * maxVecLen * scale;

 // draw gradient visual_imagealization
 line(visual_image, Point(x1 * scaleFactor, y1 * scaleFactor),
 Point(x2 * scaleFactor, y2 * scaleFactor), Scalar(0, 0, 255), 1);

 } // for (all bins)

 } // for (cellx)
 } // for (celly)

 // don't forget to free memory allocated by helper data structures!
 for (int y = 0; y < cells_in_y_dir; y++) {
 for (int x = 0; x < cells_in_x_dir; x++) {
 delete[] gradientStrengths[y][x];
 }
 delete[] gradientStrengths[y];
 delete[] cellUpdateCounter[y];
 }
 delete[] gradientStrengths;
 delete[] cellUpdateCounter;

 return visual_image;
 }
*/


double HOG_distance(Mat img1, Mat img2) {

  Size windowSize = Size(64, 8);
  Size blockSize = Size(8, 8);
  Size patchSize = Size(4, 4);
  int number_of_bins = 8;
  vector<float> descriptorsValues1;
  vector<Point> locations1;
  vector<float> descriptorsValues2;
  vector<Point> locations2;

  HOGDescriptor d1(windowSize, blockSize, patchSize, patchSize, number_of_bins);
  HOGDescriptor d2(windowSize, blockSize, patchSize, patchSize, number_of_bins);

  d1.compute(img1, descriptorsValues1, Size(0, 0), Size(0, 0), locations1);
  d2.compute(img2, descriptorsValues2, Size(0, 0), Size(0, 0), locations2);

  Mat A(descriptorsValues1.size(), 1, CV_32FC1);

  memcpy(A.data, descriptorsValues1.data(),
      descriptorsValues1.size() * sizeof(float));

  Mat B(descriptorsValues2.size(), 1, CV_32FC1);

  memcpy(B.data, descriptorsValues2.data(),
      descriptorsValues2.size() * sizeof(float));

  Mat diff = A - B;
  diff = diff.mul(diff);
  sqrt(diff, diff);
  Scalar sum_ = sum(diff);
  double cos_dist = sum_(0);
//   cout << "Cosine Distance: " << cos_dist << endl;

  /* //hog visualization
   Mat r1 = get_hogdescriptor_visual_image(r_img1_gray, descriptorsValues1,
   Size(64, 8), Size(4, 4), 10, 3);
   Mat r2 = get_hogdescriptor_visual_image(r_img2_gray, descriptorsValues2,
   Size(64, 8), Size(4, 4), 10, 3);


   imshow("hog visualization1", r1);
   imshow("hog visualization2", r2);

   waitKey(0);
   */
  return cos_dist;
}

int thresholding(int i, int j) {
  return (i >= j) ? 1 : 0;
}

Mat LBP_PatternImage(Mat img) {

  Size s1;
  s1 = img.size();
  double value;
  int center;
  Mat img3(s1.height, s1.width, CV_8UC1);

  for (int i = 1; i < img.rows - 1; i++) {
    for (int j = 1; j < img.cols - 1; j++) {

      center = img.at<uchar>(i, j);
      value = pow(2, 0) * thresholding(center, img.at<uchar>(i, j - 1))
          + pow(2, 1) * thresholding(center, img.at<uchar>(i + 1, j - 1))
          + pow(2, 2) * thresholding(center, img.at<uchar>(i + 1, j))
          + pow(2, 3) * thresholding(center, img.at<uchar>(i + 1, j + 1))
          + pow(2, 4) * thresholding(center, img.at<uchar>(i, j + 1))
          + pow(2, 5) * thresholding(center, img.at<uchar>(i - 1, j + 1))
          + pow(2, 6) * thresholding(center, img.at<uchar>(i - 1, j))
          + pow(2, 7) * thresholding(center, img.at<uchar>(i - 1, j - 1));

      img3.at<uchar>(i - 1, j - 1) = value;
    }
  }
  return img3;
}

double chi_square_distance(Mat img1, Mat img2) {

  double distance = 0;
  int num_of_patches = 8;
  int neighborhood = 5;

  for (int i = 0; i < num_of_patches; i++) {
    for (int j = 0; j < num_of_patches; j++) {

      int hist_img1[num_of_patches];
      int hist_img2[num_of_patches];

      //Make all the values 0 in the histogram
      for (int k = 0; k < num_of_patches; k++) {
        hist_img1[k] = 0;
        hist_img2[k] = 0;
      }

      //traversing through each patch and averaging for 5x5 neighborhood
      //each patch is 8x8
      for (int p = 0; p < num_of_patches; p++) {
        for (int r = 0; r < num_of_patches; r++) {

          int patch_number_1 = (img1.at<uchar>((i * num_of_patches) + p,
              (j * num_of_patches) + r)) / (neighborhood * neighborhood);

          int patch_number_2 = (img2.at<uchar>((i * num_of_patches) + p,
              (j * num_of_patches) + r)) / (neighborhood * neighborhood);

          hist_img1[patch_number_1]++;
          hist_img2[patch_number_2]++;
        }
      }

//      Chi square distance between the two histo
      for (int t = 0; t < num_of_patches; t++) {
        if ((hist_img1[t] + hist_img2[t]) != 0) {
          double num = pow((hist_img1[t] - hist_img2[t]), 2);
          distance += (double) (num / (hist_img1[t] + hist_img2[t]));
        }
      }
//      distance = compareHist( hist_img1, hist_img2, CV_COMP_CHISQR);
    }
  }
  return distance;
}

Mat erosion(Mat img1) {
  Size s1;
  float value;
  s1 = img1.size();
  Mat img3(s1.height, s1.width, CV_8UC1);

  for (int i = 0; i < s1.height; ++i) {
    for (int j = 0; j < s1.width; ++j) {
      img3.at<uchar>(i, j) = 255;
    }
  }
  return img3;
}

Mat binarize(Mat img1) {
  Size s1;
  uchar value_B, value_G, value_R;
  float value;
  s1 = img1.size();
  Mat img3(s1.height, s1.width, CV_8UC1);

  for (int i = 0; i < s1.height; ++i) {
    for (int j = 0; j < s1.width; ++j) {

      Point3_<uchar>* p1 = img1.ptr<Point3_<uchar> >(i, j);
      value_B = p1->x;
      value_G = p1->y;
      value_R = p1->z;

      if (value_R >= 140 || value_G >= 140 || value_B >= 170)

        img3.at<uchar>(i, j) = 255;
      else
        img3.at<uchar>(i, j) = 0;
    }
  }
  return img3;
}

void shift(Mat magI) {

  // crop if it has an odd number of rows or columns
  magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

  int cx = magI.cols / 2;
  int cy = magI.rows / 2;

  Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
  Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
  Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
  Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

  Mat tmp;                        // swap quadrants (Top-Left with Bottom-Right)
  q0.copyTo(tmp);
  q3.copyTo(q0);
  tmp.copyTo(q3);
  q1.copyTo(tmp);                  // swap quadrant (Top-Right with Bottom-Left)
  q2.copyTo(q1);
  tmp.copyTo(q2);
}

/*

 Mat wiener_deblur(Mat img, float Pnoise, float Psignal) {

 float K = Pnoise / Psignal;
 use CV_64FC2
 Size s1 = H.size();
 Mat G(s1.height, s1.width, CV_32F);

 for (i = 0; i < s1.height; i++) {
 for (j = 0; j < s1.width; j++) {
 //  G.at<uchar>(i, j) = H.at<uchar>(i, j)/(H.at<uchar>(i, j)**2 + K);
 }
 }
 return G * F;
 }

 */

Mat apply_filter5(Mat img1, Mat filter) {
  Size s1;
  float value;
  s1 = img1.size();
  float p, q;
  Mat img3(s1.height, s1.width, CV_8UC1);

  for (int i = 0; i < s1.height; ++i) {
    for (int j = 0; j < s1.width; ++j) {
      value = 0.0;
      for (int x = -2; x <= 2; ++x) {
        for (int y = -2; y <= 2; ++y) {

          if (j - y < 0)
            p = (j - y) + s1.width;
          else if (j - y >= s1.width)
            p = (j - y) - s1.width;
          else
            p = j - y;
          if (i - x < 0)
            q = (i - x) + s1.height;
          else if (i - x >= s1.height)
            q = (i - x) - s1.height;
          else
            q = i - x;

          float a = img1.at<uchar>(q, p);
          float b = filter.at<float>(x + 2, y + 2);

          value += a * b;
        }
      }
      if (value < 0)
        value = 0;
      else if (value > 255)
        value = 255;
      img3.at<uchar>(i, j) = value;
    }
  }
  return img3;
}

Mat apply_filter5_weird(Mat img1, Mat filter) {
  Size s1;
  float value;
  s1 = img1.size();
  float p, q;
  Mat img3(s1.height, s1.width, CV_8UC1);

  for (int i = 0; i < s1.height; ++i) {
    for (int j = 0; j < s1.width; ++j) {
      value = 0.0;
      for (int x = -2; x <= 2; ++x) {
        for (int y = -2; y <= 2; ++y) {

          if (j - y < 0)
            p = (j - y) + s1.width;
          else if (j - y >= s1.width)
            p = (j - y) - s1.width;
          else
            p = j - y;
          if (i - x < 0)
            q = (i - x) + s1.height;
          else if (i - x >= s1.height)
            q = (i - x) - s1.height;
          else
            q = i - x;

          float a = img1.at<uchar>(q, p);
          float b = filter.at<uchar>(x + 2, y + 2);

          value += a * b;
        }
      }
      if (value < 0)
        value = 0;
      else if (value > 255)
        value = 255;
      img3.at<uchar>(i, j) = value;
    }
  }
  return img3;
}

Mat FT(Mat img) {
  Size s1 = img.size();
  Mat fImage;
  img.convertTo(fImage, CV_32F);

  /*
   Mat padded;

   int dftH = 512;
   int dftW = 512;


   if (s1.width != 512 && s1.width != 512) {
   copyMakeBorder(fImage, padded, 0, dftH - fImage.rows, 0, dftW - fImage.cols,
   BORDER_CONSTANT, Scalar::all(255));
   } else {
   padded = fImage;
   }
   */

  Mat fourierTransform;
  dft(fImage, fourierTransform, DFT_SCALE | DFT_COMPLEX_OUTPUT);
  return fourierTransform;
}

Mat IFT(Mat fourierTransform) {
//  Mat inverseTransform;
  Mat temp;

  dft(fourierTransform, temp, DFT_INVERSE | DFT_SCALE);

  Mat planes[] = { Mat::zeros(fourierTransform.size(), CV_32F), Mat::zeros(
      fourierTransform.size(), CV_32F) };

  split(temp, planes);
  magnitude(planes[0], planes[1], temp);
  normalize(temp, temp, 0, 1, NORM_MINMAX);

//  Mat finalImage;
//  temp.convertTo(temp, CV_8U);
  return temp;
}

Mat mul(Mat F, Mat G) {
  Size s1 = F.size();

  Mat planes[] = { Mat::zeros(F.size(), CV_32F), Mat::zeros(F.size(), CV_32F) };

  split(F, planes);

  for (int i = 0; i < s1.height; i++) {
    for (int j = 0; j < s1.width; j++) {
      planes[0].at<uchar>(i, j) *= G.at<uchar>(i, j);
      planes[1].at<uchar>(i, j) *= G.at<uchar>(i, j);
    }
  }

  merge(planes, 2, F);
  return F;
}

Mat convolveWithFreq(Mat img, Mat H) {
  Mat F;
  F = FT(img);

//  shift(F);
  shift(H);
  Mat planes[] = { Mat::zeros(F.size(), CV_32F), Mat::zeros(F.size(), CV_32F) };

  Mat fourier_filter;
  planes[0] = H;
  planes[1] = H;
  merge(planes, 2, fourier_filter);
  mulSpectrums(F, fourier_filter, F, DFT_ROWS);

  /*
   F = mul(F,fourier_filter);
   shift(F);
   normalize(F, F, 1, 0, NORM_INF);
   return IFT(F);
   */
  return IFT(F);
}

float dist(float i, float j) {
  return sqrt(i * i + j * j);
}

float gauss(float i, float j, float d0) {
  float d = dist(i, j);
  return exp((-d * d) / (2 * d0 * d0));
}

Mat getGauss(Mat img, float d0) {
  Size s1 = img.size();
  Mat H(s1.height, s1.width, CV_32F);
  Point center(s1.width / 2, s1.height / 2);

  for (int i = 0; i < s1.height; i++) {
    for (int j = 0; j < s1.width; j++) {
      H.at<float>(i, j) = gauss(i - center.y, j - center.x, d0);
    }
  }
  return H;
}

Mat pseudo_inv(Mat H, float delta) {
  Size s1 = H.size();

  Mat temp(s1.height, s1.width, CV_32F);
  for (int i = 0; i < s1.height; i++) {
    for (int j = 0; j < s1.width; j++) {
      if (H.at<float>(i, j) > delta)
        temp.at<float>(i, j) = 1 / H.at<float>(i, j);
      else
        temp.at<float>(i, j) = 0;
    }
  }
  return temp;
}

Mat gauss_high(Mat img, float d0) {
  Size s1 = img.size();

  Mat H(s1.height, s1.width, CV_32F);
  Point center(s1.width / 2, s1.height / 2);

  for (int i = 0; i < s1.height; i++) {
    for (int j = 0; j < s1.width; j++) {
//      float e = 2.71;
//      float denom = pow(e, -1*pow(F.at<float>(i, j),2)/2*pow(d0,2));

      H.at<float>(i, j) = 1.0 - gauss(i - center.y, j - center.x, d0);
    }
  }

  return convolveWithFreq(img, H);
}

Mat gauss_low(Mat img, float d0) {
  Mat H = getGauss(img, d0);
  return convolveWithFreq(img, H);
}

Mat butter_high(Mat img, float d0, int n) {
  Size s1 = img.size();

  Mat H(s1.height, s1.width, CV_32F);
  Point center(s1.width / 2, s1.height / 2);

  float r;

  for (int i = 0; i < s1.height; i++) {
    for (int j = 0; j < s1.width; j++) {
      r = sqrt(pow(i - center.x, 2.0) + pow(j - center.y, 2.0));
//      r = dist(i, j);
      H.at<float>(i, j) = (1 / (1 + pow(d0 / r, 2 * n)));
    }
  }
  return convolveWithFreq(img, H);
}

Mat butter_low(Mat img, float d0, int n) {
  Size s1 = img.size();

  Mat H(s1.height, s1.width, CV_32F);
  Point center(s1.width / 2, s1.height / 2);

  float r;

  for (int i = 0; i < s1.height; i++) {
    for (int j = 0; j < s1.width; j++) {

      r = sqrt(pow(i - center.x, 2.0) + pow(j - center.y, 2.0));
//      r = dist(i, j);
      H.at<float>(i, j) = (1 / (1 + pow(r / d0, 2 * n)));
    }
  }
  return convolveWithFreq(img, H);
}

Mat apply_filter3(Mat img1, Mat filter) {
  int value;
  Size s1 = img1.size();
  Mat img3(s1.height, s1.width, CV_8UC1);
  for (int i = 0; i < s1.height; ++i) {
    for (int j = 0; j < s1.width; ++j) {
      value = img1.at<uchar>(i - 1, j - 1) * filter.at<float>(0, 0)
          + img1.at<uchar>(i - 1, j) * filter.at<float>(0, 1)
          + img1.at<uchar>(i - 1, j + 1) * filter.at<float>(0, 2)
          + img1.at<uchar>(i, j - 1) * filter.at<float>(1, 0)
          + img1.at<uchar>(i, j) * filter.at<float>(1, 1)
          + img1.at<uchar>(i, j + 1) * filter.at<float>(1, 2)
          + img1.at<uchar>(i + 1, j - 1) * filter.at<float>(2, 0)
          + img1.at<uchar>(i + 1, j) * filter.at<float>(2, 1)
          + img1.at<uchar>(i + 1, j + 1) * filter.at<float>(2, 2);
      if (value < 0)
        value = 0;
      if (value > 255)
        value = 255;
      img3.at<uchar>(i, j) = value;
    }
  }
  return img3;
}

Mat ScharrOperator(Mat img) {
  Size s1 = img.size();
  Mat scharr_x = (Mat_<float>(3, 3) << -3, 0, 3, -10, 0, 10, -3, 0, 3);
  Mat scharr_y = (Mat_<float>(3, 3) << -3, -10, -3, 0, 0, 0, 3, 10, 3);

  Mat i1 = apply_filter3(img, scharr_x);
  Mat i2 = apply_filter3(img, scharr_y);

  return i1 + i2;

}
