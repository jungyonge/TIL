# Generic

## Generic 이란
제네릭 타입을 이용함으로써 잘못된 타입이 사용될 수 있는 문제를 컴파일 과정에서 제거할 수 있다.  
제네릭은 클래스와 인터페이스, 메소드를 정의할 때 타입(type)을 파라미터(parameter)로 사용할 수 있도록 한다.

## 장점
1. 컴파일 시 강한 타입체크를 할 수 있다.
    -   실행시 타입 에러 나는 것 보다 컴파일 시에 미리 타입을 강하게 체크해서 에러를 사전에 방지
2. 타입변환 (casting)을 제거한다.
    -   비제네릭 코드는 불필요하게 타입 변환을 하기 때문에 프로그램 성능에 악영향을 미친다.
~~~
List list = new ArrayList();
list.add("hello");
String str = (String) list.get(0); // 타입 변환이 필요

List<String> list2 = new ArrayList<>();
list2.add("hello");
String str2 = list.get(0); // 불필요
~~~

##제네릭 타입
- 타입을 파리미터로 가지는 클래스와 인터페이스를 말한다.
    -  선언시 클래스 또는 인터페이스 이름뒤에 <>qnghrk qnxsmsek.
- <> 사이에는 타입 파라미터가 위치한다.
~~~~
 public class 클래스명<T> { ... }   
 
 public interface 인터페이스명<T> { ... }

public class Box<T> {
  private T t;
​
  public T get() { return t; }
​
  public void set(T t) { this.t = t }
}

// 선언
Box<String> box = new Box<String>();
~~~~

- T에 String, Integer을 넣으면 알아서 클래스가 생성되기에 , 불필요한 타입변환이 필요없다.

## 멀티타입 파라미터

두 개 이상의 타입 파라미터를 사용해서 선언할 수 있다.

~~~
class<K,V,...> { ... }
interface<K,V,...> { ... }

//선언
Product<Tv,String> product = new Product<>();
~~~

## 제네릭 메소드

매개변수 타입과 리턴 타입으로 타입 파라미터를 갖는 메소드를 말한다.    
- 제네릭 메소드 선언 방법  
리턴 타입 앞에 "< >"기호를 추가하고 타입 파라미터를 기술한다.  
타입 파라미터를 리턴타입(Box<T>)과 매개변수(T)에 사용한다.  

~~~
 public <타입파라미터,...> 리턴타입 메소드명(매개변수,...) { ... }

 public <T> Box<T> boxing(T t) { ... }

 Box<Integer> box = <Integer>boxing(100); //타입 파라미터를 명시적으로 Integer로 지정 
 Box<Integer> box = boxing(100);  //타입 파라미터를 Integer로 추정
~~~

일반적으로 매개값을 넣어줌으로써 컴파일러가 유추하게 만들어주는 두번째 방법을 사용한다.


## 제한된 타입 파라미터

- 상속 및 구현 관계를 이용해서 타입을 제한 한다
~~~
   public <T extends 상위타입> 리턴타입 메소드(매개변수, ...) { ... } 
~~~
인터페이스도 상속가능하나 implements말고 extends를 사용한다.
