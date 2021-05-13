# GeoLEDic

~~~
$ sudo apt-get install cmake libglfw3-dev libglew-dev libglm-dev libasound2-dev
~~~

or on Mac ([homewbrew](https://brew.sh) required)

~~~
$ brew install cmake glfw glm
~~~


And then:

~~~
$ git clone --recurse-submodules https://github.com/samsta/GeoLEDic.git
$ mkdir build
$ cd build
$ cmake ../GeoLEDic
$ make
~~~