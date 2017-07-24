# enable i2c
>sudo raspi-config 
// enable i2c in advanced options
>sudo nano /etc/modules
// add i2c-bcm2708 and i2c-dev
> sudo reboot

// install tools 
>sudo apt-get install -y i2c-tools
>ls /dev/*i2c*
>sudo i2cdetect -y 1

// add user pi to group i2c (no more sodo needed)
>sudo adduser pi i2c
// check log in/out
>groups pi
>exit

// build init and any bin
>make build-init
>make build-any


