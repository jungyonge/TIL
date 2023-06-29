#JSON(JavaScript Object Notation)이란?

- JSON은 경량(Lightweight)의 DATA-교환 형식
- Javascript에서 객체를 만들 때 사용하는 표현식을 의미한다.
- JSON 표현식은 사람과 기계 모두 이해하기 쉬우며 용량이 작아서, 최근에는 JSON이 XML을 대체해서 데이터 전송 등에 많이 사용한다.
- 특정 언어에 종속되지 않으며, 대부분의 프로그래밍 언어에서 JSON 포맷의 데이터를 핸들링 할 수 있는 라이브러리를 제공한다.

## JSON 문법

- 객체는 {}(중괄호)로 표기합니다.
- 배열은 [[]](대괄호)로 표기합니다.
- 각 속성은 key와 value쌍으로 이루어져 있으며 :(콜론)으로 구분됩니다.
- 속성이 여러개인 경우 ,(쉼표)로 구분합니다.

~~~
{
  "employees": [
    {
      "name": "Surim",
      "lastName": "Son"
    },
    {
      "name": "Someone",
      "lastName": "Huh"
    },
    {
      "name": "Someone else",
      "lastName": "Kim"
    } 
  ]
}
~~~

## JSON 라이브러리
JSON 사용 시 import되는 package를 그냥 막 사용하다보니, 사용법이 생각보다 달라서 정리해본다.
GSON을 사용 많이 안하다 보니 다소 불편

~~~
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;

            String json = "json";
            JSONParser jsonParser = new JSONParser();
            JSONObject jsonObject = (JSONObject) jsonParser.parse(json);
            JSONArray jsonArray = (JSONArray) jsonObject.get("response");
            JSONObject jsonObj = (JSONObject) jsonObject.get("code");

~~~

~~~
import org.json.JSONArray;
import org.json.JSONObject;

import org.codehaus.jettison.json.JSONArray;
import org.codehaus.jettison.json.JSONObject;
// 두개의 페키지가 사용법이 같음

            String json = "json";
            JSONObject jsonObject = new JSONObject(json);
            JSONArray jsonArray = jsonObject.getJSONArray(키값);
            JSONObject jsonObj = jsonObject.getJSONObject(키값);
~~~

~~~
import com.google.gson.Gson; 
import com.google.gson.reflect.TypeToken;

            String json = "json";
            Gson gson = new Gson();
            Map map = new HashMap<String,String>();
            map = gson.fromJson(json, map.getClass());
            //map 말고  해당 Json 형식에 맞는 VO class사용 해도 됨

            //response에 ArrayList가 있다.
            List<HashMap<Object,Object>> list = new ArrayList<>();
            list = (List<HashMap<Object, Object>>) map.get("response");

            //벗겨낼 JsonDepth가 없이 바로 List라면
            // 방법1
            Member[] array = gson.fromJson(jsonString, Member[].class);
            List<Member> list = Arrays.asList(array);
            // 방법2 
            List<Member> list2 = gson.fromJson(jsonString, new TypeToken<List<Member>>(){}.getType());
~~~

