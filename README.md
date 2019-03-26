# FeatureDetector_Framework

## 1. install 
opencv 4.0+
Qt 5.8
Visual Studio 2017 (vc15)

### 1.1 install opencv
It would be better to complie opencv by yourself, if you would like to use opencv extra modules.

I found it convinient to compile via Cmake and VS studio and if you follow this pattern,these  useful tools are required:
- cmake 3.1 or above [https://cmake.org/download/]
- git 
- VS 2015 or 2017 (or some other versions )

firstly, download soure of opencv and opencv contrib
```git
cd project
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git
```

and then, open Cmake and set the soure code path
`you dir/project/opencv` and choose the a dir to build the binaries, such as, `you dir/project/cv_vsproject/`. clike configure and you are required to choose your compiler IDE (VS here), and to choose your platform (remeber win32 by default, and you should choose x64 in my suggestion). after the configure is finish, you will find there are so many configurations for you to custom by yourself. 
![cmake](screenshoot/cmake.png)
Here are some important settings you should pay attention to :
- set `BUILD_opencv_world` on
- set `OPENCV_EXTRA_MOUDLES_PATH` to `you dir/project/opencv_contrib/modules` 
- set `OPENCV_ENABLE_NOFREE` on if you want use nonfree algorithms such as `SIFT` and `SURF`
