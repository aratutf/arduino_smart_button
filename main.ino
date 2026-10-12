int button_pin = 3;
int led_blue = 4;
int led_red = 5;
int led_green = 6;
int led_yellow = 7;

unsigned long int first_time;
unsigned long int start_time;
unsigned long int second_time;
unsigned long int total_time;
unsigned long int led_blue_time;
unsigned long int led_red_time;
unsigned long int led_green_time;
unsigned long int led_yellow_time;
unsigned long int last_click_time;
int click_count = 0;

bool before;
bool before_2;
bool current_time;
bool previous_time;
bool led_red_on;
bool led_green_on;
bool led_blue_on;
bool led_yellow_on;


void setup()
{
  Serial.begin(9600);
  pinMode(button_pin, INPUT_PULLUP);
  pinMode(led_blue, OUTPUT);
  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(led_yellow, OUTPUT);


current_time = digitalRead(button_pin);
previous_time = current_time;
}


enum State
{
  WAIT_PRESS,
  DEBOUNCE_PRESS,
  PRESSED,
  DEBOUNCE_RELEASE,
  WAIT_SECOND_CLICK,
  ACTION
};

State state = WAIT_PRESS;


void loop()
{

current_time = digitalRead(button_pin);
 switch(state)
{
  

  case WAIT_PRESS:
 if(current_time == 0 && previous_time == 1)
 {
  first_time = millis();
  before = digitalRead(button_pin);
  state = DEBOUNCE_PRESS;
 } 
 break;

  case DEBOUNCE_PRESS:
  if(millis() - first_time >=20 && before == digitalRead(button_pin) && click_count == 0 )
  {
    start_time = millis();
    state = PRESSED;
  }
  if(millis() - first_time >= 20 && before == digitalRead(button_pin) && click_count >= 1 )
  {
    state = PRESSED;
  }

  break;

case PRESSED:
 if( current_time == 1 && previous_time == 0)
 {
  second_time = millis();
  before_2 = digitalRead(button_pin);
  state = DEBOUNCE_RELEASE;
 }
 break;

case DEBOUNCE_RELEASE:
 if( millis() - second_time >= 20 && before_2 == digitalRead(button_pin) )
 {
  total_time = millis() - start_time;
   if( click_count == 0)
   {
    last_click_time = millis();
   }
  click_count++;
  state = WAIT_SECOND_CLICK;
 } 
 break;

 case WAIT_SECOND_CLICK:
 if(current_time == 0 && previous_time == 1 )
 {

  first_time = millis();
  before = digitalRead(button_pin);
  state = DEBOUNCE_PRESS;
 }
 if( millis() - last_click_time > 300 )
 {
  state = ACTION;
 }
break;


case ACTION:

if(click_count == 1)
{
    Serial.print("TOTAL TIME = ");
    Serial.println(total_time);
}

if(total_time >= 50 && total_time < 300 && click_count == 1 && led_red_on == false)
 {
  Serial.println(" short CLICK");
  digitalWrite(led_red, HIGH);
  led_red_time = millis();
  led_red_on = true;
 }



if( click_count == 2 && led_yellow_on == false)
{
  Serial.println("double click");
  digitalWrite(led_yellow, HIGH);
  led_yellow_time = millis();
  led_yellow_on = true;
}



if( total_time > 300 && total_time <= 700 && click_count == 1 && led_green_on == false)
{
  Serial.println("long click");
  digitalWrite(led_green, HIGH);
  led_green_time = millis();
  led_green_on = true;
}



if(total_time > 700 && click_count == 1 && led_blue_on == false)
{
  Serial.println(" retention ");
  digitalWrite(led_blue, HIGH);
  led_blue_time = millis();
  led_blue_on = true;
}


state = WAIT_PRESS;
click_count = 0;


} 

if(millis() - led_red_time >= 100 && led_red_on == true)
{
  digitalWrite(led_red, LOW);
  led_red_on = false;
}

if(millis() - led_yellow_time >= 100 && led_yellow_on == true)
{
  digitalWrite(led_yellow, LOW);
  led_yellow_on = false;
}

if(millis() - led_green_time >= 100 && led_green_on == true)
{
  digitalWrite(led_green, LOW);
  led_green_on = false;
}

if(millis() - led_blue_time >= 5000 && led_blue_on == true)
{
  digitalWrite(led_blue, LOW);
  led_blue_on = false;
}


previous_time = current_time;

}
