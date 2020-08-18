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
 
 
## cgroup 서브시스템
 cgroup은 여러 개의 서브시스템으로 이루어져 있습니다. (아래 표에 모든 서브시스템을 작성한 것은 아니니, 유의해주세요.)
 
 | subsystem	| description | 
 | --- | ---|
|  cpu	    | cgroups는 시스템이 busy 상태일 때 CPU 공유를 최소화 즉 사용량을 제한 할 수 있습니다. 이 서브시스템은 CPU에 cgroup 작업 액세스를 제공하기 위한 스케줄러(Documentation/scheduler/sched-design-CFS.txt)를 제공합니다.
|  cpuacct	| 프로세스 그룹 별 CPU 자원 사용에 대한 분석 통계를 생성 및 제공합니다. (Documentation/cgroup-v1/cpuacct.txt)
|  cpuset	| 개별 CPU 및 메모리 노드를 cgroup에 바인딩 하기 위해 사용하는 서브시스템입니다(Documentation/cgroup-v1/cpusets.txt.)
|  memory	| cgroup 작업에 사용되는 메모리(프로세스, 커널, swap)를 제한하고 리포팅을 제공하는 서브시스템입니다. (Documentation/cgroup-v1/memory.txt)
|  blkio	| 특정 block device에 대한 접근을 제한하거나 제어하기 위한 서브시스템입니다. block device에 대한 IO 접근 제한을 설정할 수 있습니다. (Documentation/cgroup-v1/blkio-controller.txt)
|  devices	| cgroup의 작업 단위로 device에 대한 접근을 허용하거나 제한합니다. whitelist와 blacklist로 명시되어 있습니다. (Documentation/cgroup-v1/devices.txt.)
|  freezer	| cgroup의 작업을 일시적으로 정지(suspend)하거나 다시 시작(restore)할 수 있습니다. (Documentation/cgroup-v1/freezer-subsystem.txt.)
|  net_cls	| 특정 cgroup 작업에서 발생하는 패킷을 식별하기 위한 태그(classid)를 지정할 수 있습니다. 이 태그는 방화벽 규칙으로 사용되어 질 수 있습니다. (Documentation/cgroup-v1/net_cls.txt.)
|  net_prio	| cgroup 작업에서 생성되는 네트워크 트래픽의 우선순위를 선정할 수 있습니다. (Documentation/cgroup-v1/net_prio.txt.)
|  hugetlb	| HugeTLB에 대한 제한을 설정할 수 있습니다.
|  pid	    | cgroup 작업에서 생성되는 프로세스의 수를 제한할 수 있습니다. (Documentation/cgroup-v1/pids.txt.)
 
 
