#DeadLock
둘 이상의 쓰레드가 lock 을 획득하기 위해 기다리는데, 이 lock 을 잡고 있는 쓰레드도 똑같이 다른 lock 을 기다리며 서로 블록 상태에 놓이는 것을 말한다.   
데드락은 다수의 쓰레드가 같은 lock 을, 동시에, 다른 명령에 의해, 획득하려 할 때 발생할 수 있다.
 
 #### 발생조건
 아래의 4가지 중 1가지라도 성립한다면 데드락에 빠진다.
 1. 상호배제
    - 자원은 한 프로세스만 사용
 2. 점유대기
    - 최소한 하나의 자원을 점유하고 있으면서 다른 프로세스에 할당되어 사용하고 있는 자원을 추가로 점유하기 위해 대기하는 프로세스가 있어야 한다.
 3. 비선점
    - 다른 프로세스에 할당된 자원은 사용이 끝날 때까지 강제로 빼앗을 수 없어야 한다.
 4. 순환대기
    - 프로세스의 집합 {P0, P1, ,…Pn}에서 P0는 P1이 점유한 자원을 대기하고 P1은 P2가 점유한 자원을 대기하고 P2…Pn-1은 Pn이 점유한 자원을 대기하며 Pn은 P0가 점유한 자원을 요구해야 한다.

#### 예방
1. 상호배제 부정
    - 여러개의 프로세스가 공유자원을 사용 할 수 있도록 한다.
2. 점유대기
    - 프로세스가 실행되기전에 필요한 자원을 할당한다.
3. 비선점 부정
    - 자원을 점유하고 있는 프로세스가 다른 자원을 요구 할때 점유하고 있는 자원을 반납하고, 요구한 자원을 사용하기 위해 기다리게한다
4. 순환대기 부정
    - 자원에 고유한 번호를 할당하고, 번호 순서대로 자원을  요구하도록한다.

#### 방지
1. Lock이 발생하는 순서를 정해놓는다.
2. 오픈 호출
    - 락을 확보하지 않은 상태에서 메소드를 호출
3. 락의 시간 제한
    - Lock 클래스의 명시적인 락은 일정 시간을 정해두고 그시간동안 락을 확보못한다면 tryLock 메소드가 오류를 발생 시키도록 할수 있음
