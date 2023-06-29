#  REST API
1.  URI  리소스를 표시하고 http method로 crud 를 적용하는 방법
     -  POST,GET,DELETE,PUT
  
2. 특징
    - Uniform : 지정된 방법으로 URI에 리소스 표시
    - Stateless : 상태정보를 따로 저장 안하고 관리도 안함 단순히 API서버는 요청을 처리
    - Cashable : HTTP 웹표준을 사용하기에 HTTP가 가진 캐싱기능 사용가능
    - Self-descriptiveness : API 메세지만으로 원하는 것을 알 수 있음
    - Cliet - Sever 구조 : REST 서버는 API 제공, 클라이언트는 사용자 인증이나 컨텍스트(세션, 로그인 정보)등을 직접 관리하는 구조
    - 계층형 구조 : REST 서버는 다중 계층으로 구성될 수 있으며 보안, 로드 밸런싱, 암호화 계층을 추가해 구조상의 유연성있음

3. URI 설계시 주의점
    - 슬래시 구분자(/)는 계층 관계를 나타내는 데 사용
    - URI 마지막 문자로 슬래시(/)를 포함하지 않는다
    - 하이픈(-)은 URI 가독성을 높이는데 사용
    - 밑줄(_)은 URI에 사용하지 않는다.
    - URI 경로에는 소문자가 적합하다.
    
4. 정리
    - 그동안 API를 만들때 REST API의 방식을 따라 한적이 없다.
    - 이방식을 사용하면 API 경로의 네이밍이 수월해질 듯.
    - 그러면 반드시 모든 API의 형식이 같아야하나.. 질문이 생김
    - 보안적인 Search 할 때는 그냥 POST 써야할 듯..?


## REST API 라이브러리 정리

1. HttpURLConnection
    - 기본 JDK에 포함되어 있음. (jdk1.2부터 내장되어 있으며 java.net 패키지에 있다.)
    - 상대적으로 가벼우며 핵심적인 API만 지원하고 있음.
    - HttpClient 보다 성능이 좋다고 함. (유사 사례 확인 결과 HttpClient에서 Server와 Client연결에 속도 이슈가 있어 HttpURLConnection으로 수정한 사례가 확인됨.) 
    - 서버로부터 전달 받은 Response 결과를 Stream으로 직접 처리해야 하는 등.. 개발 생산성이 떨어지는 요소가 다소 있음.

~~~
public static String getHttpURLConnection(String url) throws Exception {
	StringBuilder responseText = new StringBuilder(1024);
	URLConnection con;
        con = new URL(url).openConnection();

        // 최대한 컴퓨터가 호출하는 것이랑 동일하게 하자
        con.setRequestProperty("User-Agent", "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/32.0.1700.107 Safari/537.36");
        con.setRequestProperty("Accept-Language", "ko-KR,ko;q=0.8,en-US;q=0.6,en;q=0.4");
        con.setUseCaches(false);

        con.setReadTimeout(1000 * 30);
        con.setConnectTimeout(1000 * 30);

        // POST 방식
        String param = "xx="+xx+"&xxx="+xxx+"&xxxx="+xxxx;
        con.setRequestMethod("POST");
        // 서버로 데이터를 전송할 수 있도록 한다. GET방식이면 사용될 일이 없으나, true로
        // 설정하면 자동으로 POST로 설정된다. 기본값은 false이다.
        con.setDoOutput(true);
        // 서버로부터 메세지를 받을 수 있도록 한다. 기본값은 true이다.
        con.setDoInput(true);

        OutputStream opstrm = con.getOutputStream();
        opstrm.write(param.getBytes());
        opstrm.flush();
        opstrm.close();

        con.connect();

        BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream()));

        String inputLine;
        while ((inputLine = in.readLine()) != null)
            responseText.append(inputLine);

        in.close();

		return responseText.toString();
}

~~~
    
2. HttpClient
- Apache에서 제공
- HttpClient는 3버전과 4버전이 있으며 4버전부터는 HttpComponents로 불리고 있음.(단, 3버전과 4버전은 둘간 직접적인 호환은 되지 않음)
- HttpComponents(4버전) 부터는 Thread에 안정적인 기능들을 많이 제공함.
- 상대적으로 무거움
- HttpURLConnection 대비 다양한 API를 지원함.

개발 순서 

1. ClosableHttpClient 인스턴스를 생성
2. HTTP request type에 따른 HttpGet/HttpPost 인스턴스 생성
3. addHeader 메서드를 이용해 헤더정보 추가
4. request를 execute해서 CloseableHttpResponse 얻기
5. response 출력
6. close 메서드를 통해 연결 종료

~~~
public class Httpclient1 {
    
    private static final String USER_AGENT = "Mozila/5.0";
    private static final String GET_URL = "http://www.google.com";    
 
    public static void sendGet() throws ClientProtocolException, IOException {
        
        //http client 생성
        CloseableHttpClient httpClient = HttpClients.createDefault();
 
        //get 메서드와 URL 설정
        HttpGet httpGet = new HttpGet(GET_URL);
 
        //agent 정보 설정
        httpGet.addHeader("User-Agent", USER_AGENT);
        
        //get 요청
        CloseableHttpResponse httpResponse = httpClient.execute(httpGet);
        
        System.out.println("::GET Response Status::");
        
        //response의 status 코드 출력
        System.out.println(httpResponse.getStatusLine().getStatusCode());
 
        BufferedReader reader = new BufferedReader(new InputStreamReader(
                httpResponse.getEntity().getContent()));
 
        String inputLine;
        StringBuffer response = new StringBuffer();
 
        while ((inputLine = reader.readLine()) != null) {
            response.append(inputLine);
        }
        
        reader.close();
 
        //Print result
        System.out.println(response.toString());
        httpClient.close();
    }
}

~~~
3. OKHttp
- Square의 오픈소스 프로젝트 
- OKHttp는 통신을 동기화로 할지 비동기로 처리 할지 선택하여 사용할 수 있음.
- 단 스레드를 넘나들 수 없음. (스레드간에 데이터를 공유하기 위해서는 Handler를 활용해야함)

~~~
~~~

