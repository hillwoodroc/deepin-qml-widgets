/**
 * Copyright (C) 2015 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

import QtQuick 2.0
import Deepin.Widgets 1.0

DWindow {
    color :Qt.rgba(1.0, 0.5, 0, 0.2)
    Text {
	text : "dwindow"
    }
    width:300
    height:300
    Component.onCompleted: print(getWinId())
}
