/*
 * barrier -- mouse and keyboard sharing utility
 * Copyright (C) 2012-2016 Symless Ltd.
 * Copyright (C) 2003 Chris Schoeneman
 *
 * This package is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * found in the file LICENSE that should have accompanied this file.
 *
 * This package is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "barrier/ServerTaskBarReceiver.h"
#include "common/win32/winapi.h"

class BufferedLogOutputter;
class IEventQueue;

//! Implementation of ServerTaskBarReceiver for Microsoft Windows
class MSWindowsServerTaskBarReceiver : public ServerTaskBarReceiver {
public:
    MSWindowsServerTaskBarReceiver(HINSTANCE, const BufferedLogOutputter*, IEventQueue* events);
    virtual ~MSWindowsServerTaskBarReceiver();

    // IArchTaskBarReceiver overrides
    virtual void        showStatus();
    virtual void        runMenu(int x, int y);
    virtual void        primaryAction();
    virtual const Icon    getIcon() const;
    void cleanup();

protected:
    void                copyLog() const;

    // ServerTaskBarReceiver overrides
    virtual void        onStatusChanged();

private:
    HICON                loadIcon(UINT);
    void                deleteIcon(HICON);
    void                createWindow();
    void                destroyWindow();

    BOOL                dlgProc(HWND hwnd,
                            UINT msg, WPARAM wParam, LPARAM lParam);
    static BOOL CALLBACK
                        staticDlgProc(HWND hwnd,
                            UINT msg, WPARAM wParam, LPARAM lParam);

private:
    HINSTANCE            m_appInstance;
    HWND                m_window;
    HMENU                m_menu;
    HICON                m_icon[kMaxState];
    const BufferedLogOutputter*    m_logBuffer;
    IEventQueue*        m_events;

    static const UINT    s_stateToIconID[];
};
