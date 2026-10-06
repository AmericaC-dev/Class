# Nombre del proyecto
Resultado de práctica "Monitor de humedad del suelo"

## Descripción
El sistema está formado por una placa Arduino UNO R4 WiFi, un sensor de humedad de suelo conectado a la entrada analógica A0 (alimentado con 5V y GND) y un LED conectado al pin 13 como alerta de riego. El programa lee el sensor cada segundo, convierte la lectura a un porcentaje de humedad entre 0 y 100 y la muestra en el Monitor Serie. Si el porcentaje es menor al umbral establecido (40%), imprime que la tierra está seca y se recomienda regar, y enciende el LED. Si es igual o mayor, indica que la tierra está húmeda y mantiene el LED apagado. (Aquí inserta la imagen del diagrama del circuito.)

## Objetivos de aprendizaje
Diseñar y probar un sistema con Arduino UNO R4 WiFi que, mediante un sensor de humedad, mida el nivel de humedad del suelo, lo convierta a porcentaje y active un LED de alerta cuando la tierra esté seca, para saber cuándo es necesario regar y apoyar el uso responsable del agua.

## Material utilizado
Enumera todos los componentes usados:
1. Arduino R4 Wifi
2. Cables Dupont
3. Protoboard
4. Led
5. Resistencia
6. Arduino IDE
7. Sensor de temperatura
  
## Código
[led_sensor.ino](<Codigo/led_sensor.ino>)


## Imagenes
<img src="Imagenes/foto_armado_sensor.jpeg" width="300">
<img src="Imagenes/foto_tinkercad.png" width="300">

## Resultados
Incluye:
[Resultado_Sensor.pdf](Resultados/Resultado_Sensor.pdf)


## Video del funcionamiento
[Readme](Video/readme.txt)

[Ver video en YouTube](https://youtu.be/SdyI0Don540)



## Conclusiones
La práctica cumplió su objetivo: el sistema detectó la diferencia entre el sensor seco y el sensor en agua, y respondió con el LED de alerta, que se encendió cuando faltaba humedad y se apagó cuando la había. Es una herramienta sencilla pero útil para saber cuándo regar y evitar el desperdicio de agua, aunque para un uso real conviene calibrar el sensor según el tipo de suelo.
