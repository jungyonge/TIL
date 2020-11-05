#Stream

자바 8에서 추가한 스트림(Streams)은 람다를 활용할 수 있는 기술 중 하나입니다.   
자바 8 이전에는 배열 또는 컬렉션 인스턴스를 다루는 방법은 for 또는 foreach 문을 돌면서 요소 하나씩을 꺼내서 다루는 방법이었습니다.   
간단한 경우라면 상관없지만 로직이 복잡해질수록 코드의 양이 많아져 여러 로직이 섞이게 되고,   
메소드를 나눌 경우 루프를 여러 번 도는 경우가 발생합니다.  

스트림은 '데이터의 흐름’입니다. 배열 또는 컬렉션 인스턴스에 함수 여러 개를 조합해서 원하는 결과를 필터링하고 가공된 결과를 얻을 수 있습니다.   
또한 람다를 이용해서 코드의 양을 줄이고 간결하게 표현할 수 있습니다.   
즉, 배열과 컬렉션을 함수형으로 처리할 수 있습니다.

스트림에 대한 내용은 크게 세 가지로 나눌 수 있습니다.

1. 생성하기 : 스트림 인스턴스 생성.
2. 가공하기 : 필터링(filtering) 및 맵핑(mapping) 등 원하는 결과를 만들어가는 중간 작업(intermediate operations).
3. 결과 만들기 : 최종적으로 결과를 만들어내는 작업(terminal operations).

![jvm](./img/stream.png)

물고기들은 바닷속에서 헤엄치며 앞으로 나아가다가 어부가 놓은 그물에 잡히고, 일정한 규격의 상자에 담긴 후 한꺼번에 모아 최종 소비자에게 전달된다.  
이를 stream과 대응시켜보자.  
우선, 바다 생물들의 이동은 stream이다.  
상품가치가 있는 물고기를 잡기위해 그물로 필터링 하는것은 filter라는 중간 연산자이고, 필터링 조건은 람다 함수 또는 메소드 참조를 통해 결정된다.  
물고기를 상자에 담는 과정 또한 중간 연산자 중 하나로, map이라고 한다. 이 과정에서 물고기를 차량(컬렉션)에 적재하기 적당한 형태로 가공된다.  
마지막으로, 물고기가 실린 수많은 상자를 차에 실어서 소비자에게 제공하는데, 이러한 행위가 collect라는 최종 연산자 이다.   
이렇게 보니 간단하다. 수많은 데이터의 흐름 속에서 각각의 값을 원하는 형태로 가공하여 최종 소비자에게 제공하는 것이 stream의 역할이다.  

## 생성방법
- Arrays.stream()
~~~
String[] arr = new String[] {"Hello", "World", "Hell"};
Stream<String> stream = Arrays.stream(arr); // 배열
Stream<String> streamOfArrayPart = Arrays.stream(arr, 1, 3); // 부분 배열
~~~
- Collections.stream()
컬렉션 타입 (Collection, List, Set)은 메소드를 이용하여 스트림을 생성할 수 있다.
~~~
List<String> list = Arrays.asList("a", "b", "c");
Stream<String> stream = list.stream();
Stream<String> parallelStream = list.parallelStream(); 
~~~
- 직접 생성하는 연산자
  - empty()
  null 대신 이용할 수 있다.
  ~~~
  Stream stream = Stream.empty();
  build()
  Stream<String> generatedStream = Stream.<String>builder()
          .add("Hello")
          .add("World")
          .build();
  ~~~
  - generate()
  크기를 지정하지 않으면 무한하기 때문에 특정 사이즈만큼 생성하려면 반드시 limit을통해 최대 크기를 제한해야 한다.
  ~~~
  Stream<String> generatedStream = Stream.generate(() -> "gen").limit(5);
  ~~~
  - iterate()
  초기 값을 시작으로 계속해서 2씩 증가된 값을 생성한다. generate()와 마찬가지로 크기를 지정하지 않으면 무한하기 때문에 limit을 통해 크기를 제한해야 한다.
  ~~~
  Stream<Integer> iteratedStream = Stream.iterate(30, n -> n + 2).limit(5);
  ~~~
  - 기본 타입형 스트림
  IntStream, LongStream, DoubleStream  
  제네릭을 사용하지 않고 기본 값을 생성하는 방법이다.   제네릭을 사용하지 않기 때문에 불필요한 오토 박싱(auto-boxing)이 발생하지 않는다.
  
  range는 [startPosition, endPosition) 범위를 가진다.  
  rangeClosed는 [startPosition, endPosition] 범위를 가진다.
  ~~~  
  IntStream intStream = IntStream.range(1, 5); // [1, 2, 3, 4]
  LongStream longStream = LongStream.rangeClosed(1, 5); // [1, 2, 3, 4, 5]
  ~~~
  필요한 경우 boxed 메서드를 통해 Integer 형태로 박싱할 수 있다.
  ~~~
  Stream<Integer> boxedIntStream = IntStream.range(1, 5).boxed();
  ~~~
  난수 스트림을 생성할 수도 있다.  
  DoubleStream doubles = new Random().doubles(3); // 난수 3개 생성

## Intermediate Operations

값을 원하는 형태로 처리하기 위한 연산자이다. 각각의 중간 연산자들은 lazy하게 실행되고, 결과로 stream을 반환한다.   
그렇기 때문에 중간 연산자는 method chaining 형태로 연결하여 처리할 수 있다.   
연산의 결과가 stream으로 반환되기 때문에 stream-producing 연산자라고 부르기도 한다

- Lazy한 처리  
    - 결과가 필요하기 전까지 실행되지 않음을 의미한다. 연산의 시점을 최대한 늦춘다는 말이다.
 
- filter()

원하는 요소만 추출하기 위한 메소드이다. 인자로는 Predicate를 받는데, boolean값을 반환하는 람다식을 넣으면 된다.
~~~  
  Stream<T> filter(Predicate<? super T> predicate);
~~~
  e.g. 문자열 리스트에서 특정한 문자가 포함된 문자열 뽑아내기
~~~  
  List<String> names = Arrays.asList("Hello", "World", "Test", "array");
  List<String> filteredNames = names.stream()
          .filter(it -> it.contains("e"))
          .collect(Collectors.toList());
~~~  
e.g. 시험 점수가 80점 이상인 학생만 뽑아내기
~~~  
  Arrays.asList(19, 86, 35, 78, 12, 45, 89, 98, 100)
          .stream()
          .filter(it -> it >= 80)
          .forEach(System.out::println);
~~~

- map()  

스트림 내 요소를 가공한다. mapper를 간단히 설명하자면, T를 인자로 받아 변환한 값 R을 반환하는 함수이다. 이는 람다식으로 간단히 표현할 수 있다.
~~~
<R> Stream<R> map(Function<? super T, ? extends R> mapper);
~~~
e.g. 정사각형 한 변의 길이를 곱하여 넓이로 가공하기
~~~
Arrays.asList(3, 8, 9, 10, 20, 11, 22)
        .stream()
        .map(it -> it * it)
        .forEach(System.out::println);
~~~ 

- flatMap

중첩 구조를 한 단계 제거하고 단일 컬렉션으로 만들어 주는 역할을 한다. 이러한 작업을 flattening이라고 한다.  
map과 가장 큰 차이는 함수의 반환 값이 stream 형태라는 것이다. 이는 map만으로 처리하면 복잡해지는 코드를 간결하게 만들어준다.
~~~
  <R> Stream<R> flatMap(Function<? super T, ? extends Stream<? extends R>> mapper);
~~~
  e.g. 2차원 배열과 같이 중첩된 형태의 값을 처리할 때 map을 이용하면 2중 for문의 형태를 사용해야 한다. 반면에 flatMap을 이용하면 배열의 각 행에 있는 요소를 stream으로 만들어 처리할 수 있다.
~~~  
  String arr[][] = {
      {"minus one", "zero", "one"}, 
      {"two", "Three"}, 
      {"Four", "Five", "Six"}, 
      {"eight", "ten"}
  };
  
  Stream.of(arr)
          .flatMap(Stream::of)
          .forEach(System.out::println);
  
  int arr[][] = {{1, 2, 3}, {4, 8}, {9, 10, 20}, {11, 22}};
  Stream.of(arr)
          .flatMapToInt(IntStream::of)
          .forEach(System.out::println);
~~~

- sorted()

stream 요소를 정렬한다. 어떠한 인자도 넣지 않는다면 오름차순으로 정렬되고, Comparator를 인자로 넣으면 Comparator의 기준에 따라 정렬된다.
~~~
 Stream<T> sorted();
 Stream<T> sorted(Comparator<? super T> comparator);

 e.g. 오름차순으로 정렬하기
 
 List<String> names = Arrays.asList("Hello", "World", "stream", "API");
 names.stream()
         .sorted()
         .forEach(System.out::println);

 e.g. 내림차순으로 정렬하기
 
 List<String> names = Arrays.asList("Hello", "World", "stream", "API")
         .stream()
         .sorted(Comparator.reverseOrder())
         .forEach(System.out::println);
~~~

- Comparable VS Comparator
  - Comparable은 객체의 기본 정렬기준이 되는 메서드를 정의하는 인터페이스이다.
  - Comparator는 새로운 정렬 기준을 적용하고 싶은 경우 사용하는 인터페이스이다.
  