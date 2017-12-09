# examCards

## Задание

Преподавателю надо печатать билеты и при этом потратить как можно меньше бумаги. Упорядочите билеты так, чтобы они занимали наименьшее число листов A4, между ними было место для разреза, у листа были поля сверху и снизу, и ни один билет не оказался «разорван» между листами.

Теоретическая часть вынесена в отдельный файл.

### Формат входных и выходных данных

* Входные данные: список из весов предметов (высот экзаменационных билетов в мм) через пробел в порядке возрастания нумерации билетов. Например: "25 28 30 41 37" (высоты билетов с 1 по 5 соответственно).
* Выходные данные: номер листа и номера билетов, которые нужно расположить на этом листе. Например: "Лист 2: 17, 10, 26, 5, 11".

## Инструкция по использованию программы
Программа компилируется в командной строке с помощью компилятора g++ следующей командой:

*g++ -std=c++14 sources/main.cpp sources/cardsPacking.cpp -o binpack*

где binpack - название программы, может быть произвольным.

Затем происходит ее запуск:

*./binpack tests/001.txt tests/001.ans*

где 001.txt - текстовый файл со входными параметрами (формат описан выше);

001.ans - текстовый файл с выходными параметрами.

## Описание тестов
### Тест 1
Входной файл 001.txt

Входной файл содержит 51 число (высоту 51 экзаменационного билета). Тест проверяет работу программы при корректных входных данных.
### Тест 2
Входной файл 002.txt

Входной файл содержит числа (высоты экзаменационных билетов), сумма одного из которых со значениями верхнего и нижнего полей превышает высоту листа А4. В командной строке появляется ошибка, код программы дальше не выполняется.
### Тест 3
Входной файл 003.txt

Входной файл содержит числа (высоты экзаменационных билетов), один из которых равен нулю. Так как высота экзаменационного билета не может быть равной нулю, то в командной строке появляется ошибка, код программы дальше не выполняется.

### Тест 4
Входной файл 004.txt

Тест проверяет входной файл на наличие в нем каких-либо данных. Если он пуст, то в командной строке появляется ошибка, код программы дальше не выполняется.

### Тест 5
Входной файл 005.txt

Входной файл теста содержит высоты билетов, сумма которых равна высоте листа А4 без верхнего поля (-10 мм). Тест проверяет работу алгоритма в случае, когда какой-нибудь лист полностью заполняется. В случае высот, содержащихся в этом примере, это будут билеты 6 и 8.

### Тест 6
Входной файл 006.txt

Входной файл теста содержит высоты билетов, сумма которых на единицу меньше высоты листа А4 без верхнего поля (-10 мм). Тест проверяет работу алгоритма в случае, когда на каком-нибудь листе остается 1 мм свободного места. В случае высот, содержащихся в этом примере, это будут билеты 3 и 4.

## Логика работы программы
Программа открывает файл со входными данными и для каждого значения "высоты билета" создает пару "номер_билета - высота". Выполняется алгоритм Best Fit Decreasing, то есть сначала происходит сортировка этих пар по невозрастанию высот билетов, а затем выполняется алгоритм Best Fit. В процессе его выполнения программа создает объекты типа Bin (контейнер - в нашей задаче это лист А4), содержащие исходную вместимость контейнера (высота листа А4), оставшуюся свободную часть листа (в мм) и вектор уже содержащихся билетов на этом листе. После завершения выполнения алгоритма программа записывает ответ задачи в текстовый файл в соответствии с форматом выходных данных.

## Оценка сложности и использования памяти основными алгоритмами
### Алгоритм Best Fit Decreasing (BFD, Наилучший подходящий с упорядочиваем)
В данном алгоритме для каждого предмета сначала происходит поиск подходящего контейнера, а потом предмет помещается в контейнер. В худшем случае, когда остался последний предмет (под номером n), а все предыдущие предметы (n-1) были помещены каждый в свой отдельный контейнер, а n-ый предмет не помещается ни в один из существующих, при поиске подходящего контейнера необходимо просмотреть все существующие контейнеры. Сложность такого поиска O(n). Поиск необходимо выполнить для каждого из n элементов. Таким образом, общая сложность алгоритма O(n^2).

В памяти необходимо хранить n предметов, которые алгоритм сортирует по контейнерам, поэтому использование памяти O(n).

## Использование структур данных и обоснование их выбора
*"В любой непонятной ситуации используй вектор." Тарасов Кирилл, 2016 (с)*

С целью удобства для контейнеров создана своя структура Bin для хранения оставшегося места в контейнере и размеров предметов, находящихся в нем.

Билеты хранятся в векторе типа "пары", чтобы каждому предмету был соотнесен его размер. Вектор использован для удобства - он динамический, есть быстрый доступ к элементу и возможна необходимая для алгоритма сортировка.

В остальных случаях также используется вектор из-за удобства использования и быстрого доступа к элементам.
