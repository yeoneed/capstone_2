package com.example.busroute;


import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserFactory;

import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.URL;
import java.net.URLEncoder;

public class MainActivity extends AppCompatActivity {
    EditText edit;
    TextView text;
    XmlPullParser xpp;

    String key="pvvI2Zz%2Fe%2Bcdi5PrfOVVmTdWfxFJn0BWbPun%2FBmxt5Rn6Jt13zLa8Z%2Fe22UfqhON5zHYrn%2BAtefALJd%2FBiO36w%3D%3D";
    String data;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        edit= (EditText)findViewById(R.id.edit);
        text= (TextView)findViewById(R.id.result);

    }
    public void mOnClick(View v){
        switch (v.getId()){
            case R.id.button:
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        data=getXmlData();

                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                text.setText(data);

                            }
                        });
                    }
                }).start();
                break;


        }
    }
    String getXmlData(){
        StringBuffer buffer=new StringBuffer();
        String str= edit.getText().toString();//EditText에 작성된 Text얻어오기
        String routeId = URLEncoder.encode(str);
        String query="%EC%A0%84%EB%A0%A5%EB%A1%9C"; // 이건 왜 있는것인지??

        String queryUrl="http://openapi.gbis.go.kr/ws/rest/busrouteservice/station?serviceKey=pvvI2Zz%2Fe%2Bcdi5PrfOVVmTdWfxFJn0BWbPun%2FBmxt5Rn6Jt13zLa8Z%2Fe22UfqhON5zHYrn%2BAtefALJd%2FBiO36w%3D%3D&routeId="+routeId+"";
        try{
            URL url= new URL(queryUrl);//문자열로 된 요청 url을 URL 객체로 생성.
            InputStream is= url.openStream(); //url위치로 입력스트림 연결

            XmlPullParserFactory factory= XmlPullParserFactory.newInstance();//xml파싱을 위한
            XmlPullParser xpp= factory.newPullParser();
            xpp.setInput( new InputStreamReader(is, "UTF-8") ); //inputstream 으로부터 xml 입력받기

            String tag;

            xpp.next();
            int eventType= xpp.getEventType();
            while( eventType != XmlPullParser.END_DOCUMENT ){
                switch( eventType ){
                    case XmlPullParser.START_DOCUMENT:
                        buffer.append("파싱 시작...\n\n");
                        break;

                    case XmlPullParser.START_TAG:
                        tag= xpp.getName();//테그 이름 얻어오기

                        if(tag.equals("busRouteStationList")) ;// 첫번째 검색결과
                        else if(tag.equals("stationId")){
                            buffer.append("정류소 Id : ");
                            xpp.next();
                            buffer.append(xpp.getText());//요소의 TEXT 읽어와서 문자열버퍼에 추가
                            buffer.append("\n"); //줄바꿈 문자 추가
                        }
                        else if(tag.equals("stationName")){
                            buffer.append("정류소명 : ");
                            xpp.next();
                            buffer.append(xpp.getText());//요소의 TEXT 읽어와서 문자열버퍼에 추가
                            buffer.append("\n");//줄바꿈 문자 추가
                        }
                        else if(tag.equals("x")){
                            buffer.append("경도 :");
                            xpp.next();
                            buffer.append(xpp.getText());//요소의 TEXT 읽어와서 문자열버퍼에 추가
                            buffer.append("\n");//줄바꿈 문자 추가
                        }
                        else if(tag.equals("y")){
                            buffer.append("위도 :");
                            xpp.next();
                            buffer.append(xpp.getText());//telephone 요소의 TEXT 읽어와서 문자열버퍼에 추가
                            buffer.append("\n");//줄바꿈 문자 추가
                        }






                        break;

                    case XmlPullParser.TEXT:
                        break;

                    case XmlPullParser.END_TAG:
                        tag= xpp.getName(); //테그 이름 얻어오기

                        if(tag.equals("busRouteStationList")) buffer.append("\n");// 첫번째 검색결과종료..줄바꿈
                        break; // -> 이 부분 앤드테그 부분이 시작이랑 동일하므로 꼭 필요한 부분임.
                }

                eventType= xpp.next();
            }

        } catch (Exception e){
            e.printStackTrace();
        }

        buffer.append("클릭하시면 노선 정보를 제공합니다\n");
        return buffer.toString();//StringBuffer 문자열 객체 반환

    }//getXmlData method....
}