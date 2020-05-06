## INTRO
DB에만 있는 특정 Data만 Insert 하기 위해 DB 에서 Select하여, 존재여부를 체크하기위해 contains사용 진행  

## 시행착오
1. 처음엔 건당 Select 쿼리로 존재여부를 체크 진행했는데 속도가 너무 느려서   
2. 전체 리스트를 Select를 통해 List<String>에 담고 contains를 진행.
3. 만건당 1~2초 소모.
4. 검색 결과 List<String> 보다 Set<String>이 contains 성능이 좋음 
5. 만건당 0.1~0.2초 소모.
6. List -> Set으로 변경하는데 시간이 약간 
## 코드 
