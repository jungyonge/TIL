#사설 SSL 추가

JAVA를 이용하여 다른 업체 API나 이미지 다운로드 등 HTTPS로 remote 연결시 아래와 같은 에러 발생
~~~
javax.net.ssl.SSLHandshakeException: sun.security.validator.ValidatorException: PKIX path building failed: 

sun.security.provider.certpath.SunCertPathBuilderException: unable to find valid certification path to requested target 
~~~

SSLHandshakeException이 발생하는 이유는 연결을 시도하는 사이트의 인증서가   
신뢰하는 인증기관 인증서 목록(keystroe)에 없어서 발생한다.

해결하기 위해서는 현재 설치된 JDK의 keystore에 인증서를 생성하여 저장해야한다.

1. InstarCert.java 다운로드
    - wget https://freestrokes.tistory.com/attachment/cfile24.uf@99039A3359A277BF30627D.java
2. 해당 파일 이동
    - sudo mv [경로]/InstallCert.java ${JAVA_HOME}/jre/lib/security/
3. 해당 파일 컴파일
    - sudo javac -d . InstallCert.java
4. 컴파일 후 실행 
    - sudo java -cp . InstallCert [IP/HOST]
5. 1 누르고 엔터 

keystore에 등록된 인증서 보기  (비밀번호 : changeit)
     - keytool -list -keystore jssecacerts 
     
인증서 삭제   
    - keytool -delete -keystore jssecacerts -alias [인증서_alias]
보통 인증서 생성시 alias 안주면 IP-1이 인증서 alias   
5번 후에 alias 가 뭔지 확인 가능하다.
