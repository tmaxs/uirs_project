### Конфигурация. ###################################
CC = gcc 
SOURCES = main.c lib.c
MODULES = liblocal.so 
	
### Правила. ########################################
# Служебный целевой модуль
.PHONY:		all clean
# Стандартный целевой модуль: компиляция всех файлов.
all:	$(MODULES) main lib
	
# Удаление всего чего насобирали.
clean:
	rm -f	$(MODULES) main lib

# Собираем основные файлы.
main:		$(SOURCES) 
	$(CC)	$(CFLAGS)	-Wl,-export-dynamic -o $@ $^ -ldl

lib:		$(SOURCES)
	$(CC)	$(CFLAGS)	-Wl,-export-dynamic -o $@ $^ -ldl					
# Собираем библиотеки.
$(MODULES): 
		%.so:		%.c
	$(CC)	$(CFLAGS)	-fPIC -shared -o $@ %body%lt
#
