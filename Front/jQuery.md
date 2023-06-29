#jQuery

  - jQuery 선택자
      - $('tag')	Tag라는 이름의 모든 태그 요소를 선택
      - $(‘.class’)	class라는 클래스명의 모든 클래스 요소를 선택
      - $(‘#id’)	id라는 아이디명의 아이디 요소를 선택
      - $(‘div li’)	div에 있는 li 모두 선택
      - $(‘div > p’)	div의 p태그라는 직계 자식을 선택
      - $(this)	현재 선택 중인 요소를 가리킴
  - jQuery 메소드
      - eq(n)	n번째에 위치하는 요소를 선택.
      - length()	요소의 개수를 알 수 있음.
      - parent() / parents()	요소의 직계 부모 선택 / 요소의 모든 부모들 선택
      - children(“a”)	요소의 a태그의 직계자손 선택
      - prev() / next()	이전 요소 선택 / 다음 요소 선택
      - val()	텍스트에 입력한 값을 추출
      - text()	해당 요소의 텍스트를 변경
      - move() / clone()	해당 요소 이동 / 해당 요소 복사
      - remove()	해당 요소 삭제
      - bind(이벤트,함수) / unbind(이벤트)	해당 이벤트 실행시 함수 실행 / 이벤트 제거
          -  unbind() - 해당문서 객체와 관련된 모든 이벤트 제거
          -  unbind(eventName) - 특정 이벤트와 관련된 모든 이벤트 제거
          -  unbind(eventName, function) - 특정 이벤트의 함수 제거
      - addClass() / removeClass()	클래스 추가 / 클래스 삭제
  - jQuery 이벤트
      - mousedown()	노드영역에서 마우스르 눌렀다가 떼었을 때 발생
      - mouseenter()	노드에 마우스가 진입했을 때 발생 -> 부모 영역안의 자식영역에 커서가 가도 마우스 진입으로 판단
      - mouseleave()	노드영역에서 마우스가 나갔을 때 발생
      - mousemove()	노드영역에서 마우스가 움직일 때 발생
      - mouseover()	노드 영역에 마우스를 올려 놓았을 때 발생 -> 부모 영역안의 자식영역에 커서가 가면 마우스 아웃으로 판단
      - mouseup()	마우스 포인터를 노드에 올려놓고 마우스 버튼을 눌렀을 때 발생


