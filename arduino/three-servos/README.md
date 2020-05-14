# Three Servos
This is a very basic example which will collect the most recent message sent to you and translate the three three variables (x, y and z) within to motion (using three servo motors).

## Components
* 1 x [WeMos D1 R2](https://hobbycomponents.com/development-boards/863-wemos-d1-r2-esp8266-development-board)
* 1 x [Breadboard](https://hobbycomponents.com/prototyping/118-breadboard-830-point-solderless-pcb-bread-board-mb-102-mb102-test-development-diy)
* 1 x [Pack of Jumper wires](https://hobbycomponents.com/cables/183-20cm-male-to-male-solderless-dupont-jumper-wires-40-cable-pack)
* 3 x [SG-90 Servos](https://hobbycomponents.com/motors-and-servos/130-sg90-micro-servo-9g)

## Prerequisites 
Follow the links below to find instructions on how to install the prerequisite software and libraries.

1. Install Arduino software for [Windows](https://www.arduino.cc/en/Guide/Windows) | [MacOS](https://www.arduino.cc/en/Guide/MacOSX) | [Linux](https://www.arduino.cc/en/Guide/Linux). This is a tool to edit and upload code to Arduino compatible devices.
2. [Add the  CH340G drivers to your machine](https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all). This is software to support communication between your WeMos D1 and computer. 
3. [Add the Wemos library to the Arduino software](https://elementztechblog.wordpress.com/2016/10/14/programming-esp8266-wemos-d1-r2-using-arduino-ide/). A library of code to make your code simpler.
4. [Add the ArduinoJSON library](https://arduinojson.org/v6/doc/installation/). Another library, this one is used to decode messages from JSON format to variables in your code.
5. Register for an account at [Sobots Web App](https://sobots.xyz)

## Connecting Up
Wire up your components as below.

![Circuit Diagram](assets/circuit.png)

## Upload the Code

1. Open the Arduino Software
2. Copy the code from the `three-servos.ino` to the editor and make the following changes:
    1. Add your token to the `String TOKEN = "";`. The token can be found on the Bots page of the [Sobots Web App](https://sobots.xyz)
    2. Add your Wifi networks name to `WIFI_NAME`
    3. Add your Wifi networks password to `WIFI_PASS`
3. In the Arduino main menu select the port your WeMos board is connected to
4. Then set the board type to: `LOLIN(WEMOS) D1 R2 & mini`
5. Hit the upload and watch lots of texts and error like messages spin by. If the status reads `Upload Done` at the end, then all went well
6. Now you can open the serial monitor (button top right of Arduino editing app) to see what it's doing
7. If there is no traffic you can post a test message via the  [Sobots.xyz](http://sobots.xyz/) website
8. Attach the servos to things and hack the code :)

I am not going to tell you how to build the physical parts of your Sobot, get creative and make something with as much glue and stickyback plastic as you can afford.

To change the behaviour, simply edit the contents of the `act` function (looks like `void act(double x, double y, double z) { .. }`)

When you are up and running I suggest reading up on [Sobot Groups](https://sobots.xyz/docs/groups). The mood group (group:mood) is a good place to start. Just add `&groups=group:mood` to the url from which messages are collected, so:

* `http://us-central1-sobots.cloudfunctions.net/list/?limit=1&token="+TOKEN`

becomes:

* `http://us-central1-sobots.cloudfunctions.net/list/?limit=1&group=group:mood&token="+TOKEN`

Now your Sobot will pick up messages posted to the group and no those sent directly to you.



## Things to Note
Pin numbers can be quite confusing. Boards like the D1 are weird hybrids where the base (mother) board is designed to emulate an Arduino Uno and on top their is an ESP8266 daughter board. The ESP8266 board is the one you are actually programming using Arduino's software and it has pins which are mapped to the Arduino board pins. So when you write code you need to use the ESP8266 pin numbers, but plug your wire into the WeMos pin number to which it is mapped!

Below are some images which can help, but also the libraries helpfully provide your code with some static variables to mask this complexity. So in your code you can us D1, D2... and A1.. as pin numbers and this will tell the code to which ESP8266 pin to use.

![Circuit Diagram](assets/pins.png)

![Circuit Diagram](assets/board.jpg)
