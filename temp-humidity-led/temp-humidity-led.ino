//www.elegoo.com
//2018.10.25

#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11
#define BLUE 3 
#define GREEN 5 
#define RED 6

static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );
int redValue;
int greenValue;
int blueValue;

/*
 * Initialize the serial port.
 */
void setup( )
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  Serial.begin( 9600);
}

/*
 * Poll for a measurement, keeping the state machine alive.  Returns
 * true if a measurement is available.
 */
static bool measure_environment( float *temperature, float *humidity ){
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 3000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}


void loop( ){
  float temperature;
  float humidity;

  /* Measure temperature and humidity.  If the functions returns
     true, then a measurement is available. */
  if( measure_environment( &temperature, &humidity ) == true )
  {
    Serial.print( "T = " );
    Serial.print( temperature, 1 );
    Serial.print( " deg. C, H = " );
    Serial.print( humidity, 1 );
    Serial.println( "%" );
    
    setColor(humidity);
  }
}

void setColor( float humidity ){
  int humidityValue = (int)humidity;
  
  if(humidityValue >= 60){ //INDIGO
    redValue = 67; 
    greenValue = 22;
    blueValue = 201;    
  }else if(humidityValue >= 50 < 60){ //blue
    redValue = 22; 
    greenValue = 112;
    blueValue = 201;
  }else if(humidityValue >= 40 < 50){ //green
    redValue = 22; 
    greenValue = 201;
    blueValue = 64;
  }else if(humidityValue >= 30 < 40){ //yellow
    redValue = 247;
    greenValue = 232;
    blueValue = 17;
  }
  
  Serial.print( "RED value = " );
  Serial.print( redValue, 1 );
  Serial.print( " , greenValue = " );
  Serial.print( greenValue, 1 );
  Serial.println( " , blueValue = " );
  Serial.print( blueValue, 1 );
  Serial.println( " , humidityValue = " );
  Serial.print( humidityValue, 1 );
    
  analogWrite(RED, redValue);
  analogWrite(BLUE, blueValue);
  analogWrite(GREEN, greenValue);
  delay(10);
}
