echo "Процесс компиляции..."
g++ -c clear_w.cpp
g++ -c file.cpp
echo "11.1 %"
g++ -c config_func.cpp
echo "22.2 %"
g++ -c sort_func.cpp
echo "33.3 %"
g++ -c delete_func.cpp
echo "44.4 %"
g++ -c select_func.cpp
echo "55.6 %"
g++ -c train_func.cpp
echo "66.7 %"
g++ -c menu.cpp
echo "77.8 %"
g++ -c proga.cpp
echo "88.9 %"
g++ *.o -o proga.exe
echo "100 %"
del *.o
