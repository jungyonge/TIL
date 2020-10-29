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
  - topic, partiton
  - Producer, Consumer
  - broker, zookeepr
  - consumer group
  - replication