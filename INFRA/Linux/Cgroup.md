#Cgroup란
  
cgroup은 단일 또는 태스크 단위의 프로세스 그룹에 대한 자원 할당을 제어하는 커널 모듈입니다.  
Cgroup은 Control group으로 처음 개발되었을 때는 group이 아니라 container란 용어를 사용했었습니다.  
하지만 container란 용어는 너무 많은 의미를 내포하고 있다고 판단하여 지금의 cgroup이만 이름으로 변경되었습니다.  
현재 cgroup은 v1와 v2 두가지 버전이 공존하고 있습니다. v1의 서비스시템 중 일부는 v2에 포함되어 있는 상태입니다. 

##Container는 가상머신이다?  
 Container는 hypervisor와 완전히 다릅니다.
 궁극적으로는 hypervisor와 유사한 형태의 "가상화"를 목표로 하고 있지만 hypervisor는 OS 및 커널이 통째로 가상화되는 반면에   
 container는 간단히 보면 filesystem의 가상화만을 이루고 있습니다. container는 호스트 PC의 커널을 공유하고 따라서 init(1) 등의 프로세스가 떠있을 필요가 없으며,  
 따라서 가상화 프로그램과는 다르게 적은 메모리 사용량, 적은 overhead를 보입니다.