# examCards

## Задание

Преподавателю надо печатать билеты и при этом потратить как можно меньше бумаги. Упорядочите билеты так, чтобы они занимали наименьшее число листов A4, между ними было место для разреза, у листа были поля сверху и снизу, и ни один билет не оказался «разорван» между листами.

## Теоретическая часть

Для решения предложенного задания его можно свести к задаче о мультипликативном рюкзаке.

> Мультипликативный рюкзак (англ. Multiple Knapsack Problem) — есть N предметов и M рюкзаков (M <= N). У каждого рюкзака своя вместимость W_i. Задача: выбрать M непересекающихся множеств, назначить соответствие рюкзакам так, чтобы суммарная стоимость была максимальна, а вес предметов в каждом рюкзаке не превышал его вместимость.

### Формулировка задачи

Дано N предметов и M рюзаков (M <= N). N_i - вес i-ого предмета, W_j - вместимость j-ого рюкзака. Необходимо разложить предметы по рюкзакам таким образом, чтобы их суммарный вес в каждом рюкзаке не превышал его вместимость и при этом использовалось наименьшее количество рюкзаков, то есть:
* sum(N_i\*x_ij) -> max
* sum(N_i\*x_ij) <= Wj, i=1..N, j=1..M
* sum(x_ij) = 1 i=1..N, j=1..M

x_ij = 1, если i-ый предмет назначен j-тому рюкзаку, иначе x_ij = 0.

### Варианты решения

Задачу о рюкзаке можно решить несколькими способами:
* Перебирать все подмножества набора из N предметов. Сложность такого решения O(2^N).
* Методом Meet-in-the-middle. Сложность решения O((2^(N/2))\*N)
* Метод динамического программирования. Сложность — O(NW).

Применение динамического программирования для задачи мультипликативного рюкзака нецелесообразно. Используются вариации метода ветвей и границ.

### Формат входных и выходных данных

* Входные данные: массив из весов предметов и массив из вместимостей рюкзаков.
* Выходные данные: двумерный двоичный массив, в котором строки будут показывать принадлежность предметов рюкзаку (1 - принадлежит, 0 - не принадлежит).

### План решения задания

Использование метода поиска с возвратом (backtracking) на языке C/C++.
> Решение задачи методом поиска с возвратом сводится к последовательному расширению частичного решения. Если на очередном шаге такое расширение провести не удается, то возвращаются к более короткому частичному решению и продолжают поиск дальше. Данный алгоритм позволяет найти все решения поставленной задачи, если они существуют. Для ускорения метода стараются вычисления организовать таким образом, чтобы как можно раньше выявлять заведомо неподходящие варианты. Зачастую это позволяет значительно уменьшить время нахождения решения.
