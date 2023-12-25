// http://un7fgo.gengen.ru (C) 2020
// https://github.com/UN7FGO 
// 
// Минималистичный электронный ключ

// Определяем контакт, к которому подключен потенциометр регулировки скорости электронного ключа
#define CW_SPEED_PIN A3
// Определяем максимальную и минимальную длительность точки в миллисекундах
#define MIN_DIT_TIME 50
#define MAX_DIT_TIME 150

// Определяем контакты для подключения электронного ключа
#define CW_DIT_PIN PB2
#define CW_DASH_PIN PB1
// Контакт вывода звука для самоконтроля
#define CW_SOUND_PIN PB0
// контакт "ключа".
#define CW_OUT_PIN PB4

// переменные для работы

int t_delay;
unsigned long timing; // Переменная для хранения точки отсчета millis
int dit_on = 0;
int dash_on = 0;  // переменные обозначающие нажатую точку или тире

/* =================================================== */
void setup() {
  pinMode (CW_DIT_PIN,INPUT);
  digitalWrite(CW_DIT_PIN, HIGH);
  pinMode (CW_DASH_PIN,INPUT);
  digitalWrite(CW_DASH_PIN, HIGH);
  pinMode(CW_OUT_PIN, OUTPUT);
  digitalWrite(CW_OUT_PIN, LOW);
  pinMode(CW_SOUND_PIN, OUTPUT);
}
/* 
 В этом месте начинается выполнение аналога delay()
 Вычисляем разницу между текущим моментом и ранее сохраненной точкой отсчета.
 Если разница больше нужного значения, то выполняем код. 
 Если нет - ничего не делаем 

 if (millis() - timing > 10000){ // Вместо 10000 подставьте нужное вам значение паузы 
  timing = millis(); 
  Serial.println ("10 seconds");
 }
 */
void loop() {
  
// обрабатываем нажатие манипулятора "точка"
  if(digitalRead(CW_DIT_PIN) == 0 || dit_on == 1) {
    // расчитываем длительность "точки" по положению потенциометра
    t_delay = analogRead(CW_SPEED_PIN)*(MAX_DIT_TIME - MIN_DIT_TIME)/1023 + MIN_DIT_TIME;
//    t_delay = analogRead(CW_SPEED_PIN)/10 + MIN_DIT_TIME;
    // нажимаем "ключ"      
    digitalWrite(CW_OUT_PIN, HIGH);
    // включаем звуковой тон
    analogWrite(CW_SOUND_PIN, 128);
    // задержка длительности звука/нажатия ключа   
    if (digitalread(CW_DASH_PIN) == 0) dash_on = 1;   
    delay(t_delay);
    // выключаем звуковой тон      
    analogWrite(CW_SOUND_PIN, 0);
    // "отпускаем" ключ
    digitalWrite(CW_OUT_PIN, LOW);
    if (digitalread(CW_DASH_PIN) == 0) dash_on = 1;
    dit_on = 0;
    // выдерживаем паузу между точками/тире      
    delay(t_delay);
  }

//   обрабатываем нажатие манипулятора "тире"
  if(digitalRead(CW_DASH_PIN) == 0 || dash_on == 1) {
    // расчитываем длительность "точки" по положению потенциометра
    t_delay = analogRead(CW_SPEED_PIN)*(MAX_DIT_TIME - MIN_DIT_TIME)/1023 + MIN_DIT_TIME;
//    t_delay = analogRead(CW_SPEED_PIN)/10 + MIN_DIT_TIME;
    // нажимаем "ключ"      
    digitalWrite(CW_OUT_PIN, HIGH);
    // включаем звуковой тон
    analogWrite(CW_SOUND_PIN, 128);
    // задержка длительности звука/нажатия ключа      
    // так как у нас тут "тире", то длительность его в 3 раза больше, чем для точки
    if (digitalread(CW_DIT_PIN) == 0) dit_on = 1;  
    delay(t_delay*3);
    // выключаем звуковой тон      
    analogWrite(CW_SOUND_PIN, 0);
    // "отпускаем" ключ
    digitalWrite(CW_OUT_PIN, LOW);
    if (digitalread(CW_DIT_PIN) == 0) dit_on = 1;  
    dash_on = 0;
    // выдерживаем паузу между точками/тире      
    delay(t_delay);
  }
// конец основного цикла
}
