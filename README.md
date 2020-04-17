# HLALauncher - A Map Launcher for Half-Life: Alyx

## Features\:

*GUI that shows date created and file size
*Launch options work
*Script folder works
*Can be set as default way to open vpk for quick map launching
*Easy to use drag and drop option
(There is not yet support for multi-map campaigns, but I plan to add that soon.)

## Usage\:

First, either download a release zip from the release section, or compile it yourself using the compile.bat file in the repository. Make sure to keep the HLALauncher.jar and hlalauncher.exe files in the same folder at all times. If you downlaoded the zip, take the hlalauncher folder out of it. ***Do not run the game before the launcher***

### GUI Launcher\:

1. Download ~~Java 12 or greater~~ **Java 8 should now be sufficient and can be found here [https://java.com/en/download/](https://java.com/en/download/) (please let me know if this works)**, you may have to delete an old version of Java as well.
2. Put all your map files in the same folder as your HLALauncher.jar and hlalauncher.exe files
3. Run the jar file, select your map, and click the button at the bottom
4. If asked, enter your install location for Half-Life: Alyx (eg. C:\Program Files (x86)\Steam\steamapps\common\Half-Life Alyx) without quotes or a slash at the end
5. If asked, enter whatever launch options you would like the launcher to run the game with, or leave blank to use default. This can be changed in hlalaunchoptions.txt later
6. Enjoy!

### Drag and Drop\:

1. Drag your map file onto hlalauncher.exe
2. If asked, enter your install location for Half-Life: Alyx (eg. C:\Program Files (x86)\Steam\steamapps\common\Half-Life Alyx) without quotes or a slash at the end
3. If asked, enter whatever launch options you would like the launcher to run the game with, or leave blank to use default. This can be changed in hlalaunchoptions.txt later
4. Enjoy!

### Association\:

1. Right click on a VPK and open Properties
2. Click the "Change" button next to the Opens With: section
3. Click "More Apps" then "Look for another app on this PC"
4. Go to where you have hlalauncher.exe installed and click on it
5. Apply your settings then double click the vpk
6. If asked, enter your install location for Half-Life: Alyx (eg. C:\Program Files (x86)\Steam\steamapps\common\Half-Life Alyx) without quotes or a slash at the end
7. If asked, enter whatever launch options you would like the launcher to run the game with, or leave blank to use default. This can be changed in hlalaunchoptions.txt later
8. Enjoy!

### Using Scripts\:

1. Create a new folder in the same directory as the map you are trying to run and name it the same thing as your map file without an extension. For example, if I was trying to load test.vpk with it's scripts I would create a folder called test
2. Drag and drop your scripts folder into that new directory you created
3. Use the launcher as normal, making sure to keep the new folder in the same directory as your map whenever you run it.

## Q and A\:
Q\: Why does this seem so unfinished?

A\: Because it is. I plan on adding many more features to this as time goes on. Future planned changes include cleaning up the code (sorry it's a mess), a better gui, and much more.

---

Q\: I get a JNI error when I try to run the program

A\: I'm pretty sure that's on Java's end. Update Java to 12 or greater or try [this](https://stackoverflow.com/a/57796364) link to fix it.

---

Q\: Why isn't it working?

A\: If the program doesn't work for you for any reason, please PM me on discord at jetlennit#5990 and I'll help you resolve your problem hopefully
