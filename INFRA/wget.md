#wget

'Web Get'의 약어로 웹 상의 파일을 다운로드 받을 때 사용하는 명령어로 wget은 비 상호작용 네트워크 다운로더 이다.  
즉, 네트워크 상에서 데이터를 다운로드하는 기능을 수행한다

기본적인 사용법은 다음과 같다.

$ wget [옵션]... [URL]...
예를 들어 NGS 데이터의 de novo assembler 중의 하나인 velvet은 웹(https://www.ebi.ac.uk/~zerbino/velvet/)상에서 프로그램을 다운로드 받을 수 있다.   
그런데 웹프라우저에서 소스 다운로드 링크를 클릭하면 다시 분석서버로 해당 파일을 업로드 해야 하는 번거로움이 발생할 수 있다.   
이런 경우 wget 명령어를 이용하여 리눅스 명령행에서 바로 해당 파일을 다운로드 받을 수 있다.  
이경우 wget 명령어와 다운로드 링크를 입력하기만 하면 자동으로 현재 디렉토리에 파일이 다운로드 받아 진다.
~~~
$ wget https://www.ebi.ac.uk/~zerbino/velvet/velvet_1.2.10.tgz
~~~
wget는 command-line arguments를 처리하기 위해 GNU getopt를 사용하기 때문에 긴 옵션과 짧은 옵션이 모두 존재한다. 긴 옵션은 기억하기에는 편리하지만 입력하는데 시간이 많이 소요된다.   
옵션 스타일은 자유롭게 섞어서 사용할 수 있다. wget은 몇 가지 옵션 활용법만 알아도 더 편리하게 이용할 수 있다.

국외 서버에서 제공하는 다운로드 링크를 이용하는 경우 인터넷 통신이 불안정하여 중간에 끊길 수 있다.  
--tries 옵션은 응답이 없는 다운로드 시도에 대하여 재시도 하는 횟수를 지정한다.
~~~
$ wget --tries=10 https://www.ebi.ac.uk/~zerbino/velvet/velvet_1.2.10.tgz
~~~
다운로드 링크가 ftp 프로토콜로 제공되고 로그인 계정 정보가 요구될때는 아래와 같이 유저 정보를 지정하여 실행 할 수 있다.   
예를 들어 ftp 계정(ID)이 guest 이고 password가 ftpuser이면서 ncbi에서 제공하는 미생물의 16s rRNA 서열 다운로드 받고자 한다면 아래와 같이 입력하면 된다.
~~~
$ wget --ftp-user=guest --ftp-password=ftpuser ftp://ftp.ncbi.nlm.nih.gov/blast/db/16SMicrobial.tar.gz
~~~
원래 저 파일은 NCBI에서 비로그인 사용자에게도 제공하므로 계정 정보 없이 아래와 같이 ftp 프로토콜로 접속한다는 의미의 URL만 입력해도 다운로드 된다.
~~~
$ wget ftp://ftp.ncbi.nlm.nih.gov/blast/db/16SMicrobial.tar.gz
~~~

와일드카드 문자를 이용하여 파일들을 지정하면 다수의 파일 다운로드도 가능하다. 아래는 NCBI의 BLAST nr DB 파일을 다운로드 받을 수 있는 명령어이다.
~~~
$ wget ftp://ftp.ncbi.nlm.nih.gov/blast/db/nr*.tar.gz
~~~
다수의 파일을 다운로드 받을 경우 -o 옵션을 이용해서 다운로드 로그를 파일에 생성할 수 있다. 아래의 경우는 연결이 끊기더라도 10번을 더 시도해 보면서 다운로드를 수행하고 'log'라는 파일을 생성하여 로그를 남기는 명령어 이다.
~~~
$ wget --tries=10 http://fly.srk.fer.hr/ -o log
또는,
$ wget --tries=10 http://fly.srk.fer.hr/ --output-file=log
~~~
-a(--append-output=LOGFILE_NAME) 옵션은 -o 옵션 처럼 다운로드 로그를 남기는 옵션이지만 기존의 파일을 덮어쓰지 않고 추가만 한다. 만약 지정된 로그 파일이 존재하지 않으면 해당 이름의 파일을 생성하고 로그를 남긴다.
~~~
$ wget --tries=10 http://fly.srk.fer.hr/ -a log
또는,
$ wget --tries=10 http://fly.srk.fer.hr/ --append-output=log
~~~
그리고 유용한 옵션 중의 하나가 -c 옵션인데, 이전에 다운로드 받다가 중단된 파일을 이어서 다운로드 받는다.   
이 경우 기존의 중단된 파일이 있는 디렉토리에서 실행해야 다운로드가 이어진다.
~~~
$ wget -c https://www.ebi.ac.uk/~zerbino/velvet/velvet_1.2.10.tgz
~~~

-O은 저장될 파일명, -P는 저장될 위치 지정인데, 두개가 같이 사용이 안된다.
파일명과 위치 둘다 변경하고 싶으면 -P옵션으로 위치/파일명으로 실행시키면 된다.
두 옵션다 안주면 마지막 / 뒤가 파일명이 된다.
~~~
$ wget -P /test/ttt.tgz https://www.ebi.ac.uk/~zerbino/velvet/velvet_1.2.10.tgz
~~~



