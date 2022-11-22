# 2022 RATS FRESHMAN LINETRACER
* <img src="https://user-images.githubusercontent.com/30527114/203359807-78da7ee8-835a-4c1b-914a-42149c29d91e.gif">
* **Linetracer with P-Control**
* [REF](https://github.com/RATS-make-robot/2022-freshman-linetracer)

## ISSUE LIST
### AS-IS
1. 바퀴가 슬립남
2. 해당 코드는 State를 계속 체크하고 변경해주는 밀리머신, 중간에 흰배경 -> 검정배경 -> finsh 스테이트로 변환이 채터링과 같이 일어나는 경우가 있음.
이런 경우 흰배경 상태인줄 알지만, finish 스테이트로 돌입  

### To-be
1-1. 바퀴를 두꺼운 걸로 교체하여 슬립율 감소 (조치완료).  
1-2. 약 210g(본인 핸드폰) 하중 가할시 슬립 최소화 되는 것으로 확인됨 -> 이때 토크 부족이 야기될 수 있음. 추후 대책 필요 (OFFSET 증가로 대처 및 조치완료).  
2-1. W2B, B2W 함수에 buff 삽입하여 채터링 감소유도 (조치완료). 

### 회고
1. FSM을 설계할떄 무어머신으로 설계했지만, 막상 도는 코드는 밀리머신일 수 도 있다. State가 의도되로 안변경될 수 있으니 잘 신경쓰자.
2. FSM으로 문제를 해결할때 현재 State를 외부에서 모니터링할 수 있는 수단을 마련하자. 없으니깐 디버깅 하기 너무 힘들다.
3. 파라메타를 실험적으로 잡아야하는 경우 외부 파일을 읽는 방법으로 조치하자. 계속 컴파일할려니깐 너무 귀찮다.
4. 제어가 의도되로 안된다면 PID gain 셋팅에 매몰되지 말고 HW 이슈가 있을 수 있음을 잊지 말자. 이번에도 슬립이 제어에 큰 복병이었다.
