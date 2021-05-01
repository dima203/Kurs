echo "Процесс компиляции..."
g++ -c clear.cpp
g++ -c file.cpp
echo "12.5 %"
g++ -c sort_func.cpp
echo "25 %"
g++ -c delete_func.cpp
echo "37.5 %"
g++ -c select_func.cpp
echo "50 %"
g++ -c train_func.cpp
echo "62.5 %"
g++ -c menu.cpp
echo "75 %"
g++ -c proga.cpp
echo "87.5 %"
g++ *.o -o proga.exe
echo "100 %"
rm *.o
