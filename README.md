# CPPND: Program a Image Blurring application

<img src="data/traffic_simulation.gif"/>

This is the project for the fourth course in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213): Capstone. 

This application uses the open cv function(GaussBlur) to blur a input image provided by the user, with different sigma value, selected on a progress bar

## Dependencies for Running Locally
* cmake >= 2.8
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* OpenCV >= 4.1
  * The OpenCV 4.1.0 source code can be found [here](https://github.com/opencv/opencv/tree/4.1.0)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./image-blurring`.

## Project Structure

1. Gui: Gui use wx widgets library to create the UI elements and it's handling entitites.
2. ImgPool: This class handles all the images treatment, also keeps track of all treated images to display to the user, the idea is to avoid unecessary computing, if the user does not want big sigma values. If user wants, for example a sigma 10, it doesn't make sense to calculate sigma = 20.
3. Img class to store the computed image with the gauss blur function