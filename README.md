# Лабораторна робота №1 **"Ознайомлення з бібліотекою OpenCV"**
**Мета роботи:** ознайомитись з бібліотекою OpenCV. Навчитись завантажувати зображення засобами OpenCV. створювати додатки з найпростішими перетвореннями зображення.

**Теоретичні відомості**
*OpenCV* (англ. Open Source Computer Vision Library, бібліотека (фреймворк) комп'ютерного зору з відкритим вихідним кодом) - бібліотека алгоритмів комп'ютерного зору, обробки зображень та чисельних алгоритмів загального призначення з відкритим кодом. Реалізована на C/C++, Python, Java, Ruby, Matlab, Lua та інших мов. Може вільно використовуватися в академічних та комерційних цілях - поширюється на умовах ліцензії BSD.
Підключення OpenCV до VisualStudio
Припускаємо, що середовище розробки Microsoft Visual Studio і бібліотека OpenCV вже встановлені. Якщо ні, тоді встановлюємо. Для того щоб встановити бібліотеку OpenCV потрібно скачати архів останньої версії бібліотеки за адресою  http://sourceforge.net/projects/opencvlibrary/files/latest/download та розпакувати в потрібну директорію. Нехай це буде C:\OC\OpenCV2.4.
1. Запускаємо Visual Studio
2. Створюємо новий пустий проект
3. Налаштовуємо шляхи до бібліотек OpenCV.
Натискаємо Alt + Enter для отримання вікна властивостей проекту або клік правою кнопкою мишки на назві проекту у вікні Solution Explorer.
В пункті Configuration Properties – VC++ Directories - Additional Include Directories додаємо нові директорії для щойновстановленої OpenCV: "C:\OC\OpenCV2.4\build\include", "C:\OC\OpenCV2.4\build\include\opencv".
Аналогічним чином задаємо шляхи для інших директорій:
- *VC++ Directories*  - Library Directories - Additional Library Directories: C:\OC\OpenCV2.4\build\x86\vc10\lib 
- *Linker* - Input - Additional Dependencies: 
  - Debug: opencv_core243d.lib; opencv_features2d243d.lib; opencv_highgui243d.lib; opencv_imgproc243d.lib
  - Release: opencv_core240.lib; opencv_features2d240.lib; opencv_highgui240.lib; opencv_imgproc240.lib (можна не задавати, потрібно буде для release компіляції). 

Переключення між версіями компіляції відбувається за допомогою випадаючого вікна навпроти напису Configuration. Зверніть увагу, що ми використовуємо версію бібліотеки 2.4. Тому якщо ви завантажили іншу версію, то назви файлів відрізнятимуться. Наприклад, для версії 2.46 файли будуть наступні: opencv_core246d.lib; opencv_features2d246d.lib; opencv_highgui246d.lib; opencv_imgproc246d.lib.

Ці бібліотеки також можна задати безпосередньо в коді програми за допомогою директив препроцесора і вам непотрібно буде здійснювати вищенаведені операції для Linker - Input - Additional Dependencies

Приклад коду
```
// Директива препроцесора для підключення потрібних бібліотек,
// в цьому випадку можна не налаштовувати властивості проекту
// Linker - Input - Additional Dependencies
#ifdef _DEBUG
#pragma comment(lib, "opencv_core243d.lib")
#pragma comment(lib, "opencv_features2d243d.lib")
#pragma comment(lib, "opencv_highgui243d.lib")
#pragma comment(lib, "opencv_imgproc243d.lib")
#else
#pragma comment(lib, "opencv_core243.lib")
#pragma comment(lib, "opencv_features2d243.lib")
#pragma comment(lib, "opencv_highgui243.lib")
#pragma comment(lib, "opencv_imgproc243.lib")
#endif
```
Також можуть бути нюанси пов’язані з розрядністю операційної системи, компілятора і фреймворку (32-х розрядна і 64-х розрядна). Тому уважно перевіряйте назви файлів та розрядність процесора.

4. Додаємо в змінній Windows PATH шляхи до dll - С:\OC\Opencv2.4\build\x86\vc10\bin\ або можна просто скопіювати потрібні dll в папки Release і Debug вашого проекту.
Якщо шлях в Windows PATH не прописати, а ви не знаєте які файли потрібно копіювати тоді при запуску вашого проекту будуть виникати помилки завантаження dll бібліотек, приклад цього зображено на рис 3.

## Хід роботи ##

1) Для початку піключаємо всі необхідні нам хедери
```
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
```
2) Далі завантажуємо наше зображення в відповідну структуру даних cv::Mat
```
std::string picture;
if (argc != 2)
 picture = "picture.jpg";
else
 picture = argv[1];

cv::Mat image = cv::imread(picture, cv::IMREAD_COLOR);

if (image.empty())
{
 std::cout << "Some error, couldn't read the file!" << std::endl;
 return -1;
}
```
3) Зменшуємо розмір нашого зображення за допомогою функції cv::resize()
```
cv::Mat resizedImg;
cv::resize(image, resizedImg, cv::Size(), 0.3, 0.3, cv::INTER_AREA);
```
4) Застосування розмиття по-Гауссу нашого зображення
```
cv::Mat gaussianBlur;
for (int i = 51; i > 1; i -= 2)
{
 cv::GaussianBlur(resizedImg, gaussianBlur, cv::Size(i, i), 0, 0);
 cv::imshow("Gaussian BLURRRRR!", gaussianBlur);

 cv::waitKey(10);
}
 cv::imshow("Gaussian BLURRRRR!", resizedImg);
 cv::waitKey(0);
 ```
 5) І на кінець видалення всіх вікон
 ```
 cv::destroyAllWindows();
 ```
