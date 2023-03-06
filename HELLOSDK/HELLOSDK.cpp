#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) // 1. �ʱ�ȭ(ó���� ���) + ������(��ü) ����
{
	WNDCLASS wndclass; // �������� �Ӽ� ����. 
	HWND hwnd;
	MSG msg;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc; //�ݹ��� �� �Լ� �̸�(lpfnWndProc = �Լ� ������)
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = TEXT("HelloClass");
	if (!RegisterClass(&wndclass)) return 1;

	//������ Ŭ����(����ü) ���� �� �ü���� ���. �������ڷ� Ŭ���� �̸�, ������ �̸�, ������ ��Ÿ��, �ν��Ͻ� �ڵ� ���� ����ϰ� �� ������ ������ �ٸ� ������ ��� �⺻���� ����Ѵ�.
	hwnd = CreateWindow(TEXT("HelloClass"), TEXT("HelloSDK"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, nCmdShow);

	//2. �⺻ �޼��� ���� => �޼��� ť���� �Լ� ȣ�� => �ݹ�.�޼��� ť���� �޽����� �ϳ��� ���� ó���Ѵ�.
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);//�ݹ� => ó��
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message,
	WPARAM wParam, LPARAM lParam) //UINT = unsigned int(����ġ���� ���� ����)
{
	HDC hdc;
	PAINTSTRUCT ps;
	const TCHAR* str = TEXT("Hello, SDK");

	//�߻��� �޼����� ������ ó��
	switch (message) {
	case WM_CREATE:
		return 0;
	case WM_LBUTTONDOWN://���콺 ���� ��ư�� ���� ��
		MessageBox(hwnd, TEXT("���콺 ����!"), TEXT("���콺"), MB_OK);
		return 0;
	case WM_PAINT: //�������� �� ���. Ŭ���̾�Ʈ�� �κ��� �ٽ� �׸� �ʿ䰡 ���� �� ����ϰ� BeginPaint�� EndPaint�� ���� ���ۺκа� ���κп��� ȣ���ϴ� ������ ����Ѵ�.
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 100, 100, str, lstrlen(str));
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0); //�޼��� ������ ���� ���
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}
