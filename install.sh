echo "Installing all dependencies, It will take a while, go grab a cup of coffee..."
rm -rf lib
sudo apt update && sudo apt install -y cmake g++ wget unzip

mkdir -p lib
cd lib

wget -O opencvz https://github.com/opencv/opencv/archive/refs/tags/4.5.3.zip
wget -O opencvcontribz https://github.com/opencv/opencv_contrib/archive/refs/tags/4.5.3.zip
unzip opencvz
unzip opencvcontribz
rm opencvz
rm opencvcontribz

mkdir opencv
cd opencv

cmake -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib-4.5.3/modules ../opencv-4.5.3
cmake --build .

rm -rf opencvz
rm -rf opencvcontribz