# CAMERA_PUB_CPP 
ROS camera publish node - cpp   

# 개발 환경
Ubuntu 20.04  
ROS Noetic  / Melodic
OpenCV 버전 4.2   
C++

## opencv 4 빌드하기
먼저 opencv를 깃 클론 한 후 빌드해야함~  

```
git clone https://github.com/opencv/opencv.git
```
이동 후 빌드 디렉토리 만들기
```
cd opencv
mkdir build
```

cmake를 이용해서 build script를 생성
```
cmake ../
```

그리고 build 
```
make -j4
```

빌드가 완료되면 install을 해주자  
```
sudo make install 
```

## melodic 
use melodic branch    
ros 멜로딕 버전에서 opencv 4 잘 됨. 
