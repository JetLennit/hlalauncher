javac Launcher.java
jar cvfe HLALauncher.jar Launcher *.class
g++ .\main.cpp -o hlalauncher.exe -static
rm *.class