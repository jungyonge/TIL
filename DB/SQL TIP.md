# INTRO
업무에서 SQL작성 시 알게 된 정보 정리

## FROM 에서 UNION SUB 쿼리랑 JOIN할 시 
~~~
SELECT *
  FROM (A UNION B UNION C) UNI JOIN D 
    ON UIN.A = D.A
~~~

위와 같은 방식으로 쿼리를 작성 했을 시 UNION한 UNI의 테이블에는 INDEX가 없어서 JOIN시 상당한 시간이 걸린다.  

~~~
SELECT *
  FROM A JOIN D ON A.A.=D.D
UNION
SELECT *
  FROM B JOIN D ON B.A.=D.D
UNION
SELECT *
  FROM C JOIN D ON C.A.=D.D
~~~
조금 SQL이 지저분해보여도 위의 방식이 훨씬 빠르다
