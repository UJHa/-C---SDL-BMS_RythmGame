# -C-SDL-BMS_RythmGame
bms파싱하여 노트를 배치한 리듬게임


- 실행파일 다운로드 방법
  1. 실행파일.zip 다운로드 후 압축 해제
  2. 실행파일/Release/RythmGame.exe 실행


- 게임 플레이 키

  곡 선택 : 상하좌우, space키

  키 입력 : A,S,D,F,G,H,J,K

todoList
2018.04.02=========================================================
- InputManager 구현(완료0402)
- keyDown 구현 >> update에서 실행으로 변경(완료0404)
- 건반 애니메이션(눌렀을시 Track 애니메이션)
  -track 위에 애니메이션 출력(완료0405)
  -keyDown,hold 시에만 키 누른 건반으로 보이도록 변경(완료0405)
  -각 키별로 입력 시 해당 건반이 애니메이션 되도록 변경(완료0405)
- 건반 위 트랙에 눌렀을때 애니메이션
  --keyboardspr, noteboomspr, trackEffect 리펙토링(같은 y값 다른 x값 주는 csv로 묶어서 처리하기)

- bga 애니메이션 구현
- 일시정지 버튼 구현
