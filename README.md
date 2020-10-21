# Electronic Technologies and Biosensors Laboratory
## Academic Year 2020/2021 - I Semester
---
## Assignment 04
This repository contains the PSoC Creator workspace to be used as a starting point for the successfull submission of the Assignment 04 of the course "Electronic Technologies and Biosensors Laboratory" of the I Semester of the academic year 2020/2021.

---
### Objective
In this assignment you are required to create a project using PSoC Creator and the CY8CKIT-059 KIT along with the following components:
-	1 photoresistor and 1 10kOhm resistor
-	1 potentiometer
-	1 LED and 1 330 Ohm resistor

### Context
This week LTEBS srl is interested in exploring the home automation market and asks you to develop a smart lamp prototype. The lamp will be simulated by an LED and the prototype must have the following features:
- The bulb must turn on (ON/OFF) on the basis of a reasonable brightness threshold you have decided -> sampling of a photoresistor, ON/OFF switching of the LED
- The user can choose the intensity of the light through a potentiometer -> sampling of a potentiometer sampling and LED driving for light intensity (tip: modulate light intensity only if LED is switched on)
- The product must be able to be started remotely in order to guarantee compatibility with an App that the company's software engineers are developing -> ON/OFF command on UART + ISR Rx to start sensor reading + LED to indicate whether the PSoC is sending or not
- For diagnostic purposes, it must be possible to plot the sampled signals and save them in a text log file -> it is required to provide the Bridge Control Panel .ini and .iic file for interfacing with the firmware (NB: Both signals must be plotted)

In order to sample more than one signal you must use the PSoC Creator [AMux](https://www.cypress.com/documentation/component-datasheets/analog-multiplexer-amux) component.
Photoresistor can be sampled using a voltage divider configuration, as in figure:

<a href="https://ibb.co/Vm0pbTk"><img src="https://i.ibb.co/tXwPnD1/Cattura.jpg" alt="Photoresistor schematic" border="0"></a>

### Connections
The external LED must be connected to pin **2.7**, the potentiometer to pin **2.5** and photoresistor to pin **2.6**.
The UART must use the pins **12.6** and **12.7** in order to communicate through the KitProg.

### Serial Port Communication
For remote command part, please use the following command:
- **“B”**,**”b”**: begin, you can start sampling sensors
- **“S”**, **“s”**: stop, don’t measure anything

### Setup and Assignment Delivery
- Fork this repository 
- Clone the repository you just forked by entering the following command in your terminal:

    `git clone https://github.com/[your_username]/AY2021_I_HW_04.git`
- Open up the workspace in PSoC Creator
- Activate the project with your name and surname
- Work on your project. Remeber to save Bridge Control Panel configuration files (.ini and .iic) inside BRIDGE_CONTROL_PANEL_CONFIG_FILES folder inside your project folder
- The last commit must be named '*SURNAME_NAME* Final Delivery'
- Propose a pull request before the deadline for the assignment, which is on **October 27 at 6PM**


### Evaluation
The evaluation of the assignment will take into consideration the following aspects of the project:
- successful build process without any warning/error generated
- successful programming without any error generated
- correct functioning of the device as per the requirements
- code organization (header and source files, useful comments)
- schematic organization and documentation
- successful use of git for version control (commits with proper comments, use of branches, ...)
- successful pull request on GitHub


### Additional Resources:
- [PSoC PWM Component Datasheet](https://www.cypress.com/file/376411/download)
- [PSoC 5LP Interrupts](https://www.cypress.com/file/44256/download)
- [PSoC 101 Video Tutorial](https://www.youtube.com/watch?v=LrXXpQr1itY&list=PLX6sqqUB8iOjsMfGEDcsPSuYLEFCh50Hr)