# Hub v3.0.0

Version 3 release comes with three major updates.

- Controller firmware is no longer platform-specific. USC controllers should now work on all operating systems that support KSP.

- A new mode has been added called "Emulator Mode" that can be accessed without changing code. Just spam-press any button on the controller before it completes a connection to Simpit to activate it. A settings file is included for customized keybindings in Emulator Mode.

- Firmware is now modular. Code is generated based on the controller's CAB link (https://untitledspacecraft.com). This was a necessity to fit keyboard emulation onto a single Arduino Micro. Unused module code is not included.

Point 3 above means that it is no longer feasible to just download the code here and flash it. It must be processed through the CAB code tool. However, it isn't difficult to figure out if you don't want to do that.
