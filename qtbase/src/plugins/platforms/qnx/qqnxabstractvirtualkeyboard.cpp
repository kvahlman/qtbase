/***************************************************************************
**
** Copyright (C) 2011 - 2012 Research In Motion
** Contact: http://www.qt-project.org/legal
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qqnxabstractvirtualkeyboard.h"

QT_BEGIN_NAMESPACE

QQnxAbstractVirtualKeyboard::QQnxAbstractVirtualKeyboard(QObject *parent)
    : QObject(parent)
    , m_height(0)
    , m_visible(false)
    , m_locale(QLocale::system())
    , m_keyboardMode(Default)
{
}

void QQnxAbstractVirtualKeyboard::setKeyboardMode(KeyboardMode mode)
{
    if (mode == m_keyboardMode)
        return;

    m_keyboardMode = mode;

    applyKeyboardMode(mode);
}

void QQnxAbstractVirtualKeyboard::setInputHintsFromObject(QObject *focusObject)
{
    if (focusObject) {
        const Qt::InputMethodHints hints = static_cast<Qt::InputMethodHints>(
                    focusObject->property("inputMethodHints").toInt());
        if (hints & Qt::ImhEmailCharactersOnly) {
            setKeyboardMode(QQnxAbstractVirtualKeyboard::Email);
        } else if (hints & Qt::ImhDialableCharactersOnly) {
            setKeyboardMode(QQnxAbstractVirtualKeyboard::Phone);
        } else if (hints & Qt::ImhUrlCharactersOnly) {
            setKeyboardMode(QQnxAbstractVirtualKeyboard::Web);
        } else if (hints & Qt::ImhFormattedNumbersOnly || hints & Qt::ImhDigitsOnly ||
                   hints & Qt::ImhDate || hints & Qt::ImhTime) {
            setKeyboardMode(QQnxAbstractVirtualKeyboard::NumPunc);
        } else {
            setKeyboardMode(QQnxAbstractVirtualKeyboard::Default);
        }
    } else {
        setKeyboardMode(QQnxAbstractVirtualKeyboard::Default);
    }
}

void QQnxAbstractVirtualKeyboard::setHeight(int height)
{
    if (height == m_height)
        return;

    const int effectiveHeight = this->height();

    m_height = height;

    if (effectiveHeight != this->height())
        emit heightChanged(this->height());
}

void QQnxAbstractVirtualKeyboard::setVisible(bool visible)
{
    if (visible == m_visible)
        return;

    const int effectiveHeight = height();

    m_visible = visible;

    emit visibilityChanged(visible);

    if (effectiveHeight != height())
        emit heightChanged(height());
}

void QQnxAbstractVirtualKeyboard::setLocale(const QLocale &locale)
{
    if (locale == m_locale)
        return;

    m_locale = locale;

    emit localeChanged(locale);
}

QT_END_NAMESPACE
