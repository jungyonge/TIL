#JPA N+1

##N+1 문제 발생 케이스
 1.즉시 로딩 (fetchType.EAGER) 변경후 findAll()로 조회하는 경우  
Post와 Comment 엔티티 간에 다대일 양방향 연관 관계입니다.   
@OneToMany 언노테이션의 fetch의 기본값은 지연 로딩이지만, 즉시 로딩으로 변경하면 N+1 문제가 발생할 수 있습니다.

## 해결법
- Join Fetch

- @EntityGraph

- BatchSize