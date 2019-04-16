## Scriptsig,Scriptpubkey란

- 이 두개는 열쇠와 자물쇠의 관계이다.

- scriptPubKey : 트랜잭션을 검증하기 올바른지 검증하라는 key이다. 자물쇠의 역할이며, 잠금스크립트라고도 불린다.
- scriptSig : 트랜잭션을 발생시킨 주체의 서명 + publicKey , 열쇠의 역할이다. 잠금스크립트를 풀기위한 해제 스크립트라고도 불린다.

- 원리를 설명하면 방정식과 같다.

x + 5 = 10 이라는 방정식이 있다고 하면   

x가 의미하는 부분이 scriptSig이며  
' + 5 = 10 ' 이 부분이 scriptPubKey의 의미라고 보면된다.   

순서는 매우 간단하다.     
1. scriptSig 를 먼저 스택에 넣는다. (x를 의미)
2. scriptPubKey를 다음 스택에 넣는다. ( '+ 5 = 10' 을 의미하는 부분을 넣어본다)  
3. true인지 확인  

[참조](http://niipoong.blogspot.com/2018/03/scriptsig-scriptpubkey.html)
