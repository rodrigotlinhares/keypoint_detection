#include <cv.h>
#include <highgui.h>
#include "config.h"

class MouseSelector {
public:
  static cv::Mat select(cv::Mat image);
  static void selectionHandler(int event, int x, int y, int, void*);

private:
  static bool selecting;
  static cv::Rect selection;
  static cv::Point selectionOrigin;
};
