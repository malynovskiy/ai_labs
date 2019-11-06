# Лабораторна робота №2. Гістограма зображення
**Мета роботи:** Навчитись виконувати створювати додатки з найпростішими перетвореннями зображення.

## Теоретичні відомості

### Гістограма зображення
Гістограма - це графік розподілу півтонів зображення, в якому по горизонтальній осі представлена ​​яскравість, а по вертикалі - відносна кількість пікселів з ​​даними значенням яскравості.


Обчислення гістограми для 8-бітного напівтонового зображення може бути запрограмовано так:

```
vector <int> hist (256, 0);

for (int y = 0; y <h; y + +) 
{
     for (int x = 0; x <w; x + +) 
     {
         int color = image.at <unsigned char> (y, x);
         hist [color]++;
     }
}
```
![alt text](https://lh4.googleusercontent.com/GYdth72HGtt1sc-ez_N21vKbLXyhktzIqrxRLRx6UeTwmCGgln8wSxswq-RFnIuOO5FbQDiEGe8tjaOHd1uV2cJs7yaq9WDIZPHdXMR8FKF1RKJJDCeG0vKm18-c0chXzw2OR3w)

_Рис. Вихідне зображення та його гістограма_

### Нормалізація зображення за яскравістю
![alt text](https://lh6.googleusercontent.com/cYJizEmBBybKaUPYNwLztnlQ1328OSu_ZYBOLRNoemmXwMb99i00_9cZDLA23ZRiwmCZsjHJpuRua7d2Lgbnf-rqNmGZuRnXX84IQVHr2GIsKoX98uwwSKs9Rq4w7gyo5KsWziA)

_Рис. Вихідне зображення_

![alt text](https://lh4.googleusercontent.com/qoF3hMCamKvjGzmWEgsr42KZDnw9O63Ai_Ml1zjiLpThrsQ1MjN8kP_GwhXpJZgQaBZDn5z-GSl_5g0XKz7xu40Zb_dM_B0odnXqhyc5YHj0aEuVXhCdkWdPIigPpRdTGvaHDsw)

_Рис. Гістограма_

Нехай буде дано 8-бітове зображення A[0;255]. Тоді шукаємо Amin по всіх x,y і Amax.

Amin=min(A(x,y)) для всіх x,y

Amax=max(A(x,y)) для всіх x,y

![alt text](https://lh4.googleusercontent.com/fgw5DsZ5hATkZT6hhaatG-HvvIEC8JDTl1UUOVw2noCUNlcyXcHSA6Wa3QTgxohWI-6M7Gx16KDstGtHIN_He6gCeih2GIUi9yahFUxdbsJSxJlut68e0NMVD72efNlLX4l6SXY)

В результаті діапазон яскравості лінійно розтягнеться на всю область. Зображення стане більш контрастним, так як відстань між сусідніми областями яскравості збільшиться.

![](https://lh3.googleusercontent.com/6EMSUm_9wVk2C9_sKKgwVGB369wwHeULsU3Ypzhj0uuQrpIVO047SXjdXfKLkseQUgvMbKxP7UTJLQSqqijfrkCgjApa6uDkKBr2Uyu9Cqk76glKZ0DbrnOLCKZNW_W7r1p3f9Y)

_Рис. Нормалізоване зображення_

![](https://lh4.googleusercontent.com/jzB_1NaWxgnV_ksNanmQHHjmCOlKI_B8GlAQXKzk8R4iMx_yuB_Fzm0DprOWTa8q9y2eKyif22pY83km_yyifSZmrq39rWEDmvAUVbryH15X6OYTkE3bySZ8kliQ_zpKixtW0QE)

_Рис. Гістограма_
### Еквалізація гістограми
![](https://lh3.googleusercontent.com/dr7oeXiQJLB_I_3-JGiBNaLDh-ksAW-B_c9wfUHz15-2taq8mtC9p4XAC4HS0EmU9Y0BeUzEA-0oWrk0vaEI3b1C963rCIcWYmvk29h6KcyMMjygwy4nF_NTjqn2594YY6TFeqc)

_Рис. Зображення з еквалізованою гістограмою_

![](https://lh6.googleusercontent.com/H_u-BXQJu-2G2f3aBoZkwewtyXL3HYa6JBW0_Miiqb_CCAJmCtTws3cgIUgIymI7D7c3l-E7L8EHWweimdZB-dKl2ZEKK1x9JXOVcLzZ8sj8E-inCAVL9T8gsqth11LE67Bt5M0)

_Рис. Гістограма_

Метою еквалізації є таке перетворення, щоб гістограма яскравості максимально близько відповідала рівномірному закону розподілення, тобто вихідне зображення повинно містити однакову кількість пікселів для кожного значення яскравості.

![](https://lh4.googleusercontent.com/JNzMYNV-CRakUckQ0wjWh2wUWE0AUDJD6_lYRaTQoa-xVRQvOYx5N3vE_kSginhmwZqg7zKC0S9xMBanO_1wVUMxjY7Gg5Q4Kgezi7C86pX2lr5vO9ZV4wlXlcFsLhjRm-JfWoQ)

Алгоритм перетворення для 8-бітового зображення

В значення яскравості 0 на гістограмі переходять пікселі з яскравістю 0,1,2… поки їх кількість не перевищить q. Аналогічно в значення 1 переходять пікселі і(0)+1, і(0)+2…

0: 0,1,2…                 і(0)
1: і(0)+1, і(0)+2…і(1)
2: і(1)+1, і(1)+2…і(2)

![](https://lh3.googleusercontent.com/hqZZobHqRbh-fIK-iVEiOTjTMaljVWdXy0IXRNKjqNYB7OzLi1eA72vESX9bIw0Bm-T4VWLUh8ROgurU0tBhQcifwiW4551MviaVXVWEjC4saaBFeyspVL5xH4F1X_lxM6KsSFs)

Коли гістограма в діапазоні від Amin до Amax приблизно однакова результат еквалізації майже не відрізняється від нормалізації за яскравістю, інакше дозволяє виділити раніше непомітні деталі.
## Хід виконання

1. Трансформація зображення у півтоновий вигляд (за допомогою функції cvtColor)
```
cv::Mat grayImg;
cv::cvtColor(image, grayImg, cv::COLOR_BGR2GRAY);
```
2. Створення гістограми власними силами за допомогою власної функції getHistImg
```
cv::Mat histImg = getHistImg(grayImg, 3.0f, 3.0f);
```
```
cv::Mat getHistImg(const cv::Mat& img, float scaleX = 1, float scaleY = 1)
{
	const int histWidth = 256;
	const int histHeight = 64;
  
  // Заповнення гістограми
	std::vector<int> histData(256, 0);
	for (int y = 0, h = img.rows; y < h; ++y)
	{
		for (int x = 0, w = img.cols; x < w; ++x)
		{
			int color = img.at<uchar>(y, x);
			histData[color]++;
		}
	}
 
	cv::Mat histogram = cv::Mat(cv::Size(histWidth * scaleX, histHeight * scaleY), CV_8UC3, cv::Scalar(0.0, 0.0, 0.0));
	int histMax = *(std::max_element(histData.begin(), histData.end()));
   
	for (int i = 0; i < 255; ++i)
	{
		int currVal = histData[i];
		int nextVal = histData[i+1];

		cv::Point p1 = cv::Point(i * scaleX, histHeight * scaleY);
		cv::Point p2 = cv::Point(i * scaleX + scaleX, histHeight * scaleY);
		cv::Point p3 = cv::Point(i * scaleX + scaleX, (histHeight - nextVal * histHeight / histMax) * scaleY);
		cv::Point p4 = cv::Point(i * scaleX, (histHeight - currVal * histHeight / histMax) * scaleY);

		cv::Point points[] = {p1, p2, p3, p4, p1};
		cv::fillConvexPoly(histogram, points, 5, cv::Scalar(255, 255, 255));
	}
	return histogram;
}
```
Та вивід зображення і гістограми
```
cv::namedWindow("histogram gray", cv::WINDOW_AUTOSIZE);
cv::imshow("histogram gray", histImg);
```
![](https://github.com/malynovskiy/ai_labs/blob/lab2/outcomes/semi.PNG?raw=true)

_Рис. Вихідне зображення_

![](https://github.com/malynovskiy/ai_labs/blob/lab2/outcomes/histo.PNG?raw=true)

_Рис. Гістограма_

3. Створення гістограми за допомогою функцій OpenCV
```
const int histWidth = 256;
const int histHeight = 64;

float range[] = { 0, 256 }; 
const float* histRange = { range };

cv::Mat histo;
cv::calcHist(&grayImg, 1, 0, cv::Mat(), histo, 1, &histWidth, &histRange);
```
4. Розкладення зображення по каналах 
```
std::vector<cv::Mat> bgr_planes;
cv::split(image, bgr_planes);
```
5. Далі нормалізація нашого зображення 
```
cv::Mat normalizedImg;
normalizeImg(image, normalizedImg);
```
```
void normalizeImg(const cv::Mat& img, cv::Mat& norm)
{
	img.copyTo(norm);

	double imgMax, imgMin;
	cv::minMaxLoc(norm, &imgMin, &imgMax);

	for (int y = 0, h = norm.rows; y < h; ++y)
		for (int x = 0, w = norm.cols; x < w; ++x)
			norm.at<uchar>(y, x) = 255 * ((norm.at<uchar>(y, x) - imgMin) / (imgMax - imgMin));
}
```
![](https://github.com/malynovskiy/ai_labs/blob/lab2/outcomes/norm.PNG?raw=true)

_Рис. Нормалізоване зображення_

![](https://github.com/malynovskiy/ai_labs/blob/lab2/outcomes/normHist.PNG?raw=true)

_Рис. Гістограма нормалізованого зображення_ 

6. Еквалізація

Оскільки нормалізацію ми робили власними силами, еквалізацію проведемо за допомогою функції OpenCV
```
cv::Mat equalizedImg;
cv::equalizeHist(image, equalizedImg);
```
![](https://github.com/malynovskiy/ai_labs/blob/lab2/outcomes/equalized.PNG?raw=true)
_Рис. Еквкалізоване зображення_ 

![](https://github.com/malynovskiy/ai_labs/blob/lab2/outcomes/equalizedHist.PNG?raw=true)
_Рис. Гістограма еквкалізованого зображення_ 

![](https://github.com/malynovskiy/ai_labs/blob/lab2/outcomes/vs.gif)
