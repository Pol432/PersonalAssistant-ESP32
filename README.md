# Marcación de la aplicación 
## Inicialización de PLATFORMIO
#### Se debe ingresar a Visual studio code y a partir de ahí entrar a la pestaña de librerías y descargar la perteneciente a **PLATFORMIO** 
1. Entrar a la librería 
2. Buscar PlatformIO en el buscador 
3. Selecciona el PlatformIO IDE
4. Instalar 
![descarga de la librería de PLATFORMIO](https://docs.simplefoc.com/extras/Images/platformio_screenshot1.png)

#### Posteriormente ingresar en el icono del alien a la izquierda abrir PLatformIO y abrir un nuevo proyecto 
1. Entrar a PlatformIO
2. Abrir el programa
3. Abrir un proyecto 
![descarga de la librería de PLATFORMIO](/imagenes/2.png)

#### Al abrir un nuevo proyecto buscar el que se llama ESP32-AI-BLE y abrirlo 
![descarga de la librería de PLATFORMIO](/imagenes/3.png)

#### Una vez abierto el archivo seleccionar **Open "ESP32-AI-BLE"**
![descarga de la librería de PLATFORMIO](/imagenes/4.png)

#### Aparecerá lo siguiente a la derecha
![descarga de la librería de PLATFORMIO](/imagenes/5.png)

#### Solo se debe modificar el src, después se abrirá **Program** y a partir de ahí se debe modificar el DeviceConfig.cpp
![descarga de la librería de PLATFORMIO](/imagenes/6.png)

#### Se abrirá el siguiente código
![descarga de la librería de PLATFORMIO](/imagenes/7.png)

#### Solo se debe tener en cuenta 3 líneas de código para editar en la pestaña  

1. `String DeviceConfigName = "cortina";` En esta línea se debe poner el nombre que se quiere colocar al nuevo dispositivo colocado. 

2. `int DeviceConfigStatesNumber = 1;` En esta linea solo se debe poner el número de campos que puede tener el dispositivo.

3. `// myDevice.createState` 

`myDevice.createState(1, "status", "TEXT", "open", "power");`
#### A continuación se explica a que se refiere con cada uno de las palabras definidas en la línea de código anterior 

1. **StateID:** El estado que tiene el dispositivo, este debe iniciar en uno y que vaya avanzando en orden 
2. **FieldName:** Asignarle un nombre al campo 
3. **FieldType:** Colocar a que tipo de dato pertenece se es texto (TEXT) y si es un numero (FLOAT) 
4. **DefaultValue:** Con que estado va a empezar el dispositivo

#### Posteriormente entrar a la pestaña **Main.cpp** 
![descarga de la librería de PLATFORMIO](/imagenes/8.png)

#### Al abrirse el codigo no modificar nada de las 4 primeras líneas de código
![descarga de la librería de PLATFORMIO](/imagenes/9.png)

#### En esta pestaña se debe ingresar tu código dentro del Void ProgramSetup y del Void ProgramLoop
![descarga de la librería de PLATFORMIO](/imagenes/10.png)

#### Para poder programar en esta PlatformIO se debe tener en cuenta 3 instrucciones 

1. **myDevice.getTextField:** sirve para conseguir un campo de texto que haya especificado en el DeviceConfig
2. **myDevice.getFloatField:** sirve para conseguir un campo de números que haya especificado en el DeviceConfig
3. **myDevice.changeField:** sirve para cambiar un campo, se especifica el nombre del campo y el nuevo valor 
