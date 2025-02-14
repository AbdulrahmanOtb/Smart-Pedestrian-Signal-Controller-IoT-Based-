#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>

/* Put WiFi SSID & Password */
const char* ssid = "AA";   // Enter your SSID here
const char* password = "AA112224"; // Enter your Password here

ESP8266WebServer server(80);
SoftwareSerial espSerial(2, 3); // RX, TX for ESP8266-01
bool SignalStatus = LOW;
unsigned long long lastSignalChangeTime = 0;

void setup() {
    Serial.begin(9600);
    delay(100);

    espSerial.begin(9600); // Begin SoftwareSerial for ESP8266

    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.on("/greensignal", handle_greensignal);
    server.on("/redsignal", handle_redsignal);
    server.onNotFound(handle_NotFound);

    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();
}

void handleRoot() {
      server.send(200, "text/html", updateWebpage(SignalStatus));
}

void handle_greensignal() {
    SignalStatus = HIGH;
    Serial.println("SIGNAL: GREEN");
    espSerial.print('G');
    server.send(200, "text/html", updateWebpage(SignalStatus));
}

void handle_redsignal() {
    SignalStatus = LOW;
    server.send(200, "text/html", updateWebpage(SignalStatus)); // Send content
}

void handle_NotFound(){
    server.send(404, "text/plain", "Not found");
}

String updateWebpage(uint8_t SignalStatus){
    String ptr = "<!DOCTYPE html> <html>\n";
    ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
    ptr +="<title>Pedestrian signal</title>\n";
    ptr +="<style>html {font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    ptr += "</head>\n";
    ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
    ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
    ptr +=".button-on {background-color: #00ff00;}\n";
    ptr +=".button-on:active {background-color: #00ff00;}\n";
    ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
    ptr += "#countdown {font-size: 24px; color: #ff0000; margin-top: 30px;}\n"; // Style for the countdown timer
    ptr += ".signal {font-size: 16px; font-family: Helvetica; color: inherit; margin-top: 10px; font-weight: bold;}\n"; // Style for signal message
    ptr += ".signal-red {color: #ff0000;}\n"; // Style for red signal message
    ptr += ".signal-green {color: #00ff00;}\n"; // Style for green signal message
    ptr +="</style>\n";
    ptr +="</head>\n";
    ptr +="<body>\n";
    ptr +="<h1>Pedestrian signal</h1>\n";
    ptr +="<h3>EE366 Project</h3>\n";
    
    if(SignalStatus){
        ptr +="<p class=\"signal-green\">SIGNAL: GREEN</p>";
    }else{
        ptr +="<p class=\"signal-red\">SIGNAL: RED</p><a class=\"button button-on\" href=\"/greensignal\">START</a>\n";
    }

if (SignalStatus) {
        ptr += "<p id=\"countdown\"></p>\n"; // Countdown display
        ptr += "<script>\n";
        ptr += "var countdown = 20;\n";
        ptr += "var countdownElement = document.getElementById('countdown');\n";
        ptr += "function updateCountdown() {\n";
        ptr += "    countdownElement.innerHTML = 'Time remaining: ' + countdown + ' seconds';\n";
        ptr += "    if (countdown > 0) {\n";
        ptr += "        countdown--;\n";
        ptr += "        setTimeout(updateCountdown, 1000);\n";
        ptr += "    } else {\n";
        ptr += "        window.location.replace('/redsignal');\n";
        ptr += "    }\n";
        ptr += "}\n";
        ptr += "setTimeout(function() {\n";
        ptr += "    updateCountdown();\n";
        ptr += "}, 7000); // 7-second delay before starting the countdown\n";
        ptr += "</script>\n";
    }

    ptr +="</body>\n";
    ptr +="</html>\n";
    return ptr;
}
