#!/bin/bash
echo "===== compile compiler ====="
make
echo "===== enter your programm code (when you are done enter END and press enter) ====="
./jasminCompiler
echo "===== assembling jasmin code to java byte code ====="
java -jar ./ressources/jasmin.jar ./out/App.l -d ./out
read -p "===== Press enter if you would like to run the java bytecode now ====="
java -cp ./out App
echo "===== program done !!! ==="