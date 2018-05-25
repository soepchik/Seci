// Copyright (c) 2017-2018 SECI developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SECI_QT_SECIADDRESSVALIDATOR_H
#define SECI_QT_SECIADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class seciAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit seciAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** seci address widget validator, checks for a valid seci address.
 */
class seciAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit seciAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // SECI_QT_SECIADDRESSVALIDATOR_H
