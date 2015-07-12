# sesh
Shell

1) КОМПИЛЯЦИЯ. 
	Происходит посредством команды "make -f Makefile" в каталоге sesh.
2) ЗАПУСК ПРОГРАММЫ.
	"./sesh.c" в каталоге sesh/src
3) РАБОТА С GIT.
	"git clone git@github.com:artemsmirnov/sesh.git" - каталог с выписанной 
							с github.com веткой master.
	"git submodule update --init" - используем для восстановления целостного 
			проекта, клонируя нужные версии субмодулей(побочные ветки).
	"git checkout -b branch_name" - создание новой ветки. Создавать, находясь в ветке 'master'.
	"git checkout branch_name" - переход к некоторой существующей на github ветке.
	"git pull origin master" - обновить ветку master с github на локальное хранилище.
	КАК СДЕЛАТЬ COMMIT:
	"git status" - список всех измененных и добавленных файлов. 
	"git add name_file.c" - подготавливаем коммит, добавляя в него файлы командой.
	"git rm <file1> <file2>" - (или удаляем устаревшие файлы).
	"git commit -m "Комментарий к коммиту" " - выполняем коммит.
	"git push origin dev" - заливаем последнюю версию ветки dev на удаленный сервер.



