# DIY sonnette

First, if you want to see the result, have a look at [this video](https://youtu.be/OrXuBeXwijw).

## Requirements

- 2 x [Elegoo nano](https://www.elegoo.com/products/elegoo-nano-v3-0)
- 2 x [E32-868T20D](https://www.ebyte.com/en/product-view-news.aspx?id=132)
- 4 x 18650 battery
- 2 x 18650 battery holder (7.4v)
- 1 x Buzzer
- 1 x 220ohm resistance
- 1 x Push button

NB: Regarding local regulations, you perhaps need something different that 868mHz (maybe 433mHz), please respect local regulations. I'm not responsible if you use a forbidden frequency in your country.

# Arduino IDE configuration

- Card: Arduino nano
- Processor: Atmega328P
- Programmator: AVRISP mkll

# Code

Have a look inside the repo's code folder, or access directly [sender code](code/sender.ino) or [receiver code](code/receiver.ino).

# Schemas

## Sender

![Sender](medias/sender.jpg?raw=true "Sender")

## Receiver

![Receiver](medias/receiver.jpg?raw=true "Receiver")

# Thanks

[Kris Kasprzak](https://github.com/KrisKasprzak/EBYTE) for the usefull Ebyte lib.
[Fritzing](https://fritzing.org/) for making shemas production easier.