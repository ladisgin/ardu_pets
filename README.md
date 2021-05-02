# ardu_pets

## ir_digispark

Ir reciver for aluminium apple remote from digispark and VS1838B

![Out - P2, GND - GND, VCC - 5V](https://content.instructables.com/ORIG/FBY/AV85/KBNNOKPN/FBYAV85KBNNOKPN.png?auto=webp&frame=1&width=957&fit=bounds&md=b17ccef4d09da147e2ffdcbd55a52337)

The code for the IR sensor is taken from [the Russian forum](http://arduino.ru/forum/proekty/ik-distantsionnoe-upravlenie-kompom-cherez-digispark)

There are two control modes that are changed by the menu button:
1. Media
    * up - volume up
    * down - volume down
    * left - previous track
    * right - next track
    * center - mute
    * menu - change mode
    * play/pause - play/pause
2. Presentation Remote
    * up - arrow up
    * down - arrow down
    * left - arrow left
    * right - arrow right
    * center - space
    * menu - change mode
    * play/pause - play/pause

library:

* [TrinketHidCombo](https://github.com/adafruit/Adafruit-Trinket-USB)