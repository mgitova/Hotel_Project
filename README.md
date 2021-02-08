# Hotel_Project

Програмата съхранява и обработва данните за стаите в хотела във файл.

След като приложението отвори даден файл, то трябва да може да извършва посочените по-долу операции, в допълнение на общите операции (open, close, save, save as, help и exit):

checkin <room> <from> <to> <note> [<guests>]
 ------------------------------------------------------------------------
Регистриране в стая с номер <room> от дата <from> до дата <to> и се добавя бележка <note>. 
Незадължителният параметър <guests> задава броя на гостите, настанени в стаята. 
Ако той не е указан, се счита, че броят на настанените гости е равен на броя на леглата в стаята.

Пример: checkin 229 2020-03-23 2020-03-31 The Simpsons

availability [<date>]
 ------------------------------------------------------------------------
Извежда списък на свободните стаи на дата <date>, ако не е зададена, се използва текущата дата.

checkout <room>
 ------------------------------------------------------------------------
Освобождаване на заета стая с номер <room>.

report <from> <to>
  ------------------------------------------------------------------------
Извежда справка за използването на стаи в периода от дата <from> до <to>. 
Извежда се списък, в който за всяка стая, използвана в дадения период, се извежда и броя на дните, в които е била използвана.

find <beds> <from> <to>
  ------------------------------------------------------------------------
Намиране на подходяща свободна стая с поне <beds> на брой легла в периода от <from> до <to>. 
При наличие на повече свободни стаи се предпочитат такива с по-малко на брой легла.

find! <beds> <from> <to>
   ------------------------------------------------------------------------
Да се реализира алгоритъм, който предлага спешно намиране на стая за важен гост в случай на липса на свободни стаи за даден период. 
Алгоритъмът да предлага разместване на настанените от най-много две стаи.

unavailable <room> <from> <to> <note>
 ------------------------------------------------------------------------
Обявява стаята с номер <room> от дата <from> до дата <to> за временно недостъпна и се добавя бележка <note>.
В стаята няма регистриран гост, но никой не може да бъде настанен в нея.

Пример:
unavailable 200 2018-06-01 2019-03-01 Under construction



