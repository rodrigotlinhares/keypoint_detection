//TODO BOWImgDescriptorExtractor
//TODO FernClassifier
//TODO OneWayDescriptorBase

#include <iostream>
#include "controller.h"

int main(int argc, char** argv) {
  Controller controller;
  controller.parseArguments(argc, argv);
  controller.run();
  std::cout << "Done." << std::endl;
  return 0;
}
