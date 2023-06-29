#JSP 변경사항 새로고침

tomcat을 사용시에는 설정에서 Update 설정에서 변경해주면 됐는데, Boot는 적용이 안돼서 알아보니 설정법이 달랐다.

Spring Boot JSP화면의 변경 사항이 새로고침을 해도 반영되지 않는 문제가 발생했다.   
JSP 수정시마다 서버 재시작을 할 수는 없는 법, 캐쉬를 삭제하고 새로고침을 시도해도 현상은 마찬가지.  
검색 결과 server.jsp-servlet.init-parameters.development=true 설정을 추가하는 방법도 있었으나  
spring boot reference에서 찾을 수 없는 설정값인데다 해당 설정값이 어디에서 관리되고 있는지에  
대한 설명 글을 찾을 수 없어서 다른 방법을 찾던 중
spring-boot-devtools에서 JSP 변경 사항 동적으로 새로고침 기능을 지원해준다고 하여 적용하였다.   
spring-boot-devtools은 평소 spring boot 프로젝트 생성시 궁금해하던 기능이였는데 이런 기능을 지원해주는구나.
## 방법
- dependency 추가
~~~
  <dependency>
      <groupId>org.springframework.boot</groupId>
      <artifactId>spring-boot-devtools</artifactId>
  </dependency>
~~~

- application.properties 추가
~~~
    spring.devtools.livereload.enabled=true
~~~