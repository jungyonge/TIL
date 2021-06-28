#@Async

이 글에서 스프링의 비동기 실행 지원asynchronous execution support과 @Async annotation에 대해 살펴볼 것이다. 간단히 설명하면,   
@Async 어노테이션을 빈bean에 넣으면 별도의 쓰레드에서 실행되는 것이다. 이를테면 호출자는 호출된 메소드가 완료될 때까지 기다릴 필요가 없다.

- 주의사항 
    - 반드시 public 으로 메서드를 선언
    - 같은 클래스의 메서드에 @Async 설정하여 호출할 경우 동작하지 않는다.
    - 리턴 타입은 void나 Future<V> 인터페이스만 가능
    
- 설정방법 
    - @EnableAsync : spring의 메소드의 비동기 기능을 활성화 해준다.
       - ThreadPoolTaskExecutor로 비동기로 호출하는 Thread 대한 설정을 한다.
       -  corePoolSize: 기본적으로 실행을 대기하고 있는 Thread의 갯수
       -  MaxPoolSise: 동시 동작하는, 최대 Thread 갯수
       -  QueueCapacity : MaxPoolSize를 초과하는 요청이 Thread 생성 요청시 해당 내용을 Queue에 저장하게 되고, 사용할수 있는 Thread 여유 자리가 발생하면 하나씩 꺼내져서 동작하게 된다.
       - ThreadNamePrefix: spring이 생성하는 쓰레드의 접두사를 지정한다.
    - 메소드에 @Async를 붙인다.

~~~
public class AsyncConfig extends AsyncConfigurerSupport {

    
    public Executor getAsyncExecutor() {
        ThreadPoolTaskExecutor executor = new ThreadPoolTaskExecutor();
        executor.setCorePoolSize(2);
        executor.setMaxPoolSize(10);
        executor.setQueueCapacity(500);
        executor.setThreadNamePrefix("hanumoka-async-");
        executor.initialize();
        return executor;
    }
}
~~~
~~~


public class AsyncService {

    private static final Logger logger = LoggerFactory.getLogger(AsyncService.class);

    //비동기로 동작하는 메소드
    
    public void onAsync() {
        try {
            Thread.sleep(5000);
            logger.info("onAsync");
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    //동기로 동작하는 메소드
    public void onSync() {
        try {
            Thread.sleep(5000);
            logger.info("onSync");
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
~~~
- 참조
    - https://springboot.tistory.com/38 [스프링부트는 사랑입니다]
    - https://gofnrk.tistory.com/34
    - https://www.hanumoka.net/2020/07/02/springBoot-20200702-sringboot-async-service/
    - https://huisam.tistory.com/entry/completableFuture