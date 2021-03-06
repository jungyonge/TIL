#Shorteset Job First Scheduling (SJF)

최소작업 우선 스케줄링이란 각 작업의 프로세서 실행 시간을 이용하여 프로세서가 사용 가능할 때 실행 시간이 가장 짧은 작업에 할당하는 방법이다.

 

최소 작업 우선 스케줄링은 FIFO 스케줄링에서 실행 시간에 따른 할당 방식의 차이가 FIFO와 SJF의 차이점이라고 할 수 있다.

 

- 장점
    - 항상 실행 시간이 짧은 작업을 신속하게 실행하므로 평균 대기 시간이 가장 짧다.
- 단점
    - 초기의 긴 작업을 짧은 작업을 종료할 때 까지 대기시켜 기아가 발생한다.
    - 기본적으로 짧은 작업이 항상 실행되도록 설정하므로 불공정한 작업을 실행한다.
    - 실행 시간을 예측하기 어려워 실용적이지 못하다.
 
 - 참조
    - https://wonit.tistory.com/104