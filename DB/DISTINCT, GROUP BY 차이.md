# INTRO
A 테이블의 row 수가 1500만개인데 B랑 INNER JOIN을 걸었더니 
row수가 1600만개가 나와서 확인해보니, B의 중복된 데이터가 있어서 더 나오는 것이였다. 
그래서 중복된 데이터를 제거하기 위해 GROUP BY, DISTINCT 사용하다가 차이점이 궁금하여 정리

## 차이점
두 개는 결국 내부적으로 같은 로직으로 수행 되나, 
DISTINCT는 단순히 그룹핑, GROUP BY는 그룹핑 후 정렬을 한다고 한다.

~~~ 
SELECT * 
  FROM A INNER JOIN B ON A.A = B.B 
~~~
단순히 위와 같은 쿼리에서는 DISTINCT가 성능적으로는 효과적이라고 한다.

허나 만약 
~~~ 
SELECT *, (SELECT * FROM C)
  FROM A INNER JOIN B ON A.A = B.B 
~~~
SELECT 안에 하위 쿼리가 있다면 GROUP BY가 효과적이라고 한다.

참조  
[기본 정보 ](http://intomysql.blogspot.com/2011/01/distinct-group-by.html)   
[SELCECT 안에 하위 쿼리 있을 시 성능 ](https://codeday.me/ko/qa/20190507/479561.html)
