/**
 * @file main.c
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief Пример модуля
 * @version 0.1.0
 * @date 25-10-2022
 * 
 * @copyright Арен Елчинян (c) 2022
 * 
 */


#include <modules.h>
#include <strings.h>
#include <libk.h>
#include <tools.h>


/**
 * @brief Имя модуля
 * 
 */
string_utf8_t *mod_example_name = "Echo module";


/**
 * @brief Разрешения модуля
 * 
 */
module_permissions_t mod_example_permissions;


/**
 * @brief Ответ ОК модуля
 * 
 */
module_response_t mod_example_response_true;


/**
 * @brief Информация о модуле
 * 
 */
module_info_t mod_example_info;


/**
 * @brief Версия модуля
 * 
 */
version_t mod_example_version = {
    0, 1, 0
};



static void *(*alert)(char*);


/**
 * @brief Отправка данных
 * 
 * @param func Подфункция
 * @return void* Буффер
 */
void *mod_example_get(uint32_t func) {
    UNUSED(func);
    return NULL;
}


/**
 * @brief Функция приема данных
 * 
 * @param func Номер подфункции
 * @param data Данные
 */
void mod_example_post(uint32_t func, uint32_t *data) {
    switch(func) {
        default:
            alert(data);
            break;
    }
}


/**
 * @brief Получение разрешений
 * 
 * @param permissions Структура разрешений
 */
void mod_example_permissions_func(module_permissions_t *permissions) {
    alert = permissions[MODULE_PERMISSION_ALERT].permissions_funcs;
}


/**
 * @brief Входная точка модуля
 * 
 * @param mode Режим запуска модуля
 * 0 - настройка модуля, 
 * 1 - проверка работы, 
 * 2 - отключение модуля
 * @param argc Количество аргументов
 * @param argv Массив аргументов
 * @return Указатель на структуру-ответ модуля
 */
void *mod_example_main(uint8_t mode, int argc, char **argv) {
    UNUSED(argc);
    UNUSED(argv);

    switch(mode) {
        case 0: {
            mod_example_permissions.permissions[MODULE_PERMISSION_ALERT] = true;

            mod_example_info.name = mod_example_name;
            mod_example_info.version = mod_example_version;
            mod_example_info.permissions = mod_example_permissions;

            mod_example_info.module_get = &mod_example_get;
            mod_example_info.module_post = &mod_example_post;
            mod_example_info.module_permissions = &mod_example_permissions_func;

            return &mod_example_info;
        }

        case 1: {
            return &mod_example_info;
        }

        case 2: {
            return &mod_example_response_true;
        }

        default: {
            return NULL;
        }
    }
}