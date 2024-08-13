#include "detector.h"

KeyPointVector Detector::findKeyPoints(cv::Mat image, std::string method) {
  KeyPointVector result;
  if(method.compare(METHOD_FAST) == 0)
    cv::FAST(image, result, 100); //TODO parameters

  else if(method.compare(METHOD_ORB) == 0) {
    cv::ORB orb; //TODO parameters
    orb(image, cv::Mat(), result, cv::noArray());
  }

  else if(method.compare(METHOD_BRISK) == 0) {
    cv::BRISK brisk; //TODO parameters
    cv::Mat output; // Workaround. cv::noArray() should work, but it doesn't.
    brisk(image, cv::Mat(), result, output);
  }

  else if(method.compare(METHOD_SIFT) == 0) {
    cv::SIFT sift; //TODO parameters
    sift(image, cv::Mat(), result, cv::noArray());
  }

  else if(method.compare(METHOD_SURF) == 0) {
    cv::SURF surf; //TODO parameters
    surf(image, cv::Mat(), result, cv::noArray());
  }
  return result;
}

void Detector::runMSER(cv::Mat image) {
  cv::MSER mser(5, 60, 1000); //TODO parameters
  std::vector<std::vector<cv::Point> > contours;
  mser(image, contours, cv::Mat());
  Utils::drawContours(image, contours, RED);
}
