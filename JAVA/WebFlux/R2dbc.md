## R2DBC

Webflux는 비동기 통신으로 통신을 하는데,  
기존의 관계형 DB들은 블로킹 방식이라 DB단에서 병목이 걸린다

그래서 이를 해결해주기 위해서 나온게 R2DBC이다.

### JPA는 사용을 추천하지 않는다.
Webflux는 비동기로 돌아가는데 위에 적었다 싶이 JPA는 블로킹이라 사용할 이유가 없어진다.  
비동기 인데 결국 DB단에서 동기이면 webflux의미가 없어질 듯.  
아래는 성능비교  
- https://happyer16.tistory.com/entry/%EC%8A%A4%ED%94%84%EB%A7%81-blocking-vs-non-blocking-R2DBC-vs-JDBC-WebFlux-vs-Web-MVC

### 그래서 R2DBC
그래서 블로킹방식의 DB를 논블로킹방식의 DB로 통신하게끔 도와주는게 R2DBC이다.  
R2dbcRepository를 통해서 JpaRepository처럼 어느정도의 기술을 사용 할 수 있지만 지원하지 않는 기술도 있다.
- 공통점 
  - 테이블생성, 데이터매핑은 해줌
  - CRUD의 간편함
  - TX관리

- 차이점
  - 쿼리 언어: Spring Data JPA는 JPQL(QueryDSL)이나 네이티브 SQL 쿼리를 사용하여 데이터베이스에 쿼리를 전송합니다. Spring Data R2DBC는 주로 네이티브 SQL 쿼리를 사용하며, JPQL(QueryDSL)보다는 네이티브 SQL에 더 초점을 맞추고 있습니다.
  - 엔티티 상속: Spring Data JPA는 엔티티 상속 전략을 지원하며, 상속 구조를 통해 테이블을 생성하고 데이터를 저장할 수 있습니다. Spring Data R2DBC는 엔티티 상속을 지원하지 않습니다.
  - Lazy Loading: Spring Data JPA는 지연 로딩(Lazy Loading)을 지원합니다. Spring Data R2DBC는 리액티브 프로그래밍 모델과 함께 사용되기 때문에, 기본적으로 지연 로딩을 지원하지 않습니다.
  - 두 번째 레벨 캐시: Spring Data JPA는 두 번째 레벨 캐시(Second Level Cache)를 지원합니다. Spring Data R2DBC는 리액티브한 특성을 가지므로 두 번째 레벨 캐시를 지원하지 않습니다.
  - Specification 패턴: Spring Data JPA는 Specification 패턴을 사용하여 동적인 쿼리를 구성하는 기능을 제공합니다. Spring Data R2DBC는 Specification 패턴을 지원하지 않습니다.
  - QueryDSL 통합: Spring Data JPA는 QueryDSL을 사용하여 동적인 쿼리를 작성하고 실행하는 기능을 제공합니다. Spring Data R2DBC에서는 QueryDSL의 기능을 사용할 수 없습니다.
  - 데이터베이스 드라이버: Spring Data JPA는 JDBC 기반의 데이터베이스 드라이버를 사용합니다. Spring Data R2DBC는 R2DBC 기반의 데이터베이스 드라이버를 사용합니다.
  - 지원하는 데이터베이스: Spring Data JPA는 전통적인 RDBMS와 연동되는 데 강점을 가지며, 다양한 데이터베이스 시스템과 호환됩니다. Spring Data R2DBC는 비동기적인 리액티브 데이터베이스와 연동됩니다.