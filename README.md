# CAMERA_PUB_CPP 
ROS camera publish node - cpp   
카메라 화면을 /camera/color/image_raw topic으로 Publish 하는 노드 입니다.   

noetic-tinker 브랜치  

싱글보드 컴퓨터 tinker board 2 (ASUS) 를 사용하는 버전.  
ROS 메세지를 받아서 카메라를 작동시키고, 중지 해야할 경우에는 CameraDriver 클래스에서 이미지 처리를 하지 않고  
클래스 Delete 시켜서 Cpu 사용을 거의 안하게 되는 카메라 노드

## 개발 환경
Ubuntu 20.04  
ROS Noetic
OpenCV 버전 4.2   
C++
Tinker Board 2 (single board computer)

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

### opencv4 빌드
melodic 버전에서는 opencv 4 빌드한 후에 사용  (또는 noetic에서도 빌드가 필요한 경우 참고)   
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

새로운 터미널을 열어서 런치파일 실행
```
roslaunch camera_pub_cpp camera_pub.launch 
```

> 런치파일 사용 시 파라미터 사용가능하므로 config 디렉토리의 환경설정 파일 사용가능

또는 노드만 실행 (기본파라미터 사용)
```
rosrun camera_pub_cpp camera_pub_cpp_node 
```

또 다른 터미널을 열고 
```
rosrun rqt_image_view rqt_image_view 
```
토픽을 /camera/color/image_raw 로 맞춰주면 화면이 나옴


## config
config 디렉토리의 camera_params.yaml 에서 사용

- camera_id : integer로 지정 

비디오 id 확인하려면
```
ls -l /dev/video*
```
로 나온 결과가 있으면 높은 결과로 0 으로 사용,   
먄약 0이 아닌 /dev/video3 이런식으로 나오면 3으로 사용   

> 여러개가 나올 경우에는 (한 device에서) 하나씩 테스트 해본다.

- rate: integer로 지정 ... publish 속도 또는 imgshow 의 속도

- enable_imgshow: bool type 지정. imgshow 로 보여준다. default는 false

