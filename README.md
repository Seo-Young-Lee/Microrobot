# Microrobot
version 1 QIT protocol 기반의 구조체 정의

modbus.cpp은 modbus TCP/IP 통신 관련 함수들, matrix.cpp은 행렬 연산 함수들 정의.

current_cal.cpp에는 코일데이터(csv)를 읽어서 LUT를 만드는 LUT_init 함수,
자기장ref, 위치를 입력으로 받아서 LUT 기반으로 interpolation한 뒤, 역행렬 계산하여 전류ref 생성하는 get_cur_ref 함수 정의.

functions.cpp에는 일정 시간마다 get_cur_ref를 실행하는 input_to_cur_ref 함수,
일정 시간마다 외부 modbus 모듈의 데이터를 읽고, sys_mode_decision 에서 처리한 뒤, 데이터를 내보내는 modbus_communication 함수 정의.


추가해야하는 코드
1. 구조체 수정
2. 프로파일 코드로 테스트 진행(GUI 입력)
3. sys_mode_decision 함수 구체화
4. 데이터 저장(csv)

----------------------------------------------------------------------------------------------------------------------------------
