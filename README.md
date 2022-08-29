# CAMERA_PUB_CPP 
ROS camera publish node - cpp   
카메라 화면을 /camera/color/image_raw topic으로 Publish 하는 노드 입니다.   


## 개발 환경
Ubuntu 20.04  
ROS Noetic
OpenCV 버전 4.2   
C++

## Noetic
에서는 따로 opencv 관련해서 특별히 해줄 것은 없고  
만약 opencv가 설치가 안 되어 있다면  

우분투 경우
```
sudo apt install libopencv-dev python3-opencv
```

다른 리눅스 디스트로일 경우에는 
```
pip3 install --upgrade pip
python3 -m pip install opencv-python
```

## Melodic
멜로딕에서는 CMakelists.txt 에 따로 opencv 패키지를 찾아서 넣어줘야 한다   
현재 camera_pub_cpp 패키지를 melodic 브랜치로 클론하면 된다   
```
git clone -b melodic https://github.com/terrificmn/camera_pub_cpp.git
```

### opencv4 빌드
melodic에서는 opencv 4 빌드한 후에 사용  
python으로 설치하는 것은 별 도움이 안 됨

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


## 모두 완료된 후 사용법
```
roscore
```

새로운 터미널을 열어서 
```
rosrun camera_pub_cpp camera_pub_cpp_node 
```

또 다른 터미널을 열고 
```
rosrun rqt_image_view rqt_image_view 
```
토픽을 /camera/color/image_raw 로 맞춰주면 화면이 나옴






