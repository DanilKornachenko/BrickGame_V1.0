# BrickGame_V1.0
Implementation of the Tetris game in C language.  
![TetrisPreview](img/TetrisPreview.png)  
  
## Реализация игры Тетрис на языке Си  
### Директория src cодержит Makefile с целями:  
- All (make) сборка игры и запуск исполняемого файла.  
- install (make install) - компиляция библиотеки backend.  
- uninstall (make uninstall) - удаление программы  
- dvi (make dvi) - реализация конечного автомата в тетрисе  
- dist (make dist) - упаковка в архив  
- run (make run) - запуск игры.  
- test (make test) - Запуск юнит-тестов.  
- gcov_report (make gcov_report) - Покрытие функций юнит-тестами.  
- clean (make clean) - Удаление лишних файлов.  
- clang-n (make clang-n) - Проверка кода на code style.  
- clang-i (make clang-i) - Редактирование кода под code style.  
