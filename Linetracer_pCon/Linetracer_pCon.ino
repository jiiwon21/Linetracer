#define ENA 10
#define ENB 11
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 12
#define TGT_line 3
#define Kp_WHITE 40
#define Kp_BLACK 20
#define MOTOR_OFFSET_A 90
#define MOTOR_OFFSET_B 90

void read_sensor();
void monitoring_sensor();
void on_led_whitebackground();
void on_led_blackbackground();
void pControl_white(int current_line);
void pControl_black(int current_line);
void setting_sensor();
int whiteground_current_line();
int blackground_current_line();
void drive_white_background();
void drive_black_background();
bool check_W2B();
bool check_B2W();


int sensor_value[5];                                                                                                                                                                                                                                                                                       
int std_sensor[5]; //= {243,282,306,335,360};

void setup() {
  Serial.begin(9600);
  setting_sensor();
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);// 2. 8번 핀을 출력으로 설정합니다.
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  //drive_white_background();
  //drive_black_background();
  read_sensor();
  if(check_W2B())
    Serial.println("STATE CHANGEe W2B");

  if(check_B2W())
    Serial.println("STATE CHANGE B2W");
    
}

void read_sensor()
{
  sensor_value[0]=analogRead(A0);
  sensor_value[1]=analogRead(A1);
  sensor_value[2]=analogRead(A2);
  sensor_value[3]=analogRead(A3);
  sensor_value[4]=analogRead(A4);
}

void monitoring_sensor()
{
  Serial.print(sensor_value[0]);Serial.print("\t");
  Serial.print(sensor_value[1]);Serial.print("\t");
  Serial.print(sensor_value[2]);Serial.print("\t");
  Serial.print(sensor_value[3]);Serial.print("\t");
  Serial.print(sensor_value[4]);Serial.print("\t");
  Serial.print("\n");
}

void on_led_blackbackground()
{
  if(sensor_value[0]<std_sensor[0]){
    digitalWrite(2, LOW);
  }
  else{
    digitalWrite(2, HIGH);
  }
  if(sensor_value[1]<std_sensor[1]){
    digitalWrite(3, LOW);
  }
  else{
    digitalWrite(3, HIGH);
  }
  if(sensor_value[2]<std_sensor[2]){
    digitalWrite(4, LOW);
  }
  else{
    digitalWrite(4, HIGH);
  }
  if(sensor_value[3]<std_sensor[3]){
    digitalWrite(5, LOW);
  }
  else{
    digitalWrite(5, HIGH);
  }
  if(sensor_value[4]<std_sensor[4]){
    digitalWrite(6, LOW);
  }
  else{
    digitalWrite(6, HIGH);
  }
}
void on_led_whitebackground()
{
  if(sensor_value[0]>std_sensor[0]){
    digitalWrite(2, LOW);
  }
  else{
    digitalWrite(2, HIGH);
  }
  if(sensor_value[1]>std_sensor[1]){
    digitalWrite(3, LOW);
  }
  else{
    digitalWrite(3, HIGH);
  }
  if(sensor_value[2]>std_sensor[2]){
    digitalWrite(4, LOW);
  }
  else{
    digitalWrite(4, HIGH);
  }
  if(sensor_value[3]>std_sensor[3]){
    digitalWrite(5, LOW);
  }
  else{
    digitalWrite(5, HIGH);
  }
  if(sensor_value[4]>std_sensor[4]){
    digitalWrite(6, LOW);
  }
  else{
    digitalWrite(6, HIGH);
  }
}

void pControl_white(int current_line){
  int error = TGT_line - current_line;
  int control_value = Kp_WHITE*error;
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, MOTOR_OFFSET_A - control_value);
  analogWrite(ENB, MOTOR_OFFSET_B + control_value);
 
}
void pControl_black(int current_line){
  int error = TGT_line - current_line;
  int control_value = Kp_BLACK*error;
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, MOTOR_OFFSET_A + control_value);
  analogWrite(ENB, MOTOR_OFFSET_B - control_value);
 
}


int whiteground_current_line(){
  if(sensor_value[0]<std_sensor[0]){
    return 1;
  }
  else if(sensor_value[0]>std_sensor[0] && sensor_value[1]<std_sensor[1]){
    return 2;
  }
  else if((sensor_value[0]>std_sensor[0] && sensor_value[1]<std_sensor[1] && sensor_value[2]<std_sensor[2] && sensor_value[3]<std_sensor[3] && sensor_value[4]>std_sensor[4])||(sensor_value[0]>std_sensor[0]&&sensor_value[1]>std_sensor[1]&&sensor_value[2]<std_sensor[2]&&sensor_value[3]>std_sensor[3]&&sensor_value[4]>std_sensor[4])){
    return 3;
  }
  else if(sensor_value[2]>std_sensor[2] && sensor_value[3]<std_sensor[3]){
    return 4;
  }
  else if(sensor_value[4]<std_sensor[4]){
    return 5;
  }
}

int blackground_current_line(){
  if(sensor_value[0]>std_sensor[0]){
    return 1;
  }
  else if(sensor_value[0]<std_sensor[0] && sensor_value[1]>std_sensor[1]){
    return 2;
  }
  else if((sensor_value[0]<std_sensor[0] && sensor_value[1]>std_sensor[1] && sensor_value[2]>std_sensor[2] && sensor_value[3]>std_sensor[3] && sensor_value[4]<std_sensor[4])||(sensor_value[0]<std_sensor[0]&&sensor_value[1]<std_sensor[1] && sensor_value[2]>std_sensor[2] && sensor_value[3]<std_sensor[3] && sensor_value[4]<std_sensor[4])){
    return 3;
  }
  else if(sensor_value[2]<std_sensor[2] && sensor_value[3]>std_sensor[3]){
    return 4;
  }
  else if(sensor_value[4]>std_sensor[4]){
    return 5;
  }
  else if(sensor_value[0]>std_sensor[0] && sensor_value[1]>std_sensor[1] && sensor_value[2]>std_sensor[2] && sensor_value[3]>std_sensor[3] && sensor_value[4]>std_sensor[4]){
    return 3;
  }
}

void setting_sensor(){
  int white_value[5];
  int black_value[5];
  Serial.println("INPUT WHITE");
  for (int i = 0; i < 100; i++)
  {
    read_sensor();
  }
  for (int i = 0; i < 5; i++)
  {
    white_value[i] = sensor_value[i];
  }
  Serial.println("READY");
  delay(5000);
  Serial.println("INPUT BLACK");
  for (int i = 0; i < 100; i++)
  {
    read_sensor();
  }
  for (int i = 0; i < 5; i++)
  {
    black_value[i] = sensor_value[i];
  }
  for (int i = 0; i < 5; i++)
  {
    std_sensor[i] = ( black_value[i] + white_value[i] ) / 2;
  }
  Serial.println("SETTING DONE");
}

void drive_white_background(){
  int current_line;
  read_sensor();
  monitoring_sensor();
  on_led_whitebackground();
  current_line=whiteground_current_line();
  pControl_white(current_line);  
  Serial.println(current_line);
}

void drive_black_background(){
  int current_line;
  read_sensor();
  monitoring_sensor();
  on_led_blackbackground();
  current_line=blackground_current_line();
  pControl_black(current_line);  
  Serial.println(current_line);
}


bool check_W2B(){
  if( sensor_value[0]<std_sensor[0] && sensor_value[4]<std_sensor[4] && ( sensor_value[1]>std_sensor[1] || sensor_value[2]>std_sensor[2] || sensor_value[3]>std_sensor[3] ))
    return true;
  else
    return false;
}
bool check_B2W(){
  if( sensor_value[0]>std_sensor[0]  && sensor_value[4]>std_sensor[4] && ( sensor_value[1]<std_sensor[1] || sensor_value[2]<std_sensor[2] || sensor_value[3]<std_sensor[3] ))
    return true;
  else 
    return false;
}
