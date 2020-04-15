javac Launcher.java
jar cvfe HLALauncher.jar Launcher *.class
g++ .\main.cpp -o hlalauncher.exe -static -O2 -s
rm *.class