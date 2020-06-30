#@ControllerAdvice, @ExceptionHandler

# 예외 처리 과정

프로그래밍에서 예외 처리는 아주 중요하면서도 아주 어렵다.  
과하다할 만큼 상세하고 다양하게 예외를 잡아 처리해준다면, 클라이언트도 그렇고 서버도 그렇고 더 안정적인 프로그램이 될 수 있게 도와준다.  
예외 처리를 하는 경우와 방법은 다양하다.  

- 메서드 내에서 예측하여 try-catch 사용
- 요구사항에 의한 예외 처리 (ex. validation > 특정 값이 0~255범위가 아니면 유효하지 않은 값으로 판단하고 예외 처리)
- 스프링 시큐리티에서 인터셉터로 잡아서 UnauthorizedException 같은 예외 처리

너무 많은 try-catch를 사용하다보니 코드가 복잡해지고 어디서 에러가 발생하는지 찾기가 어려움. 
각 Exception마다 오류메시지를 통일할 수 있어서 좋은 듯 하다.

## 사용법
@ControllerAdvice 어노테이션을 사용하여 오류를 캐치할 구현 클래스를 만들게 도와준다.
@Controller와 @RestController가 선언된 클래스에서 발생한 예외를 감지한다

-  먼저 사용할 Exception 하나를 만든다. 기존에 Spring에서 제공되는 Exception도 사용가능
~~~
public class YongException extends RuntimeException {

	private static final long serialVersionUID = 1L;
	private String message;

	public TestException(String message) {
		this.message = message;
	}
	public String getMessage() {
		return message;
	}
	public void setMessage(String message) {
		this.message = message;
	}
}
~~~

-  사용할 Controller 생성
~~~
@RestController
public class YongController {
	@RequestMapping(value="/")
	public void ExecuteException(){
        // 고의로 Exceoption 던
		throw new YongController("TEST");
	}
}
~~~

-  사용할 ErrorMessage 생성
    - Enum 도 추가하여 넘어온 status나 ErrorCode마다 메세지 설정 가능하다.
~~~
public class ErrorMessage {
	private String status;
	private String message;

	public String getStatus() {
		return status;
	}
	public void setStatus(String status) {
		this.status = status;
	}
	public String getMessage() {
		return message;
	}
	public void setMessage(String message) {
		this.message = message;
	}
}
~~~

- ControllerAdvice 생성  
 @ControllerAdvice 어노테이션을 선언하는 클래스는 추후 생기는 예외Exception를 catch해서 처리한다
  따라서 지금 작성된 클래스는 아까전 만들어 뒀던 TestException 예외가 발생했을 경우 해당 예외를 처리하는 코드가 담겨 있다.
 ~~~
@ControllerAdvice
public class YongAdvice {

   @ExceptionHandler(value = { YongException.class })
   @ResponseStatus(HttpStatus.INTERNAL_SERVER_ERROR)
   @ResponseBody
   protected ErrorMessage handleConflict(RuntimeException ex, WebRequest request) {
   	ErrorMessage em = new ErrorMessage();
   	em.setStatus(HttpStatus.INTERNAL_SERVER_ERROR.toString());
   	em.setMessage(ex.getMessage());
       return em;
   }
}
 ~~~
YongException이 발생했을 때 에러 메세지처리와 로그처리를 한곳에서 관리 가능하다.

try catch마다 에러메세지를 남겨주고, 리턴값이 달라서 불편했는데,
해당 어노테이션을 사용하면 한 곳에서 관리되니 코드가 확실히 깔끔해졌다.