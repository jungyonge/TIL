#Bean

## Bean이란

![bean](img/bean.png)

- Spring에서 POJO(plain, old java object)를 ‘Beans’라고 부른다.  
- Beans는 애플리케이션의 핵심을 이루는 객체이며, Spring IoC(Inversion of Control) 컨테이너에 의해 인스턴스화, 관리, 생성된다.  
- Beans는 우리가 컨테이너에 공급하는 설정 메타 데이터(XML 파일)에 의해 생성된다.  
- 컨테이너는 이 메타 데이터를 통해 Bean의 생성, Bean Life Cycle, Bean Dependency(종속성) 등을 알 수 있다.  
- 애플리케이션의 객체가 지정되면, 해당 객체는 getBean() 메서드를 통해 가져올 수 있다.  

Spring Bean 정의
일반적으로 XML 파일에 정의한다.
- 주요 속성
    - class(필수): 정규화된 자바 클래스 이름
    - id: bean의 고유 식별자
    - scope: 객체의 범위 (sigleton, prototype)
    - constructor-arg: 생성 시 생성자에 전달할 인수
    - property: 생성 시 bean setter에 전달할 인수
    - init method와 destroy method
    
선언 예제 
~~~
<!-- A simple bean definition -->
<bean id="..." class="..."></bean>

<!-- A bean definition with scope-->
<bean id="..." class="..." scope="singleton"></bean>

<!-- A bean definition with property -->
<bean id="..." class="...">
	<property name="message" value="Hello World!"/>
</bean>

<!-- A bean definition with initialization method -->
<bean id="..." class="..." init-method="..."></bean>
~~~

## SCOPE

![bean](img/scope.png)

스프링은 기본적으로 모든 bean을 singleton으로 생성하여 관리한다.
 - request, session, global session의 Scope는 일반 Spring 어플리케이션이 아닌, Spring MVC Web Application에서만 사용된다.


1. Singleton
    - singletondms Spring 컨테이너에서 한번 생성된다.
    - 컨테이너가 사라질 때 baen도 제거된다.
    - 생성된 하나의 인스턴스는 single bean cache에 저장되고, 해당 bean을 호출, 참조할 때 캐시된 객체를 반환
![bean](img/singleton.png)

2. Prototype
    - 모든 요청에 새로운 객체를 생성하는 것을 의미한다.
    - gc에 의해 bean이 제거된다 
 ![bean](img/prototype.png)
 
 
 - 싱글톤으로 적합한 객체
    - 상태가 없는 공유 객체: 상태를 가지고 있지 않은 객체는 동기화 비용이 없다. 따라서 매번 이 객체를 참조하는 곳에서 새로운 객체를 생성할 이유가 없다.  
    - 읽기용으로만 상태를 가진 공유 객체: 1번과 유사하게 상태를 가지고 있으나 읽기 전용이므로 여전히 동기화 비용이 들지 않는다. 매 요청마다 새로운 객체 생성할 필요가 없다.
    - 공유가 필요한 상태를 지닌 공유 객체: 객체 간의 반드시 공유해야 할 상태를 지닌 객체가 하나 있다면, 이 경우에는 해당 상태의 쓰기를 가능한 동기화 할 경우 싱글톤도 적합하다.
    - 쓰기가 가능한 상태를 지니면서도 사용빈도가 매우 높은 객체: 애플리케이션 안에서 정말로 사용빈도가 높다면, 쓰기 접근에 대한 동기화 비용을 감안하고서라도 싱글톤을 고려할만하다.
        이 방법은  
           1. 장시간에 걸쳐 매우 많은 객체가 생성될 때  
           2. 해당 객체가 매우 작은 양의 쓰기상태를 가지고 있을 때  
           3. 객체 생성비용이 매우 클 때에 유용한 선택이 될 수 있다.  
 - 비싱글톤으로 적합한 객체
    - 쓰기가 가능한 상태를 지닌 객체: 쓰기가 가능한 상태가 많아서 동기화 비용이 객체 생성 비용보다 크다면 싱글톤으로 적합하지 않다.
    - 상태가 노출되지 않은 객체: 일부 제한적인 경우, 내부 상태를 외부에 노출하지 않는 빈을 참조하여 다른 의존객체와는 독립적으로 작업을 수행하는 의존 객체가 있다면 
      싱글톤보다 비싱글톤 객체를 사용하는 것이 더 나을 수 있다.

##Singleton은 Thread-safe?

Singleton으로 생성된 bean에서 전역변수로 무언가 사용하고 있고 해당 bean을 멀티 쓰레드를 돌리게 되면  
하나의 공유자원을 놓고 여러 개의 쓰레드가 읽기/쓰기를 하면서 데이터 조작 중 문제가 발생한다. (Race Condition)  
이 경우는 Thread-safe 하지 못합니다.
                                           
본인이 짠 코드를 한번 생각해보면 스프링 빈(@Controller, @Service, @Repository, @Component 어노테이션이 달린 객체 등)의 전역변수에는   
주로 스프링 빈과 같은 불변 객체들이 있지 VO, DTO, Map 같은 가변 객체가 존재하지 않을 겁니다.  
만약 있다면 synchronized 키워드나 concurrent 패키지의 클래스들을 사용하여 동시성 문제를 해결했을 것입니다.
리고 스프링 빈 사이의 데이터를 주고받을 때에는 스프링빈의 상태를 변경 시키는 것이 아니라 메소드의 파라미터를 이용했을 것이고요.  
자신도 모르게 관행에 따라 개발을 하다 보니 Thread-safe 하게 개발 한 것 같습니다.

결론은 스프링 빈을 상태를 변경할 수 있게 만든다면 Thread-safe 하지 않습니다.               

- 참조  
https://renuevo.github.io/spring/scope/spring-scope/