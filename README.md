# FixWindowsTimerResolution
Sets the windows timer resolution to 1 ms, down from the default 15,6ms.
This makes the system more responsive overall and likely prevents stuttering or microsttuters from happening in the first place.

Only one instance of this program can run at a time.

FixWindowsTimer.exe -> Adds the program path to startup and keeps the timer resolution at 0.5ms while running silently in the background. No manual clicking or setting the timer needed.

uninstallFixWindowsTimer.exe -> Removes program from startup.


<h2>What you need to build:</h2>

Import project into Visual studio
