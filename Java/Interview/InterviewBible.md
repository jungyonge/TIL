## 개발자 면접 Bible 2023ver

### 설명
- 2023년 기준 면접 30번이상 본 경험을 바탕으로 작성
- 해당 질문제외하고 추가적으로 더 공부할 부분은 알아서 생길거임
- 다 일단 해두면 분명 도움됨
- 공부내용 github 정리해두면 좋음(가끔 면접관이 github 봄)
- 면까몰이라고 하는데 부정적인 분위기는 대부분 탈락함
- 긍정적 분위기인데 탈락하는 경우 많음(이게 면까몰 인듯)

### 기본준비
- 기본적으로 해온 프로젝트에 대한 설명, 기술스택 숙지, 사용이유, 장단점, 정리
- 트러블 슈팅
- 해온 프로젝트에서 성능향상을 위해 노력한 점
- 지원한 회사의 프로덕트 공부, 서비스 있으면 미리 설치, 사용해보고 어필
- 지원동기 3개 이상(지원동기에 대한 추가 질문이 들어올 수 있음으로 거짓 ㄴㄴ)
- 자기소개
  - 경럭기반, 해온 업무, 기술스택 설명
  - 본인의 필살기 (개발자로서 장점 or 자랑할 수 있는 경험 or 레거시 성능향상,리펙토링 경험)
  - 필살기 바탕으로 난 이러한 개발자니 날 뽑아라 어필
  - 지원동기 3개이상

### 코딩테스트
- 코딩테스트는 프로그래머스가 90%, 코딜리티 10%, 구름 1번
- 프로그래머스는 SQL 문제도 있음
- 시간과 문제 갯수는 회사별로 다 상이
- 복붙 막아논 코딩테스트도 있음
- 코딜리티는 단순히 코딩테스트 말고도 API 구현, 테스트코드 작성도 있다.
- 코딩테스트 필수 알고리즘 DFS, BFS, DP, PrefixSum, 단순 요구사항 구현 
- 솔직히 운빨도 있음. 모르는 문제유형 나오면 아무리 고민해도 못 품(과감히 포기)
- 코딩테스트는 백준, 프로그래머스로 연습
- ChatGPT로 문제 복붙하고 어느 정도 기본틀 만들어주는데, 수정해서 해도 됨(복붙막아논 경우 크롬 드래그프리 설치해서 사용)

### 과제테스트
- 가장 많은 유형은 당연히 API 서버 개발
- SpringBoot, Gradle, JPA, H2, 테스트코드는 거의 Default
- README 필수
- 과제 유형
  - Spring Security + JWT 사용하여 회원가입 구현
    - 회원가입 구현을 바탕으로 요구사항 API 개발
    - 입사지원한 회사마다 요구사항 API 상이(대부분 회사 도메인관련)
  - 특정 입력이 있고 그것을 원하는 결과값으로 출력
    - 해당유형 맨날 탈락, 이유 모르겠음
    - 주소 입력 -> 올바른 주소 출력
    - 댓글 리스트 log 입력 -> 댓글에서 학교이름 추출해서 count 출력

### 기술질문
- OOP 란
- OOP 특징 4개, 사용해본 특징
- SOLID 설명, 내가 개발할때 실제로 적용한 부분, 장,단점
- 클린코드, 클린아키텍처란?
- 헥사고날 아키텍처란?
- Spring, SpringBoot 장단점, 차이점
- 인터페이스와 abstract 원론적 두개가 존재하는 이유(원론적인 이유는 나도 모름)
- Rest API 설명, 특징, 장단점, 어떠한 규칙은 지키려고 하는지(솔직히 다 못지킴)
- HTTP 4가지 Method 설명 차이점
- HTTP 멱등성
- 프레임워크 라이브러리 차이
- 싱글톤 패턴이란? 주의할 점
- JVM 란?
- GC 설명
- Bean 이란?
- POJO 란?
- Bean Container 란?
- IOC/DI 란? 실제 개발시 적용한 부분
- DI 방법, 방법별로 차이점
- AOP 란? 실제 개발시 적용한 부분
- 각 Collection 별 차이, 장단점
- Thread-Safe 란? Thread-Safe 위한 방법, 경험
- CORS 란?
- JAVA 버전별 차이, 추가된 기능, 사용해본 기능
- ACID 란? (질문 받은 적은 없지만 공부해두면 좋음)
- DB 트랜잭션 격리수준 (질문 받은 적은 없지만 공부해두면 좋음)
- RDBMS,NOSQL 사용해본 DB, 차이점
- DB 스키마 설계 경험
- Index 설명, 설정시 주의할 점, 장단점
- Join 종류
- 쿼리 얼마나 사용하는지?(주관적)
- 스프링에서 Bean 만드는 방법 3가지
- JPA, Mybatis 설명, 차이, 사용해본 부분
- JPA 영속성 컨텍스트란? 장점
- JPA N + 1 설명, 해결법, 해결법 중 사용해본 부분
- Query DSL 설명, 사용해본 부분
- 동시성 문제(비관적락, 낙관적락)
- 동기, 비동기
- 블록, 논블록
- API 설계시 고려하는 부분
- Spring security, Oauth 란?
- JWT 란?
- 세션, 쿠키란?
- 필터, 인터셉터 설명, 차이점, 사용해본 부분
- 도커, 쿠버네티스란? 사용해본 부분
- CI/CD란? 사용해본 부분
- MAS 란? 장단점
- 기본적인 암호화 알고리즘 종류 (단방향, 양방향)
- HTTP, HTTP2 차이, 장단점
- CSR, SSR 차이 장단점
- 상황설명 후 어떻게 아키텍처 구성할지
- 트래픽이 몰리는 상황이라면 어떻게 구성할지(오토스케일링, Nginx)
- Redis 설명, 장단점, 사용 경험
- 테스크코드 작성 경험
- DDD, TDD, 레이어드아키텍쳐 설명, 왜 사용하는지, 장단점
- MVC 설명, 라이프사이클 (질문 받은 적은 없음, 너무 기본적인 질문이라 그런건가)
- DTO, DAO 사용이유
- DBCP 란?
- 추상적이지만 어떠한 가치관, 방법론으로 개발하려고 하는지 설명
- 모니터링 방법, 경험
- 프로젝트 아키텍쳐 구현경험 (주니어한테 이걸 왜 묻는지는 의문)
- 프로세스, 쓰레드 설명
- 인프라 경험(AWS)
- 


### 인성질문
- 왜 우리회사인지? (지원동기) 
- 본인의 장단점
- 동료, 친구들이 본인을 평소에 어떻게 평가하는지
- 어떠한 개발자가 되고 싶은지?
- 왜 백엔드 개발자 인지?
- 평소에 공부방법?
- 최근에 공부한 기술, 앞으로 공부 하고 싶은 기술
- 지금 공부하고 있는거 말고 공부했던 기술
- 코드 리뷰 경험
- 학생때 제일 재밌게 공부한 과목
- 기본적으로 협업경험(필수)
- 의견 대립시 대처,설득방법, 경험, 본인만의 노하우
- 기획자, 타팀과 대화방법, 협업방법
- 어떠한 개발자, 팀원이랑 일하고 싶은지/ 일하기 싫은지
- 언제 스트레스를 받는지
- 취미, 스트레스 푸는방법
- 팀워크란?
- 퇴사이유
- 팔로워, 리더중 무슨 유형인지
- 단기적, 장기적 묙표(직무, 개인)
- 공백기가 있다면 뭐했는지, 왜했는지

### 내가 회사에 했던 질문
- 지원한 회사에 대한 궁금점 질문(서비스가 있으면 사용해보고 왜 이런거에요? 어필)
- 입사할 팀의 구성, 연차
- 입사하게 된다면 맡게될 개발도메인
- 개발, 유지보수해야 할 프로젝트 수
- MSA, 모놀로틱 중 어떤걸로 구성
- 현재 회사의 지향점 (신규개발, 유지보수, 고도화)
- 프로젝트의 진행방식
- 코드리뷰 유무, 방식
- 온보딩 시스템, 기존 시스템 문서화 잘되어 있는지 질문
- 회사에 입사하게 된다면 다른 회사보다 많이 해볼 수 있는 경험
- 회사게 입사하게 된다면 미리 공부하면 좋은 기술스택, 비지니스도메인
- 면접관님들은 왜 이 회사를 선택했는지, 느끼시는 회사의 장점
- 결원 or 충원
- 유연근무, 재택근무 한다면 어떠한 방식으로 하는지 질문
- 연봉, 복지 질문은 하지 말 것(어차피 합격하고나서 물어봐도됨)

### 유용한 블로그
- https://velog.io/@j_user0719/%EA%B8%B0%EC%88%A0%EB%A9%B4%EC%A0%91-%EC%A4%80%EB%B9%84-CS-%ED%8E%B8
- https://jeong-pro.tistory.com/
- https://gmoon92.github.io/
- https://steady-coding.tistory.com/599
- https://mangkyu.tistory.com/150?category=761302
- https://notspoon.tistory.com/32
- https://backendcode.tistory.com/166
- https://ehdvudee.tistory.com/52
