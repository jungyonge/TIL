# Mempool Test

  - Test system 
    1. Master Node(wallet mode), Slave Node ,Local Node 3개 구성
    2. Slave Node에 cpu 마이너 2개 연결
    3. Master Node에 nomp 설치 , gpu miner 1개 연결
    4. Block explorer 설치


1. utxo 관련
    - 하나의 UTXO 최대 25개의 자식tx를 생성할 수 있다,
    - too-long-mempool-chain이 뜬 tx는 바로 Mempool에 적용 안되고 wallet.dat에 있다.
    - 어느정도 시간이 지난 후 다시 tx가 Mempool에 담기고 tx전파를 하지만 얼만큼의 시간인지는 모르겠다. (10분 ~ 30분 제각각 길게는 24시간까지)
    - 각 Node의 네트워크의 상황에 따라 tx전파가 안 될수 있다.
    - tx를 만든 노드의 Mempool에는 tx가 있지만 Mining이 되는 Slave에는 tx가 전파가 안되어 블록이 계속 생성되어도 tx가 블록에 안담기는 오류가 발생했다.
    - 그래서 문제 3의 원인을 추론해보면 tx만든 노드에는 있었지만 Mining node에는 전파를 실패하여 계속 balance와 listunspent가 안 들어올 가능성이 있다. 실험 중에도 같은 상황이 발생했다.(too long mempool chain 에러가 뜨면 다른 노드의 전파가 바로 안됬다.)
2.	Core 실행 옵션 관련
    - Core실행 옵션을 주면 자식tx개수를 늘릴 수 있다 (498개까지 시도해봄)
    - 옵션 실행할 때 tx만드는 노드와 Mining node 둘 다 옵션으로 실행해야 25개 이상이 한번에 tx가 만들어 지고 전파가 된 후 블록에 담긴다.
3.	fee , 주소 수정 관련
    - createrawtransaction -> signrawtransaction -> sendrawtransaction 으로 직접 fee 수정과 보내는 주소 받는 주소 고정 할 수 있다.
4.	다른  rpc 명령어 관련
    - sendtoaddress와 sendfrom은 하나의 utxo로 최대 25개의 자식tx생성하는 같은 실험결과를 얻었다.
    - sendmany를 활용하면 하나의 utxo로 여러명에게 보낼 수 있고 fee도 0.01한번 만 낸다 
