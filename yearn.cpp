/*-------------------------------------------------------------------------
 * This source code is confidential proprietary information which is
 * copyright (c) 2016, 2021 TrueBlocks, LLC (http://trueblocks.io)
 * All Rights Reserved
 *------------------------------------------------------------------------*/
#include "acctlib.h"

//-----------------------------------------------------------------------
class CMattTraverser : public CTraverser {
public:
    CMattTraverser(void) : CTraverser(cout, "matt") {
    }
};

//------------------------------------------------------------------------------------------------
map<address_t, string> colorMap = {
    {"0x5f18c75abdae578b483e5f43f12a39cf75b973a9", bRed},
    {"0x19d3364a399d251e894ac732651be8b0e4e85001", bGreen},
    {"0xa258c4606ca8206d8aa700ce2143d7db854d168c", bYellow},
    {"0xa696a63cc78dffa1a63e9e50587c197387ff6c7e", bBlue},
};

//------------------------------------------------------------------------------------------------
bool init(CTraverser* trav, void* data) {
    cout << "address,";
    cout << "block,";
    cout << "txid,";
    cout << "date,";
    cout << "pricePerShare";
    cout << endl;
    return true;
}

//------------------------------------------------------------------------------------------------
bool visit(CTraverser* trav, void* data) {
    CEthCall theCall;
    theCall.address = trav->curMonitor->address;
    theCall.encoding = "0x99530b06";
    theCall.bytes = "";
    theCall.blockNumber = trav->trans.blockNumber;
    theCall.abi_spec.loadAbiFromEtherscan(trav->curMonitor->address);
    doEthCall(theCall);

    ostringstream os;
    os << "\"" << colorMap[trav->curMonitor->address] << trav->curMonitor->address << cOff << "\",";
    os << "\"" << trav->trans.blockNumber << "\",";
    os << "\"" << trav->trans.transactionIndex << "\",";
    os << "\"" << trav->trans.Format("[{DATE}]") << "\",";
    os << "\"" << str_2_Wei(theCall.getResults()) << "\"";
    os << endl;
    appendToAsciiFile("./" + trav->curMonitor->address + ".txt", os.str());
    cout << os.str();

    return true;
}

//-----------------------------------------------------------------------
extern "C" CTraverser* makeTraverser(void) {
    freshenTimestamps(getBlockProgress().client);
    loadTimestamps(&expContext().tsMemMap, expContext().tsCnt);
    CMattTraverser* trav = new CMattTraverser;
    trav->filterFunc = trav->postFunc = trav->dataFunc = noopFunc;
    trav->preFunc = init;
    trav->displayFunc = visit;
    return trav;
}
