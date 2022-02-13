# [42Seoul] fract-ol
> miniLibX (mlx) 라는 간단한 그래픽 라이브러리를 이용하여 프랙탈 그리기\
[fract-ol](https://warm-salsa-f69.notion.site/fract-ol-040257364a354b2faeb54977a73d4b1f)\
[miniLibX mlx](https://warm-salsa-f69.notion.site/miniLibX-mlx-43703bbe0bbe47f3a2e82604c3b1910c)

## 프로젝트 소개
- mlx 라이브러리의 사용법을 익힌다.
- fractal에 대해 공부한다.
- GPU의 GLSL 같은 것을 사용할 수 없고 CPU로만 연산을 해야하는 상황에서 hook 만으로 어떻게 최적화를 해야할지 고민하게 된다.
- mlx 라이브러리의 코드는 주어진다.

## 주의 사항
다음 사항을 지키지 않으면 0점 받을 것이다.
- 코드는 [norm](https://warm-salsa-f69.notion.site/Norm-85024906b60243e99a060194620cef3e)을 준수해서 작성되어야 한다.
- 어떤 상황에서도 프로그램은 segment fault, bus error, dangling pointer 등으로 중단되어서는 안 된다. (평가자가 특정 상황을 저격해서 만들어 낼 수 있음)
- heap에 할당된 모든 메모리는 적절하게 해제되어야 한다. 메모리 누수가 생겨서는 안 된다.
- gcc -Wall -Wextra -Werror 플래그로 컴파일해야 한다.
- Makefile은 relink 되어서는 안 된다.

## 사용가능한 함수 (그 외 외부 라이브러리 함수 사용불가)
- malloc, free
- open, close, read, write
- printf
- perror, strerror, exit

## 구현해야 할 것
### Mandatroy part
- [Julia](https://ko.wikipedia.org/wiki/%EC%A5%98%EB%A6%AC%EC%95%84_%EC%A7%91%ED%95%A9)와 [Mandelbrot](https://ko.wikipedia.org/wiki/%EB%A7%9D%EB%8D%B8%EB%B8%8C%EB%A1%9C_%EC%A7%91%ED%95%A9) set을 시각화 해야 한다.
- 마우스 휠은 컴퓨터 한계까지 무한히 돌아야 한다.
- 프랙탈의 depth를 나타내기 위해 색을 사용해야 한다.
- 프로그램 파라미터로 어떤 프랙탈을 나타낼지 들어가야 한다. 파라미터가 비었거나 잘못 됐으면 가능한 파라미터와 속성들을 리스트해야 한다.
- 줄리아 셋은 파라미터를 통해 다르게 보여줄 수 있어야 한다.
- ESC를 누르면 종료해야 한다.
- minilibX의 images를 사용하는게 권장된다. (왜 사용하는지 이유도 알아야 되는 거임)

### Bonus Part
- 다른 프랙탈 하나를 더 구현하라.
- 마우스 포지션에 따라 줌을 하라.
- 방향키로 움직여라.
- 색을 바꿀 수 있는 기능을 넣어라.
