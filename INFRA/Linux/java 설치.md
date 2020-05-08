## java 설치

1. 자바 설치할 디렉토리 생성  
    - sudo mkdir -p /usr/local/java
2. 자바 다운로드
    - http://www.oracle.com/technetwork/java/javase/downloads/index.html 접속 후 다운로드
    - 아니면 wget 으로 다운로드 
3. 다운로드 파일 이동 후 압축 해제 
    - sudo mv jdk1.8.0_221 /usr/local
    - sudo tar -xvf jdk-8u221-linux-x64.tar
    - sudo ln -s jdk-8u221-linux-x64 /java
        - 링크를 걸어줘서 /usr/local에 여러개의 jdk 버전을 설치 해두고 링크로 바꾸면 편하다. 
4. 환경변수 설정 
    - sudo vi /etc/profile
    - JAVA_HOME=/usr/local/java
    - CLASSPATH=.:$JAVA_HOME/lib/tools.jar
    - PATH=$PATH:$JAVA_HOME/bin
    - export JAVA_HOME CLASSPATH PATH
5. 환경변수 셀에 적용
    - source /etc/profile
6. 자바 버전확인
    - java -version
    
    
etc. openJDK와 oracleJDK 구분법
java -version 시

Java Oracle output:  
java version "1.7.0_80"  
Java(TM) SE Runtime Environment (build 1.7.0_80-b15)  
Java HotSpot(TM) 64-Bit Server VM (build 24.80-b11, mixed mode)  

java OpenJDK Output:
java version "1.7.0_91"  
OpenJDK Runtime Environment (amzn-2.6.2.2.63.amzn1-x86_64 u91-b00)  
OpenJDK 64-Bit Server VM (build 24.91-b01, mixed mode)  
 