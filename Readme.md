#Grapics Term Project
전남대학교 2022년도 1학기 컴퓨터 그래픽스 수업 Project입니다.
--------
## 개발에 앞서! 프로젝트 설정
### Nuget설치
> freeglut.3.0.0.v140 1.0.2
> glew.v140 1.12.0
> glm 0.9.9.800

### Solution 설정
> GrapicsProject -> 속성 -> C/C++ -> 추가 포함 디렉터리 ..\include 추가
> GrapicsProject -> 속성 -> 링커 -> 추가 라이브러리 디렉터리 ..\Library 추가
> GrapicsProject -> 속성 -> 입력 -> 추가 종속성 glaux.lib 및 legacy_stdio_definitions.lib 추가

### 빌드 설정
> Debug, x86 사용
> 만약 자신이 사용하는 비쥬얼스튜디오가 2019라면
> GrapicsProject -> 속성 -> 일반 -> 플랫폼 도구 집합을 자기 버전으로 설정. **2022 버전으로 업그레이드를 권장합니다.