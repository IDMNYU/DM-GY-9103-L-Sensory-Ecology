# How to Solar Power Your Projects

## Basic Components of Off-grid PhotoVoltaic(PV) Systems

For most DC-based off-grid systems it really comes down to four main components – solar panels, charger controller, battery bank, and inverter (whenever needed for powering AC-based appliances). So let's take a look at them individually: 

### PV 
#### It produces electricity when exposed to light
![PV Panel](https://github.com/alexnathanson/solar-protocol/blob/17bf2e020b7f5992ba648b61bbfd3f9b7c1dcf36/wikimg/panel.png)

Photovoltaic means 'voltage from light' and refers to a solid-state semiconductor device, aka a solar cell, that produces a potential difference (Voltage) and current of electrons (Electricity) when exposed to light. PV panels, or modules, are made of multiple solar cells assembled between protective layers of glass and plastic, and typically framed in aluminum (for easy mounting). 

Using solar power is all about timing. Solar panels produce electricity when sunlight is shining on them, usually between 11 am to 4 pm (depnding on geolocation and seasonality). They provide more power when the sunlight is more intense and not reduced by cloud cover. They will produce some on a cloudy day, too, but typically much less efficiently (less than 10%) than what they would on a sunny day. And they don't produce at night (at least for now!).

The PV modules are available in a range of brands, sizes, and output capacity, and in some ways, they are easiest part to source in most markets. Look for modules with all the necessary approvals (UL, CE, or CSA labeled) and a 25-year warranty on their power output. 

### Charge controller 
#### It regulates the flow of electricity from PV modules to batteries
![Charge Controller](https://github.com/alexnathanson/solar-protocol/blob/17bf2e020b7f5992ba648b61bbfd3f9b7c1dcf36/wikimg/controllersm.png)

The primary function of a charge controller is to regulate the flow of electric current from the array of solar modules to the batteries. This ensures the batteries are correctly charged and prevents damage from over-charging. Charge controllers come in different types (PWM vs MPPT) and range of capacities based on the voltage and current they can handle. 

A **PWM (Pulse Width Modulation) charge controller** regulates the flow of power from solar panels to batteries by rapidly switching the charge on and off to maintain optimal voltage and prevent overcharging. PWM CC tend to be much cheaper but offer less flexibility. A great feature to look for is high-voltage maximum power point tracking (MPPT). 

An **MPPT charge controller** can accept the input from the solar modules at high voltage and charge the batteries at an appropriate lower voltage, using an optimization algorithm to maximize the amount of power going to the battery bank.

### Battery 
#### It stores electricity
![Battery](https://github.com/alexnathanson/solar-protocol/blob/17bf2e020b7f5992ba648b61bbfd3f9b7c1dcf36/wikimg/batterysm.png)

The two most common types of batteries used in renewable energy systems are deep-cycle lead-acid batteries and lithium-ion batteries. Both types of batteries work well and provide dependable energy storage for off-grid solar power systems.

Lead-acid batteries have been used for well over a century. They're relatively more affordable and can provide plenty of electric currents. Lead-acid batteries last approximately ten years, or 1,500 cycles, providing they are well-maintained and used as directed. They are large, heavy, and require periodic maintenance. They contain a mix of a recycled and new lead, a toxic metal that must be recycled properly.

Lithium-ion batteries are lighter and smaller than lead-acid batteries. They are significantly higher in price to purchase than lead-acid batteries but require less maintenance, withstand deeper discharges, and last about 13 or more years, or 2000 cycles. Lithium-ion batteries are made from a mix of recycled and new lithium, a rare and reactive metal that must be recycled properly. They can be extremely sensitive to heat and need proper maintanance and in general can be less suitable for applications exposed to extreme weather and/or the elements. Make sure to check your local regulations about Lithium-ion batteries. 

### Inverter [Optional]
#### It converts direct current (DC) to alternating current ([AC](https://www.buildwithrise.com/stories/ac-dc-power)) suitable for home appliances
PV modules and batteries produce electricity in the form of direct current (DC). This can charge devices that use DC, like phones, tablets, and battery maintenance chargers. You can get DC lighting and appliances for your off-grid place, especially at motorhomes and sailing boat shops. But the most commonly available and affordable appliances run on alternating current (AC), and the wiring for AC in a building is more standard for electricians. A highly efficient device called an inverter can convert DC from your batteries to AC for your house wiring. For home use, there are two basic kinds of inverters: micro-inverters and string inverters.

-- Illustrations by Crystal Chen

## TL;TR

The core components of an off-grid solar system include the photovoltaic (PV) panel, battery, and charge controller. 

The **PV panel** converts sunlight into electricity, serving as the primary energy source for the system. <br>
The **battery** stores excess energy generated by the PV panel, providing power during periods without sunlight, such as at night or during cloudy weather. <br>
The **charge controller** optimizes the energy harvested from the PV panel, ensuring efficient charging of the battery by adjusting the voltage and current to match the system's needs.<br>

<div align="center"><img src="https://github.com/Community-Tech-Lab/PNK/blob/main/assets/basicsolarload.png" alt="Basic off-grid solar system" width="" /></div>
<div align="center"><sub>Basic diagram of an off-grid solar system.</sub></div>
<br>

>[!WARNING]
> **Warning:** _When connecting the components of a solar system, always connect the batteries to the charge controller first, before connecting the PV panel. This ensures the charge controller is properly configured to the battery’s voltage and avoids potential damage to the system._

## Some options for projects

When powering microcontrollers projects (Arduino, etc.) or single board computer projects (Raspberry Pi, etc.) with solar energy, there are a range of approaches depending on your needs, scale, and desired level of customization and uptime. 

Approaches can range from easy _plug-n-play kits_ to more experimental or educational builds, where you can assemble your own _solar recharging circuits_, or for ultra-efficient or intermittent applications, _low-power solar systems using supercapacitors_ can store just enough energy for short bursts of uptime, supporting lightweight and environmentally responsive designs.

### Low-power & Battery-less (Supercapacitors) 


### Solar recharging 

### Plug-n-play kits 
For simple, ready-to-use setups, plug-and-play solar kits such as those from [**Voltaic Systems**](https://voltaicsystems.com/solar-panel-kits/)

<img src="https://github.com/IDMNYU/DM-GY-9103-L-Sensory-Ecology/blob/9772a1c7f360746cf181094698885c32a80ef0b0/images/5.5W-Kit__68577.jpg" style="width:40%;"><img src="https://github.com/IDMNYU/DM-GY-9103-L-Sensory-Ecology/blob/74b646e2eb36f021e51e10decd839263304e8bca/images/10WKIT__76242.jpg" style="width:40%;">
<div align="left"><sub>Voltaic Systems 5.5W and 10W Solar Kits</sub></div><br>

offer both [solar panels](https://voltaicsystems.com/small-solar-panels/) paired with [integrated battery packs + charge controllers](https://voltaicsystems.com/iot-battery-packs/) designed for ease and consistency. The [V25](https://voltaicsystems.com/v25/), [V50](https://voltaicsystems.com/V50/) & [V75](https://voltaicsystems.com/v75) battery packs are particular versitile. I also use them for solar charging my portable devices, let them charge up in the Sun and throw them in my back as a back-up power bank. 

<img src="https://github.com/IDMNYU/DM-GY-9103-L-Sensory-Ecology/blob/main/images/v50-how-it-works.jpg">
<div align="center"><sub>Voltaic Systems Solar Kits</sub></div><br>

### Larger DIY off-grid PV 
Larger plug-and-play systems like [GoalZero](https://goalzero.com/collections/portable-solar-generator-kits/products/yeti-1500x-2-nomad-200-solar-generator) and [GroWatt](https://growattportable.com/products/growatt-infinity-2000-portable-power-station) offer foldable panels and integrated batteries with built-in charge controllers and inverters, creating a portable, all-in-one solution ideal for temporary installations that require easy setup and mobility over permanent infrastructure. While more expensive, they might be useful options for certain environments and conditions. 

<div align="center"><img src="https://github.com/Community-Tech-Lab/PNK/blob/main/assets/Goalzero.png" alt="GoalZero integrated system)" width="700" /></div>
<div align="center"><sub>Turn Key GoalZero System, 200W PV and 1516W Battery, ~$1780</sub></div>
<div align="center"><img src="https://github.com/Community-Tech-Lab/PNK/blob/main/assets/growatt.png" alt="Growatt integrated system)" width="700" /></div>
<div align="center"><sub>Turn Key GroWatt System, 200W PV and 2200W Battery, ~$2150</sub></div>

## For More
> [!IMPORTANT]
> Different locations and varying equipment needs will require adjustments to your choice of components, such as PV panel size, battery capacity, and charge controller specifications, to ensure optimal performance and system reliability under specific environmental and operational conditions. There is a bit of math to do in order to make sure you are matching the power demand of your devices, the battery capacity, size of the panel and capacity of the charge controller, but for lower power microcontrollers & single board computers you should be able to get away with one of the earlier options! 


