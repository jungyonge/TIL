#DBCP (Database Connection Pool)
 
Database Connection Pool 의 약자이다. 요청이 올때마다 Connection 객체를 얻는 것이 아닌,  
미리 일정 갯수 찍어내서 Connection Pool 로 관리하는 것이다. DBCP를 사용치 않으면 아래와 같은 과정을 거친다.

1) DB 서버 접속을 위해 JDBC 드라이버를 로드한다.
2) DB 접속 정보와 DriverManager.getConnection() Method를 통해 DB Connection 객체를 얻는다.
3) Connection 객체로 부터 쿼리를 수행하기 위한 PreparedStatement 객체를 받는다.
4) executeQuery를 수행하여 그 결과로 ResultSet 객체를 받아서 데이터를 처리한다.
5) 처리가 완료되면 처리에 사용된 리소스들을 close하여 반환한다.

하지만, DBCP 를 사용하면

1) WAS가 실행되면서 미리 일정량의 DB Connection 객체를 생성하고 Pool 이라는 공간에 저장해 둔다.
2) HTTP 요청에 따라 필요할 때 Pool에서 Connection 객체를 가져다 쓰고 반환한다.  

이와 같은 방식으로 HTTP 요청 마다 DB Driver를 로드하고 물리적인 연결에 의한 Connection 객체를 생성하는 비용이 줄어들게 된다.

##Commons 의 DBCP
가장 많이 쓰이는 DBCP 이다.
지금 프로젝트들 DBCP 검색하면 다 apache commons DBCP 일것 이다.

- 버전 
현재 기준으로 dbcp 홈페이지에 가보면 Last Published: 27 December 2017 | Version: 2.2.0 라고 되어있다.  
dbcp2 는 Commons Pool2 를 기반으로 하며, 1.x보다 성능이 좋아졌다고한다. 또한 JMX(Java Management eXtensions)를 지원한다.

## 속성

- initialSize : 최초 시점에 getConnection() 를 통해 커넥션 풀에 채워 넣을 커넥션 개수 (default = 0)
- maxTotal (1.x에서는 maxActive): 동시에 사용할 수 있는 최대 커넥션 개수 (default = 8)
- maxIdle : Connection Pool에 반납할 때 최대로 유지될 수 있는 커넥션 개수 (default = 8)
- minIdle : 최소한으로 유지할 커넥션 개수 (default = 0)
- maxWaitMillis (1.x에서는 maxWait) : pool이 고갈되었을 경우 최대 대기 시간 (ms단위, default = -1 = 무한정)  
  이걸 설정하지 않았는데, pool이 고갈되었고, 엔드유저의 요청은 계속 들어온다면?  
    tomcat 스레드 풀이 고갈되어 죽는다. 엔드유저 요청마다 무한정 대기중일 테니
- validationQuery : 풀에 커넥션을 반환하기 전이나, 풀을 획득하기 전에 커넥션이 valid한지를 검사,  
   mysql 기준으로 보통 select 1 설정

### 참조

[네이버 D2](https://d2.naver.com/helloworld/5102792)