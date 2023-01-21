#!/bin/bash
led_row=32
led_col=64
gpio_slowdown=5
font=~/rpi-rgb-led-matrix/fonts/10x20.bdf
led_gpio_mapping=regular

echo "Welcome To Matronix Display Module Ver 0.1, Copyright 2023 No Rights Reserved :)"
echo " "
echo "Input the number of displays connected from Right to Left (Chain)"
read -p 'Chained display number:' NumberChained
echo "Input the number of displays connected from bottom to top (Parallel)"
read -p 'Parallel display number:' NumberParallel
if [ $NumberParallel -eq 1 ]
then
    led_gpio_mapping=1display
fi

echo "What would you like to display?"
echo "1. Text/ Scrolling text"
echo "2. Video"
echo "3. Image"
echo "4. Clock"
read -p 'Option:' function

if [ $function -eq 1 ]
then
    echo "Enter Text you wish to display"
    read -p 'Text:' Text
    echo "Enter the color of the text"
    read -p 'Color:' Color
    echo "enter the scrolling speed (use 0 for no scrolling)"
    read -p 'Scrolling Speed:' ScrollSpeed
    sudo ./rpi-rgb-led-matrix/utils/text-scroller -f $font --led-slowdown-gpio $gpio_slowdown --led-rows $led_row --led-cols $led_col --led-chain $NumberChained --led-parallel $NumberParallel -y $ScrollSpeed -C $Color $Text --led-gpio-mapping $led_gpio_mapping
fi
if [ $function -eq 2 ]
then
    echo "Enter the path to the video file"
    read -p 'Video Path:' VideoPath
    sudo ./rpi-rgb-led-matrix/utils/video-viewer --led-slowdown-gpio $gpio_slowdown --led-rows $led_row --led-cols $led_col --led-chain $NumberChained --led-parallel $NumberParallel $VideoPath -f --led-gpio-mapping $led_gpio_mapping
fi
if [ $function -eq 3 ]
then
    echo "Enter the path to the image file"
    read -p 'Image Path:' ImagePath
    sudo ./rpi-rgb-led-matrix/utils/led-image-viewer --led-slowdown-gpio $gpio_slowdown --led-rows $led_row --led-cols $led_col --led-chain $NumberChained --led-parallel $NumberParallel $ImagePath --led-gpio-mapping $led_gpio_mapping
fi
if [ $function -eq 4 ]
then
    sudo ./rpi-rgb-led-matrix/examples-api-use/clock --led-slowdown-gpio $gpio_slowdown -f $font --led-rows $led_row --led-cols $led_col --led-chain $NumberChained --led-parallel $NumberParallel  --led-gpio-mapping $led_gpio_mapping
fi
