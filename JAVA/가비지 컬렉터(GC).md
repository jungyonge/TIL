#가비지 컬렉터(GC)
자바에서는 메모리를 GC라는 알고리즘을 통하여 관리(automatic memory management)하기 때문에,   
개발자가 힙메모리를 처리하기 위한 로직을 만들 필요가 없고, 절대로 만들어서는 안됩니다.

Garbage Collection. 자바에서 쓰레기는 객체입니다. 하나의 객체는 힙메모리를 점유하고,   
필요하지 않으면 힙메모리에서 해제되어야 합니다. 메모리 점유는 다음과 같이 쉽게 할 수 있습니다.

이러한 코드에서 a라는 객체가 만들어져 힙메모리의 한부분을 점유하게 되고, 특정 메소드 호출한 후 수행이 완료되어 해당 객체가 더이상 필요없는 객체, 쓰레기가 됩니다.   
이 쓰레기 객체를 효과적으로 처리하는 작업을 GC라고 합니다.

## GC의 원리
GC가 하는 역할은 다음과 같다.
1. 메모리할당
2. 사용중인 메모리 인식
3. 사용하지 않는 메모리 인식

JVM메모리는 크게 클래스영역, 자바스택, 힙, 네이티브 메소드 스택 4개영역으로 나뉘는데 GC는 힙영역에 대하여 메모리 할당을 정리하는 것이다.

![jvm](./img/jvm.png)

힙은 Young, Old, Perm 세 영역으로 나뉜다.
이 중 Perm(Permanent) 영역은 거의 사용되지 않는 영역으로서 클래스와 메소드 정보와 같이 자바 언어 레벨에서 사용되지 않습니다.   
Yong, Old 영역 그리고 Young 영역은 Eden영역과 두 개의 Survivor 영역으로 나뉩니다.   
우리가 고려해야 할 자바의 메모리 영역은 총 4개의 영역으로 나뉜다고 볼 수 있습니다.  ( Young (1. Eden, 2. Survivor 1, 3. Survivor 2), Old (4. 메모리) )

#### GC 순서

![jvm](./img/minor.png)

일단 메모리에 객체가 생성되면, Eden 영역에 객체가 지정됩니다.  Eden 영역에 데이터가 어느 정도 쌓이면,   
이 영역에 있던 객체가 어디론가 옮겨지거나 삭제됩니다. 이 때 옮겨가는 위치가 survivor 영역입니다.   
두개의 Survivor 영역 사이에 우선 순위가 있는 것은 아닙니다. 하지만, 이 두 개의 영역 중 한 영역은 반드시 비어 있어야 합니다.   
그 비어있는 영역에 Eden 영역에 있던 객체가 할당됩니다.

Eden에서 survivor 둘 중 하나의 영역으로 할당 되고, 할당된 Survivor 영역이 차면,   
GC가 되면서 Eden 영역에 있는 객체와 꽉 찬 Survivor 영역에 있는 객체가 비어 있는 Survivor 영역으로 이동합니다.   
그러다가 더 큰 객체가 생성되거나, 더 이상 Young 영역에 공간이 남지 않으면 객체들은 Old 영역으로 이동하게 됩니다.

#### GC 알고리즘 
- Reference Counting Algorithm
    - Garbage의 Detection에 초점이 맞추어진 초기 Algorithm이다. 각 Object마다 Reference Count를 관리하여 Reference Count가 0이 되면 GC를 수행한다.
    - 장점
        - Reference Count가 0이 될 때마다 GC가 발생하기 때문에 Pause Time이 분산되어 실시간 작업에도 거의 영향을 주지 않고 즉시 메모리에서 해제된다
    - 단점
        - 각 Object마다 Count를 계속 변경 해야한다.
        - 참조가 많이 되어있는 Object는 연쇄적으로 GC가 발생
        - Linked List와 같은 순환구조에서 Memory leak 발생
        
- Mark-and-Sweep Alogrithm
    - 
- Mark-and-Compact Algorithm
- Copying Algorithm
- Generational Algorithm


#### GC 종류

GC는 크게 두 가지 타입으로 나뉩니다. 마이너 GC와 메이저 GC의 두가지 GC가 발생할 수 있습니다.
- 마이너 GC: Young 영역에서 발생하는 GC
- 메이저 GC: Old 영역이나 Perm 영역에서 발생하는 GC

이 두가지 GC가 어떻게 상호 작용하느냐에 따라서 GC 방식에 차이가 나며, 성능에도 영향을 줍니다.   
GC가 발생하거나 객체가 각 영역에서 다른 영역으로 이동할 때 애플리케이션의 병목이 발생하면서 성능에 영향을 주게 됩니다.   
그래서 핫 스팟(Hot Spot) JVM에서는 스레드 로컬 할당 버퍼(TLABs: Thread-Local Allocation Buffers)라는 것을 사용합니다.   
이를 통해 각 스레드별 메모리 버퍼를 사용하면 다른 스레드에 영향을 주지 않는 메모리 할당 작업이 가능합니다.


