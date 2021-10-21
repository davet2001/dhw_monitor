# Domestic Hot Water Monitor
## Summary
An ESP32 controlled Home-Assistant connected wall mounted display to provide accurate heating information to help save energy.
## Background
My house has a hot water tank, heated by a natural gas boiler.  Backup heating is available via am electric heating element ("immersion heater").  Generally this tank gets heated up at strategic times of the day, then used by the family (showers, baths etc) in an unpredictable pattern.
In addition, last year I set up an intelligent controller to switch on the immersion heater when our solar panels are producing excess electricity.  In normal sunny weather (spring-autumn) this is more than enough to heat the tank.

## The problem
Noone really knows how much hot water is left at any time.  So people end up boosting it 'just to be sure', even if there is actually plenty left.  I experimented with a temperature sensor added to the tank, but of course this only tells you the temperature of just one height in the tank.  As the water is used, cold water enters from the bottom, so the measure of 'how much water is left' is more a question of 'how far down the tank does the water transition from warm to cold'.  With a mixing shower/bath, typically the amount of hot water needed also depends on how hot the water is.  For example 100L of 65degC water can fill more baths than 100L of 45degC water.
So the question is complex.

## The solution
Connected a series 7 of DS18B20 sensors to the tank via a sonoff TH16 allowing reporting of the temperature at 7 levels.  Asside: I made a small cgi script https://github.com/davet2001/miscellaneous/blob/master/dhw_tank.cgi that visuallises this.

Then an ESPhome controlled AZ-Touch box mounted on the wall displays a picture of the tank, ranging from red to blue showing the 'level' of hot water.  On top of this tank is the estimated number of litres of 40degC water available, as well as the approx number of baths this produces.

The aim: people look at this display before deciding to boost the water with gas.
