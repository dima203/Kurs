echo "Процесс компиляции..."
g++ -std=c++20 -c clear_w.cpp
g++ -std=c++20 -c file.cpp
echo "11.1 %"
g++ -std=c++20 -c config_func.cpp
echo "22.2 %"
g++ -std=c++20 -c sort_func.cpp
echo "33.3 %"
g++ -std=c++20 -c delete_func.cpp
echo "44.4 %"
g++ -std=c++20 -c select_func.cpp
echo "55.6 %"
g++ -std=c++20 -c train_func.cpp
echo "66.7 %"
g++ -std=c++20 -c menu.cpp
echo "77.8 %"
g++ -std=c++20 -c proga.cpp
echo "88.9 %"
g++ -std=c++20 *.o -o proga.exe
echo "100 %"
del *.o
