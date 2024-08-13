#include "mouse_selector.h"

bool MouseSelector::selecting;
cv::Rect MouseSelector::selection;
cv::Point MouseSelector::selectionOrigin;

cv::Mat MouseSelector::select(cv::Mat image) {
  cv::namedWindow("Selected Object", CV_WINDOW_NORMAL);
  cv::setMouseCallback("", selectionHandler, &image);
  selecting = false;
  cv::imshow("", image);
  cv::waitKey();
  cv::destroyWindow("Selected Object");
  return cv::Mat(image, selection).clone();
}

void MouseSelector::selectionHandler(int event, int x, int y, int, void* imagePointer) {
  cv::Mat image = *(cv::Mat*)imagePointer;
  cv::Mat imageCopy = image.clone();
  if(event == CV_EVENT_LBUTTONDOWN && !selecting) {
    selectionOrigin = cv::Point(x, y);
    selecting = true;
  }
  else if(event == CV_EVENT_LBUTTONDOWN && selecting) {
    selection = cv::Rect(selectionOrigin, cv::Point(x, y));
    selecting = false;
    cv::imshow("Selected Object", cv::Mat(image, selection));
  }
  if(selecting)
    rectangle(imageCopy, selectionOrigin, cv::Point(x, y), BLUE, 2);
  cv::imshow("", imageCopy);
}
