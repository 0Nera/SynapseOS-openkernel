# SynapseOS-openkernel


Open Source реализация ядра SynapseOS

[Сайт проекта](https://0nera.ru/o/SynapseOS)<br>
[Документация](https://0nera.ru/o/docs)

[![push](https://github.com/0Nera/SynapseOS-openkernel/actions/workflows/push.yml/badge.svg?branch=main)](https://github.com/0Nera/SynapseOS-openkernel/actions/workflows/push.yml)

![GitHub Actions](https://img.shields.io/badge/github%20actions-%232671E5.svg?style=for-the-badge&logo=githubactions&logoColor=black)
![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=black)
![Python](https://img.shields.io/badge/python-3670A0?style=for-the-badge&logo=python&logoColor=black)


### Безопасность

Система не передает личные данные пользователей. Даже ради статистики.

## На данный момент реализовано

- [X] Гибкая система зависимого от архитектуры кода
- [X] Автогенерация и публикация документации
- [X] Публикация ISO образов

## Сборка и запуск

Получение ISO образа системы с новым ядром (с закрытым исходным кодом) осуществляется по заявкам - a2.dev@yandex.ru.

Перед сборкой установите `xorriso`, `i686-elf-gcc`, `limine` (а конкретно `limine-deploy`)

Для сборки открытого ядра:

```python
python3 scripts/build.py
```

Для установки зависимостей:

```python
python3 scripts/install.py
```

## Минимальные системные требования

- 5 мегабайт оперативной памяти
- 4 мегабайта видеопамяти
- i686 процессор на x86 архитектуре

## Благодарности

- Геннадий Геннадьевич (наставник)
- [Михаил Фролов](https://vk.com/id_doczom)
- [rgimad](https://github.com/rgimad)
- И другие

## Отказ от ответственности

SynapseOS это не дистрибутив linux, это новый проект который не имеет за собой компании или организации которая могла бы дать гарантий.
Ядро SynapseOS имеет открытый исходный код, вы можете сами удостовериться в отсутствии вредоносного ПО изучая файлы этого репозитория.
При использовании материалов вы обязуетесь соблюдать авторские права.
Я не несу ответственности за причиненный ущерб. Используйте на свой страх и риск.
