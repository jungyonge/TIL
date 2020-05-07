## INTRO
DB에만 있는 특정 Data만 Insert 하기 위해 DB 에서 Select하여, 존재여부를 체크하기위해 contains사용 진행  

## 시행착오

1. 처음엔 건당 Select 쿼리로 존재여부를 체크 진행했는데 속도가 너무 느려서   
2. 전체 리스트를 Select를 통해 List<String>에 담고 contains를 진행.
3. 만건당 1~2초 소모.
4. 검색 결과 List<String> 보다 Set<String>이 contains 성능이 좋음 
5. 만건당 0.1~0.2초 소모.
6. List -> Set으로 변경하는데 시간이 약간 소모됨

## 성능 차이가 나는 이유

1. 내부적으로 HashSet은 HashMap Instance를 구현하고 있고 contains() 메서드를 호출하게되면 HashMap.containsKey(object)가 호출된다고 보면 된다.
2. ArrayList는 해당 값이 list에 있는지 판단하기 위해 내부적으로 indexOf(object) 메서드를 사용한다. indexOf(object) 메서드는 array 전체를 반복해서 돌고 각각의 element와 비교를 진행한다

List는 모든 element를 비교하기 때문에 hashset보단 속도가 느리다.

~~~

  List<String> temlList = sqlSessionTemplate.selectList("쿼리");
  Set<String> setList = new HashSet<>(temlList);

  if(setList.contains("비교값"){
        로직
  }

~~~
