# Лабораторна робота №4. Розпізнавання об’єктів шляхом аналізу габаритних прямокутників  
## Мета роботи: Навчитись розпізнавати об’єкти шляхом аналізу габаритних прямокутників.
## Хід виконання

1. Створіть новий консольний проект для OpenCV.

2. Виберіть довільне зображення для пошуку об’єктів згідно варіанту. 
  - У моєму випадку варіант №8, а це медалі.
  
  ![](https://github.com/malynovskiy/ai_labs/blob/lab4-medals-recognition/outcomes/src.PNG?raw=true)
  
  _Рис. Оригінальне зображення_
```
Mat src, src_gray;
src = imread("images/medals.png", IMREAD_COLOR);

if (src.empty())
{
	std::cout << "Some error, couldn't read the file!" << std::endl;
	return -1;
}
```
3. Зображення приведіть до монохромного вигляду.

```
cvtColor(src, src_gray, COLOR_BGR2GRAY);
```
![](https://github.com/malynovskiy/ai_labs/blob/lab4-medals-recognition/outcomes/gray.PNG?raw=true)

_Рис. Монохромне зображення_

4. Розпізнайте всі об’єкти шляхом аналізу габаритних прямокутників.

Для того щоб алгоритм з більшої ефективністю розпізнавав наші об'єкти, я застосував фунцію threshhold, яка перетворює зображення в ще простіший вигляд.
```
threshold(src_gray, src_gray, 178, 150, THRESH_BINARY);
```
![](https://github.com/malynovskiy/ai_labs/blob/lab4-medals-recognition/outcomes/treshold.PNG?raw=true)

_Рис. Зображення після threshold_

А далі наш алгоритм габаритних прямокутників.
```
const int minRectDim = 120; //макс і мін розміри шарів
const int maxRectDim = 150;

for (int y = 0; y < src.rows; y++) 
{
	for (int x = 0; x < src.cols; x++) 
	{
		int value = src.at<uchar>(y, x);
		if (value == 255) 
		{ 
								//якщо значення- 255, то заливаємо значенням 200
								//щоб повторно не заливати
			Rect rect;			// буде містити габаритний прямокутник, що ми залили
			int count = floodFill(src_gray, Point(x, y), Scalar(200), &rect);

			//перевіряємо розміри залитої області
			if (rect.width >= minRectDim && rect.width <= maxRectDim
				&& rect.height >= minRectDim && rect.height <= maxRectDim)
			{
				//центр області
				int x = rect.x + rect.width / 2;
				int y = rect.y + rect.height / 2;

				//радіус кола
				int rad = ((rect.width + rect.height) / 4);

				//коло товщиною 2 пікселя
				circle(src, Point(x, y), rad, Scalar(255, 0, 255), 2);
			}
			
	}	
}
```

![](https://github.com/malynovskiy/ai_labs/blob/lab4-medals-recognition/outcomes/final.PNG?raw=true)

_Рис. Фінальне зображення, зі знайденими медалями_
