# JPA 

### JPA란

JPA란 자바 ORM 기술에 대한 API 표준 명세를 의미합니다.
JPA는 ORM을 사용하기 위한 인터페이스를 모아둔 것이며, JPA를 사용하기 위해서는 JPA를 구현한 Hibernate, EclipseLink, DataNucleus 같은 ORM 프레임워크를 사용해야 합니다.

그렇다면 ORM은 무엇일까요?
ORM이란 객체와 DB의 테이블이 매핑을 이루는 것을 말합니다. (Java 진영에 국한된 기술은 아닙니다.)
즉, 객체가 테이블이 되도록 매핑 시켜주는 것을 말합니다.
ORM을 이용하면 SQL Query가 아닌 직관적인 코드(메서드)로서 데이터를 조작할 수 있습니다.

### 왜 사용 해야 하는가?
1. SQL 중심적인 개발에서 객체 중심으로 개발
    - 반본적인 CRUM Mapper 작업
2. 생산성
    - JPA를 사용하는 것은 마치 Java Collection에 데이터를 넣었다 빼는 것처럼 사용할 수 있게 만든 것이다.
        - 간단한 CRUD
          - 저장: jpa.persist(member)
          - 조회: Member member = jpa.find(memberId)
          - 수정: member.setName("변경할 이름")
          - 삭제: jpa.remove(member)  
     특히, 수정이 굉장히 간단하다.객체를 변경하면 그냥 알아서 DB에 UPDATE Query가 나간다.  
 3. 유지보수
    - 기존: 필드 변경 시 모든 SQL을 수정해야 한다.
    - JPA: 필드만 추가하면 된다. SQL은 JPA가 처리하기 때문에 손댈 것이 없다.
