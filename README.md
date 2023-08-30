# campercontroller
Arduino based relay and sensor board replacing my Campercontroller

Our old camper from 1990 contains a kind of controlbox which handles charging the batteries, measure level of the dirt water tank and contains some relays to switch the "main" power of the lights. This box is controlled from a display with some buttons which reside in the kitchen of the camper.

I want to remove this old controller box and replace it with some more modern setup.

Charging the batteries (200Ah) will be done using a decent Victron Battery Charger of 25Amps.
220V has a seperate circuit in the camper and is in fact only used to feed the Battery Charger and the refridgerator. Lights and even a future television can be powered by 12V. 
Remaining is some switches for the "main" power to the lights (1 and 2), the freshwater pump and apparently there is some frost protection system (not yet known how that one is powered). 

The controlbox will be an Arduino Uno/Mego/Nano/Micro (to be determined) which drives some simple circuits to switch 12v car relays (which are in my opinion more suitable for heavy loads than the relay boards from AliExpress/EBay). Some other circuits are to be created to measure voltage of the batteries and to measure the resistance of the level sensors of clean/dirt water.

The controlbox itself is dump and will have a serial communication with a camperdisplay which will replace the display/buttons in the kitchen. Controlbox will send battery voltage, water levels, etc to the display controller. The display controller will send required state of the relays to the controlbox.

It will be a serial connection so it is easy to re-use the flatcable which already resides in the camper.

