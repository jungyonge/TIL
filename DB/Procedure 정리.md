#Procedure 정리

##Procedure란
  특정 작업을 수행 하는, 이름이 있는 PL/SQL BLOCK 이다.  
  매개 변수를 받을 수 있고, 반복적으로 사용 할 수 있는 BLOCK 이다.  
  보통 연속 실행 또는 구현이 복잡한 트랜잭션을 수행하는 PL/SQL BLOCK을 데이터베이스에 저장하기 위해 생성 한다.  
  
##Procedure 생성
~~~
DELIMITER $$

create
    definer = locahost@`%` procedure TEST_PROC(IN IN_JOB_LOG_ID varchar(250)) 파라미터 
BEGIN

    DECLARE err INT DEFAULT 0; 
    DECLARE T_LOG_STEP            VARCHAR(200);  사용할 변수 선언
    
     WHILE LOOPCNT <= MX AND T_ERROR_CHECK = 0 DO

      /*여러가지 비지니스 로직 */


     END WHILE;
    /* 커밋 */
    COMMIT;

END;$$
DELIMITER ;
~~~
DELIMITER는 프로시저 앞,뒤의 위치하여 안에 있는 부분은  한번에 실행될 수 있게 하는 역할을 한다.

##Procedure 에러 핸들링
프로시저는 에러가나면 디버깅이 정말 힘들다.  
그래서 사용을 안하는 추세이기도 하다.  
허나 에러 핸들링을 사용 시 그나마 어디서 에러 발생, 원인은 파악 할 수 있다.


~~~~
    DECLARE continue/exit HANDLER FOR sqlexception
        BEGIN
            GET DIAGNOSTICS CONDITION 1 @sqlstate = RETURNED_SQLSTATE, @errno = MYSQL_ERRNO, @text = MESSAGE_TEXT, @table_name = TABLE_NAME;
            SET @full_error = CONCAT("ERROR ", @errno, " (", @sqlstate, "): ", @text, ", TABLE NAME : ", @table_name);
            INSERT INTO ERROR_MSG(ERROR) VALUE (@full_error);
        END;
~~~~

1. continue를 사용하면 에러나도 진행하고 , exit면 프로시저 종료  
2. GET DIAGNOSTICS 구문으로 디버깅에 필요한 다음 세 가지 condition information을 얻을 수 있음..
 RETURNED_SQLSTATE, MYSQL_ERRNO, MESSAGE_TEXT
3. full_error변수에 에러 내용 CONCAT으로 생성
4. 에러메세지 테이블로 INSERT

