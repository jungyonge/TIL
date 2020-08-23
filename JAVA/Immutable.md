#Immutable
Immutable을 사전적으로 찾아보면, 불변의, 변경할 수 없는 이라는 뜻임을 알 수 있습니다.  
즉 Immutable Class는 변경이 불가능한 클래스이며, 가변적이지 않는 클래스입니다.   
만들어진 Immutable Class는 레퍼런스 타입의 객체이기 때문에 heap영역에 생성됩니다. 

대표적으로 String, Boolean, Integer, Float, Long이 Immutable Class다.  
Immutable Class들은 heap 영역에서 변경이 불가능 한거지 재할당은 가능하다.  
예를 들어 
~~~ 
String a = "aa";
a = "bb";
~~~
로 했을때 a가 참조하고 있는 heap영역의 객체가 바뀌는 것이지 heap영역에 있는 값이 바뀌는 것이 아닙니다.   
a가 처음에 참조하고 있는 "aa"값이 "bb"로 변경되는 것이 아니라 아예 "bb"라는 새로운 객체를 만들고 그 객체를 a가 참조하게 하는 것입니다.   
이렇게 했을 경우 "aa"값을 지니고있는 객체는 이제 그 누구도 참조하고 있지 않는 객체가 되며 gc대상이 됩니다. 
그래서 String을 많이 변화 시킨다고 가정했을 때 새로운 객체를 계속 생성하여 성능 저하 발생할 수 있다.

####Immutable 의 특징

- set 메소드가 없음 멤버변수 변경 불가능
- return type이 void인 메소드
- immutabel 사용시 멀티스레드 환경에서 신뢰할 수 있는 코드를 만들어내기 쉬움
- 보통 final 클래스로 정의 한다.
- 장점 
    - 생성자, 접근메소드에 대한 방어 복사가 필요없습니다. 멀티스레드 환경에서 동기화 처리없이 객체를 공유할 수 있습니다.(Thread-safe) 불변이기 때문에 객체가 안전합니다.
- 단점 
    - 객체가 가지는 값마다 새로운 객체가 필요합니다. 따라서 메모리 누수와 새로운 객체를 계속 생성해야하기 때문에 성능저하를 발생시킬 수 있습니다.


####Immutable 예
Immutable Class를 만들기 위해서 2가지를 알면 됩니다.

1. 멤버변수를 final로 선언.
2. 접근 메서드를 구현하지 않는다. (Setter메서드)

~~~
public class ImmutableString {

    private final String name;

    ImmutableString(String name){
        this.name = name;
    }

    @Override
    public String toString(){
        return this.name;
    }

    public static void main(String[] args) {
        String name = "Amazing";
        ImmutableString immutableString = new ImmutableString(name);
        name.concat("Day");
        System.out.println(name);
        name = name.concat("Day");
        System.out.println(name);
        System.out.println(immutableString);
    }


}

로그
Amazing
AmazingDay
Amazing
~~~

처음 concat이 안되는 이유는 concat 함수를 보면 new String으로 넘겨주는데 그 받을 객체가 없기에 기존 name 그대로 Amaging만 출력한다.   
아마도 힙 어딘가에는 AmagingDay라는 객체가 생성되어 할당 되지만 그곳을 바라보는 곳이 없는 것이다.   
허나 두번째는 name 객채에서 AmagingDay객체가 생성된 곳을 바라보기에 AmagingDay가 출력되고,   
세번째는 맨처음 생성한 name 객체가 바라 보는 곳은 Amaging 이기에 Amaging만 출력된다. 
가끔 특정 함수를 쓸 때 어떤건 바로 적용되고 어떤건 안되는 차이가 immutable 차이였던것 같다
