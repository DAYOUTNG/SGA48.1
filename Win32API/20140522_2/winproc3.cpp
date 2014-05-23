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
		
		RECT rc;
		::GetClientRect(hWnd, &rc);

		RECT rcBox = {0,0,20,20};


		for (LONG y = 0; y < rc.bottom; y += 20)
		{
			BYTE r = rand()%256;
			BYTE g = rand()%256;
			BYTE b = rand()%256;
			COLORREF color = RGB(r,g,b);

			for (LONG x = 0; x < rc.right; x += 20)
			{
				r = max(0, GetRValue(color)-10);
				g = max(0, g-10);
				b = max(0, b-10);

				color = RGB(r,g,b);

				HBRUSH hBrush = ::CreateSolidBrush(color);
				HBRUSH hOldBrush = (HBRUSH)::SelectObject(hdc, hBrush);

				HPEN hPen = ::CreatePen(PS_SOLID, 1, color);
				HPEN hOldPen = (HPEN)::SelectObject(hdc, hPen);

				rcBox.top = y;
				rcBox.bottom = rcBox.top + 20;

				rcBox.left = x;
				rcBox.right = rcBox.left + 20;

				::Rectangle(hdc, rcBox.left, rcBox.top,
					rcBox.right, rcBox.bottom);

				::SelectObject(hdc, hOldPen);
				::DeleteObject(hPen);

				::SelectObject(hdc, hOldBrush);
				::DeleteObject(hBrush);
			}
		}

		::EndPaint(hWnd, &ps);

		return 0;
	}

	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}