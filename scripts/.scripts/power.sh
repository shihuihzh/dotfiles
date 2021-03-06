#!/bin/bash

echo "Enter which power operation you want" 
read -n 1 -p "Poweroff->o, Reboot->r, Logout->e, Sleep->s: " opt
case ${opt} in
	o | O)
		systemctl poweroff
		;;
	r | R)
		systemctl reboot
		;;
	e | E)
		xdotool key Shift+Super+c
		;;
	s | S)
		systemctl suspend
		;;
esac
