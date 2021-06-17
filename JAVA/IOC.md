#IOC 제어의 역전

## intro
IoC Inversion of Control의 약자   
무슨 말이냐 ?! 제어의 역전! 즉 제어의 주체가 바뀌었다. 누구로? IoC 컨테이너로!

1. 사용이유  
    기존 자바기반 어플리케이션 개발 시 , 자바 객체를 생성하고 의존 관계를 연결 시키는건 보통 개발되는 어플리케이션이였다.  
    그래서 서블릿, EJB등 사용하는 경우 컨테이너에게 제어권이 넘어가서 객체의 생명주기를 컨테이너에서 전담한다.  (그래서 얻는 이득이 뭐임? 아래의 장점)
    객체의 생성에서 부터 생명주기 곤리 까지 개발자, 어플리케이션이 아니라 컨테이너가 대신 해준다! 그래서 제어의 역전
    
2. 장,단점
    - 장점
        - 인터페이스 기반 설계가 가능.
        - 컴퍼넌트 재사용성 증가
        - 체계적이고 효율적인 Dependency 관리
    - 단점
        - 제어구조가 반대로 되어 있으므로 이해하기 어려운 코드가 될 수 있음
         
3. DI(Dependency Injection) 이란   
    Dependency Injection이란 각 클래스 사이의 의존관계를 빈 설정(Bean Definition)정보를 바탕으로 컨테이너가 자동적으로 연결해주는 것을 말한다.  
    개발자들은 단지 빈 설정파일(저장소 관리 파일)에서 의존관계가 필요하다는 정보를 추가하기만 하면 된다.
    - 장점 
         - 코드가 단순해 진다.
         - 컴포넌트간의 결합도가 제거된다.
         - 테스트가 유리하다. Mock/Stub 사용 가능
    - 방법
        - Constructor Injection : 컴퍼넌트의 dependency 가 constructor의 argument를 통해 제공되는 방식
        - Setter Injection : 컴퍼넌트의 dependency 가 JavaBean-style setter를 통해 제공되는 방식
        - Method(Interface) Injection : 컴퍼넌트의 dependency 가 일반 메소드를 통해서 제공되는 방식 (거의 사용하지 않음)
4. DL(Dependency Lookup) 이란  
    DL은 의존성 검색이다. 이는 Bean에 접근하기 위해 컨테이너가 제공하는 API를 이용하여 Bean을 Lookup하는 것이다.  
    아래와 같이 Bean에 대한 정보가 있는 xml파일이 있다고 생각해보자.  
   ~~~
    <beans>
        <bean id="myObject" class="com.example.MyObject"/>
    </beans>
   ~~~
    java에서는 해당 xml의 Bean 정보들을 보고 어떤 클래스를 사용할지 검색하여 주입하게 된다.  
    아래 자바코드를 살펴보자.
    ~~~
    String myConfigLocation = "classpath:myApplicationCTX.xml";
    AbstractApplicationContext ctx = new GenericXmlApplicationContext(myConfigLocation);
    MyObject myObject = ctx.getBean("myObject", MyObject.class);
    ~~~
    그 결과 위와 같은 코드를 통해 적절한 MyObject클래스를 가져올 수 있는 것이다.
 
- 참조
    - https://happy-playboy.tistory.com/entry/%EB%B0%B1%EC%88%98%EC%9D%98-%EC%8A%A4%ED%94%84%EB%A7%81-IoC%EC%99%80-DI%EC%97%90-%EB%8C%80%ED%95%B4%EC%84%9C