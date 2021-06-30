#Thread
- 프로세스란 실행중인 프로그램이다.
- 프로그램을 실행하면 OS로부터 실행에 필요한 자원(메모리)를 할당받아 프로세스가 된다.
- 프로세스의 자원을 이용해서 실제로 작업을 수행하는 것이 쓰레드다.
- 모든 프로세스에는 최소한 하나 이상의 쓰레드가 존재한다.
- 쓰레드가 작업을 수행하려면 개별적인 메모리 공간(호출스택)이 필요하다.
- CPU의 코어(core)가 한 번에 단 하나의 작업만 수행할 수 있으므로, 동시에 처리되는 작업의 수는 코어의 개수와 일치한다.

## 구현방법
- 쓰레드를 구현하는 방법은 Thread 클래스를 상속받는 방법과 Runnable 인터페이스를 구현하는 방법이 있다.
- Thread 클래스를 상속받으면 다른 클래스를 상속받을 수 없기 때문에,   
   Runnable 인터페이스를 구현하는 방법이 일반적이다.
   
## start() vs run()
- run()을 호출하는 것은 생성된 쓰레드를 실행시키는 것이 아니라 단순히 클래스에 속한 메서드 하나를 호출하는 것이다.  
 반면에 start()는 새로운 쓰레드가 작업을 실행하는데 필요한 호출스택을 생성한 다음에 run()을 호출해서,   
 생성된 호출스택에 run()이 첫번째로 저장되게 한다.
   
## 그럼에도 두개가 존재하는 이유?
- Thread는 한개만 상속가능하고 Runnable은 여러개 상속가능
- Thread는 run함수가 끝나면 GC가 되어 쓰레드가 삭제되어 쓰레드 재사용불가
- Runnable은 run함수가 끝나도 GC의 대상이 안되어 쓰레드 재사용가

~~~
public class ThreadTest {

    public static void main(String[] args) throws Exception {
           
            Thread thread1 = new MyThread();
            thread1.start();
            thread1.join();  //thread가 종료될때까지 main이 기다린다.
           
            //아래 부분의 주석을 풀면 오류남...
            //Thread를 상속받아 구현한 쓰레드는 재사용 불가
            //thread1.start();
            //thread1.join();         
           
           
        Runnable r = new MyRunnable();

        Thread rThread = new Thread(r);

        rThread.start();
        rThread.join();
       
        //재사용
        rThread = new Thread(r);
       
               
                //재사용
                Thread rThread2 = new Thread(r);
                rThread2.start();
                rThread2.join();
    }
}
   
/**
 * Thread를 상속받은 Thread
 * 재사용 불가, run 메소드가 종료되면 Garbage Collection 되므로 사용자가 변경 불가능
 *
 */
class MyThread extends Thread {
    public void run() {
        System.out.println("MyThread......");
    }
}

/**
 * Runnable을 구현한 Thread
 * 이 경우엔 run 메소드가 종료되면 Thread 클래스는 Garbage Collection 되지만
 * MyRunnable 클래스는 Garbage Collection 되지 않음
 */
class MyRunnable implements Runnable {
    public void run() {
        System.out.println("MyRunnable......");
    }
~~~

- 참조
    - https://codingdog.tistory.com/entry/java-thread-start-vs-run-%EC%96%B4%EB%96%A4-%EC%B0%A8%EC%9D%B4%EA%B0%80-%EC%9E%88%EC%9D%84%EA%B9%8C%EC%9A%94
    - https://wakestand.tistory.com/94
    - http://ojc.asia/bbs/board.php?bo_table=LecJava&wr_id=241
    - https://math-coding.tistory.com/171