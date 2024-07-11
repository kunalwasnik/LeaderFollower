## Leader Line Follower
Introduction
Leader Line follower is bot where leader bot follows a line and follower bot follows the leader.
Component Used for leader bot:

1. Tiva tm4c123gh6pm Microcontroller
2. ESP 8266
3. 5 Array IR sensor
4. Power Supply


The same components excluding IR sensor is used for follower.

Methodology
Leader Bot Tasks
1. Configuration of sensors
2. Reading IR sensor values : Here IR sensors is programmed using interrupts and return 1
 whether it detects black line or not.
3. Transmitting using UART : Ones IR sensor values are read it sent using uart to esp8266.
4. Esp8266 sends this command using wifi to the other esp8266 present on follower bot.
5. Line following based on ir sensor values


Follower Bot Tasks
1. 1.Configuration of sensors
2. Receiving Data: The data sent by leader esp is received here.
3. Esp8266 send the receiving data command using uart to the tiva present on follower bot.
4. Following based on ir sensor values
