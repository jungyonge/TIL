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

###엔티티 설명
~~~
@Entity
@Table(name="guestbook")
public class Guestbook {
    @Id
    @GeneratedValue(strategy=GenerationType.IDENTITY)
    private Integer no;

    @Column(name="name", nullable=false, length=100)
    private String name;

    @Column(name="pwd", nullable=false, length=64)
    private String pwd;

    @Column(name="message", nullable=false)
    private String message;

    @Temporal(TemporalType.TIMESTAMP)
    @Column(name="reg_date", nullable=false)
    private Date regDate;

    // getter setter 생략
}
~~~

- @Entity
    - 객체를 테이블과 매핑 할 엔티티라고 JPA에게 알려주는 역할을 합니다. ( 엔티티 매핑 )  
     - @Entity가 붙은 클래스는 JPA가 관리하며, 이를 엔티티 클래스라 합니다.
     - @Entity 선언시 주의 사항
        - 기본 생성자는 꼭 존재해야 합니다.
        - final class, inner class, enum, interface에는 사용할 수 없습니다.
        - 필드에 final 을 사용하면 안됩니다.
    - 속성
        - name
            - JPA가 사용할 엔티티 이름을 지정합니다. ( 예제에서는 생략 )
            - name 속성은 기본 값으로 클래스 이름을 사용하기 때문에 name 속성은 생략해도 무방하지만, 만약 다른 패키지에 이름이 같은 엔티티 클래스가 있다면 이름을 지정해서 충돌하지 않도록 해야 합니다.

- @Table(name="guestbook")
    - 엔티티 클래스에 매핑할 테이블명을 선언합니다.
    - 예제에서는 name 속성을 사용해서 Guestbook 엔티티를 guestbook 테이블에 매핑했습니다.
    - 해당 어노테이션을 생략하면 엔티티 이름을 테이블 이름으로 자동 매핑합니다. ( 대소문자 구분 안함 )
     - 속성
        - name
            - 매핑할 테이블 이름 ( 기본값은 엔티티의 이름)
        - schema
            - schema 기능이 있는 데이터베이스에서 schema를 매핑
        
- @Id
    - 테이블의 기본키(PK)에 매핑합니다.
        - 기본키 생성 전략
        - 자동생성
            - @GeneratedValue 어노테이션으로 대리키 사용 방식 
            - AUTO
                - DB종류에 따라 JPA가 알맞는 것 선택
            - IDENTITY
                - 기본키 생성을 데이터 베이스에 위임.
                - MySQL, PostgreSQL, SQL Server, DB2에서 사용 가능
            - SEQUENCE
                - 데이터베이스 시퀀스를 사용해서 기본 키를 할당합니다.
                - Oracle, PostgreSQL, DB2, H2
            - TABLE
                - 키 생성 전용 테이블을 만들어서 sequence처럼 사용합니다.
         - 직접할당
            - PK값을 직접 부여하는 방식
            
- @Column
    - 엔티티의 필드를 테이블의 칼럼에 매핑합니다.
        - 속성
            - name 
                - 필드와 매핑할 테이블의 컬럼 이름 ( 기본값은 필드 이름 )
            - nullable
                - null 값 허용 여부를 설정합니다.
                - 기본 값은 true이며, false일 경우 테이블 정의 시 필드에 NOT NULL 제약 조건이 붙습니다.
            - length
                - 문자 길이 제약 조건으로 기본 값은 255이며, String 타입에만 적용 가능합니다.
      

            
            