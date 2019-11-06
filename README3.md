# Обробка зображення

**Мета роботи:** Навчитися виконувати геометричне вирівнювання; морфологічні операції ерозії, дилатації, відкриття, замикання та застосовувати фільтри згладжування.

## Теоретичні відомості

### Геометричне вирівнювання
Іноді постає проблема вирівнювати зображення, наприклад коли камера дивиться збоку на площину. Тоді слід вирівняти отриману картинку так, ніби камера дивиться строго зверху.

Виділяються декілька основних видів перетворення: перспективне перетворення та білінійне.

**Перспективне перетворення**
![](https://lh4.googleusercontent.com/wwiJWl_VQYHqGqGVRAHnCDcSAFP8mFRql9yPa4xA_pCqR2iyHQ-p9we935QoT8mkVFHC64jpZIQTM1aylsOOgIKiraziIw3gmtRZlgKHN13GwpdoOmgeWjUM3VcsSCUAA2Kg8-0)

**Алгоритм**

1. Необхідно вказати координати декількох точок на зображенні і вказати в які точки вони повинні перейти. Потрібно не менше 4 точок для для пошуку перспективної проекції. Причому будь-які три точки не повинні лежати на одній прямій. В найпростішому випадку це просто 4 точки, що вказують, куди повинні перейти кути зображення:
    
    (A,B,C,D) -> [0,w] x [0,h]

2. Матрица перспективного перетворення M здійснює перетворення по правилу
    
    (x,y) -> M *(x,y,1) T

   За допомогою ф-ї getPerspectiveTransform знаходимо оптимальну матрицю перспективного перетворення OpenCV використовує 4 точки.
   
3. Дана матриця підставляється в ф-ю warpPerspective для отримання каліброваного зображення.

```
//будемо використовувати 4 точки.
const int K = 4;
cv::Point2f src[K]; //координати точок на зображенні
cv::Point2f dst[K]; //координати кінцевих точок

//координати A,B,C,D на зображенні



//повинні йти по годинниковій стрілці
// з лівого верхнього кута

//у відповідності з dst
src[ 0 ] = cv::Point2f( ..., ... );
src[ 1 ] = cv::Point2f( ..., ... );
src[ 2 ] = cv::Point2f( ..., ... );
src[ 3 ] = cv::Point2f( ..., ... );

//кінцеві точки; w и h - розміри результата
dst[ 0 ] = cv::Point2f( 0, 0 );
dst[ 1 ] = cv::Point2f( w, 0 );
dst[ 2 ] = cv::Point2f( w, h );
dst[ 3 ] = cv::Point2f( 0, h );

//рахуємо матрицю перетворення
Mat transform = getPerspectiveTransform( src, dst );
warpPerspective( image, imageResult, transform,                                                            
cv::Size( w, h ), INTER_LINEAR );
//отримуємо результат imageResult
```

**Білінійне перетворення**

Для білінійного перетворення можна використати функцію remap. Вона дозволяє вказати куди повинен перейти кожен піксель зображення і здійснити перетворення.
![](https://lh5.googleusercontent.com/Y4K_6UP1POT2gNetB5bhBchfx7UcIleXUS-ed632ir3U6a13ILZq0qckm5IYcKi_nYY5S60IbzFk7CIv909xyGg75GRhXBENFAXjjdZSujfly6zH7fPujj2EzHL3omS292bPa1U)

```
void remap (InputArray src,
  OutputArray dst,
  InputArray map1,
  InputArray map2,
  int interpolation,
  int borderMode=BORDER_CONSTANT,
  const Scalar& borderValue=Scalar())
```
**Морфологічні операції**

Приклад виконання ерозії

![](https://lh4.googleusercontent.com/I7hRKCnK3rChbJUIBIHZ5T-8vpFknYUq4EJUWAH2kX2hDgEQkZu3Ukm3lqOnSw00iJo9vHPrXLnN4Saw0bA6wubWWTot2td90mkkj3KCpWGI2v1S9XtvlOI4KknUgyjnVbsfAF0)

_Рис 1. Оригінальне зображення_

![](https://lh5.googleusercontent.com/zA3s5q4FlqXHpomKT0_wuxW4WtEGpfF6rTPHvnrQT4nNni5nwhS_mNXQEXhngBQZjgKxoXt_x8Qo5Jc6B1P8hUVhiPuttD_2Ibc19h796RcNTB2AyNKHJ6wR2iFq7HKNSTFH4vM)

_Рис 2. Після виконання морфологічної операції ерозії_

![](https://lh4.googleusercontent.com/TcXh7S7tRGED1nwz-XXIKqnR_uZJlP-b-4h6ddz0SOJ8JPfk_7iDIVUrIIcl60uJ2SczvjuRq-e274BIHcRqGAM4d_2-hl8saCF5cDx2d8Rt4dLcIswd4ealexRtMasTMYj1a98)

_Рис 3. Після виконання морфологічної операції дилатації_

Приклад виконання морфологічних операцій відкриття та замикання, коли в якості структуруючого елементу виступає хрестоподібний елемент (параметр MORPH_CROSS)
![](https://lh6.googleusercontent.com/ogtxdz_8O2A1cq7iOW4V-iEuKrpTOUctfzJ9tvMlci-ElfmxHxmhxs1qT5kUjqEhRmh8ioGKGPcYH5Kl66ROgAkOCKGR2myRyYactIxRXSLcpSCJjPCjdthNlK5X5ZMu9MeG-g0)

_Рис 4. Після виконання морфологічної операції відкриття_

![](https://lh6.googleusercontent.com/ogtxdz_8O2A1cq7iOW4V-iEuKrpTOUctfzJ9tvMlci-ElfmxHxmhxs1qT5kUjqEhRmh8ioGKGPcYH5Kl66ROgAkOCKGR2myRyYactIxRXSLcpSCJjPCjdthNlK5X5ZMu9MeG-g0)

_Рис 5. Після виконання морфологічної операції замикання_

**Фільтри згладжування**
Гаусівський фільтр дає саме природнє зображення. Медіанний фільтр виділяє області одного кольору, видаляє маленькі деталі. Фільтр усереднення підкреслює маленькі деталі.

Обгрунтування застосування:

1. Видалення шуму для наступного аналізу зображення. Частіше використовується гаусівська фільтрація, рідше медіанна.
2. Для виділення неоднорідності фону. Використовується гаусівський фільтр великого розміру, із вихідної картинки віднімається згладжене зображення.
3. Для підкреслення пікселів контурів об’єктів. Використовується два гаусівськи фільтри з розмірами a і 2a і виконується різниця.
4. Гаусівським фільтром моделюється ефект дефокусовання.
5. Несиметричним фільтром створюється ефект motionBlur.

Медіанна фільтрація зберігає різні переходи на зображення і ефективна для згладжування імпульсного шуму, алгоритм базується на знаходженні медіани середнього значення варіаційного ряду.

### Хід виконання

1. Створив проект на OpenCV
2. Підготував зображення сфотографоване під кутом
3. Написав з використанням графічної бібліотеки ImGui - графічний інтерфейс, через який користувач вибирає область на зображенні яку він хоче трансформувати (задає 4 точки на зображенні, починаючи з лівої нижньої)
4. Далі за допомогою перспективного перетворення трансформується область з криволінійної в прямокутну
```
cv::Mat transformedImg = transformArea();
```
```
cv::Mat transformArea()
{
	box = cv::minAreaRect(cv::Mat(transformPoints));

	cv::Point2f pts[4];
	box.points(pts);

	const cv::Point* point = &transformPoints[0];
	int n = (int)transformPoints.size();
	cv::polylines(img, &point, &n, 1, true, cv::Scalar(0, 255, 0), 1, cv::LINE_AA);
	cv::imshow("Image", img);

	cv::Point2f src_vertices[4];
	src_vertices[0] = transformPoints[0];
	src_vertices[1] = transformPoints[1];
	src_vertices[2] = transformPoints[2];
	src_vertices[3] = transformPoints[3];

	cv::Point2f dst_vertices[4];
	dst_vertices[2] = cv::Point(0, 0);
	dst_vertices[3] = cv::Point(0, box.boundingRect().height - 1);
	dst_vertices[0] = cv::Point(box.boundingRect().width - 1, box.boundingRect().height - 1);
	dst_vertices[1] = cv::Point(box.boundingRect().width - 1, 0);

	cv::Mat warpMatrix = getPerspectiveTransform(src_vertices, dst_vertices);

	cv::Mat rotated;

	cv::Size size(box.boundingRect().width, box.boundingRect().height);
	warpPerspective(originalImg, rotated, warpMatrix, size, cv::INTER_LINEAR, cv::BORDER_CONSTANT);

	return rotated;
}
```
Функція повертає готову трансформовану матрицю а далі вивід у вікно
![](https://github.com/malynovskiy/ai_labs/blob/lab3/outcomes/ImagePerspectivetransformation.gif?raw=true)

6. Далі обробка зображення за допомогою морфологічних операцій ерозії, дилатації, відкриття та замикання

![](https://github.com/malynovskiy/ai_labs/blob/lab3/outcomes/orgImg.PNG?raw=true)

_Рис. Початкове зображення_

Застосування операції ерозії та дилатації за допомогою відповідних фунцій OpenCV
```
cv::Mat erosed;
	cv::Mat element = cv::getStructuringElement(morp_shape,
		cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		cv::Point(erosion_size, erosion_size));
	cv::erode(src, erosed, element);
```
```
cv::Mat dilated;
	cv::Mat element = cv::getStructuringElement(morp_shape,
		cv::Size(2 * dilatation_size + 1, 2 * dilatation_size + 1),
		cv::Point(dilatation_size, dilatation_size));
	cv::dilate(src, dilated, element);
```
![](https://github.com/malynovskiy/ai_labs/blob/lab3/outcomes/eroded.PNG?raw=true)

_Рис. Зображення після ерозії_

![](https://github.com/malynovskiy/ai_labs/blob/lab3/outcomes/dilated.PNG?raw=true)

_Рис. Зображення після дилатації_

Далі виконання операцій відкриття та замикання
```
cv::Mat revealed = erosion(secondaryImg, 2, cv::MORPH_CROSS);
revealed = dilatation(revealed, 1, cv::MORPH_CROSS);
```
```
cv::Mat locked = dilatation(secondaryImg, 2, cv::MORPH_CROSS);
locked = erosion(locked, 1, cv::MORPH_CROSS);
```
![](https://github.com/malynovskiy/ai_labs/blob/lab3/outcomes/revealed.PNG?raw=true)

_Рис. Зображення після операції відкриття_

![](https://github.com/malynovskiy/ai_labs/blob/lab3/outcomes/locked.PNG?raw=true)

_Рис. Зображення після операції замикання_

7. Використання розмиття по Гауссу і компонування у відеофайл
```
cv::Mat diafilmImg;
for (int i = 1, k = 1; i < 201; i += 2, ++k)
{
	cv::GaussianBlur(secondaryImg, diafilmImg, cv::Size(i, i), 0, 0);
	char file_name[22];

	sprintf_s(file_name, "outcomes/image%d%d%d.bmp", i / 100, i / 10, i % 10);
	cv::imwrite(file_name, diafilmImg);
}
```
![](https://github.com/malynovskiy/ai_labs/blob/lab3/outcomes/image001.gif?raw=true)

### Висновок
Під час виконання лабораторної роботи я пригадав деталі використання бібліотеки графічного інтерфейсу ImGui та навчився трансформувати криволійнійну область зображення у прямокутну і навпаки при потребі. Також я навчився застосовувати морфологічні операції над зображенням, а саме ерозію, дилатацію, замикання та відкриття. Ще навчився накладати ефект розмиття на зображення та компонувати зображення у відеофал за допомогою утиліти VirtualDub.
