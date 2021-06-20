#pragma once
/*-------------------------------------------------------------------------------------------
 * qblocks - fast, easily-accessible, fully-decentralized data from blockchains
 * copyright (c) 2016, 2021 TrueBlocks, LLC (http://trueblocks.io)
 *
 * This program is free software: you may redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version. This program is
 * distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details. You should have received a copy of the GNU General
 * Public License along with this program. If not, see http://www.gnu.org/licenses/.
 *-------------------------------------------------------------------------------------------*/
/*
 * Parts of this file were generated with makeClass --run. Edit only those parts of
 * the code inside of 'EXISTING_CODE' tags.
 */
#include "etherlib.h"

namespace qblocks {

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
class CPricePerShare : public CTransaction {
  public:
    address_t address;
    wei_t pricePerShare;

  public:
    CPricePerShare(void);
    CPricePerShare(const CPricePerShare& pr);
    virtual ~CPricePerShare(void);
    CPricePerShare& operator=(const CPricePerShare& pr);

    DECLARE_NODE(CPricePerShare);

    // EXISTING_CODE
    CPricePerShare(const CTransaction& trans) {
        (*(CTransaction*)this) = trans;
    }
    // EXISTING_CODE
    bool operator==(const CPricePerShare& it) const;
    bool operator!=(const CPricePerShare& it) const {
        return !operator==(it);
    }
    friend bool operator<(const CPricePerShare& v1, const CPricePerShare& v2);
    friend ostream& operator<<(ostream& os, const CPricePerShare& it);

  protected:
    void clear(void);
    void initialize(void);
    void duplicate(const CPricePerShare& pr);
    bool readBackLevel(CArchive& archive) override;

    // EXISTING_CODE
    // EXISTING_CODE
};

//--------------------------------------------------------------------------
inline CPricePerShare::CPricePerShare(void) {
    initialize();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline CPricePerShare::CPricePerShare(const CPricePerShare& pr) {
    // EXISTING_CODE
    // EXISTING_CODE
    duplicate(pr);
}

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
inline CPricePerShare::~CPricePerShare(void) {
    clear();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CPricePerShare::clear(void) {
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CPricePerShare::initialize(void) {
    CTransaction::initialize();

    address = "";
    pricePerShare = 0;

    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CPricePerShare::duplicate(const CPricePerShare& pr) {
    clear();
    CTransaction::duplicate(pr);

    address = pr.address;
    pricePerShare = pr.pricePerShare;

    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline CPricePerShare& CPricePerShare::operator=(const CPricePerShare& pr) {
    duplicate(pr);
    // EXISTING_CODE
    // EXISTING_CODE
    return *this;
}

//-------------------------------------------------------------------------
inline bool CPricePerShare::operator==(const CPricePerShare& it) const {
    // EXISTING_CODE
    // EXISTING_CODE
    // No default equal operator in class definition, assume none are equal (so find fails)
    return false;
}

//-------------------------------------------------------------------------
inline bool operator<(const CPricePerShare& v1, const CPricePerShare& v2) {
    // EXISTING_CODE
    // EXISTING_CODE
    // No default sort defined in class definition, assume already sorted, preserve ordering
    return true;
}

//---------------------------------------------------------------------------
typedef vector<CPricePerShare> CPricePerShareArray;
extern CArchive& operator>>(CArchive& archive, CPricePerShareArray& array);
extern CArchive& operator<<(CArchive& archive, const CPricePerShareArray& array);

//---------------------------------------------------------------------------
extern const char* STR_DISPLAY_PRICEPERSHARE;

//---------------------------------------------------------------------------
// EXISTING_CODE
// EXISTING_CODE
}  // namespace qblocks
