#Too many open files Exception in Tomcat 해결

톰캣로그에서 Too many open files Exception in Tomcat 발생한다면 OS문제로 인식된다 .  
OS에서 한 프로세스에서 최대로 사용할 수 있는 File Descriptor의 개수는 정해져 있다. 리눅스의 경우는 ulimit -a (csh에서는 limit)으로 확인할 수 있다.  
보통 Default로 1024개로 설정 되어 있다.

lsof -p [PID] | wc -l 
위의 명령어로 PID가 읽고 있는 파일 개수 파악이 가능하다.

## 해결법
<Solution>

1)/etc/security/limits.conf 파일을 수정한다.
You need to modify /etc/security/limits.conf file

vi /etc/security/limits.conf

~~~
#<domain>        <type>  <item>  <value>
# add those thing
* soft nofile 16000
* hard nofile 16000
~~~

open files 숫자를 1024 에서 16000 으로 늘렸다.
Increase 1024 to 16000 in the number of open files.

2) 톰캣을 리스타트 한다.
Restart Tomcat.

3) 제대로 적용이 안된다면 OS도 재기동해야한다.


