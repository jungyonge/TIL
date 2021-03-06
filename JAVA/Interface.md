# Interface

## 인터페이스란
인터페이스란 상수(static final)와 추상 메서드(abstract method)의 집합입니다.   
생성자를 가질 수 없으며 따라서 객체화가 불가능합니다.  
 인터페이스에 선언된 상수와 추상 메서드는 public static final 과 public abstract 를 생략해도 되는데   
이유는 컴파일 시에 자동으로 생성해주기 때문입니다. 인터페이스는 다중상속을 지원하며, 구현체에 여러개의 인터페이스를 구현할 수 있습니다.

## 인터페이스 사용이유
1. 협업
   여러명이 개발을 동시에 진행할 시 사용할 interface를 구성해놓고 
   impl하여 진행하면 메소드통일을 할 수 있고, 원하는 객체를 골라서 사용 가능하다.
   
2. 교체 용이
   만약 사용하는 객체가 바뀌어야 한다면 
   생성하는 부분에 필요한 객체로면 변경 해주면 된다.
   
3. 다중상속
    추상화와 다르게 다중 상속가능, 추상화클래스 상속 + 인터페이스 impl도 가능 
    
##etc
의미 없이 사용 하는 경우가 너무 많다.  
확장성여부도 없는데 일단 service부터 만들고 impl로 시작하면,, 오히려 코드 분석이 더 복잡스러운 듯 하다.  
허나 확장 가능성이 있으면 제대로 구성해놓고 사용하면 분명 코드생산성은 증가할 듯 하다.   
정말 초기 interface를 잘 만들지 못한다면 유지보수가 늘어나는 것 같다..

[참고]  
- https://junspapa-itdev.tistory.com/36
- https://gofnrk.tistory.com/22
- https://medium.com/webeveloper/%EC%9E%90%EB%B0%94-%EC%9D%B8%ED%84%B0%ED%8E%98%EC%9D%B4%EC%8A%A4%EC%99%80-%EC%B6%94%EC%83%81%ED%81%B4%EB%9E%98%EC%8A%A4-6eecbe5d6350
- https://myjamong.tistory.com/150