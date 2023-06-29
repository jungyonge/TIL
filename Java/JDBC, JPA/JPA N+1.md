#JPA N+1

##N+1 문제 발생 케이스
 - 즉시 로딩 (fetchType.EAGER) 변경후 findAll()로 조회하는 경우  
        - Post와 Comment 엔티티 간에 다대일 양방향 연관 관계입니다.   
        - @OneToMany 언노테이션의 fetch의 기본값은 지연 로딩이지만, 즉시 로딩으로 변경하면 N+1 문제가 발생할 수 있습니다.
 - 지연 로딩(LAZY) 변경 + Loop으로 조회하는 경우
 

## 해결법
- Join Fetch
    - JPQL에 fetch join 키워드를 사용해서 join 대상을 함께 조회할 수 있습니다. Post 조회 시 p.commentList도 같이 join 해서 조회해옵니다. 
~~~
@Repository
public interface PostRepository extends JpaRepository<Post, Long> {
    @Query("select p from Post p left join fetch p.commentList")
    List<Post> findAllWithFetchJoin();
}
~~~

- BatchSize
    - JPQL 페치 조인 대신 Batch 크기를 지정하는 방법도 있습니다. @BatchSize 어노테이션에 size를 지정하고 fetch 타입은 즉시로 설정합니다.
~~~
@Table(name = "post")
public class Post extends DateAudit {
 		...(생략)...
    @JsonIgnore //JSON 변환시 무한 루프 방지용
    @BatchSize(size = 2) //batch size를 지정한다
    @OneToMany(mappedBy = "post", fetch = FetchType.EAGER) //즉시로딩으로 변경한다
    private List<Comment> commentList = Lists.newArrayList();
}
~~~

- @EntityGraph
    - Eager로 가져오고 싶은것만 가져 올 수 있지만 아우터 조인이 발생하여 불필요한 쿼리를 실행하여 비추

- 참고
    - https://blog.advenoh.pe.kr/database/JPA-N1-%EB%AC%B8%EC%A0%9C-%ED%95%B4%EA%B2%B0%EB%B0%A9%EB%B2%95/
    - https://jisooo.tistory.com/entry/JPA-N1-%EC%A1%B0%ED%9A%8C-%EB%AC%B8%EC%A0%9C%EC%99%80-%ED%95%B4%EA%B2%B0%EB%B0%A9%EB%B2%95 
    - https://www.popit.kr/jpa-n1-%EB%B0%9C%EC%83%9D%EC%9B%90%EC%9D%B8%EA%B3%BC-%ED%95%B4%EA%B2%B0-%EB%B0%A9%EB%B2%95/
    - https://maivve.tistory.com/340