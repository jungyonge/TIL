## Mapper 비교

### ObjectMapper:

- Jackson 라이브러리에서 제공하는 ObjectMapper는 JSON과 Java 객체 간의 변환을 처리합니다.
- JSON 문자열을 Java 객체로 변환하거나, Java 객체를 JSON으로 직렬화하는 데 사용됩니다.
- ObjectMapper는 다양한 JSON 형식과 많은 설정 옵션을 지원합니다.
- 주로 JSON 데이터를 처리하는 데 사용되며, RESTful 웹 서비스의 요청 및 응답 데이터를 변환하는 데 유용합니다.
~~~
   public static void main(String[] args) {
        ObjectMapper objectMapper = new ObjectMapper();

	// Java Object ->  JSON
        Person person = new Person("zooneon", 25, "seoul");
        try {
            objectMapper.writeValue(new File("src/person.json"), person);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    public static void main(String[] args) {
        ObjectMapper objectMapper = new ObjectMapper();

        // JSON -> Java Object
        String json = "{\"name\":\"zooneon\",\"age\":25,\"address\":\"seoul\"}";
        try {
            Person deserializedPerson = objectMapper.readValue(json, Person.class);
            System.out.println(deserializedPerson);
        } catch (JsonProcessingException e) {
            e.printStackTrace();
        }
    }
~~~
    

### ModelMapper:

- ModelMapper는 Java 객체 간의 매핑을 담당합니다.
- 두 개의 Java 객체 사이에서 필드 값을 복사하거나 매핑하는 데 사용됩니다.
- 객체 간의 구조나 필드명이 다를 경우에도 유연하게 매핑할 수 있는 기능을 제공합니다.
- ModelMapper는 복잡한 매핑 규칙을 정의하거나 구성하기 위해 사용됩니다.
- 주로 데이터베이스 엔티티와 DTO(Data Transfer Object) 사이의 매핑이나 비슷한 상황에서 유용합니다.

요약하면, ObjectMapper는 JSON과 Java 객체 간의 변환에 사용되는 반면에 ModelMapper는 Java 객체 간의 필드 매핑에 사용됩니다.   
ObjectMapper는 JSON 라이브러리로서 다양한 JSON 형식을 지원하고, ModelMapper는 객체 간의 구조적인 매핑을 수행할 수 있는 기능을 제공합니다.

### ModelMapper vs MapStruct
- 간단히 사용하기는 ModelMapper가 좋은듯
- MapStruct는 세팅할 데이터가 좀 많음 
- 성능은 50만개 기준으로 3초 vs 0.0008초로 심하긴함
- 근데 한개씩 할때는 굳이?
- 성능차이가 나는 이유는 리플렉션 때문
- ModelMapper는 세팅이 없이 리플렉션으로 동적 할당
- MapStruct는 세팅을 겁나해서 리플렉션을 사용안함 

### 참조
- https://velog.io/@zooneon/Java-ObjectMapper%EB%A5%BC-%EC%9D%B4%EC%9A%A9%ED%95%98%EC%97%AC-JSON-%ED%8C%8C%EC%8B%B1%ED%95%98%EA%B8%B0
- https://dev-splin.github.io/spring/Spring-ModelMapper,MapStruct/