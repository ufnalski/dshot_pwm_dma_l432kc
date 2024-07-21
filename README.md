# DShot protocol in action (STM32L432KC)
An STM32 HAL example of arming and sending a reference speed to an ESC (electronic speed controller) that supports DShot (Digital Shot) protocol.

![Dshot protocol in action](/Assets/Images/dshot_university_lab.jpg)

# Motivation
Quadcopters are inherently unstable. They only become stable due to control. That makes them excellent plants[^1] to elevate your control system design skills. There are many ways to start your journey with drones. You can buy a complete device that is ready to use out of the box, with all the necessary firmware preinstalled. This is for people who need it fly now and want to focus on gaining flying experience[^2]. Some of us take the hard way and build their first drone from scratch including all the software needed to stabilize it and control it remotely. A hardcore DIYer would probably consider developing even his or her own ESCs. Here we take a bit less exteme approach and use a commercial ESC. Oh, and in this example we address only arming and sending a reference speed to the ESC. You can consider it being the very first step in developing your own drone.

[^1]: https://en.wikipedia.org/wiki/Plant_(control_theory)]
[^2]: Check the regulations before you do that - in most countries you have to undergo some basic training and get an official certificate to be allowed to fly a drone.

# Missing files?
Don't worry :slightly_smiling_face: Just hit Alt-K to generate /Drivers/CMCIS/ and /Drivers/STM32L4xx_HAL_Driver/ based on the .ioc file. After a couple of seconds your project will be ready for building.

# If you are new to the DShot protocol and BLHeli_S/BLHeli_32 firmware
* [DSHOT - the missing Handbook](https://brushlesswhoop.com/dshot-and-bidirectional-dshot/) (Brushless Whoop)
* [DShot ESC's for Meltybrains](https://www.swallenhardware.io/battlebots/2019/4/20/a-developers-guide-to-dshot-escs) (Spencer's Hardware Blog)
* [DSHOT on Mbed](https://os.mbed.com/users/bwest32/notebook/dshot/)
* [ESC protocols explained for beginners (PWM, OneShot, DSHOT, calibrating!)](https://www.youtube.com/watch?v=okUrPLP_Eec)
* [BLHeli_32 Is Finished? - Time To Back AM32!](https://www.youtube.com/watch?v=GU0RoH_Pof0) (Mads Tech)
* [BLHeli_32 ESC - The Facts Today & Questions Answered](https://www.youtube.com/watch?v=-t4Q63fhfHc)

# Exemplary hardware for breadboarding
* [ESC Little-Bee Mini 30A BLHeli_S 2-6S](https://ajmaker.pl/produkt/esc-little-bee-mini-30a-blheli_s-2-6s-opto-7g-dshot-multishot-oneshot125/)
* [V2306 V3.0 VELOX 2550KV](https://www.dronopedia.pl/pl/p/Silnik-T-MOTOR-V2306-V3.0-VELOX-2550KV/1590) (T-MOTOR)
* [HQProp S3](https://www.dronopedia.pl/pl/p/Smigla-HQProp-Ethix-S3-Prop-Watermelon-roznokolorowy-2xCW-2xCCW/369) (Ethix)
* [2200mAh 11.1V 30C 3S1P LiPo battery](https://www.dronopedia.pl/pl/p/Bateria-Gens-ace-2200mAh-11.1V-30C-3S1P-Lipo-XT60-Soaring/1744) [^3]

[^3]: Why not a bench power supply? If you allready have one capable of delivering 30 A, lucky you :slightly_smiling_face: If not, it is usually much cheaper to buy a battery. It's roughly 25 EUR vs. 250 EUR. You can charge the battery from any CC/CV power supply if you know what you are doing. If you are not sure, use a quality charger. I'm quite happy with iMAX B6 Mini from SKYRC (approx. 35 EUR).

> [!WARNING]
> Propellers that spin at tens of thousands rpm are not toys :exclamation:

> [!WARNING]
> LiPo batteries are not toys either - learn to handle them before you use one in your project :exclamation:

# Hints
The PWM pin operates in the push-pull mode. However, if the ESC is powered befere the uC, it is advisable to have a pull-down resitor (e.g. 4k7 to draw below 1 mA from the GPIO), to get consistent behaviour at the startup phase. It's a good practice not to have signal lines flapping in the breeze.

# Sources and inspirations
* [stm32_hal_dshot](https://github.com/mokhwasomssi/stm32_hal_dshot/tree/main) (MIT license)
* [DShotRMT](https://github.com/derdoktor667/DShotRMT) (ESP32, Arduino framework, MIT license)

# A couple of next steps
Get familiar with attitude and heading reference systems (AHRS):
* [Attitude and heading reference system](https://en.wikipedia.org/wiki/Attitude_and_heading_reference_system) (Wikipedia)
* [The Difference Between IMU, AHRS, and INS](https://www.youtube.com/watch?v=4CZQQ0VLCG8) (Inertial Sense, Inc.)

Play with a selected one. Some examples are:
* [BNO055](https://www.bosch-sensortec.com/products/smart-sensor-systems/bno055/) (Bosch Sensortec GmbH)
* [BNO085/BNO086](https://www.ceva-ip.com/product/bno-9-axis-imu/) (Ceva, Inc.)

There are eval boards ready for breadboarding from e.g. [Adafruit Industries](https://learn.adafruit.com/search?q=9-dof).

Then build a test rig to safely evaluate your control algorithms. Check some common approaches on YT:
* [Aluminum PID test and tuning rig stand for quadcopter UAV drone](https://www.youtube.com/watch?v=IG5VzPl7NDU)
* [A 4DOF Quadcopter Test Bench](https://www.youtube.com/watch?v=Nju5yUpFetU)
* [Drone Gimbal Rig 2](https://www.youtube.com/watch?v=M09hvlPbqek)
* [Drone Jig](https://www.youtube.com/watch?v=n8JJgECg7v0)
* [UAV Test Stand in Action](https://www.youtube.com/watch?v=p9n0MNw_Wms)
* [Normal Quadrotor in a Gyroscopic Test Bench Experiment - Grin UFJF](https://www.youtube.com/watch?v=UabnWK2C-YY)
* [The FFT GYRO, the best tool for drones.](https://www.youtube.com/watch?v=lhqUZzHFyzU)

Search for more: drone/quadcopter test bench/platform/jig/rig/stand.

# Call for action
Create your own [home laboratory/workshop/garage](http://ufnalski.edu.pl/control_engineering_for_hobbyists/2024_dzien_otwarty_we/Dzien_Otwarty_WE_2024_Control_Engineering_for_Hobbyists.pdf)! Get inspired by [ControllersTech](https://www.youtube.com/@ControllersTech), [DroneBot Workshop](https://www.youtube.com/@Dronebotworkshop), [Andreas Spiess](https://www.youtube.com/@AndreasSpiess), [GreatScott!](https://www.youtube.com/@greatscottlab), [ElectroBOOM](https://www.youtube.com/@ElectroBOOM), [Phil's Lab](https://www.youtube.com/@PhilsLab), [atomic14](https://www.youtube.com/@atomic14), [That Project](https://www.youtube.com/@ThatProject), [Paul McWhorter](https://www.youtube.com/@paulmcwhorter), and many other professional hobbyists sharing their awesome projects and tutorials! Shout-out/kudos to all of them!

> [!WARNING]
> Electric drives - try them at home :exclamation:

190+ challenges to start from: [Control Engineering for Hobbyists at the Warsaw University of Technology](http://ufnalski.edu.pl/control_engineering_for_hobbyists/Control_Engineering_for_Hobbyists_list_of_challenges.pdf).

Stay tuned :exclamation:
