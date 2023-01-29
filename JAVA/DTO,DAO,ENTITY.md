### DTO

DTO(Data Transfer Object) 는 계층 간 데이터 교환을 하기 위해 사용하는 객체로, DTO는 로직을 가지지 않는 순수한 데이터 객체(getter & setter 만 가진 클래스)입니다.
유저가 입력한 데이터를 DB에 넣는 과정을 보겠습니다.
유저가 자신의 브라우저에서 데이터를 입력하여 form에 있는 데이터를 DTO에 넣어서 전송합니다.
해당 DTO를 받은 서버가 DAO를 이용하여 데이터베이스로 데이터를 집어넣습니다.

### VO

VO(Value Object) 값 오브젝트로써 값을 위해 쓰입니다. read-Only 특징(사용하는 도중에 변경 불가능하며 오직 읽기만 가능)을 가집니다.
DTO와 유사하지만 DTO는 setter를 가지고 있어 값이 변할 수 있습니다.

### Entity(Domain)
실제 DB의 테이블과 매칭시키는 클래스.

@Entity, @Column, @Id 등과 같은 annotation 사용.
- Entity와 DTO를 분리하는 이유
  - Entity는 DB Layer를 위한, DTO는 View Layer를 위한 것.

Entity는 테이블 매핑 클래스로 변경사항이 생기면,
Entity 뿐만 아니라 다른 여러 클래스에 영향을 주기 때문에 설계 시에 신중히 만들고
이후 변경사항이 상대적으로 다소 적은 클래스다.

반면에 DTO는
request/response에 대한 부분 혹은 View 관련 Presentaion Logic을 가지는
상대적으로 자주 변경되는 클래스이기 때문에 이 둘을 분리할 필요가 있다.

DTO는 Entity(=Domain) Model을 복사 해 와서,
Presentaion Logic을 추가하거나 DTO 상에서만 필요/불필요 한 필드 멤버를 추가/삭제한
클래스 구조인 것이다.

### DAO

DAO(Data Access Object) 는 데이터베이스의 data에 접근하기 위한 객체입니다.   
DataBase에 접근 하기 위한 로직 & 비지니스 로직을 분리하기 위해 사용합니다.

### Repository

- DAO는 Data Peristence의 추상화이고, Repository는 객체 Collection의 추상화이다.
- DAO는 storage system에 더 가까운 개념이고 상대적으로 low level concept, Repository는 Domain객체에 가까운 개념이며 상대적으로 high level concept
- DAO는 데이터 맵핑/접근 계층으로 쿼리를 숨기지만, Repository는 Domain과 DAL사이의 계층으로 데이터를 대조하고 Domain 객체로 Mapping하는 로직을 숨긴다.
- DAO는 Repository를 사용하여 구현할 수 없지만, Repository는 DAO를 사용해 구현할 수 있다.
- Data Access한다는 점에서 Repository와 DAO는 공통점을 갖지만, Repository는 객체 중심, DAO는 데이터 저장소(DB 테이블) 중심인 것이다.

또한, Repository는 객체 중심으로 데이터를 다루기 위해 하나 이상의 DAO를 사용할 수 있으며, 따라서 DAO보다 higher layer이다.

