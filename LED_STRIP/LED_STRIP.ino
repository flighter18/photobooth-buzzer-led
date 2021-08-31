 /*
 * ESP8266 LED STRIPE for Photobooth > https://github.com/andi34/photobooth
 * Raphael Schib (https://github.com/flighter18)
 */


#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    D4

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 94

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// ADD SSID AND PASSWORD!!!!
// *****************************
const char* ssid = "";
const char* password = "";
 
int ledPin = D5;

WiFiServer server(80);
IPAddress ip(x,x,x,x); // where xx is the desired IP Address
IPAddress gateway(255, 255, 255, 0); // set gateway to match your network
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  Serial.print(F("Setting static ip to : "));
  Serial.println(ip);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your network
  WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

   //LED STRIP
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
   #endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(150); // Set BRIGHTNESS to about 1/5 (max = 255)
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/COUNTDOWN") != -1) {
  Serial.println("COUNTDOWN");
   countdown(strip.Color(255,   255,   255), 1000); // Red
  } 
  if (request.indexOf("/BACK") != -1) {
    Serial.println("BACK");
   back(strip.Color(0,   0,   0), 1000); // Red
  } 
  if (request.indexOf("/THREE") != -1) {
    Serial.println("BACKTHREE");
   backthree(strip.Color(0,   0,   0), 1000); // Red
  } 
    if (request.indexOf("/TWO") != -1) {
    Serial.println("TWO");
   backtwo(strip.Color(0,   0,   0), 1000); // Red
  } 
  if (request.indexOf("/COLLAGE") != -1){
    Serial.println("COLLAGE");
   
   theaterChaseRainbow(30);
  }
    if (request.indexOf("/PIC") != -1){
    Serial.println("PIC");
   rainbow(4);
  }
 
 
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.println("<br><br>");
  client.println("Click <a href=\"/COUNTDOWN\">here</a> to start the countdown<br>");
  client.println("Click <a href=\"/BACK\">here</a> to start the countdownback<br>");
  client.println("Click <a href=\"/THREE\">here</a> to start the countdownback<br>");
  client.println("Click <a href=\"/TWO\">here</a> to start the countdownback<br>");
  client.println("Click <a href=\"/COLLAGE\">here</a> to start collage<br>");
  client.println("Click <a href=\"/PIC\">here</a> to start pic<br>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void countdown(uint32_t color, int wait){
  
  strip.clear();
  int p=83;
  
  for(int i=2;i<strip.numPixels();) { // For each pixel in strip...
    strip.fill(color,i,9);
    strip.fill(color,p,9);
    strip.show(); //  Update strip to match
    if (i>=47){
      delay(100);
      break;
    }
      
    p = p - 9; //  Pause for a moment
    i = i + 9;
    delay(wait);
  } 
  stripClear();
}


void back(uint32_t color, int wait){

  strip.fill(strip.Color(255,   255,   255),2,90);
  strip.show();
  delay(1000);
  
  int p=38;
 
  for(int i=47;i<strip.numPixels();) { // For each pixel in strip...
    strip.fill(color,i,9);
    strip.fill(color,p,9);

    strip.show();                          //  Update strip to match
    if (i>=76){
      delay(100);
      break;
    }

    p = p - 9; 
    i = i + 9;
    delay(wait); 
  } 
  stripClear();
  
}

void backthree(uint32_t color, int wait){

  strip.fill(strip.Color(255,   255,   255),2,90);
  strip.show();
  delay(1000);
  
  int p=32;
 
  for(int i=47;i<strip.numPixels();) { // For each pixel in strip...
    strip.fill(color,i,15);
    strip.fill(color,p,15);

    strip.show();                          //  Update strip to match
    if (i>=76){
      delay(100);
      break;
    }

    p = p - 15; 
    i = i + 15;
    delay(wait); 
  } 
  stripClear();
  
}

void backtwo(uint32_t color, int wait){

  strip.fill(strip.Color(255,   255,   255),2,91);
  strip.show();
  delay(1000);
  
  int p=24;
 
  for(int i=47;i<strip.numPixels();) { // For each pixel in strip...
    strip.fill(color,i,23);
    strip.fill(color,p,23);

    strip.show();                          //  Update strip to match
    if (i>=70){
      delay(100);
      break;
    }

    p = p - 23; 
    i = i + 23;
    delay(wait); 
    Serial.println(p);
    Serial.println(i);
  } 
  stripClear();
  
}

void rainbow(int wait) {
   strip.clear();
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 1*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
  stripClear();
}

void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<20; a++) {  // Repeat 20 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
  stripClear();
}


void stripClear() {
  for (int ii = 0; ii < strip.numPixels(); ++ii) {  
    strip.setPixelColor(ii, 0, 0, 0);  
  }
  strip.show();
}
  
