## 배열 

- 선언 : int[] a = new int[8]; 
         int[] a = {1,2,3,4,5};
- 배열 -> 문자열 : Arrays.toString();
- char 배열 -> 문자열 : String.valueOf();-
- 문자열 -> char : .toCharArray;

- 배열 오름차순 : Arrays.sort(arr);
- 배열 내림차순 : Arrays.sort(arr, Collections.reverseOrder());

- 배열의 길이 : arr.length;
- 2차원 배열의 길이 : arr[0].length; 0번째 배열의 길이

- 배열의 특정 범위만 빼기 : Arrays.copyOfRange(arr, 2 ,4 ); 2번째 인자(포함)부터 3번째 인자(미포함) 앞까지 추출)


## 문자열

- 선언 : String str = "";

- str.startWith(a); : 특정 문자로 시작하는지 판단
- str.endWith(a); : 특정 문자로 끝나는지 판단

- str.equals(a); : 같은지 아닌지 판단
- str.indexOf("a"); : a가 몇번째 위치하는지 판단

- str.length; : 문자열길이판단
- String[] strArr = str.split("") : 문자열 1개씩 나누어 배열로 반환, 넣는 값을 기준으로 나눌수도있음 (str.split(" ") 
- str.substring(0, 2); : 1번째 인자부터 2번째 인자 앞까지 문자추출
- str.toLowerCase : 모든문자 소문자 변환
- str.toUpperCase : 모든문자 대문자 변환

- str.trim(); : 문자열 빈칸 제거
- String.valueOf(int i) : i를 문자열로 변환  

- str.charAt(i) : i번째 문자 추출

- StringBuilder sb -> sb.toString : StringBuilder을 문자열로 변환 
- sb.append(); : 문자열 뒤에 붙임 

## 해쉬맵
- 선언 "  HashMap<String, Integer> hm = new HashMap<>();

- hm.getOrDefault(player, 0) : 찾는 key가 존재하면 해당 key에 매핑되어 있는 값을 반환하고, 그렇지 않으면 디폴트 값이 반환됩니다.
- ~~~
  for (String key : hm.keySet()) {
              if (hm.get(key) != 0){
                  answer = key;
              }
          }
  ~~~
  hm안의 Key 값으로 포문 돌림
  
## 스택
-  Stack<Integer> stack = new Stack<>(); //int형 스택 선언
-  Stack<String> stack = new Stack<>(); //char형 스택 선언
-  stack.push(1);     // stack에 값 1 추가
-  stack.push(2);     // stack에 값 2 추가
-  stack.pop();       // stack에 값 제거
-  stack.clear();     // stack의 전체 값 제거 (초기화)
-  stack.peek();     // stack의 가장 상단의 값 출력

## 큐

- Queue<Integer> queue = new LinkedList<>(); //int형 queue 선언
- queue.offer(1);     // queue에 값 1 추가
- queue.offer(2);     // queue에 값 2 추가
- queue.offer(3);     // queue에 값 3 추가
- queue.poll();       // queue에 첫번째 값을 반환하고 제거 비어있다면 null
- queue.remove();     // queue에 첫번째 값 제거
- queue.clear();      // queue 초기화
- queue.peek();       // queue의 첫번째 값 참조

## 우선순위
//int형 priorityQueue 선언 (우선순위가 낮은 숫자 순)
- PriorityQueue<Integer> priorityQueue = new PriorityQueue<>();

//int형 priorityQueue 선언 (우선순위가 높은 숫자 순)
- PriorityQueue<Integer> priorityQueue = new PriorityQueue<>(Collections.reverseOrder());

//String형 priorityQueue 선언 (우선순위가 낮은 숫자 순)
- PriorityQueue<String> priorityQueue = new PriorityQueue<>(); 

//String형 priorityQueue 선언 (우선순위가 높은 숫자 순)
- PriorityQueue<String> priorityQueue = new PriorityQueue<>(Collections.reverseOrder());

- priorityQueue.add(1);     // priorityQueue 값 1 추가
- priorityQueue.add(2);     // priorityQueue 값 2 추가
- priorityQueue.offer(3);   // priorityQueue 값 3 추가
- priorityQueue.poll();       // priorityQueue에 첫번째 값을 반환하고 제거 비어있다면 null
- priorityQueue.remove();     // priorityQueue에 첫번째 값 제거
- priorityQueue.clear();      // priorityQueue에 초기화
- priorityQueue.peek();       // priorityQueue에 첫번째 값 참조 = 1

                                
                                