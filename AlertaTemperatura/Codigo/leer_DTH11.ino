#include <WiFiS3.h>
#include <WiFiSSLClient.h>
#include <DHT.h>

#define DHT_PIN 2
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

const char* ssid = "INFINITUM5C58";      // debe ser red de 2.4 GHz
const char* password = "Nba9hX7Nf5";
const char* host = "hook.eu1.make.com";      // igual que tu URL del webhook
const char* webhookPath = "/v8ecjesiiddgkkyqv3kzxjfvrf7d99tg";  // parte despues del dominio

const int ledPin = 13;
const float UMBRAL_TEMP = 27.0;              // grados Celsius

bool estadoCaliente = false;
float ultimaTemp = 0;
float ultimaHum = 0;
unsigned long ultimaLectura = 0;
const unsigned long INTERVALO_LECTURA = 2000;

WiFiServer server(80);
WiFiSSLClient client;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  while (WiFi.localIP() == IPAddress(0, 0, 0, 0)) {
    delay(500);
    Serial.print("*");
  }
  Serial.println();
  Serial.print("Servidor listo en: http://");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  if (millis() - ultimaLectura >= INTERVALO_LECTURA) {
    ultimaLectura = millis();
    leerYEvaluar();
  }

  WiFiClient webClient = server.available();
  if (webClient) {
    while (webClient.connected() && webClient.available()) {
      char c = webClient.read();
      if (c == '\n') break;
    }
    enviarPagina(webClient);
    webClient.stop();
  }
}

void leerYEvaluar() {
  float temperatura = dht.readTemperature();   // en Celsius
  float humedad = dht.readHumidity();

  if (isnan(temperatura) || isnan(humedad)) {
    Serial.println("Error: sensor DHT11 no detectado (revisa cableado y resistencia)");
    return;
  }

  ultimaTemp = temperatura;
  ultimaHum = humedad;

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print(" *C  |  Humedad: ");
  Serial.print(humedad);
  Serial.println(" %");

  bool estaCalienteAhora = (temperatura >= UMBRAL_TEMP);
  digitalWrite(ledPin, estaCalienteAhora ? HIGH : LOW);

  if (estaCalienteAhora && !estadoCaliente) {
    enviarAlertaMake(temperatura, humedad);
  }
  estadoCaliente = estaCalienteAhora;
}

void enviarPagina(WiFiClient &webClient) {
  webClient.println("HTTP/1.1 200 OK");
  webClient.println("Content-Type: text/html");
  webClient.println("Connection: close");
  webClient.println();
  webClient.println("<!DOCTYPE html><html><head>");
  webClient.println("<meta name='viewport' content=");
  webClient.println("'width=device-width, initial-scale=1'>");
  webClient.println("<meta http-equiv='refresh' content='5'>");
  webClient.println("<style>");
  webClient.println("body{font-family:sans-serif;text-align:center;}");
  webClient.println("body{margin-top:50px;}");
  webClient.println("h1{font-size:28px;}");
  webClient.println(".valor{font-size:48px;font-weight:bold;}");
  webClient.println("</style></head><body>");
  webClient.println("<h1>Monitor del cuarto</h1>");
  webClient.print("<p>Temperatura</p><p class='valor'>");
  webClient.print(ultimaTemp);
  webClient.println(" &deg;C</p>");
  webClient.print("<p>Humedad</p><p class='valor'>");
  webClient.print(ultimaHum);
  webClient.println(" %</p>");
  webClient.print("<p>Estado: <b>");
  webClient.print(estadoCaliente ? "CALIENTE (LED encendido)" : "Normal");
  webClient.println("</b></p>");
  webClient.println("</body></html>");
}

void enviarAlertaMake(float temp, float hum) {
  if (client.connect(host, 443)) {
    String jsonPayload = "{\"temperatura\":" + String(temp) +
                         ",\"humedad\":" + String(hum) + "}";
    client.println("POST " + String(webhookPath) + " HTTP/1.1");
    client.println("Host: " + String(host));
    client.println("Content-Type: application/json");
    client.println("Content-Length: " + String(jsonPayload.length()));
    client.println("Connection: close");
    client.println();
    client.print(jsonPayload);
    Serial.println("Alerta enviada a Make");
  } else {
    Serial.println("Fallo la conexion al webhook");
  }
  client.stop();
}