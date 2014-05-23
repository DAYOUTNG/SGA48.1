#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	const int count = 10;
	const int radius = 20;
	static POINT center[count];
	static POINT pt = {0,0};
	static POINT pt2 = {0,0};
	static bool bDrag = false;

	if (uMsg == WM_CREATE)
	{
		RECT rc;
		::GetClientRect(hWnd, &rc);
		int cx = rc.right - rc.left;
		int cy = rc.bottom - rc.top;

		for (int i = 0; i < count; i++)
		{
			center[i].x = rand()%cx;
			center[i].y = rand()%cy;
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
		RECT rc;
		::GetClientRect(hWnd, &rc);

		std::wostringstream oss;
		oss << _T("pt : (") << pt.x << _T(", ") << pt.y << _T(")\r\n");
		oss << _T("pt2 : (") << pt2.x << _T(", ") << pt2.y << _T(")\r\n");
		oss << _T("DragState : ") << bDrag;

		::DrawText(hdc, oss.str().c_str(), -1,
			&rc, DT_TOP | DT_LEFT);

		if (bDrag)
		{
			::Rectangle(hdc, pt.x, pt.y, pt2.x, pt2.y);
		}

		for (int i = 0; i < count; i++)
		{
			::Ellipse(hdc, center[i].x - radius, center[i].y - radius,
				center[i].x + radius, center[i].y + radius);
		}

		RECT rcBox = {200,200,400,400};

		COLORREF color = RGB(255,255,255);

		if (::PtInRect(&rcBox, pt))
		{
			color = RGB(0,255,0);
		}

		HBRUSH hBrush = ::CreateSolidBrush(color);
		HBRUSH hOldBrush = (HBRUSH)::SelectObject(hdc, hBrush);

		::Rectangle(hdc, rcBox.left, rcBox.top,
			rcBox.right, rcBox.bottom);

		::SelectObject(hdc, hOldBrush);
		::DeleteObject(hBrush);


		::EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_MOUSEMOVE)
	{
		//pt.x = GET_X_LPARAM(lParam);
		//pt.y = GET_Y_LPARAM(lParam);

		if (bDrag)
		{
			pt2.x = GET_X_LPARAM(lParam);
			pt2.y = GET_Y_LPARAM(lParam);
		}

		RECT rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}
	else if (uMsg == WM_LBUTTONDOWN)
	{
		bDrag = true;

		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);

		pt2.x = GET_X_LPARAM(lParam);
		pt2.y = GET_Y_LPARAM(lParam);

		RECT rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}
	else if (uMsg == WM_LBUTTONUP)
	{
		bDrag = false;
		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}
