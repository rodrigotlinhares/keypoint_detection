#include "descriptor_generator.h"

cv::Mat DescriptorGenerator::generate(cv::Mat image, KeyPointVector keyPoints, std::string method) {
  cv::Mat result;
  if(method.compare(METHOD_ORB) == 0) {
    cv::ORB orb; //TODO parameters
    orb(image, cv::Mat(), keyPoints, result, true);
  }

  else if(method.compare(METHOD_BRISK) == 0) {
    cv::BRISK brisk; //TODO parameters
    brisk(image, cv::Mat(), keyPoints, result, true);
  }

  else if(method.compare(METHOD_SIFT) == 0) {
    cv::SIFT sift; //TODO parameters
    sift(image, cv::Mat(), keyPoints, result, true);
  }

  else if(method.compare(METHOD_SURF) == 0) {
    cv::SURF surf; //TODO parameters
    surf(image, cv::Mat(), keyPoints, result, true);
  }
  return result;
}
