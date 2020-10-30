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

  - Producer, Consumer
  - broker, zookeepr
  - consumer group
  - replication