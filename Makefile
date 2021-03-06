### Конфигурация. ###################################
CC = gcc 
SOURCES = main.c lib.c
MODULES = liblocal.so 
	
### Правила. ########################################
# Служебный целевой модуль
.PHONY:		all clean
# Стандартный целевой модуль: компиляция всех файлов.
all:	$(MODULES) main 
	
# Удаление всего чего насобирали.
clean:
	rm -f	$(MODULES) main 

# Собираем основные файлы.
main:		$(SOURCES) 
	$(CC)	$(CFLAGS)	-Wl,-export-dynamic -o $@ $^ -ldl
					
# Собираем библиотеки.
$(MODULES): %.so:		%.c
	$(CC)	$(CFLAGS)	-fPIC -shared -o $@ liblocal.c
####################################################
