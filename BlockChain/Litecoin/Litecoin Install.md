# Litecoin core 설치 방법

## 기본 설치 환경
Virtural Box 5.2.18 r124319 (Qt5.6.2)
1.	Cpu 4 core
2.	Ram 8gb
3.	저장공간 52gb


## 기본 설치 순서
-git clone
1. git clone https://github.com/litecoin-project/litecoin.git





-Dependency 설치

1.	Berkeley DB 설치
    - sudo apt-get install software-properties-common
    - sudo add-apt-repository ppa:bitcoin/bitcoin
    - sudo apt-get update
    - sudo apt-get install libdb4.8-dev libdb4.8++-dev

2.	Qt5 설치
    - sudo apt-get install libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler

3.	libboost 설치
    - sudo apt-get install build-essential autoconf libssl-dev libboost-dev libboost-chrono-dev libboost-filesystem-dev libboost-program-options-dev libboost-system-dev libboost-test-dev libboost-thread-dev

4.	Libtool, libssl, libevent 설치
    - sudo apt-get install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils python3

5.	ZMQ 설치
    - sudo apt-get install libzmq3-dev

6.	라이트코인 코어설치
    - ./autogen.sh
    - ./configure
    - make
    - sudo make install




7.	설치확인
    - Litecoind
    - 새로운 터미널 실행
    - Cd litecoin
    - Litecoind -daemon -debug
    - Litecoin 버전 정보가 뜨면 정상적으로 설치
