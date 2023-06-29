## maven 외부 라이브러리 추가 방법

Maven repository에 외부 라이브러리가 없을시,  
로컬컴퓨터에서 IDE로 그냥 개발시에는 intellij에서 Project Structure에서 Module이나 Libraires에 추가하여 빌드하면 정상적으로 빌드가 되나,  
운영이나, 개발서버에 jenkins나 해당 jar파일을 배포할 시 해당 외부 라이브러리가 없기 때문에 빌드 에러가 발생한다.

외부 라이브러리 추가 방법은 여러가지가 있다.
1. catalina.sh에 ClassPath를 추가
2. catalina.properites에 common.loader추가
3. 사설 Repository 구성
4. 프로젝트 내에 jar파일 추가 후 maven에 설정

4가지 방법이 있느나, 1,2번은 여러개 서버에 모두 jar파일을 넣어주어야 함으로 패스했다.  
3번은 사설 Repository가 있으나 히스토리가 없어서 불가능.  

직관적으로는 4번이 가장 베스트였다.

### 방법
1. webapp/WEB-INF/lib/ 위치에 jar 파일을 저장
2. pom.xml에 추가 
    ~~~
    <dependency>
        <groupId>그룹아이디</groupId>
        <artifactId>아티팩트아이디</artifactId>
        <version>버전</version>
        <scope>system</scope>
        <systemPath>${basedir}/src/main/webapp/WEB-INF/lib/파일명.jar</systemPath>
    </dependency>
    ~~~
3. pom.xml에 properties로 해당경로 저장하여 사용 할 수도 있다
   ~~~
   	<properties>
   		<webcontent-dir>${project.basedir}/src/main/webapp/WEB-INF/lib</webcontent-dir>
   	</properties>
   
       <dependency>
           <groupId>그룹아이디</groupId>
           <artifactId>아티팩트아이디</artifactId>
           <version>버전</version>
           <scope>system</scope>
           <systemPath>${webcontent-dir}/파일명.jar</systemPath>
       </dependency>
   ~~~
   
###주의사항
위처럼 설정 했음에도 이상하게 jar파일 위치를 찾질 못해 하루동안 삽질을 했는데,  
원인은 경로에서 역슬래시를 사용하여 제대로 경로를 못 잡았다. 
반드시 리눅스 계열 서버는 슬래시를 사용 할 것

