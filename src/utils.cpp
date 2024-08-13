#include "utils.h"

void Utils::drawContours(cv::Mat image, std::vector<std::vector<cv::Point> > contours,
                         cv::Scalar color) {
  const cv::Point** polygons = new const cv::Point*[contours.size()];
  int* numVertices = new int[contours.size()];
  for(int i = 0; i < contours.size(); i++) {
    cv::Point* polygon = new cv::Point[contours[i].size()];
    numVertices[i] = contours[i].size();
    for(int j = 0; j < contours[i].size(); j++)
      polygon[j] = contours[i][j];
    polygons[i] = polygon;
  }

  fillPoly(image, polygons, numVertices, contours.size(), RED);

  for(int i = 0; i < contours.size(); i++)
    delete polygons[i];
  delete polygons;
  delete numVertices;
}

std::string Utils::toUpper(std::string s) {
  std::transform(s.begin(), s.end(), s.begin(), ::toupper);
  return s;
}
