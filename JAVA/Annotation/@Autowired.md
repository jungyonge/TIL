#@Autowired

@Autowired어노테이션은 이름을 보면 알 수 있듯이 이 어노테이션을 부여하면 각 상황의 타입에 맞는 IoC컨테이너 안에 존재하는 Bean을 자동으로 주입해주게 됩니다.   
예제를 통해 알아보는것이 역시 좋을 것 같습니다.

## 편리함
- @Autowired 사용전
~~~
@Service
public class BookService {

    private BookRepository bookRepository;

    public BookService(BookRepository bookRepository){
        this.bookRepository = bookRepository;
    }

}
~~~
우선 BookService Class를 살펴보겠습니다. BookService Class는 생성자로 BookRepository를 전달받고 인스턴스   
변수에 할당하는 코드를 가지고 있습니다.

 
~~~
<bean id="bookRepository" class="com.keesun.spring.BookRepository"/>

<bean id="bookService" class="com.keesun.spring.BookService">
    <constructor-arg name="bookRepository" ref="bookRepository"/>
</bean>
~~~
이때 원래의 경우라면 BookService에 BookRepository를 주입하기 위해서 XML파일에 다음과 같이 Bean설정을 해주어야 했습니다.  
~~~
@Configuration
public class ApplicationConfig {    
    @Bean
    public BookRepository bookRepository(){
        return new BookRepository();
    }
    
    @Bean
    public BookService bookService(){
        return new BookService(bookRepository());
    }    
}
~~~
또는 위처럼 XML 설정 파일을 대신하는 Java Class에 Bean설정을 만들어주어 해결할 수도 있습니다. 

- @Autowired 사용
~~~
@Service
public class BookService {
    private BookRepository bookRepository;

    @Autowired
    public BookService(BookRepository bookRepository){
        this.bookRepository = bookRepository;
    }    
}
~~~

하지만 @Autowired어노테이션을 사용하는 경우 위와 같이 객체의 의존성을 가지는 부분에 간단히 @Autowired 어노테이션을 사용하면  
쉽게 의존성 주입을 받을 수 있게 됩니다.

~~~
@Repository
public class BookRepository { ... }
~~~
의존성 주입 타켓이 되는 Class 역시 당연히 Bean으로 등록이 되기위한 @Repository어노테이션이 부여되어 있는것을 주목해야 합니다.


- 참조
    - https://galid1.tistory.com/512