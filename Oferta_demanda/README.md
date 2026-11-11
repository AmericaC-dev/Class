# Nombre del proyecto
Simulador de oferta y demanda

## Descripción
“Simulador de oferta y demanda con potenciómetros” es un sistema IoT que convierte un fenómeno económico en datos y alertas. Un potenciómetro representa la demanda de camarón (conectado a A0) y el otro la oferta (conectado a A1). El Arduino lee ambos valores, los escala de 10 a 90, calcula el precio de equilibrio con un modelo lineal, lo muestra en su matriz LED y, cuando detecta escasez, envía los datos a un webhook de Make, que manda una alerta al bot de Telegram “Mercado Equipo”.

## Objetivos de aprendizaje
Que el alumno explique cómo la oferta y la demanda fijan los precios, relacione la escasez de un
recurso natural con su precio, y construya un sistema IoT que convierta un fenómeno económico en
datos y alertas automáticas.

## Material utilizado
Enumera todos los componentes usados:
• Arduino UNO R4 WiFi con su cable USB-C.
• 2 potenciómetros de 10 kΩ, protoboard y cables jumper.
• Computadora con Arduino IDE y las librerías ArduinoGraphics y Arduino_LED_Matrix (la
segunda viene con el paquete de la placa UNO R4).
• Red WiFi de 2.4 GHz con usuario y contraseña (no funciona con redes que piden iniciar
sesión en una página).
• Cuenta de Make del curso y Telegram en el celular.
   
  
## Código
[Mercado_Equipo.blueprint.json](<Codigo/Mercado_Equipo.blueprint.json>)

## Imagenes
Foto del diagrama Make

<img src="Imagenes/foto_make_mercado.png" width="300">

Foto Telegram

<img src="Imagenes/foto_telegram_mercado.png" width="300">

Foto armado

<img src="Imagenes/foto_armado_make.jpeg" width="300">

Foto Arduino IDE

<img src="Imagenes/foto_arduinoIDE_mercado.png" width="300">


[Investigacion](Imagenes/Act1_oferta_demanda.pdf)

## Resultados
Incluye:
[Resultados](Resultados/Resultado_Simulador_Oferta_Demanda.pdf)


## Video del funcionamiento
[Readme](Video/readme.txt)

[Ver video en YouTube](https://youtube.com/shorts/cO8YILxc75o)



## Conclusiones
La práctica cumple su objetivo: se construyó un simulador que convierte la oferta y la demanda de un kilo de camarón en un precio de equilibrio y avisa por Telegram cuando hay escasez. En los cinco escenarios, el precio subió en la veda, en Semana Santa y con el huracán, que son los casos en que la demanda superó a la oferta, y bajó con la sobreproducción de granjas. Esto muestra que el precio responde a la escasez, aunque el producto sea el mismo. El modelo es una simplificación y no considera factores reales como el clima, los costos, las importaciones ni el costo ambiental, pero permitió entender cómo funciona el mercado y cómo la automatización ayuda a un productor o a una cooperativa a reaccionar a tiempo.
