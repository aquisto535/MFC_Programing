#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) // 1. 초기화(처리기 등록) + 윈도우(객체) 생성
{
	WNDCLASS wndclass; // 윈도우의 속성 종류. 
	HWND hwnd;
	MSG msg;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc; //콜백이 될 함수 이름(lpfnWndProc = 함수 포인터)
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = TEXT("HelloClass");
	if (!RegisterClass(&wndclass)) return 1;

	//윈도우 클래스(구조체) 생성 후 운영체제에 등록. 전달인자로 클래스 이름, 윈도우 이름, 윈도우 스타일, 인스턴스 핸들 등을 사용하고 이 값들을 제외한 다른 값들은 모두 기본값을 사용한다.
	hwnd = CreateWindow(TEXT("HelloClass"), TEXT("HelloSDK"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, nCmdShow);

	//2. 기본 메세지 루프 => 메세지 큐에서 함수 호출 => 콜백.메세지 큐에서 메시지를 하나씩 꺼내 처리한다.
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);//콜백 => 처리
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message,
	WPARAM wParam, LPARAM lParam) //UINT = unsigned int(스위치문을 쓰는 이유)
{
	HDC hdc;
	PAINTSTRUCT ps;
	const TCHAR* str = TEXT("Hello, SDK");

	//발생할 메세지의 종류와 처리
	switch (message) {
	case WM_CREATE:
		return 0;
	case WM_LBUTTONDOWN://마우스 왼쪽 버튼을 누를 때
		MessageBox(hwnd, TEXT("마우스 누름!"), TEXT("마우스"), MB_OK);
		return 0;
	case WM_PAINT: //렌더링할 때 사용. 클라이언트의 부분을 다시 그릴 필요가 있을 때 사용하고 BeginPaint와 EndPaint를 각각 시작부분과 끝부분에서 호출하는 식으로 사용한다.
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 100, 100, str, lstrlen(str));
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0); //메세지 루프를 끊는 기능
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}
