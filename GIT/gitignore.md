# .gitignore 설정

## 기본적인 설정 

~~~
/target/
!.mvn/wrapper/maven-wrapper.jar

### STS ###
.apt_generated
.classpath
.factorypath
.project
.settings
.springBeans
.sts4-cache

### IntelliJ IDEA ###
.idea
.idea/*
*.iws
*.iml
*.ipr

### NetBeans ###
/nbproject/private/
/build/
/nbbuild/
/dist/
/nbdist/
/.nb-gradle/
~~~

## gitignore 변경 적용 안될 때

1. git rm -r --cached .
2. git add .
3. git commit -m "fixed untracked files"
4. push - 푸쉬해야 적용, git에 .gitignore에 설정된 파일 삭제까지 됨
