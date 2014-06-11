#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	static POINT pt = {0,0};
	static POINT pt2 = {0,0};
	static bool bDrag = false;

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

		std::wostringstream oss;
		oss << _T("pt : (") << pt.x << _T(", ") << pt.y << _T(")\r\n");
		oss << _T("pt2 : (") << pt2.x << _T(", ") << pt2.y << _T(")\r\n");
		oss << _T("DragState : ") << bDrag;

		::DrawText(hdc, oss.str().c_str(), -1,
			&rc, DT_TOP | DT_LEFT);

		::EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_MOUSEMOVE)
	{
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);

		pt2.x = LOWORD(lParam);
		pt2.y = HIWORD(lParam);

		RECT rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);

		return 0;
	}
	else if (uMsg == WM_LBUTTONDOWN)
	{
		bDrag = true;
		return 0;
	}
	else if (uMsg == WM_LBUTTONUP)
	{
		bDrag = false;
		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}
