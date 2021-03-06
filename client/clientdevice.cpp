/*
  clientdevice.cpp

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Volker Krause <volker.krause@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "clientdevice.h"
#include "tcpclientdevice.h"
#include "localclientdevice.h"

#include <QDebug>

using namespace GammaRay;

ClientDevice::ClientDevice(QObject* parent): QObject(parent)
{
}

ClientDevice::~ClientDevice()
{
}

ClientDevice* ClientDevice::create(const QUrl& url, QObject *parent)
{
    ClientDevice* device = 0;
    if (url.scheme() == "tcp")
        device = new TcpClientDevice(parent);
    else if (url.scheme() == "local")
        device = new LocalClientDevice(parent);

    if (!device) {
        qWarning() << "Unsupported transport protocol:" << url.toString();
        return 0;
    }

    device->m_serverAddress = url;
    return device;
}
