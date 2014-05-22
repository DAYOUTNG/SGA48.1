#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	if (uMsg == WM_CREATE)
	{
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
		RECT rc;
		::GetClientRect(hWnd, &rc);
		::InflateRect(&rc, -50, -50);

		HPEN hPen = ::CreatePen(PS_SOLID, 5, RGB(255,0,0));
		HPEN hOldPen = (HPEN)::SelectObject(hdc, hPen);

		HBRUSH hBrush = ::CreateSolidBrush(RGB(0,0,255));
		HBRUSH hOldBrush = (HBRUSH)::SelectObject(hdc, hBrush);

		::Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

		::SelectObject(hdc, hOldBrush);
		::DeleteObject(hBrush);

		hBrush = ::CreateSolidBrush(RGB(255,255,0));
		hOldBrush = (HBRUSH)::SelectObject(hdc, hBrush);

		::Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);

		::SelectObject(hdc, hOldBrush);
		::DeleteObject(hBrush);

		::SelectObject(hdc, hOldPen);
		::DeleteObject(hPen);

		::EndPaint(hWnd, &ps);
		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}
