# 핫월렛 VS 콜드월렛

## 핫월렛
- 인터넷이 연결된 지갑 (온라인지갑)
- 실시간으로 편리하게 사용가능, 보안취약
- 일반적으로 사용들이 사용하는 지갑
    - Metamask, Trust , 등 모바일지갑 

- 크롬확장프로그램 Wallet
   - Private key는 로컬에 저장
   - Salt 값으로 암호화 되어 저장됨
   - [참조](https://metamask.zendesk.com/hc/en-us/articles/360018766351-How-to-use-the-Vault-Decryptor-with-the-MetaMask-Vault-Data
)

- 모바일 Wallet
    - IOS : Keychain라는 Mac OS X, iOS의 다양한 응용 프로그램에서 사용되는 비밀번호를 저장하는 암호화 되어 있는 저장소 저장
    - Android : Keystore 시스템은 암호용 키 저장소로 디바이스에서 중요한 키 값을 추출해 내기 더 어렵도록 만들어준다.
                키가 일단 Keystore에 들어가게 되면, 암호관련 operation을 통해서만 사용할 수 있게 된다
      - 안드로이드는 버전 15,18,23별로 키저장 분기처리 해야함
      - 18 이전에는 Keystore 없으므로 AES 암호화 처리 후 저장
      - 18 이후는 Keystroe에 저장
      - 23 이후는 Keystore 저장방식이 18과 다름
      
      
      
## 콜드월렛
- 인터넷에 연결되지 않은 지갑 (오프라인지갑)
- USB 저장장치처럼 생긴 하드웨어 지갑, 보안강화
- 코인어스, 렛져나노, 펜타등등
- Private Key 자체를 오프라인인 콜드월렛에서 생성하고, TX 서명도 콜드월렛에서 한 후 온라인으로 TX만 전송한다


    
