# Exploring Local Storage for Arduino Projects

When working with Arduino projects that collect or process data, it’s often useful to store information locally rather than sending it to and/or receiving it from the cloud. 

Arduino boards support two really useful types of local storage: **EEPROM**, which is a small built-in memory ideal for saving settings, storing  values, or other small bits of data that you want to be able to retrieve even when the board is powered off; and **SD cards**, which provide much larger, removable storage for logging larger data sets like sensor data, updating and retrieving measurements, or saving full on files like text files, images and audio.
