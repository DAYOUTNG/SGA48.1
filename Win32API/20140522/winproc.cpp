#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	const int count = 100;
	static POINT pt[count];

	if (uMsg == WM_CREATE)
	{
		RECT rc;
		::GetClientRect(hWnd, &rc);
		const LONG margin = 20;
		rc.left += margin;
		rc.top += margin;
		rc.right -= margin;
		rc.bottom -= margin;

		int cx = rc.right - rc.left;
		int cy = rc.bottom - rc.top;

		for (int i = 0; i < count; i++)
		{
			pt[i].x = rand()%cx + rc.left;
			pt[i].y = rand()%cy + rc.top;
		}

		return 0;
	}
	else if (uMsg == WM_DESTROY)
	{
		::PostQuitMessage(0);
		return 0;
	}
	else if (uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC hdc = ::BeginPaint(hWnd, &ps);

		// TODO
		for (int i = 0; i < count-1; i++)
		{
			::MoveToEx(hdc, pt[i].x, pt[i].y, NULL);
			::LineTo(hdc, pt[i+1].x, pt[i+1].y);
		}

		::EndPaint(hWnd, &ps);

		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}
