#@Transactional 
## 트랜잭션의 성질
▶ 원자성(Atomicity)
 - 한 트랜잭션 내에서 실행한 작업들은 하나로 간주한다. 즉, 모두 성공 또는 모두 실패. 

▶ 일관성(Consistency)
 - 트랜잭션은 일관성 있는 데이타베이스 상태를 유지한다. (data integrity 만족 등.)

▶ 격리성(Isolation)
 - 동시에 실행되는 트랜잭션들이 서로 영향을 미치지 않도록 격리해야한다.

▶ 지속성(Durability)
 - 트랜잭션을 성공적으로 마치면 결과가 항상 저장되어야 한다.

## 스프링에서 트랜잭션 처리 방식

스프링에서는 트랜잭션 처리를 지원하는데 그중 어노테이션 방식으로 @Transactional을 선언하여 사용하는 방법이 일반적이며, 선언적 트랜잭션이라 부른다.  
클래스, 메서드위에 @Transactional 이 추가되면, 이 클래스에 트랜잭션 기능이 적용된 프록시 객체가 생성된다.  
이 프록시 객체는 @Transactional이 포함된 메소드가 호출 될 경우, PlatformTransactionManager를 사용하여 트랜잭션을 시작하고, 정상 여부에 따라 Commit 또는 Rollback 한다.


## 특징
- RuntimeException에 대해서만 롤백처리가 가능하다
  (Exception에 대한 설명은 여기 잘 정리되어 있음 http://www.nextree.co.kr/p3239/)

- MySQL일 경우 Inno일때만 트랜잭션이 작동함
- proxy를 사용할 때 반드시 public 메소드에 사용해야 한다
- 클래스들이 인터페이스를 사용하는지 확인해야함
  Spring Framework 의 경우 JDK Dynamic Proxy(인터페이스 기반) 로 Proxy 를 생성하고
  Spring Boot 의 경우 CGLib(클래스 기반) 로 Proxy 를 생성한다.
- 인터페이스없이 트랜잭션을 작동시키려면 CGLib Proxy를 사용하면됨(proxy-target-class="true")  
ex) <tx:annotation-driven transaction-manager="transactionManager" proxy-target-class="true"/>
- https://velog.io/@ette9844/Spring-Transactional-%EC%96%B4%EB%85%B8%ED%85%8C%EC%9D%B4%EC%85%98-%EC%83%81%EC%86%8D

##참조
- https://cchoimin.tistory.com/entry/Transactional-%EC%84%B8%ED%8C%85-%EB%B0%8F-%EC%82%AC%EC%9A%A9%EB%B2%95
- https://www.podo-dev.com/blogs/133
- https://goddaehee.tistory.com/167
- https://interconnection.tistory.com/123