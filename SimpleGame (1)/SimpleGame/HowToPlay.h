/*

게임 설명

- 북쪽에서는 공중몹과 지상몹이 일정 주기로 생산

- 남쪽에서는 좌클릭(지상) 우클릭(공중) 생산가능

- 화면흔들림은 너무 어지러울  수 있어서 건물이 발사하는 총알이 건물에 부딪힐 경우만 화면흔들림

- 총알 화살 파티클, 케릭터 전부 스프라이트 이미지 사용

- 총알 발사시 사운드 출력, 캐릭터 생성시 사운드 출력,  게임 배경음존재

- 캐릭터 충돌 이후 적군이 사라져도 움직이지 않는것은 의도한 것. (움직이다가 위치 발각되면 은엄폐컨셉)

- 오브젝트 속성중에 어택 타입, 유닛 타입, 상태 변수 추가

- 유닛 타입은 이 유닛이 지상유닛인지 공중유닛인지 파악, 공격타입은 공격가능한 유닛 대상 나타냄 , 상태변수는 유닛이 멈추었는지 움직이는지에 대한 값

- 건물이 모두 없어진 플레이어가 있다면 메인루프 탈출하며 게임 종료


*/