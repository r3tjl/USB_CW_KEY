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

void loop() {
  
// обрабатываем нажатие манипулятора "точка"
  if(digitalRead(CW_DIT_PIN) == 0) {
    // расчитываем длительность "точки" по положению потенциометра
    t_delay = analogRead(CW_SPEED_PIN)*(MAX_DIT_TIME - MIN_DIT_TIME)/1023 + MIN_DIT_TIME;
//    t_delay = analogRead(CW_SPEED_PIN)/10 + MIN_DIT_TIME;
    // нажимаем "ключ"      
    digitalWrite(CW_OUT_PIN, HIGH);
    // включаем звуковой тон
    analogWrite(CW_SOUND_PIN, 128);
    // задержка длительности звука/нажатия ключа      
    delay(t_delay);
    // выключаем звуковой тон      
    analogWrite(CW_SOUND_PIN, 0);
    // "отпускаем" ключ
    digitalWrite(CW_OUT_PIN, LOW);
    // выдерживаем паузу между точками/тире      
    delay(t_delay);
  }

//   обрабатываем нажатие манипулятора "тире"
  if(digitalRead(CW_DASH_PIN) == 0) {
    // расчитываем длительность "точки" по положению потенциометра
    t_delay = analogRead(CW_SPEED_PIN)*(MAX_DIT_TIME - MIN_DIT_TIME)/1023 + MIN_DIT_TIME;
//    t_delay = analogRead(CW_SPEED_PIN)/10 + MIN_DIT_TIME;
    // нажимаем "ключ"      
    digitalWrite(CW_OUT_PIN, HIGH);
    // включаем звуковой тон
    analogWrite(CW_SOUND_PIN, 128);
    // задержка длительности звука/нажатия ключа      
    // так как у нас тут "тире", то длительность его в 3 раза больше, чем для точки
    delay(t_delay*3);
    // выключаем звуковой тон      
    analogWrite(CW_SOUND_PIN, 0);
    // "отпускаем" ключ
    digitalWrite(CW_OUT_PIN, LOW);
    // выдерживаем паузу между точками/тире      
    delay(t_delay);
  }
// конец основного цикла
}
