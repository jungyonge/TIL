# Kafka

## Kafka
아파치 재단의 카프카는 pub-sub모델의 메세지 큐이고, 분산환경에 특화되어 설계되어 있다는 특징을 가짐으로써,   
기란존의 RabbitMQ와 같은 다른 메세지큐와의 성능 차이가 난다(훨씬 빠르게 처리한다).   
그 외에도 클러스터 구성, fail-over, replication와 같은 여러 가지 특징들을 가지고 있다.

##Pub-Sub 모델
카프카는 pub-sub(발행/구독) 모델을 사용하기 때문에, 발행/구독모델이 뭔지 알아보자.  
pub-sub은 메세지를 특정 수신자에게 직접적으로 보내주는 시스템이 아니다. publisher는 메세지를 topic을 통해서 카테고리화 한다.   
분류된 메세지를 받기를 원하는 receiver는 그 해당 topic을 구독(subscribe)함으로써 메세지를 읽어 올 수 있다.   
즉, publisher는 topic에 대한 정보만 알고 있고, 마찬가지로 subscriber도 topic만 바라본다.   
publisher 와 subscriber는 서로 모르는 상태다. 가장 간단한 예제를 들어보자, 신문사에서 신문의 종류(topic)에 메세지를 쓴다.   
우리는 그 해당 신문을 구독한다.

##카프카의 구성요소 및 특징
###1.topic, partiton  

메세지는 topic으로 분류되고, topic은 여러개의 파티션으로 나눠 질 수 있다.   
파티션내의 한 칸은 로그라고 불린다. 데이터는 한 칸의 로그에 순차적으로 append된다.   
메세지의 상대적인 위치를 나타내는게 offset이다. 배열에서의 index를 생각하면 좀 쉬울듯.  
파티션은 늘릴 수는 있어도 줄일 수는 없다.
또한, 파티션을 늘렸을 때 메세지가 Round-robin방식으로 쓰여진다.   
즉, 순차적으로 메세지가 쓰여지지 않는다는 말이다. 이 말은, 나중에 해당 토픽을 소비하는 소비자가 만약에 메세지의 순서가 엄청   
중요한 모델(증권시스템)이라면 순차적으로 소비됨을 보장해 주지 않기 때문에 상당히 위험한 것이다.

###2.Producer, Consumer
Producer는 메세지를 생산하는 주체이다. 메세지를 만들고 Topic에 메세지를 쓴다.   
Producer는 Consumer의 존재를 알지 못한다. 그냥 카프카에 메세지를 쓴다.   
Consumer는 소비자로써 메세지를 소비하는 주체이다. 역시 Producer의 존재를 모른다. 해당 topic을 구독함으로써, 자기가 스스로 조절해가면서 소비할 수 있는 것이다.   
소비를 했다는 표시는 해당 topic내의 각 파티션에 존재하는 offset의 위치를 통해서 이전에 소비했던 offset위치를 기억하고 관리하고 이를 통해서,   
혹시나 Consumer가 죽었다가 다시 살아나도, 전에 마지막으로 읽었던 위치에서 부터 다시 읽어들일 수 있다. 그렇기 때문에 fail-over에 대한 신뢰가 존재한다.

###3.broker, zookeepr
broker는 카프카의 서버를 칭한다. broker.id=1..n으로 함으로써 동일한 노드내에서 여러개의 broker서버를 띄울 수도 있다.   
zookeeper는 이러한 분산 메세지 큐의 정보를 관리해 주는 역할을 한다.   
kafka를 띄우기 위해서는 zookeeper가 반드시 실행되어야 한다.
왜냐하면 zookeeper에서 오프셋 관리한다.

###4.consumer group
카프카에서는 Consumer 그룹이라는 개념이 나온다. 말 그대로 consumer들의 묶음이고, 기본적인 룰이 하나가 존재한다.   
반드시 해당 topic의 파티션은 그 consumer group과 1:n 매칭을 해야한다. 그렇기 때문에 아래의 경우가 존재한다.  
 case1) partiton 3 :consumer 2 = consumer 중에 하나는 2개의 파티션을 소비  
 case2) partiton 3: consumer 3 = consumer 1개랑 파티션1나랑 1:1매칭  
 case3) partiton 3: consumer 4 = consumer 1개가 아무것도 하지 않음  
그렇기 때문에 파티션을 늘릴때는, Consumer의 개수도 고려해야한다. 보통은 개수를 같이 맞춰주는 것을 권장하지만,  
실제 메세지가 쌓이는 속도보다 처리하는 속도가 훨씬 빠르다면 굳이 1:1매핑보다는 파티션개수 => 컨슈머 개수 로 설정하는 것도 나쁘지 않다.  
그럼 도대체 Consumer Group이 존재하는 진짜? 이유는 뭘까?  
컨슈머 그룹은 하나의 topic에 대한 책임을 갖고 있다. 이 말인 즉슨, 같은 그룹내의 어떤 컨슈머가 down된다면,    
걔가 원래 파티션1에 대해서 소비를 맡았던 놈인데, 파티션1에 대한 소비를 할 수 없는 상황이다.   
이런 상황이 오면(Rebalance)된 상황이라고 한다. 리밸런스가 된 상황이면, 파티션 재조정을 통해서 다른 컨슈머가 파티션1의 소비를 이어서 하게된다.  
물론 위에서 설명한 offset 정보를 그룹내에서 서로간의 공유하고 있기 때문에, 뻗기 직전의 offset위치를 알고 그 다음부터 소비하면 문제가 없어지는 것이다.

###5.replication
local에 broker3대를 띄우고(replica-factor=3)로 복제되는 경우를 살펴보자.  
복제는 수평적으로 스케일 아웃이다. broker 3대에서 하나의 서버만 leader가 되고 나머지 둘은 follower 가 된다.   
producer가 메세지를 쓰고, consumer가 메세지를 읽는 건 오로지 leader가 전적으로 역할을 담당한다.  
나머지 follower들의 역할은?
나머지 follower들은 leader와 싱크를 항상 맞춘다. 해당 option이 있다. 혹시나 leader가 죽었을 경우,   
나머지 follower중에 하나가 leader로 선출되어서 메세지의 쓰고/읽는 것을 처리한다.