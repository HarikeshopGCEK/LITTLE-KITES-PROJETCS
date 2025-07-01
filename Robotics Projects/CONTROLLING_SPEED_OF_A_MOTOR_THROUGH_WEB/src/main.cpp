#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define ENA D4
#define ENB D5
#define M1 D6
#define M2 D7

ESP8266WebServer server(80);
const char *ssid = "your_SSID";
const char *password = "your_PASSWORD";
// ...existing code...

void handleRoot()
{
    String html = R"rawliteral(
        <!DOCTYPE html>
        <html>
        <head>
            <title>Motor Speed Control</title>
        </head>
        <body>
            <h2>Motor Speed Control</h2>
            <input type="range" min="0" max="255" value="0" id="speedSlider" oninput="updateSpeed(this.value)">
            <span id="speedValue">0</span>
            <script>
                function updateSpeed(val) {
                    document.getElementById('speedValue').innerText = val;
                    var xhr = new XMLHttpRequest();
                    xhr.open("GET", "/set_speed?speed=" + val, true);
                    xhr.send();
                }
            </script>
        </body>
        </html>
    )rawliteral";
    server.send(200, "text/html", html);
}

void setup()
{
    Serial.begin(115200);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(M1, OUTPUT);
    pinMode(M2, OUTPUT);

    digitalWrite(M1, LOW);
    digitalWrite(M2, LOW);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    server.on("/", HTTP_GET, handleRoot);

    server.on("/set_speed", HTTP_GET, []()
              {
        if (server.hasArg("speed")) {
            int speed = server.arg("speed").toInt();
            digitalWrite(M1, speed > 0 ? HIGH : LOW);
            digitalWrite(M2, speed > 0 ? LOW : HIGH);
            analogWrite(ENA, speed);
            analogWrite(ENB, speed);
            server.send(200, "text/plain", "Speed set to " + String(speed));
        } else {
            server.send(400, "text/plain", "Speed parameter missing");
        } });

    server.begin();
}

void loop()
{
    server.handleClient();
    // Remove the example speed control code below if you only want web control
    // static int speed = 0;
    // if (speed < 255)
    // {
    //     speed += 5; // Increase speed
    //     analogWrite(ENA, speed);
    //     analogWrite(ENB, speed);
    //     delay(1000); // Wait for a second
    // }
    // else
    // {
    //     speed = 0; // Reset speed
    // }
}
// ...existing code...