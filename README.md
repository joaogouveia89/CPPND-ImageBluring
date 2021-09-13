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

## Classes attributes, and functions overview

1. Gui: Gui use wx widgets library to create the UI elements and it's handling entitites.<br/>
2. ImgPool

    2.1 -Attributes:<br/>
        <u><b> _images:</b></u> Array that saves during runtime the handled images<br/>
          <u><b>_originalImage: </b></u>Mat object that holds the loaded image, so it can be passed by reference to computing function avoiding data copies(it does make difference with big images)<br/>
          <u><b>_inputWidth: </b></u>image width<br/>
          <u><b>_inputHeight: </b></u>image height<br/>
          <u><b>advanceRatio: </b></u>this attribute considers the width and height of the image to decide how much images should be calculated in advance to offer a better experience to the user. So whenever he/she advances the seek bar the image is ready to be shown<br/>
      2.2 -Methods:<br/>
        AskFor: receives a sigma as parameter and returns the handled image for the asked sigma<br/>


3. Img class to store the computed image with the gauss blur function<br/>
  3.1 -Attributes:<br/>
     <u><b> _sigma_:</b></u> Sigma value to apply the gaussian filter<br/>
       <u><b>_result_: </b></u>Shared pointer that holds the result of computing<br/>
       <u><b>_width: </b></u>image width<br/>
       <u><b>_height: </b></u>image height<br/>
       <u><b>computingDone: </b></u>Flag to check the status of computation<br/>
  3.2 -Methods:<br/>
    toWxBitmap: Converts mat object to wx widgets wximage object to be displayed on panel<br/>
    Sigma: returns sigma<br/>
    Compute: Computes the gauss filter using a async task in order to do it in parallel<br/>
    isComputingDone: Check if compute is done<br/>