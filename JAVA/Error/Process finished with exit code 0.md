#Spring boot Process finished with exit code 0 해결

Spring boot 시작 시 앱이 실행하자마자 Process finished with exit code 0 뜨면서 바로 종료되는 경우가 있다.
구글링 하니 여러가지 방법이 나와서 정리...

필자는 3번하니 됐음..
Maven 경로가 잘못 되어있는 경우가 종종 있는듯

4개다 했는데도 안된다면 프로젝트 재생성을 추천

- pom.xml에서 <packaging>war</packaging> 로 되어있는 경우
~~~
<dependency>
	<groupId>org.springframework.boot</groupId> 
    <artifactId>spring-boot-starter-tomcat</artifactId> 
    <scope>compile</scope> 
</dependency>
~~~
추가 하거나 
~~~
<packaging>jar</packaging>
~~~
로 변경

-  아니라면 아래 라이브러리 추가
~~~
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>
 ~~~
- ㅁMaven 리로드
    위에도 다 안된다면 Maven 프로젝트 리로드
     사진 맨 왼쪽 버튼 클릭

- 만약 Maven에 spring-boot-starter-web와 spring-boot-starter-tomcat이 둘다 있다면 tomcat 삭제
