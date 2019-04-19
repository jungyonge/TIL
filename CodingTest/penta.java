import java.util.*;

public class test{

    public static void main(String args[]) {
        String str = "123@ㅁㄴㅇㄹ123#!$#zzzddDdffff";
        String[] strArr =
                { "13","but", "i", "wont", "hesitate", "no", "more", "no", "more", "it", "cannot", "wait", "im", "yours" };

        test.problemOne(str);
        test.problemTwo();
        test.problemThr(strArr);

    }

    public static void problemOne(String str){

        String[] strArr = new String[str.length()];
        String[] strArr2 = new String[str.length()];
        HashMap<String ,Integer> map = new HashMap<>();

        //문자열에서 알파벳만 파싱
        int a = 0;
        for(int i = 0 ; i < str.length(); i++){
            int ascii = (byte)str.charAt(i);
            if((ascii >= 65 && ascii <= 90) || (ascii >= 97 && ascii <= 122) ){
                String strLower = String.valueOf(str.charAt(i)).toLowerCase();// 대소문자 구분시 .toLowerCase 삭제
                strArr[a] = strLower;
                a++;
            }
        }

        //알파벳 횟수 카운트
        for(int i = 0 ; i < a; i++){
            if(!map.containsKey(strArr[i])){
                map.put(strArr[i],1);
            }
            else{
                int cnt = map.get(strArr[i]) + 1 ;
                map.put(strArr[i],cnt);
            }
        }

        //value 기준을 정렬
        Iterator it = test.sortByValue(map).iterator();
        int j = 0;
        //카운트, 정렬 후 알파벳 strArr2에 저장
        while(it.hasNext()){
            String temp = (String) it.next();
            strArr2[j] = temp;
            j++;
        }

        //최고횟수와 똑같은 횟수가 있는 지 확인 후 출력
        System.out.println("1번 문제");
        for(int i = 0; i < strArr2.length; i++){
            if(map.get(strArr2[0]) == map.get(strArr2[i])){
                System.out.println("가장 많은 알파벳은 " + strArr2[i] + "이고 횟수는 " + map.get(strArr2[i])+ "번 입니다.");
            }
        }

    }

    public static void problemTwo(){
        int result = 0;
        int sum2 = 0;
        boolean check[] = new boolean[5000];

        //제네레이터계산 후 true 처리
        for(int i = 1 ; i < 5000; i++){
            int sum = 0;
            int j = i;

            while(j != 0) {
                sum += j%10;
                j /= 10;
            }

            result = sum + i ;

            if( (result > 1) && (result < 5000)){
                check[result] = true;
            }
        }

        //false이면 셀프 넘버
        for(int i = 1 ; i < 5000; i++ ){
            if(check[i] == false){
                sum2 = sum2 + i;
            }
        }

        System.out.println("2번 문제");
        System.out.println(sum2);
    }

    public static void problemThr(String[] strArr){

        //받은 문자열 정렬
        Arrays.sort(strArr);

        //문자열 정렬 후 길이 순 정렬
        Arrays.sort(strArr,1,strArr.length, new java.util.Comparator<String>() {
            @Override
            public int compare(String s1, String s2) {
                return s1.length() - s2.length();
            }
        });

        //첫번째는 문자열의 길이이므로 제외, 이전 문자열과 중복 일 시 출력 안함
        System.out.println("3번 문제");
        for(int i=1; i < strArr.length; i++) {
            if(strArr[i] != strArr[i-1]) {
                System.out.println(strArr[i]);
            }
        }

    }


    public static List sortByValue(final Map map){
        List<String> list = new ArrayList();
        list.addAll(map.keySet());

        Collections.sort(list,new Comparator(){
            public int compare(Object o1,Object o2){
                Object v1 = map.get(o1);
                Object v2 = map.get(o2);
                return ((Comparable) v1).compareTo(v2);
            }

        });
        Collections.reverse(list);
        return list;
    }
}

