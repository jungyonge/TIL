## 클래스형 컴포넌트 vs 함수형 컴포넌트

React 컴포넌트를 만들때 클래스형 컴포넌트, 함수형 컴포넌트 2가지 방식이 있다  
과거에는 클래스형 컴포넌트를 많이 사용했지만  
2019년 v16.8 부터 함수형 컴포넌트에 리액트 훅(hook)을 지원해 주어서  
현재는 공식 문서에서도 함수형 컴포넌트와 훅(hook)을 함께 사용할 것을 권장하고 있다.   


## class component
<img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2Fb8VeTX%2FbtrTa5UxQJB%2FRrneVKfMAPj6ZYXMAfHLD1%2Fimg.png" alt="image" width="800" height="auto">

1. class 키워드가 반드시 필요하다.
2. Component로 상속 받아야 한다. 
3. render() 메소드가 반드시 필요하다.

## function component
<img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FldRoV%2FbtrTbkw9fPf%2FNJsOT1rrmViz3ttY1N41K0%2Fimg.png" alt="image" width="800" height="500">   

1. 함수형 컴포넌트 선언이 매우 간편하다.


### 기능적 차이

- 클래스형(class component)
  - state, lifeCycle 관련 기능사용 가능하다.
  - 메모리 자원을 함수형 컴포넌트보다 조금 더 사용한다.
  - 임의 메서드를 정의할 수 있다.

- 함수형(function component)
  - state, lifeCycle 관련 기능사용 불가능 (Hook을 통해 해결 가능)
  - 메모리 자원을 함수형 컴포넌트보다 덜 사용한다.
