# Hash

해시(Hash)/해시 함수(Hash Function)/해싱(Hashing)?  
해시(Hash) 란 데이터를 다루는 기법 중 하나이며,해시 함수(Hash Function)는 데이터를 효율적으로 관리하기 위해서 임의의 길이의 데이터를 고정된 길이의 데이터로 매핑하는 함수이다.  
매핑전 원래 데이터의 값을 키(key), 매핑 후 데이터의 값을 해시값(Hash Value) 또는 해시코드 라고 하며, 키(key)와 값(value)으로 매핑되는 과정 자체를 해싱(Hashing) 이라고 한다.  

## HashTable
키(key)와 값(value)가 한쌍을 이루는 구조.  
키를 index로 사용한다.  
해시 테이블은 키를 해시 함수(hash function) 로 계산하여 그 값을 배열의 인덱스로 사용한다. 이때, 해시 함수에 의해 반환된 데이터의 고유 숫자 값을 해시값 또는 해시코드 라고 한다.  
즉, key 값을 해시 함수를 통해서 배열의 인덱스로 바꿔주고, 그 자리에 데이터를 저장한다. 정리하면 다음과 같다.

    int index = X.hashCode() % M;

원래 데이터의 값(Key) -> Hash Function -> Hash Function의 결과 = Hash Code  
-> Hash Code를 배열의 Index 로 사용 -> 해당하는 Index에 data 넣기


## 충돌(Collision)
충돌(Collision) 은 서로 다른 문자열이 Hash function을 통해 Hash 한 결과가 같은 경우 (중복되는 경우)이다.  
충돌을 줄여주는 좋은 해시 함수를 사용하는 것이 좋다.   
왜냐하면 충돌이 많아질 수록 탐색의 시간 복잡도가 O(1)에서 O(n)에 가까워지기 때문이다. 해결 방법은 다음과 같다.

- Separating Chaining - Linked List, Tree(Red-Black Tree)  
  - 자바 해시테이블, 해시맵은 두번째 방식인 세퍼레이트 체이닝(Separate Chaining)은 이름처럼 여러개를 해당 버킷에 엮는 방식이라 생각하면 된다. 링크드리스트로 엮는다.
- Open addressing - Linear Probing, Quadratic Probing, Double hashing
  - 해시 충돌이 발생하면 근처 버킷에 자료를 저장하는 방식을 가지기 때문에 그림처럼 존 스미스와 산드라 디가 같은 인덱스를 가질 때 152에 저장하지 못하고 153 버킷에 저장한다.   
  그 다음 테드 베이커가 153에 저장되려고 보면 산드라 디가 저장되어있어서 삭제를 비롯 다른 근처 버킷에 저장해야 하는 단점이 존재한다.  
  검색할 때에도 충돌 검색이 이루어진다면 근처 버킷을 순회하여 찾는 방식으로 비어있는 버킷이 보일때까지 찾는다. 
- Resizing
  - 저장 공간이 일정 수준 채워지면 Separating Chaining의 경우 성능 향을 위해, Open addressing의 경우 배열 크기 확장을 위해 Resizing
  - 보통 두배로 확장
  - 확장 임계점은 현재 데이터 개수가 Hash Bucket 개수의 75%가 될 때


데이터 갯수가 적을땐 오픈 어드레싱, 반대의 경우엔 체이닝이 효율이 좋다.   

* HashTable 장점
    * 적은 리소스로 많은 데이터를 효율적으로 관리 가능
        * ex. HDD. Cloud에 있는 많은 데이터를 Hash로 매핑하여 작은 크기의 시 메모리로 프로세스 관리 가능
    * 배열의 인덱스를 사용하기 때문에 빠른 검색, 삽입, 삭제 (O(1))
        * HashTable의 경우 인덱스는 데이터의 고유 위치이기 때문에 삽입 삭제 시 다른 데이터를 이동할 필요가 없어 삽입, 삭제도 빠른 속도 가능
    * Key와 Hash에 연관성이 없어 보안 유리
    * 데이터 캐싱에 많이 사용
        * get, put 기능에 캐시 로직 추가 시 자주 hit하는 데이터 바로 검색 가능
    * 중복 제거 유용

* HashTable 단점
    * 충돌 발생 가능성
    * 공간 복잡도 증가
    * 순서 무시
    * 해시 함수에 의존

* HashTable vs HashMap
    * Key-Value 구조 및 Key에 대한 Hash로 Value 관리하는 것은 동일
    * HashTable
        * 동기
        * Key-Value 값으로 null 미허용 (Key가 hashcode(), equals()를 사용하기 때문)
        * 보조 Hash Function과 separating Chaining을 사용해서 비교적 충돌 덜 발생 (Key의 Hash 변형)
    * HashMap
        * 비동기 (멀티 스레드 환경에서 주의)
        * Key-Value 값으로 null 허용

* HashTable 성능

  | |평균|최악|
      |----|----|----|
  |탐색|O(1)|O(N)|
  |삽입|O(1)|O(N)|
  |삭제|O(1)|O(N)|

