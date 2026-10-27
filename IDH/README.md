# Nombre del proyecto
Página web IDH de mi estado
## Descripción
“IDH de mi estado” es una página web de un solo archivo HTML con una lista desplegable de las 32 entidades federativas y un botón “Consultar”. Al presionarlo, envía la entidad elegida con el método POST, como formulario con un solo campo llamado “entidad”, a un webhook de Make. En el escenario, un Make AI Agent que tiene como conocimiento el archivo IDH_entidades.pdf responde en texto plano con el IDH, los índices de salud, educación e ingreso, el lugar nacional, el año de los datos y una breve interpretación; después, un módulo Webhook Response devuelve ese texto a la página, que lo muestra en un recuadro.
Los datos provienen del informe del PNUD “Índice de Desarrollo Humano para las entidades federativas, México 2015” y corresponden al año 2012.

## Objetivos de aprendizaje
Interpretar el Índice de Desarrollo Humano (IDH) y sus componentes para las entidades de México, construir sin programar una página web conectada a Make y a un agente de IA que consulte datos oficiales del PNUD, y verificar que la información que genera la IA sea fiel a la fuente.

## Material utilizado
Enumera todos los componentes usados:
1. Make
   
  
## Código
[Buzon ambiental.blueprint.json](<Codigo/Buzon ambiental.blueprint.json>)


## Imagenes
Foto del diagrama Make

<img src="Imagenes/make_buzon_foto.png" width="300">

Foto Bot Telegram

<img src="Imagenes/telegram_buzon_foto.png" width="300">

Foto Google sheets

<img src="Imagenes/Google_sheets_buzon_foto.png" width="300">

Foto act. 1

<img src="Imagenes/act1_foto_buzon.png" width="300">

## Resultados
Incluye:
[Resultados](Resultados/Resultado_Buzon_Ciudadano.pdf)


## Video del funcionamiento
[Readme](Video/readme.txt)

[Ver video en YouTube](https://youtu.be/dlbZfRPe83c)



## Conclusiones
La práctica cumple su objetivo: se construyó un buzón ciudadano automatizado que registra reportes ambientales con folio, fecha y usuario, y que responde al ciudadano con un comprobante. Al compararlo con los sistemas oficiales se identificó que su principal limitación es que no cuenta con una autoridad que lo atienda ni con plazos de respuesta, lo que muestra que la tecnología facilita la participación, pero no sustituye la responsabilidad de las instituciones.

