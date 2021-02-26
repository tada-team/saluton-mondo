# Библиотека

JS-модуль находится в папке `revert`, подключение в проект и использование производится следующим образом:

```javascript

const revert = require('./revert/string')

const text = 'Текстовые данные для смешивания'

const mixed = revert(text)

console.log(mixed)

```

# Пример

[Здесь](./shuffler.js) находится готовый скрипт, конвертирующий текст из `STDIN`.

Примеры:
```bash
$ node shuffler.js < ../data/sample.txt # вывод в STDOUT
$ node shuffler.sh < ../data/sample.txt > text.out # вывод в файл text.out
```
