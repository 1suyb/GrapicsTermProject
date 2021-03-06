# Grapics Team Project   
###### 전남대학교 2022년도 1학기 컴퓨터 그래픽스 수업 Project입니다.
#### 제작
+ 단정욱
+ 박수연
+ 정용진
--------
## 실행
###### 아래 링크에서 download받아 압축을 풀어 실행해 볼 수 있습니다.
https://github.com/1suyb/GrapicsTermProject/blob/main/GrapicsTeamProject.zip
#### 조작
+ w : 전진
+ a : 좌회전
+ s : 후진
+ d : 우회전
+ f : 시점 변경
+ l : 낮조명
+ ; : 밤조명

--------
## 구현
#### 모델
+ obj 파일
  + 3점 매쉬의 파일들 사용 4점 메쉬인 경우 Blender을 이용하여 3점매쉬로 수정
  + ModelClass의 LoadObj 함수로 Obj를 import함
+ 이동 및 회전, 충돌
  + Position과 Rotation을 설정할 수 있게함.
  + 한번에 연산된 Position과 Rotation을 적용하여 연산을 간단하게함.
  + 충돌연산에 사용될 Colider 벡터를 구함.
#### 충돌처리
+ 사각형 메쉬의 충돌감지를 구현함
  + 1차로 구형의 범위의 충돌을 검사한후 1차 감지에 걸린 오브젝트만 2차 사각 범위 충돌 감지
  + 사각 범위 충돌 감지는 구형 충돌범위 검사보다 조금 더 많은 연산을 필요로 하므로 일정 범위 이내의 오브젝트만 사각범위 충돌감지를 함
#### 이동
+ 전진, 후진 방향키를 누르면 가속도가 0.5로 설정
+ 40ms마다 속도에 가속도가 매번 더해지며, 일정 속도이상으로는 올라가지 못함.
+ 매 40ms마다 속도가 0.3씩 감소 (마찰력)
+ 조금 그럴싸한 물리를 구현함
#### 폭발(particle)
+ 폭발이 시작되면 파티클과 debis를 일정한 개수만큼 생성
+ 매40ms 마다 파티클과 잔해들의 위치를 재계산해 랜더링
+ 500번 루프 후 제거됨
#### 랜덤 오브젝트
+ 트랙위에 랜덤한 위치에 상자 생성
+ 충돌하여 제거시 랜덤한 위치에 새로 생성함

