const int cantidadPines = 10;
const int pinLED[cantidadPines] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4};
const int pinBoton = 2;

const int cantidadEfectos = 3;
int efectoActual = 0;

// --- Variables para debounce del botón ---
bool estadoBotonAnterior = HIGH;
unsigned long ultimoRebote = 0;
const unsigned long tiempoRebote = 50;

// --- Variables del Efecto 1: Parpadeo independiente ---
const long intervaloParpadeo[cantidadPines] = {200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100};
unsigned long ultimoCambioParpadeo[cantidadPines] = {0};
bool estadoLEDParpadeo[cantidadPines] = {false};

// --- Variables del Efecto 2: Knight Rider ---
const long intervaloKnightRider = 150;
unsigned long ultimoCambioKnightRider = 0;
int posicionKnightRider = 0;
int direccionKnightRider = 1;

// --- Variables del Efecto 3: Cometa con chispas ---
int brillo[cantidadPines] = {0};
const int desvanecimiento = 45;
const long intervaloCometa = 80;
unsigned long ultimoCambioCometa = 0;
int posicionCometa = 0;
int direccionCometa = 1;
unsigned long cicloPWM = 0;
const int resolucionPWM = 256;

void setup() {
  for (int i = 0; i < cantidadPines; i++) {
    pinMode(pinLED[i], OUTPUT);
  }
  pinMode(pinBoton, INPUT_PULLUP);
  randomSeed(analogRead(A0));
}

void loop() {
  revisarBoton();

  switch (efectoActual) {
    case 0: efectoParpadeoIndependiente(); break;
    case 1: efectoKnightRider(); break;
    case 2: efectoCometa(); break;
  }
}

// ================== BOTÓN ==================
void revisarBoton() {
  bool lectura = digitalRead(pinBoton);

  // Detecta flanco de bajada (botón presionado) con debounce
  if (lectura == LOW && estadoBotonAnterior == HIGH &&
      (millis() - ultimoRebote) > tiempoRebote) {
    ultimoRebote = millis();
    cambiarEfecto();
  }
  estadoBotonAnterior = lectura;
}

void cambiarEfecto() {
  efectoActual = (efectoActual + 1) % cantidadEfectos;
  apagarTodos();
  reiniciarVariablesEfecto();
}

void apagarTodos() {
  for (int i = 0; i < cantidadPines; i++) {
    digitalWrite(pinLED[i], LOW);
  }
}

// Reinicia variables para que cada efecto siempre empiece "limpio"
void reiniciarVariablesEfecto() {
  for (int i = 0; i < cantidadPines; i++) {
    estadoLEDParpadeo[i] = false;
    ultimoCambioParpadeo[i] = 0;
    brillo[i] = 0;
  }
  posicionKnightRider = 0;
  direccionKnightRider = 1;
  posicionCometa = 0;
  direccionCometa = 1;
}

// ================== EFECTO 1: Parpadeo independiente ==================
void efectoParpadeoIndependiente() {
  unsigned long tiempoActual = millis();
  for (int i = 0; i < cantidadPines; i++) {
    if (tiempoActual - ultimoCambioParpadeo[i] >= intervaloParpadeo[i]) {
      ultimoCambioParpadeo[i] = tiempoActual;
      estadoLEDParpadeo[i] = !estadoLEDParpadeo[i];
      digitalWrite(pinLED[i], estadoLEDParpadeo[i] ? HIGH : LOW);
    }
  }
}

// ================== EFECTO 2: Knight Rider ==================
void efectoKnightRider() {
  unsigned long tiempoActual = millis();
  if (tiempoActual - ultimoCambioKnightRider >= intervaloKnightRider) {
    ultimoCambioKnightRider = tiempoActual;

    apagarTodos();
    digitalWrite(pinLED[posicionKnightRider], HIGH);

    posicionKnightRider += direccionKnightRider;
    if (posicionKnightRider == cantidadPines - 1 || posicionKnightRider == 0) {
      direccionKnightRider = -direccionKnightRider;
    }
  }
}

// ================== EFECTO 3: Cometa con chispas ==================
void efectoCometa() {
  unsigned long tiempoActual = millis();

  if (tiempoActual - ultimoCambioCometa >= intervaloCometa) {
    ultimoCambioCometa = tiempoActual;

    for (int i = 0; i < cantidadPines; i++) {
      brillo[i] = max(0, brillo[i] - desvanecimiento);
    }
    brillo[posicionCometa] = 255;

    if (random(0, 10) == 0) {
      int chispa = random(0, cantidadPines);
      brillo[chispa] = random(80, 180);
    }

    posicionCometa += direccionCometa;
    if (posicionCometa == cantidadPines - 1 || posicionCometa == 0) {
      direccionCometa = -direccionCometa;
    }
  }

  // PWM por software para este efecto
  cicloPWM = (cicloPWM + 1) % resolucionPWM;
  for (int i = 0; i < cantidadPines; i++) {
    digitalWrite(pinLED[i], cicloPWM < brillo[i] ? HIGH : LOW);
  }
}
